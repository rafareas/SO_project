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

typedef struct Program{
    char name[200];
    int age;
} Program;




int main(int argc, char ** argv){

    while(1){

    int fd = open("fifo",O_RDONLY);

    if (fd < 0){
        perror("Error to open fifo\n");
    }

    int bytes_read;
    
    char buffer[50];
    int res;
    int i=0;
    char *exec_args[20];
    char * string;

    while ((bytes_read = read(fd,&buffer,sizeof(buffer)))>0){
        //write(1,&buffer,sizeof(buffer));
        string = malloc(bytes_read);
        
        printf("%s\n",string);
        
        //printf("\n--------memset--------\n");
        memcpy(string,buffer,bytes_read);
        memset(buffer,0,sizeof(buffer));
        exec_args[i]=string;
        //printf("\n---------memcpy-------\n");
        //memset(buffer,0,sizeof(buffer));
        printf("%s\n",exec_args[i]);
        //write(1,exec_args[i],bytes_read);
        printf("\n");
        printf("aqui\n");
        //memset(string,0,sizeof(bytes_read));
        i++; 
    }

    close(fd);

    memset(buffer,0,sizeof(buffer));


    for(int j=0;j<i;j++){
        pid_t res = fork();
        if (res ==0){
        
        char * array[6];
        char *nova_string;

        int k = 0;

        printf("----fork novo-----\n");

        while((nova_string=strsep(&exec_args[j]," "))!=NULL){
            array[k] = nova_string;
            printf("%s\n",array[k]);
            k++;
            }
        // aqui adicionar a estrutura (lista ligada) e fazer compare do primeiro elemento do array;




            printf("------fork seguinte-----\n");
            _exit(0);

        }
        
    }

    for(int j=0;j<i;j++){
        wait(NULL);
    }

    //close (fd);

    //printf("%s\n",exec_args[2]);
    //printf("estou aqui\n");
    //printf("%d\n",i);
    //write(1,&buffer,sizeof(buffer));
    //memset(buffer,0,sizeof(buffer));
    //printf("%d\n\n",res);

    //for(int j=1;j<i;j++){
        //printf("%s\n",exec_args[j]);
    //    strcat(exec_args[0],exec_args[j]);
    //}

    //strcat(exec_args[0],"\0");
    //printf("%s\n",exec_args[0]);

    //char *temp[1];
    //temp[0] = exec_args[0];

    //char* string2;
    //char* args[20];
    //int k=0;
    //char *command;
    //command = strdup(temp[0]);
    //printf("%s\n",command);

    //while((string2=strsep(&command," "))!=NULL){
    //    args[k] = string2;
    //    printf("%s\n",args[k]);
    //    k++;
    //}

    //printf("%d\n",k);
    //printf("%s\n",exec_args[0]);
    //memset(exec_args,0,sizeof(exec_args));

    //int t=0

    //for(int j=0;j<(t/2);j++){
    //    if(t<=3){
    //        printf("%s -> %s\n",args[0],args[1]);
    //        break;
    //    }
    //    else if (t>3){
    //        if(strcmp("executaU ",args[j]) && strcmp("executaU ",args[j+1])){
    /*        char *exec_args2[(t/2)][3];
            //printf("%d\n\n",t);
            exec_args2[j][0] = args[j];
            exec_args2[j][1] = args[(j+(t/2))-1]; //0+3
            exec_args2[j][2] = args[j+(t/2)];
            printf("%s -> %s -> %s\n",exec_args2[j][0],exec_args2[j][1],exec_args2[j][2]);
            }
            else{
            char *exec_args2[(t/2)][2];
            //printf("%d\n\n",t);
            exec_args2[j][0] = args[j];
            exec_args2[j][1] = args[j+1];
            exec_args2[j][2] = args[j+2];
            printf("%s -> %s\n",exec_args2[j][0],exec_args2[j][1]); 
            }
        }
    }
    */

    //memset(args,0,sizeof(args));
    memset(exec_args,0,sizeof(exec_args));

}
return 0;
}