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


long int stats_time(char *command,int argc){
    long int tot = 0;
    int i = 0;
    char *exec_args[20];
    char *nova_string=strdup(command);
    char *string;
    char *string_txt;

    printf("cheguei aqui\n");


    while((string=strsep(&nova_string," "))!=NULL){
        exec_args[i]=string;
        i++;
    }
  
   
    for(int j = 0;j < i;j++){
        char buffer[10];
        ssize_t bytes_read;
        int fd;

        char *file_name = malloc(strlen(exec_args[j]) + 5);

            if(argc==1){
                strcpy(file_name, exec_args[j]);
                strcat(file_name, ".txt");


                fd = open(file_name, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o arquivo");
                }
            }
            else if(argc==2){
                char name_pid_fd[24];
                char name_inter[24];
                char path_final[24];
                char *path = "../";
                strcpy(path_final,path);
                strcat(path_final,"PIDS-folder");
                strcpy(name_pid_fd, exec_args[j]);
                strcat(name_pid_fd, ".txt");
                strcpy(name_inter,"/");
                strcat(name_inter,name_pid_fd);
                strcat(path_final,name_inter);

                printf("path:%s\n",path_final);

                fd = open(path_final, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o arquivo");
                    return 1;
                }

            }

        char *new_string;
        long int aux;

        while ((bytes_read = read(fd, buffer,sizeof(buffer))) > 0){
            new_string = malloc(sizeof(buffer));
            memcpy(new_string,buffer,bytes_read);
            memset(buffer,0,sizeof(buffer));
            //aux = atol(new_string);
            
            //tot += aux;
        }
        char* string_final;
        char* array[3];
        int k =0;

        while((nova_string=strsep(&new_string,"_"))!=NULL){
            array[k] = nova_string;
            printf("%s\n",array[k]);
            k++;
            }
        aux = atol(array[1]);
        tot+=aux;

    }

    return tot;
}

void stats_uniq(char *command,int argc){
    long int tot = 0;
    int i = 0;
    char *exec_args[20];
    char *nova_string=strdup(command);
    char *string;
    char *string_txt;

    printf("cheguei aqui\n");


    while((string=strsep(&nova_string," "))!=NULL){
        exec_args[i]=string;
        i++;
    }
  
    char* string_final;

    for(int j = 0;j < i;j++){
        char buffer[10];
        ssize_t bytes_read;
        int fd;

        char *file_name = malloc(strlen(exec_args[j]) + 5);

            if(argc==1){
                strcpy(file_name, exec_args[j]);
                strcat(file_name, ".txt");


                fd = open(file_name, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o arquivo");
                }
            }
            else if(argc==2){
                char name_pid_fd[24];
                char name_inter[24];
                char path_final[24];
                char *path = "../";
                strcpy(path_final,path);
                strcat(path_final,"PIDS-folder");
                strcpy(name_pid_fd, exec_args[j]);
                strcat(name_pid_fd, ".txt");
                strcpy(name_inter,"/");
                strcat(name_inter,name_pid_fd);
                strcat(path_final,name_inter);

                printf("path:%s\n",path_final);

                fd = open(path_final, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o arquivo");
                    return 1;
                }

            }

        char *new_string;
        long int aux;

        while ((bytes_read = read(fd, buffer,sizeof(buffer))) > 0){
            new_string = malloc(sizeof(buffer));
            memcpy(new_string,buffer,bytes_read);
            memset(buffer,0,sizeof(buffer));
        }

        
        char* array[3];
        int k =0;

        while((nova_string=strsep(&new_string,"_"))!=NULL){
            array[k] = nova_string;
            printf("%s\n",array[k]);
            k++;
            }
        

        int fd3 = open("../bin/fifo3",O_WRONLY);

        if(fd3 < 0){
          perror("Error to open fifo\n"); 
        }

        char buffer2[10];

        int t2 = snprintf(buffer2,10,"%s_",array[0]);
        write(fd3,buffer2,t2);

        close(fd3);
    }
}

int stats_command(char *comando1,char *comando2,int argc){
    int tot = 0;
    int i = 0;
    char *exec_args[20];
    char *compare = strdup(comando1);
    char *nova_string=strdup(comando2);
    char *string;
    char *string_txt;

    printf("cheguei aqui\n");


    while((string=strsep(&nova_string," "))!=NULL){
        exec_args[i]=string;
        i++;
    }
  
    char* string_final;

    for(int j = 0;j < i;j++){
        char buffer[10];
        ssize_t bytes_read;
        int fd;

        char *file_name = malloc(strlen(exec_args[j]) + 5);

            if(argc==1){
                strcpy(file_name, exec_args[j]);
                strcat(file_name, ".txt");


                fd = open(file_name, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o arquivo");
                }
            }
            else if(argc==2){
                char name_pid_fd[24];
                char name_inter[24];
                char path_final[24];
                char *path = "../";
                strcpy(path_final,path);
                strcat(path_final,"PIDS-folder");
                strcpy(name_pid_fd, exec_args[j]);
                strcat(name_pid_fd, ".txt");
                strcpy(name_inter,"/");
                strcat(name_inter,name_pid_fd);
                strcat(path_final,name_inter);

                printf("path:%s\n",path_final);

                fd = open(path_final, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o arquivo");
                    return 1;
                }

            }

        char *new_string;
        long int aux;

        while ((bytes_read = read(fd, buffer,sizeof(buffer))) > 0){
            new_string = malloc(sizeof(buffer));
            memcpy(new_string,buffer,bytes_read);
            memset(buffer,0,sizeof(buffer));
        }

        
        char* array[3];
        int k =0;

        while((nova_string=strsep(&new_string,"_"))!=NULL){
            array[k] = nova_string;
            printf("%s\n",array[k]);
            k++;
            }
        
        if(strcmp(compare,array[0])==0){
            tot++;
        }
        
    }
    return tot;
}

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
            printf("%s\n",array[k]);
            k++;
            }
        
        if(strcmp("executaU",array[0])==0){
            printf("entrei no executaU\n");
            
            if(argc==1){
                char name_pid_fd[24];
            
                strcpy(name_pid_fd, array[3]);
                strcat(name_pid_fd, ".txt");

                int fd_pid = open(name_pid_fd, O_WRONLY | O_CREAT, 0600);
                if (fd == -1) {
                    perror("Erro ao abrir o arquivo");
                    return 1;
                }

                char escreve_ficheiro[20];
                char escreve_ficheiroF[20];
                strcpy(escreve_ficheiroF,array[1]);
                strcat(escreve_ficheiroF,"_");
                strcpy(escreve_ficheiro,array[2]);
                strcat(escreve_ficheiroF,escreve_ficheiro);


        
                int num_bytes = write(fd_pid, &escreve_ficheiroF, strlen(escreve_ficheiroF));
                if (num_bytes == -1) {
                    perror("Erro ao escrever no arquivo");
                    close(fd);
                    return 1;
                }

                close(fd_pid);
            }
            else if(argc==2){
                char name_pid_fd[24];
                char name_inter[24];
                char path_final[24];
                char *path = "../";
                strcpy(path_final,path);
                strcat(path_final,argv[1]);
                strcpy(name_pid_fd, array[3]);
                strcat(name_pid_fd, ".txt");
                strcpy(name_inter,"/");
                strcat(name_inter,name_pid_fd);
                strcat(path_final,name_inter);

                printf("path:%s\n",path_final);

                int fd_pid = open(path_final, O_WRONLY | O_CREAT, 0600);
                if (fd == -1) {
                    perror("Erro ao abrir o arquivo");
                    return 1;
                }
        
                int num_bytes = write(fd_pid, array[2], strlen(array[2]));
                if (num_bytes == -1) {
                    perror("Erro ao escrever no arquivo");
                    close(fd);
                    return 1;
                }

                close(fd_pid);
            }
            _exit(0);
            }
        
        if(strcmp("executaP",array[0])==0){
            printf("entrei no executaP\n");

            char name_pid_fd[24];
    
            strcpy(name_pid_fd, array[4]);
            strcat(name_pid_fd, ".txt");

            int fd_pid = open(name_pid_fd, O_WRONLY | O_CREAT, 0600);
            if (fd == -1) {
                perror("Erro ao abrir o arquivo");
                return 1;
            }

        
            int num_bytes = write(fd_pid, array[3], strlen(array[3]));
            if (num_bytes == -1) {
                perror("Erro ao escrever no arquivo");
                close(fd);
                return 1;
            }

            close(fd_pid);
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
            else if(strcmp("stats-time",array[0])==0){
                printf("entrei\n");
                int fd2 = open("../bin/fifo2",O_RDONLY);

                if(fd2 < 0){
                    perror("Error to open fifo\n");
                }

                ssize_t bytes_read2;
                char buffer2[50];
                char *string2;
                char *string_final;
                string_final = malloc(sizeof(buffer2));

                while((bytes_read2=read(fd2,&buffer2,sizeof(buffer2)))>0){
                    string2 = malloc(sizeof(buffer2));
                    memcpy(string2,buffer2,bytes_read2);
                    strcat(string_final,string2);
                    memset(buffer2,0,sizeof(buffer2));
                }

                close(fd2);

                long int resultado=stats_time(string_final,argc);

                int fd3 = open("../bin/fifo2",O_WRONLY);

                if(fd3 < 0){
                    perror("Error to open fifo\n");
                }

                char buffer3[30];
                int t2 = snprintf(buffer3,30,"%ld",resultado);
                write(fd3,buffer3,t2);

                close(fd3);
            }

            else if(strcmp("stats-uniq",array[0])==0){
                printf("entrei\n");
                int fd2 = open("../bin/fifo3",O_RDONLY);

                if(fd2 < 0){
                    perror("Error to open fifo\n");
                }

                ssize_t bytes_read2;
                char buffer2[50];
                char *string2;
                char *string_final;
                string_final = malloc(sizeof(buffer2));

                while((bytes_read2=read(fd2,&buffer2,sizeof(buffer2)))>0){
                    string2 = malloc(sizeof(buffer2));
                    memcpy(string2,buffer2,bytes_read2);
                    strcat(string_final,string2);
                    memset(buffer2,0,sizeof(buffer2));
                }

                close(fd2);

                stats_uniq(string_final,argc);

            }
            else if(strcmp("stats-command",array[0])==0){
                printf("entrei\n");
                int fd2 = open("../bin/fifo4",O_RDONLY);

                if(fd2 < 0){
                    perror("Error to open fifo\n");
                }

                ssize_t bytes_read2;
                char buffer2[50];
                char *string2;
                char *string_final;
                string_final = malloc(sizeof(buffer2));

                while((bytes_read2=read(fd2,&buffer2,sizeof(buffer2)))>0){
                    string2 = malloc(sizeof(buffer2));
                    memcpy(string2,buffer2,bytes_read2);
                    strcat(string_final,string2);
                    memset(buffer2,0,sizeof(buffer2));
                }
                close(fd2);
                //parsing
                printf("string final : %s\n",string_final);
                printf("a entrar no parsing\n");
                int j =0;
                char *string_statsC;
                char *arraySC[2];

                while((string_statsC=strsep(&string_final,"_"))!=NULL){
                    array[j] = string_statsC;
                    printf("%s\n",array[j]);
                    j++;
                }

                printf("resultados\n"),
                printf("%s %s",array[0],array[1]);
                int resultado = stats_command(array[0],array[1],argc);

                int fd3 = open("../bin/fifo4",O_WRONLY);

                if(fd3 < 0){
                    perror("Error to open fifo\n"); 
                }

                char buffer3[10];

                int t2 = snprintf(buffer3,10,"%d",resultado);
                write(fd3,buffer3,t2);

                close(fd3);

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
