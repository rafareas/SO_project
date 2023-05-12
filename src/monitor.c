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

        int fd = open("../bin/fifo",O_RDONLY);

        if (fd < 0){
            perror("Error to open fifo\n");
        }

    while ((bytes_read = read(fd,&buffer,sizeof(buffer)))>0){

        string = malloc(sizeof(buffer));
        
        memcpy(string,buffer,bytes_read);
        memset(buffer,0,sizeof(buffer));
        exec_args[i]=string;
        
        pid_t res = fork();

        if(res<0){
            perror("Error creating fork\n");
        }

        if (res ==0){
        
        close(fd);

        char * array[6];
        char *nova_string;
        char *string_parte = strdup(exec_args[i]);

        int k = 0;

        while((nova_string=strsep(&string_parte," "))!=NULL){
            array[k] = nova_string;
            //printf("%s\n",array[k]);
            k++;
            }

        
        if(strcmp("executaU",array[0])==0){
            printf("entrei no executaU\n");
            _exit(0);
            }
        
        if(strcmp("executaP",array[0])==0){
            printf("entrei no executaP\n");
            _exit(0);
            }

        else if(strcmp("status",array[0])==0){
            printf("entrei no status\n");

             int fd1 = open("../bin/fifo1",O_WRONLY,0660);

            if(fd1 < 0){
                perror("Error to open fifo\n");
            }

            char * array2[5];
            char * nova_string2;

            for(int j = 0;j<i;j++){

                int k = 0;

                while((nova_string2=strsep(&exec_args[j]," "))!=NULL){
                    array2[k] = nova_string2;
                    k++;
                }
            
                if(strcmp("executaU",array2[0])==0){
                    printf("entrei na criaçao U\n");
                    char buffer_novo[30];

                    int t1 = snprintf(buffer_novo,40,"%d %s %s ms_",atoi(array2[3]),array2[1],array2[2]);
                    write(fd1,buffer_novo,t1);
                }
                else if(strcmp("executaP",array2[0])==0 && k==5){
                    printf("entrei na criaçao P\n");
                    char buffer_novo[50];

                    int t1 = snprintf(buffer_novo,50,"%d %s %s %s ms_",atoi(array2[4]),array2[1],array2[2],array2[3]);
                    write(fd1,buffer_novo,t1);
                }
                else if(strcmp("executaP",array2[0])==0 && k==4){
                    printf("entrei na criaçao P\n");
                    char buffer_novo[50];


                    int t1 = snprintf(buffer_novo,50,"%d %s %s ms_",atoi(array2[3]),array2[1],array2[2]);
                    write(fd1,buffer_novo,t1);
                }
            }

            close(fd1);
            _exit(0);
            }
        }

        wait(NULL);
        i++;
    }
    close(fd);
    }


    memset(buffer,0,sizeof(buffer));
    memset(exec_args,0,sizeof(exec_args));

return 0;

}
