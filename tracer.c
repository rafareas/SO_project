#include <sys/types.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <time.h>
#include <string.h>

int executaU(char* comando){        
    int return_exec, status, bytes_read;
    int k = 0;
    int i=0;
    int fd1[2];
    pipe(fd1);

    int start_t, end_t;
    double total_t;
    
    char *exec_args[20];
    char *nova_string=strdup(comando);
    char *string;

    int fd = open("fifo",O_WRONLY);

    if(fd < 0){
        perror("Error to open fifo\n");
    }

    while((string=strsep(&nova_string," "))!=NULL){
        //printf("%s\n\n",string);
        exec_args[i]=string;
        //printf("%s\n",exec_args[i]);
        i++;
    }

    exec_args[i]=NULL;

    pid_t res = fork();
    
    if(res<0){
        perror("Erro no fork");
    }
    if(res==0){
        close(fd1[0]);

        pid_t filho = getpid();
        char buffer[30];
        printf("O pid é %d\n",filho);

        start_t = clock();

        int t2 = snprintf(buffer,30,"%d %d %s",filho,start_t,exec_args[0]);
        write(1,buffer,t2);
        write(fd1[1],buffer,t2);
        printf("\n");

        close(fd1[1]);
        return_exec=execvp(exec_args[0],exec_args);
        _exit(return_exec);

        }

    else{

        close(fd1[1]);

        char buffer[20];
        char *ex = "executaU";
        pid_t wait_pid = wait(&status);
        char * string2;

        while((bytes_read = read(fd1[0],&buffer,sizeof(buffer)))>0){
                string2 = malloc(sizeof(bytes_read));
                memcpy(string2,buffer,bytes_read);
                //printf("%s\n",string2);
                memset(buffer,0,sizeof(buffer));
        }

        close(fd1[0]);

        char* final;
        char* nova_string2 = strdup(string2);
        char *exec_args2[2];
        i=0;

        while((final=strsep(&nova_string2," "))!=NULL){
        exec_args2[i]=final;
        //printf("%s\n",exec_args2[i]);
        i++;
        }

        int start = atoi(exec_args2[1]);
        //printf("start -> %d\n",start);
        //char buffer[20];
        end_t = clock();
        //printf("%d\n",end_t);

        double total_t = (double) (end_t-start_t) / CLOCKS_PER_SEC;
        //printf("%f\n",total_t);

        char buffer2[50];

        int t2 = snprintf(buffer,50,"%s %s %d %d %f",ex,exec_args2[2],start,end_t,total_t);
        write(1,buffer,t2);
        write(fd,buffer,t2);
        printf("\n");

        if(WIFEXITED(status)){
            printf("Pai o filho %d terminou com exit code %d\n",wait_pid,WEXITSTATUS(status));
        }

        close(fd);
    }    
}

//funciona com apenas dois programas
int executaP(char* comando){        
    int return_exec;
    int status;
    int k=0;
    int i=0;
    
    int array_pid[20];
    char *exec_args[20];
    char *nova_string=strdup(comando);
    char *string;

    int fds[2];
    int return_pipe = pipe(fds);

    while((string=strsep(&nova_string,"|"))!=NULL){
        //printf("%s\n\n",string);
        exec_args[i]=string;
        //printf("%s\n",exec_args[i]);
        i++;   
    }

    for(k=0;k<i;k++){
        pid_t res = fork();
        int j=0;
        char *string2;
        char *string3;
        char *exec_args2[20];

        
        if(res==0){
        string2=exec_args[k];
        //printf("%s\n",string2);
        string3 = strtok(string2," ");
        while(string3!=NULL){
            exec_args2[j]=string3;
            //printf("%s\n",exec_args2[j]);
            string3=strtok(NULL," ");
            j++;
        }
        exec_args2[j]=NULL;

        if(k==0){
            dup2(fds[1],STDOUT_FILENO);
            close(fds[0]);
            close(fds[1]);
            return_exec=execvp(exec_args2[0],exec_args2);
            _exit(return_exec);
        }
        else{
            dup2(fds[0],STDIN_FILENO);
            close(fds[0]);
            close(fds[1]);
            return_exec=execvp(exec_args2[0],exec_args2);
            _exit(return_exec);
        }
        }
        else{
            array_pid[k] = res;
        }
    }

    for (int l=0;l<i;l++){
            pid_t wait_pid = waitpid(array_pid[l],&status,0);
            if(WIFEXITED(status)){
                printf("Pai o filho %d terminou com exit code %d\n",wait_pid,WEXITSTATUS(status));
            }
            close(fds[0]);
            close(fds[1]);
        }    
}

int status(){
    char buffer[20];
    char *ex = "status";

    int fd = open("fifo",O_WRONLY);

    if(fd < 0){
        perror("Error to open fifo\n");
    }

    int t = snprintf(buffer,20,"%s",ex);
    write(fd,buffer,t);

    close(fd);


}


int main(int argc, char **argv){
    int ret=0;

    //Inicializacao FIFO
    int create_fifo = mkfifo("fifo",0660);

    //if(create_fifo < 0){
    //    perror("Error in the creation of fifo.\n");
    //}

    //Open do file descriptor
    //int fd = open("fifo",O_WRONLY);

    //if(fd < 0){
    //    perror("Error to open fifo\n");
    //}
    
    clock_t start_t, end_t;
    double total_t;
    if(strcmp(argv[1],"execute")==0){
        if(strcmp(argv[2],"-u")==0){
            
            char *comando = strdup(argv[3]);
            //printf("%s\n\n",comando);
            
            //close(fd);

            start_t = clock();
            ret = executaU(comando);
            end_t = clock();
            total_t = (double) (end_t-start_t) / CLOCKS_PER_SEC;
            printf("%f\n",total_t);
        }
        else if(strcmp(argv[2],"-p")==0){
            
            char *comando = strdup(argv[3]);
            //printf("%s\n\n",comando);
            
            //start_t = clock();
            ret = executaP(comando);
            //end_t = clock();
            //total_t = (double) (end_t-start_t) / CLOCKS_PER_SEC;
            //printf("%f\n",total_t);
        }
    }
    else if (strcmp(argv[1],"status")==0){
        status();        
    }

    //close(fd);
    //unlink("fifo");
    printf("Terminei\n");

    return 0;
}