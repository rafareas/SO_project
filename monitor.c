#include <sys/types.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <string.h>

int main(int argc, char ** argv){

    while(1){

    int fd = open("fifo",O_RDONLY);

    if (fd < 0){
        perror("Error to open fifo\n");
    }

    int bytes_read,res;
    

    char buffer[20];

    while ((bytes_read = read(fd,&buffer,sizeof(buffer)))>0){
        printf("estou na comparaçao\n");
        printf("%s\n",buffer);
        if(strcmp(buffer,"executaU\n")==0){
            memset(buffer,0,sizeof(buffer));
            printf("entrei aqui\n");
            res=fork();
            if(res==0){
                //printf("entrei\n");
                int res;
                char buffer2[20];
                for(int i=0 ;(res = read(fd,&buffer2,sizeof(buffer2)))>0 && i<3;i++){
                    switch(i){
                    case 0:
                    write(1,&buffer2,sizeof(buffer));
                    int num = atoi(buffer2);
                    //printf("estou aqui\n");
                    memset(buffer2,0,sizeof(buffer2));
                    printf("\ncase 0\n");
                    break;

                    case 1:
                        write(1,&buffer2,sizeof(buffer));
                        num = atoi(buffer2);
                        //printf("estou aqui\n");
                        memset(buffer2,0,sizeof(buffer2));

                        printf("case 1\n");
                        break;

                    case 2:
                        printf("case 2\n");
                        memset(buffer2,0,sizeof(buffer2));
                        break;

                    }
                 }
            close(fd);
            _exit(0);
            }
            else{
                int status;
                //memset(buffer,0,sizeof(buffer));
                pid_t terminated_pid = wait(NULL);
                close(fd);
            }
        }
        //tenho de implementar melhor este exit
        //else{
        //    printf("estou no exit\n");
        //    return 0;
        //}
    }
    //close (fd);
}
return 0;
}