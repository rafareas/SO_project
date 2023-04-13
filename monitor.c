#include <sys/types.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

int main(int argc, char ** argv){

    int fd = open("fifo",O_RDONLY);

    if (fd < 0){
        perror("Error to open fifo\n");
    }

    int res;
    char buffer[50];
    while ((res = read(fd,&buffer,sizeof(buffer)))>0){
        write(1,&buffer,res);
    }
    
    close(fd);
    return 0;
}