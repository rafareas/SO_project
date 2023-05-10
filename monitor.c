#include <sys/types.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <string.h>
#include <math.h>


int main(int argc, char ** argv){

    int bytes_read;
    
    char buffer[50];
    int i=0;
    char *exec_args[20];
    char * string;

    while(1){

        int fd = open("fifo",O_RDONLY);

        if (fd < 0){
            perror("Error to open fifo\n");
        }

    while ((bytes_read = read(fd,&buffer,sizeof(buffer)))>0){

        string = malloc(bytes_read);
        
        printf("%s\n",string);
        
        memcpy(string,buffer,bytes_read);
        memset(buffer,0,sizeof(buffer));
        exec_args[i]=string;
        printf("%s\n",exec_args[i]);
        
        pid_t res = fork();

        if (res ==0){
        
        close(fd);

        char * array[6];
        char *nova_string;
        char *string_parte = strdup(exec_args[i]);

        int k = 0;

        printf("----fork novo-----\n");

        while((nova_string=strsep(&string_parte," "))!=NULL){
            array[k] = nova_string;
            printf("%s\n",array[k]);
            k++;
            }

        
        if(strcmp("executaU",array[0])==0){
            printf("entrei no executaU\n");
            _exit(0);
            }

        else if(strcmp("status",array[0])==0){

            int fd1 = open("fifo1",O_WRONLY,0660);

            if(fd1 < 0){
                perror("Error to open fifo\n");
            }


            printf("entrei no status\n");
            printf("%d\n",i);
            printf("%s\n",exec_args[0]);
            char * array2[6];
            char * nova_string2;

            for(int j = 0;j<i;j++){

                int k = 0;

                while((nova_string2=strsep(&exec_args[j]," "))!=NULL){
                array2[k] = nova_string2;
                printf("%s\n",array2[k]);
                k++;
                }
            
                if(strcmp("executaU",array2[0])==0){
                    printf("entrei na criaçao\n");
                    printf("%s\n",array2[1]);
                    
                    
                    char buffer_novo[20];
                    printf("criei o buffer\n");

                    int t1 = snprintf(buffer_novo,20,"%s %s",array2[1],array2[5]);
                    printf("snprintf\n");
                    write(1,buffer_novo,t1);
                    write(fd1,buffer_novo,t1);
                    printf("escrevi\n");
                }

                printf("%d\n",j);
            }

            close(fd1);
            printf("sai\n");
            _exit(0);
            }
        }

        wait(NULL);
        printf("passei aqui\n");
        i++;
    }
    close(fd);
    }

    printf("estou aqui\n");

    memset(buffer,0,sizeof(buffer));
    memset(exec_args,0,sizeof(exec_args));

return 0;

}