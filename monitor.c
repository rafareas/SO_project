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

    int fd = open("fifo",O_RDONLY);

    if (fd < 0){
        perror("Error to open fifo\n");
    }

    int res;
    char buffer[20];

    int fd1 = open("fifo",O_WRONLY);
    while ((res = read(fd,&buffer,sizeof(buffer)))>0){
            if(strcmp(buffer,"executaU\n")==0){
                printf("entrei\n");
                int res;
                char buffer2[20];
                while((res = read(fd,&buffer2,sizeof(buffer2)))>0){
                    write(1,&buffer2,sizeof(buffer));
                    if(strcmp(buffer2,"exit\n")==0) return 0;
                    printf("estou aqui\n");
                }
            }
            
    }
    
    close(fd);
    return 0;
}