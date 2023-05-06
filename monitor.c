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
    
    char buffer[20];
    int res;
    int i=0;
    char *exec_args[10];

    while ((bytes_read = read(fd,&buffer,sizeof(buffer)))>0){
        res+=bytes_read;
        //write(1,&buffer,sizeof(buffer));
        char *string = malloc(bytes_read);
        
        printf("%s\n",string);
        
        //printf("\n--------memset--------\n");
        memcpy(string,buffer,bytes_read);
        memset(buffer,0,sizeof(buffer));
        exec_args[i]=string;
        //printf("\n---------memcpy-------\n");
        //memset(buffer,0,sizeof(buffer));
        write(1,exec_args[i],bytes_read);
        printf("\n");
        i++;
        
    }

    //close (fd);

    //printf("%s\n",exec_args[2]);
    //printf("estou aqui\n");
    //printf("%d\n",i);
    //write(1,&buffer,sizeof(buffer));
    memset(buffer,0,sizeof(buffer));
    //printf("%d\n\n",res);

    for(int j=1;j<i;j++){
        //printf("%s\n",exec_args[j]);
        strcat(exec_args[0],exec_args[j]);
    }

    printf("%s\n",exec_args[0]);

    char* string2;
    char* args[10];
    int k=0;
    char *command = strdup(exec_args[0]);

    while((string2=strsep(&command," "))!=NULL){
        args[k] = string2;
        k++;
    }

    printf("%d\n",k);
    //printf("%s\n",exec_args[0]);
    //memset(exec_args,0,sizeof(exec_args));

    int t=0;

    //ver melhor isto ??????????????????????????????
    for (int j = k-1;j>0;j--){
        if(k>=2){
        args[k] = args[k+1];
        t++;
        }
    }


    //printf("\n");

    for(int j=0;j<(t/2);j++){
        if(t<=2){
            printf("%s -> %s\n",args[0],args[1]);
            break;
        }
        else if (t>=2){
            int l=0;
            char *exec_args2[(t/2)][2];
            //printf("%d\n\n",t);
            exec_args2[j][0] = args[j];
            exec_args2[j][1] = args[j+(t/2)];
            printf("%s -> %s\n",exec_args2[j][0],exec_args2[j][1]); 
            l++;
        }
    }

    memset(args,0,sizeof(args));
    memset(exec_args,0,sizeof(exec_args));

}
return 0;
}