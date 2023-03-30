#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int executa(char** comando){
    int return_exec;
    int status;
    int i = 0;
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
    if(strcmp(argv[1],"-u")==0){
        int i=2;
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
        ret = executa(comando);
    }

    return ret;
}