#include "tracer.h"

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
    //ls -l
    //snprintf(ls -l)
    //ls
    //-l
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

    int fd = open("fifo",O_WRONLY);

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
        printf("O pid é %d\n",filho);

        gettimeofday(&start,NULL);

        int t2 = snprintf(buffer,MAX_BUFFER,"%d %ld %ld %s",filho,start.tv_sec,start.tv_usec,comando);
        //write(1,buffer,t2);
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

        while((final=strsep(&string2," "))!=NULL){
            exec_args2[i]=final;
            i++;
        }

        
        long tempoi_sec = atol(exec_args2[1]);
    
        double result =((end.tv_usec - atol(exec_args2[2]))/1000) + ((end.tv_sec - atol(exec_args2[1]))*1000);

        int t2 = snprintf(buffer,MAX_BUFFER,"%s %s %f %d",ex,exec_args2[3],result,atoi(exec_args2[0]));
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

    char* string;
    char* nova_string = strdup(comando);
    char **commands = (char**) malloc(sizeof(char)*2);

    printf("%ld\n",sizeof(commands));

    int i=0;
    
    //rever realloc;
    while((string=strsep(&nova_string,"|"))!=NULL){
        commands[i]=string;
        printf("%d\n",i);
        
        if(i==(sizeof(commands)/4)-1){
            printf("entrei\n");
            commands=(char**) realloc(commands,sizeof(commands)*2);
        }
        i++;
    }

    printf("%d\n",i);


    int ncommads = i;

    int pipes[ncommads-1][2];

    //start
    for(int i=0 ;i<ncommads; i++){
        
        if(i==0){
            //cabeça da pipeline
            pipe(pipes[i]);
            int fres=fork();
            if(fres==0){
                close(pipes[i][0]);
                dup2(pipes[i][1],1);
                close(pipes[i][1]);
                //start
                //snprintf

                exec_command(commands[i]);
            }
            else{
                //end
                //Recebes
                //snprintf
                close(pipes[i][1]);

            }
        }
        if(i==ncommads-1){
            int fres=fork();
            if(fres==0){
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
    //end

    //start - end = tempo total

    for(int i=0;i<ncommads;i++){
        wait(NULL);
    }

    printf("Pipeline terminada\n");
    return 0;
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


    int fd1 = open("fifo1",O_RDONLY,0660);

    if(fd1 < 0){
        perror("Error to open fifo\n");
   }

   int bytes_read;
   char * string2;
   char buffer2[20];


    while((bytes_read = read(fd1,&buffer2,sizeof(buffer2)))>0){
                string2 = malloc(sizeof(bytes_read));
                memcpy(string2,buffer2,bytes_read);
                printf("%s\n",string2);
                memset(buffer2,0,sizeof(buffer2));

        }

    printf("resultado %s\n",string2);
    close(fd1);
    return 0;
}


int main(int argc, char **argv){
    int ret=0;
    int create_fifo = mkfifo("fifo",0660);
    int create_fifo1 = mkfifo("fifo1",0660);
    clock_t start_t, end_t;
    double total_t;
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
        status();        
    }

    printf("Terminei\n");

    return 0;
}
