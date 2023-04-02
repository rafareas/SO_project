#include <sys/types.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

int main(int argc, char **argv){
    int create_fifo = mkfifo("fifo",0660);

    if(create_fifo < 0){
        perror("Error in the creation of fifo.\n");
    }

    int fd = open("fifo",O_WRONLY);

    if(fd < 0){
        perror("Error to open fifo\n");
    }

    write(fd,argv[1],sizeof(argv[1]));

    close(fd);
    printf("Terminei\n");

    return 0;

    return 0;
}