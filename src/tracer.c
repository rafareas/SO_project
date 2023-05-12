#include <sys/types.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <sys/time.h>
#include <time.h>
#include <string.h>

#define MAX_BUFFER 50

int exec_command(char * cmd){

    char* args[10];
    
    char* string;
    int i = 0;

    char * command = strdup(cmd);

    while((string=strsep(&command," "))!=NULL){
        args[i] = string;
        i++;
    }

    args[i] = NULL;

    return execvp(args[0],args);

}



int executaU(char* comando){        
    int return_exec, status, bytes_read;
    int k = 0;
    int i=0;
    int fd1[2];
    pipe(fd1);

    int start_t, end_t;
    double total_t;

    struct timeval start,end;
    
    char *exec_args[20];
    char *nova_string=strdup(comando);
    char *string;

    int fd = open("../bin/fifo",O_WRONLY);

    if(fd < 0){
        perror("Error to open fifo\n");
    }

    while((string=strsep(&nova_string," "))!=NULL){
        exec_args[i]=string;
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
        char buffer[MAX_BUFFER];
        printf("Running pid %d\n",filho);

        gettimeofday(&start,NULL);

        int t2 = snprintf(buffer,MAX_BUFFER,"%d %ld %ld %s",filho,start.tv_sec,start.tv_usec,comando);
        write(fd1[1],buffer,t2);

        close(fd1[1]);
        return_exec=execvp(exec_args[0],exec_args);
        _exit(return_exec);

        }

    else{

        close(fd1[1]);

        char buffer[MAX_BUFFER];
        char *ex = "executaU";
        pid_t wait_pid = wait(&status);
        
        gettimeofday(&end,NULL);
        
        char * string2;
        int res=0;

        while((bytes_read = read(fd1[0],&buffer,sizeof(buffer)))>0){
                res+=bytes_read;
                string2 = malloc(sizeof(buffer));
                memcpy(string2,buffer,bytes_read);
                memset(buffer,0,sizeof(buffer));
        }

        close(fd1[0]);


        char* final;
        char *exec_args2[4];
        i=0;

        while((final=strsep(&string2," "))!=NULL && i<4){
            exec_args2[i]=final;
            i++;
        }

        
        long tempoi_sec = atol(exec_args2[1]);
    
        long result =((end.tv_usec - atol(exec_args2[2]))/1000) + ((end.tv_sec - atol(exec_args2[1]))*1000);

        int t2 = snprintf(buffer,MAX_BUFFER,"%s %s %ld %d",ex,exec_args2[3],result,atoi(exec_args2[0]));
        write(fd,buffer,t2);
        printf("Ended in %ld\n",result);


        if(WIFEXITED(status)){
            printf("Pai o filho %d terminou com exit code %d\n",wait_pid,WEXITSTATUS(status));
        }

        close(fd);
    }
    return 0;
}

int executaP(char* comando){        

    char* string;
    char* nova_string = strdup(comando);
    char *commands[20];

    int i=0;
    
    struct timeval end,start;

    while((string=strsep(&nova_string,"|"))!=NULL){
        commands[i]=string;
        i++;
    }

    int fd = open("../bin/fifo",O_WRONLY);

    if(fd < 0){
        perror("Error to open fifo\n");
    }


    int ncommads = i;

    int pipes[ncommads-1][2];


    gettimeofday(&start,NULL);

    pid_t pid = getpid();

    for(int i=0 ;i<ncommads; i++){
        
        if(i==0){
            pipe(pipes[i]);
            int fres=fork();
            if(fres==0){
                close(fd);
                close(pipes[i][0]);
                dup2(pipes[i][1],1);
                close(pipes[i][1]);
                exec_command(commands[i]);
            }
            else{
                close(pipes[i][1]);

            }
        }
        if(i==ncommads-1){
            int fres=fork();
            if(fres==0){
                close(fd);
                dup2(pipes[i-1][0],0);
                close(pipes[i-1][0]);
                exec_command(commands[i]);
            }
            else{
                close(pipes[i-1][0]);
            }
        }
        else{
            pipe(pipes[i]);
            int fres=fork();
            if(fres==0){
                close(fd);
                dup2(pipes[i-1][0],0);
                close(pipes[i-1][0]);

                dup2(pipes[i][1],1);
                close(pipes[i][1]);

                close(pipes[i][0]);
                exec_command(commands[i]);
            }
            else{
                close(pipes[i][1]);
                close(pipes[i-1][0]);
            }

        }
    }

    for(int i=0;i<ncommads;i++){
        wait(NULL);
    }

    gettimeofday(&end,NULL);
    long result =((end.tv_usec - start.tv_usec)/1000) + ((end.tv_sec - start.tv_sec)*1000);
    printf("Ended in %ld\n",result);

    char buffer[50];
    char *ex = "executaP";
    int t = snprintf(buffer,50,"%s %s %ld %d",ex,comando,result,pid);
    write(fd,buffer,t);

    close(fd);

    printf("Pipeline terminada\n");
    return 0;
}

int status(){
    char buffer[20];
    char *ex = "status";

    int fd = open("../bin/fifo",O_WRONLY);

    if(fd < 0){
        perror("Error to open fifo\n");
    }

    int t = snprintf(buffer,20,"%s",ex);
    write(fd,buffer,t);

    close(fd);


    int fd1 = open("../bin/fifo1",O_RDONLY,0660);

    if(fd1 < 0){
        perror("Error to open fifo\n");
   }

   int bytes_read;
   char * string2;
   
   char buffer2[512];
   char *string_final;
   string_final = malloc(sizeof(buffer2));
   char* exec_args[50];
   int i =0;


    while((bytes_read = read(fd1,&buffer2,sizeof(buffer2)))>0){
                string2 = malloc(sizeof(buffer2));
                memcpy(string2,buffer2,bytes_read);
                strcat(string_final,string2);
                memset(buffer2,0,sizeof(buffer2));
                i++;
        }


    char* nova_string;
    char* exec_args2[50];
    int k=0;

    while((nova_string=strsep(&string_final,"_"))!=NULL){
        exec_args2[i]=nova_string;
        printf("%s\n",exec_args2[i]);
        k++;
    }


    close(fd1);
    return 0;
}

void stats_time(char *command){
    long int tot = 0;
    int i = 0;
    char *exec_args[20];
    char *nova_string=strdup(command);
    char *string;
    char *string_txt;


    while((string=strsep(&nova_string," "))!=NULL){
        exec_args[i]=string;
        i++;
    }
  
   
    for(int j = 0;j < i;j++){
        char buffer[10];
        ssize_t bytes_read;

        char *file_name = malloc(strlen(exec_args[j]) + 5);

        strcpy(file_name, exec_args[j]);
        strcat(file_name, ".txt");


        int fd = open(file_name, O_RDONLY);
            if (fd == -1) {
                perror("Erro ao abrir o arquivo");
            }

        char *new_string;
        long int aux;

        while ((bytes_read = read(fd, buffer,sizeof(buffer))) > 0) {
            // Faça algo com o conteúdo lido, por exemplo, imprimir na tela
            new_string = malloc(sizeof(buffer));
            memcpy(new_string,buffer,bytes_read);
            memset(buffer,0,sizeof(buffer));
            aux = atol(new_string);
            
            tot += aux;
        }  
    }
    printf("%ld ms\n",tot);
}


int main(int argc, char **argv){
    int ret=0;
    int create_fifo = mkfifo("../bin/fifo",0660);

    if(strcmp(argv[1],"execute")==0){
        if(strcmp(argv[2],"-u")==0){
            
            char *comando = strdup(argv[3]);

            ret = executaU(comando);
        }

        else if(strcmp(argv[2],"-p")==0){
            
            char *comando = strdup(argv[3]);
            ret = executaP(comando);
        }
    }
    else if (strcmp(argv[1],"status")==0){
        int create_fifo1 = mkfifo("../bin/fifo1",0660);
        status();        
    }
    else if (strcmp(argv[1],"stats-time") == 0){
        stats_time(argv[2]);
    }


    return 0;
}