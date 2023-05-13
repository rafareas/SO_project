#include "../include/monitor.h"


long int stats_time(char *command,int argc){
    char *exec_args[20];
    char *nova_string=strdup(command);
    char *string;
    char *string_txt;
    long int tot = 0;
    int i = 0;

    while((string=strsep(&nova_string," "))!=NULL){
        exec_args[i]=string;
        i++;
    }

    for(int j = 0;j < i;j++){
        char *new_string;
        char *string_final;
        char buffer[10];
        ssize_t bytes_read;
        long int aux;
        int fd;
        int t = 0;

        char *file_name = malloc(strlen(exec_args[j]) + 5);

            if(argc==1){
                strcpy(file_name, exec_args[j]);
                strcat(file_name, ".txt");


                fd = open(file_name, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o ficheiro\n");
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

                fd = open(path_final, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o ficheiro\n");
                }

            }
        
        
        string_final = malloc(sizeof(buffer));
        
        while ((bytes_read = read(fd, buffer,sizeof(buffer))) > 0){
            new_string = malloc(sizeof(buffer));
            memcpy(new_string,buffer,bytes_read);
            strcat(string_final,new_string);
            memset(buffer,0,sizeof(buffer));
            t++;
        }

        if(t>0){

        close(fd);

        char* string_aux;
        char* array[3];
        int k =0;

        while((string_aux=strsep(&string_final,"_"))!=NULL){
            array[k] = string_aux;
            k++;
            }
        aux = atol(array[1]);
        tot+=aux;
        }
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
    char final[100];

    while((string=strsep(&nova_string," "))!=NULL){
        exec_args[i]=string;
        i++;
    }

    for(int j = 0;j < i;j++){
        char *new_string;
        char *string_final;
        char buffer[20];
        ssize_t bytes_read;
        int fd;
        long int aux;
        int t =0;

        char *file_name = malloc(strlen(exec_args[j]) + 5);

            if(argc==1){
                strcpy(file_name, exec_args[j]);
                strcat(file_name, ".txt");


                fd = open(file_name, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o ficheiro\n");
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

                fd = open(path_final, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o ficheiro\n");
                }

            }
        
        
        string_final = malloc(sizeof(buffer));

        while ((bytes_read = read(fd, buffer,sizeof(buffer))) > 0){
            new_string = malloc(sizeof(buffer));
            memcpy(new_string,buffer,bytes_read);
            strcat(string_final,new_string);
            memset(buffer,0,sizeof(buffer));
            t++;
        }

        if(t>0){

        close(fd);

        char* array[3];
        int k =0;
        char *string_aux;

        while((string_aux=strsep(&string_final,"_"))!=NULL){
            array[k] = string_aux;
            k++;
            }

        int fd3 = open("../bin/fifo3",O_WRONLY);

        if(fd3 < 0){
          perror("Error to open fifo\n"); 
        }

        char buffer2[20];

        int t2 = snprintf(buffer2,20,"%s_",array[0]);
        write(fd3,buffer2,t2);

        close(fd3);
        }
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

    while((string=strsep(&nova_string," "))!=NULL){
        exec_args[i]=string;
        i++;
    }

    for(int j = 0;j < i;j++){
        char *new_string;
        char *string_final;
        char buffer[10];
        ssize_t bytes_read;
        long int aux;
        int fd;
        int t =0;

        char *file_name = malloc(strlen(exec_args[j]) + 5);

            if(argc==1){
                strcpy(file_name, exec_args[j]);
                strcat(file_name, ".txt");


                fd = open(file_name, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o ficheiro\n");
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

                fd = open(path_final, O_RDONLY);
                if (fd == -1) {
                    perror("Erro ao abrir o ficheiro\n");
                }

            }
        
        
        string_final = malloc(sizeof(buffer));

        while ((bytes_read = read(fd, buffer,sizeof(buffer))) > 0){
            new_string = malloc(sizeof(buffer));
            memcpy(new_string,buffer,bytes_read);
            strcat(string_final,new_string);
            memset(buffer,0,sizeof(buffer));
            t++;
        }
        
        if(t>0){

        close(fd);
        
        char* array[2];
        int k =0;
        char *string_aux;

        while((string_aux=strsep(&string_final,"_"))!=NULL){
            array[k] = string_aux;
            k++;
            }

        if(strcmp(compare,array[0])==0){
            tot++;
        }
        }
    }
    return tot;
}

int main(int argc, char ** argv){

    char buffer[50];
    int i=0;
    char *exec_args[20];
    char * string;
    int bytes_read;

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
            perror("Error ao criar o fork\n");
        }

        if (res==0){
        
        close(fd);

        char * array[6];
        char *nova_string;
        char *string_parte = strdup(exec_args[i]);
        char *string_reserv = strdup(exec_args[i]);

        int k = 0;

        while((nova_string=strsep(&string_parte," "))!=NULL){
            array[k] = nova_string;
            k++;
            }
        
        if(strcmp("executaU",array[0])==0){
            
            if(argc==1){
                char name_pid_fd[24];
            
                strcpy(name_pid_fd, array[3]);
                strcat(name_pid_fd, ".txt");

                int fd_pid = open(name_pid_fd, O_WRONLY | O_CREAT, 0600);
                if (fd == -1) {
                    perror("Erro ao abrir o ficheiro\n");
                }

                char escreve_ficheiro[20];
                char escreve_ficheiroF[20];
                strcpy(escreve_ficheiroF,array[1]);
                strcat(escreve_ficheiroF,"_");
                strcpy(escreve_ficheiro,array[2]);
                strcat(escreve_ficheiroF,escreve_ficheiro);
        
                int num_bytes = write(fd_pid, &escreve_ficheiroF, strlen(escreve_ficheiroF));
                if (num_bytes == -1) {
                    perror("Erro ao escrever no ficheiro\n");
                    close(fd);
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

                int fd_pid = open(path_final, O_WRONLY | O_CREAT, 0600);
                if (fd == -1) {
                    perror("Erro ao abrir o ficheiro\n");
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
                    perror("Erro ao escrever no ficheiro\n");
                    close(fd);
                    return 1;
                }

                close(fd_pid);
            }
            _exit(0);
            }
        
        if(strcmp("executaP",array[0])==0){

            int fd_pid;
            
            if(argc==1){
                char escreve_ficheiro[20];
                char escreve_ficheiroF[20];
                char name_pid_fd[24];
                char *arrayU[8];
                char *string_execu;
                int l=0;
            
                strcpy(name_pid_fd, array[2]);
                strcat(name_pid_fd, ".txt");

                fd_pid = open(name_pid_fd, O_WRONLY | O_CREAT, 0600);
                if (fd == -1) {
                    perror("Erro ao abrir o ficheiro\n");
                    return 1;
                }

                while((string_execu=strsep(&string_reserv,"_"))!=NULL){
                    arrayU[l] = string_execu;
                    l++;
                }

                strcpy(escreve_ficheiroF,arrayU[1]);
                strcat(escreve_ficheiroF,"_");
                strcpy(escreve_ficheiro,array[1]);
                strcat(escreve_ficheiroF,escreve_ficheiro);
        
                int num_bytes = write(fd_pid, &escreve_ficheiroF, strlen(escreve_ficheiroF));
                if (num_bytes == -1) {
                    perror("Erro ao escrever no ficheiro\n");
                    close(fd);
                    return 1;
                }

                close(fd_pid);
            }
            else if(argc==2){

                char escreve_ficheiro[20];
                char escreve_ficheiroF[20];
                char name_pid_fd[24];
                char name_inter[24];
                char path_final[24];
                char *string_execu;
                char *path = "../";
                char *arrayU[8];
                int l=0;


                strcpy(path_final,path);
                strcat(path_final,argv[1]);
                strcpy(name_pid_fd, array[2]);
                strcat(name_pid_fd, ".txt");
                strcpy(name_inter,"/");
                strcat(name_inter,name_pid_fd);
                strcat(path_final,name_inter);

                fd_pid = open(path_final, O_WRONLY | O_CREAT, 0600);
                if (fd == -1) {
                    perror("Erro ao abrir o ficheiro\n");
                    return 1;
                }

                while((string_execu=strsep(&string_reserv,"_"))!=NULL){
                    arrayU[l] = string_execu;
                    l++;
                }

                strcpy(escreve_ficheiroF,arrayU[1]);
                strcat(escreve_ficheiroF,"_");
                strcpy(escreve_ficheiro,array[1]);
                strcat(escreve_ficheiroF,escreve_ficheiro);

                int num_bytes = write(fd_pid, &escreve_ficheiroF, strlen(escreve_ficheiroF));
                if (num_bytes == -1) {
                    perror("Erro ao escrever no ficheiro\n");
                    close(fd);
                    return 1;
                }

                close(fd_pid);
            }
            _exit(0);
        }

        else if(strcmp("status",array[0])==0){

            char * array2[5];
            char * nova_string2;

            int fd1 = open("../bin/fifo1",O_WRONLY,0660);

            if(fd1 < 0){
                perror("Erro ao abrir o fifo\n");
            }

            for(int j = 0;j<i;j++){

                int k = 0;

                char* string_status = strdup(exec_args[j]);

                while((nova_string2=strsep(&exec_args[j]," "))!=NULL){
                    array2[k] = nova_string2;
                    k++;
                }
            
                if(strcmp("executaU",array2[0])==0){

                    char buffer_novo[30];

                    int t1 = snprintf(buffer_novo,40,"%d %s %s ms_",atoi(array2[3]),array2[1],array2[2]);
                    write(fd1,buffer_novo,t1);
                }

                else if(strcmp("executaP",array2[0])==0){

                    char *arrayU[2];
                    char *string_execu;
                    char buffer_novo[50];
                    int l=0;

                    while((string_execu=strsep(&string_status,"_"))!=NULL){
                        arrayU[l] = string_execu;
                        l++;
                    }

                    int t1 = snprintf(buffer_novo,50,"%d %s %s ms_",atoi(array2[2]),arrayU[1],array2[1]);
                    write(fd1,buffer_novo,t1);
                }
            }

            close(fd1);
            _exit(0);
        }
            else if(strcmp("stats-time",array[0])==0){

                char buffer2[50];
                char buffer3[30];
                char *string2;
                char *string_final;
                ssize_t bytes_read2;
                long int resultado;
                
                int fd2 = open("../bin/fifo2",O_RDONLY);

                if(fd2 < 0){
                    perror("Erro ao abrir o fifo\n");
                }

                string_final = malloc(sizeof(buffer2));

                while((bytes_read2=read(fd2,&buffer2,sizeof(buffer2)))>0){
                    string2 = malloc(sizeof(buffer2));
                    memcpy(string2,buffer2,bytes_read2);
                    strcat(string_final,string2);
                    memset(buffer2,0,sizeof(buffer2));
                }

                close(fd2);

                resultado=stats_time(string_final,argc);

                int fd3 = open("../bin/fifo2",O_WRONLY);

                if(fd3 < 0){
                    perror("Erro ao abrir o fifo\n");
                }

                int t2 = snprintf(buffer3,30,"%ld",resultado);
                write(fd3,buffer3,t2);

                close(fd3);
            }

            else if(strcmp("stats-uniq",array[0])==0){
                
                char buffer2[50];
                char *string2;
                char *string_final;
                ssize_t bytes_read2;

                int fd2 = open("../bin/fifo3",O_RDONLY);

                if(fd2 < 0){
                    perror("Erro ao abrir o fifo\n");
                }

                
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
                
                char buffer2[50];
                char buffer3[10];
                char *string2;
                char *string_final;
                char *string_statsC;
                char *arraySC[2];
                ssize_t bytes_read2;
                int j =0;
                
                int fd2 = open("../bin/fifo4",O_RDONLY);

                if(fd2 < 0){
                    perror("Error ao abrir o fifo\n");
                }
                
                string_final = malloc(sizeof(buffer2));

                while((bytes_read2=read(fd2,&buffer2,sizeof(buffer2)))>0){
                    string2 = malloc(sizeof(buffer2));
                    memcpy(string2,buffer2,bytes_read2);
                    strcat(string_final,string2);
                    memset(buffer2,0,sizeof(buffer2));
                }
                close(fd2);

                while((string_statsC=strsep(&string_final,"_"))!=NULL){
                    array[j] = string_statsC;
                    j++;
                }

                int resultado = stats_command(array[0],array[1],argc);

                int fd3 = open("../bin/fifo4",O_WRONLY);

                if(fd3 < 0){
                    perror("Erro ao abrir o fifo\n"); 
                }

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