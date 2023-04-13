#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int executa(char** comando){
    int return_exec;
    int status;
    
    //printf("%s\n",comando[0]);

    pid_t res = fork();

        if(res<0){
            perror("Error using fork");
        }
        else if(res==0){
            //codigo do filho
            //printf("FILHO\n");
           
           return_exec=execvp(comando[0],comando);
           
           _exit(return_exec);
        }
        else{
            pid_t wait_pid = wait(&status);
            if(WIFEXITED(status)){
                printf("Pai o filho %d terminou com exit code %d\n",wait_pid,WEXITSTATUS(status));
            }
        }
}

int main(int argc,char** argv){
    int ret=0;
    clock_t start_t, end_t;
    double total_t;
    if(strcmp(argv[1],"execute")==0){
        if(strcmp(argv[2],"-u")==0){
            int i=3;
            int k=0;
            char *comando[argc];
            while(i<argc && k<argc){
                comando[k] = strdup(argv[i]);
                //printf("%s\n",comando[k]);
                k++;
                i++;
            }
            comando[k]=NULL;
            //printf("%s\n\n",comando[0]);
            
            start_t = clock();
            ret = executa(comando);
            end_t = clock();
            total_t = (double) (end_t-start_t) / CLOCKS_PER_SEC;
            printf("%f\n",total_t);
        }
    }
    return ret;
}