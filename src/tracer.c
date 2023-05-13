#include "../include/tracer.h"

int exec_command(char * cmd){

    char* args[20];
    
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
        perror("Erro ao criar o fork\n");
    }
    if(res==0){
        close(fd1[0]);

        pid_t filho = getpid();
        char buffer[50];
        printf("Running pid %d\n",filho);

        gettimeofday(&start,NULL);

        int t2 = snprintf(buffer,50,"%d %ld %ld %s",filho,start.tv_sec,start.tv_usec,comando);
        write(fd1[1],buffer,t2);

        close(fd1[1]);
        return_exec=execvp(exec_args[0],exec_args);
        _exit(return_exec);

        }

    else{

        close(fd1[1]);

        char buffer[50];
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
    
        long result =((end.tv_usec - atol(exec_args2[2]))/1000) + ((end.tv_sec - atol(exec_args2[1]))*1000);

        int t2 = snprintf(buffer,50,"%s %s %ld %d",ex,exec_args2[3],result,atoi(exec_args2[0]));
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
    printf("Running pid %d\n",pid);

    for(int i=0 ;i<ncommads; i++){
        
        if(i==0){
            pipe(pipes[i]);
            int fres=fork();
            if(fres<0){
                perror("Erro ao criar o fork\n");
            }
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
            if(fres<0){
                perror("Erro ao criar o fork\n");
            }
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
            if(fres<0){
                perror("Erro ao criar o fork\n");
            }
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
    int t = snprintf(buffer,50,"%s %ld %d _%s_",ex,result,pid,comando);
    write(fd,buffer,t);

    close(fd);
    return 0;
}

int status(){
    char * string;
    char *ex = "status";
    char *string_final;
    char* nova_string;
    char* exec_args[50];
    char buffer[20];
    char buffer2[512];
    int bytes_read;
    int i =0;
    int k=0;

    int fd = open("../bin/fifo",O_WRONLY);

    if(fd < 0){
        perror("Erro ao abrir o fifo\n");
    }

    int t = snprintf(buffer,20,"%s",ex);
    write(fd,buffer,t);

    close(fd);

    int fd1 = open("../bin/fifo1",O_RDONLY,0660);

    if(fd1 < 0){
        perror("Erro ao abrir o fifo\n");
    }

   string_final = malloc(sizeof(buffer2));   

    while((bytes_read = read(fd1,&buffer2,sizeof(buffer2)))>0){
                string = malloc(sizeof(buffer2));
                memcpy(string,buffer2,bytes_read);
                strcat(string_final,string);
                memset(buffer2,0,sizeof(buffer2));
                i++;
    }

    while((nova_string=strsep(&string_final,"_"))!=NULL){
        exec_args[k]=nova_string;
        printf("%s\n",exec_args[k]);
        k++;
    }

    close(fd1);
    return 0;
}

void stats_time(char *command){
    char *new_string;
    char *comando = strdup(command);
    char *ex = "stats-time";
    char buffer[20];
    char buffer2[30];
    char buffer3[30];
    ssize_t bytes_read;
    long int aux;

    int fd = open("../bin/fifo",O_WRONLY);

    if(fd < 0){
        perror("Erro ao abrir o fifo\n");
    }

    int t = snprintf(buffer,20,"%s",ex);
    write(fd,buffer,t);

    close(fd);

    int fd1 = open("../bin/fifo2",O_WRONLY);

    if(fd1 < 0){
        perror("Erro ao abrir o fifo\n");
    }

    int t1 = snprintf(buffer2,30,"%s",comando);
    write(fd1,buffer2,t1);
    
    close(fd1);

    int fd2 = open("../bin/fifo2",O_RDONLY);

    if(fd2 < 0){
        perror("Erro ao abrir o fifo\n");
    }

    while((bytes_read=read(fd2,&buffer3,sizeof(buffer3)))>0){
            new_string = malloc(sizeof(buffer3));
            memcpy(new_string,buffer3,bytes_read);
            memset(buffer3,0,sizeof(buffer3));
            aux = atol(new_string);
    }
    printf("%ld\n",aux);
}

void stats_uniq(char *command){
    char *new_string;
    char *nova_string;
    char *string_final;
    char *comando = strdup(command);
    char *ex = "stats-uniq";
    char *array[20];
    char buffer[20];
    char buffer2[30];
    char buffer3[50];
    ssize_t bytes_read;
    long int aux;
    int i = 0;

    int fd = open("../bin/fifo",O_WRONLY);

    if(fd < 0){
        perror("Erro ao abrir o fifo\n");
    }

    int t = snprintf(buffer,20,"%s",ex);
    write(fd,buffer,t);

    close(fd);

    int fd1 = open("../bin/fifo3",O_WRONLY);

    if(fd1 < 0){
        perror("Erro ao abrir o fifo\n");
    }

    int t1 = snprintf(buffer2,30,"%s",comando);
    write(fd1,buffer2,t1);
    
    close(fd1);

    int fd2 = open("../bin/fifo3",O_RDONLY);

    if(fd2 < 0){
        perror("Erro ao abrir o fifo\n");
    }

    string_final = malloc(sizeof(buffer2));

    while((bytes_read=read(fd2,&buffer3,sizeof(buffer3)))>0){
            new_string = malloc(sizeof(buffer3));
            memcpy(new_string,buffer3,bytes_read);
            strcat(string_final,new_string);
            memset(buffer3,0,sizeof(buffer3));
    }

    while((nova_string=strsep(&string_final,"_"))!=NULL){
            array[i] = nova_string;
            printf("%s\n",array[i]);
            i++;
    }
}

void stats_command(char *comando1,char* comando2){
    char *new_string;
    char *comando = strdup(comando1);
    char *scomando = strdup(comando2);
    char *ex = "stats-command";
    char buffer[20];
    char buffer2[30];
    char buffer3[30];
    ssize_t bytes_read3;
    int aux;

    int fd = open("../bin/fifo",O_WRONLY);

    if(fd < 0){
        perror("Erro ao abrir fifo\n");
    }

    int t = snprintf(buffer,20,"%s",ex);
    write(fd,buffer,t);

    close(fd);

    int fd1 = open("../bin/fifo4",O_WRONLY);

    if(fd1 < 0){
        perror("Erro ao abrir o fifo\n");
    }

    int t1 = snprintf(buffer2,30,"%s_%s",comando,scomando);
    write(fd1,buffer2,t1);
    
    close(fd1);

    int fd2 = open("../bin/fifo4",O_RDONLY);

    if(fd2 < 0){
        perror("Erro ao abrir o fifo\n");
    }
    
    while((bytes_read3=read(fd2,&buffer3,sizeof(buffer3)))>0){
            new_string = malloc(sizeof(buffer3));
            memcpy(new_string,buffer3,bytes_read3);
            memset(buffer3,0,sizeof(buffer3));
            aux = atoi(new_string);
    }
    printf("%s was executed %d times\n",comando,aux);
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
        int create_fifo = mkfifo("../bin/fifo2",0660);

        char *comando = strdup(argv[2]);
        stats_time(comando);
    }
    else if (strcmp(argv[1],"stats-uniq")==0){
        int create_fifo = mkfifo("../bin/fifo3",0660);

        char *comando = strdup(argv[2]);
        stats_uniq(comando);
    }
    else if(strcmp(argv[1],"stats-command")==0){
        int create_fifo = mkfifo("../bin/fifo4",0660);

        char *comando1 = strdup(argv[2]);
        char *comando2 = strdup(argv[3]); 
        stats_command(comando1,comando2);

    }

    return 0;
}