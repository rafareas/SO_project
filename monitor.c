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

#define FILENAME "file_pessoas5.txt" 

typedef struct Store{
    char *aux;
    char *nome;
    int ti;
    int tf;
    double tt;
    struct Store *prox;

};


// int cria(char *array[],int fd1){

//     int res;
//     Guarda a;
//     a.aux=array[0];
//     //strcpy(a.aux,array[0]);
//     a.nome = array[1];
//     //strcpy(a.nome,array[1]);
//     a.ti = atoi(array[2]);
//     printf("%d\n",a.ti);
//     a.tf = atoi(array[3]); 
//     char *auxiliar;
//     double result;

//     result= strtod(array[4],&auxiliar);
//     a.tt = result;

    
//     lseek(fd1,0,SEEK_END);
//     write(fd1,&a,sizeof(Guarda));
//     res = lseek(fd1,-sizeof(Guarda),SEEK_CUR);
//     close(fd1);
//     return (res/sizeof(Guarda));
// }


// void insere(int fd, Guarda prog) {

//     off_t offset = lseek(fd, 0, SEEK_END);
//     write(fd, &prog, sizeof(prog));
//     printf("registo %ld\n", (offset/sizeof(prog))+1);
//     close(fd);
// }

struct Store* cria(char* arr[],struct Store* prog){
    prog->aux = arr[0];
    prog->nome = arr[1];
    prog->ti = atoi(arr[2]);
    prog->tf = atoi(arr[3]);

    char *auxiliar;
    double result;

    result= strtod(arr[4],&auxiliar);
    prog->tt = result;

    return prog;

}

// void read_people() {

//     int fd1 = open(FILENAME,O_RDONLY,0600);

//     if(fd1<0){
//         perror("erro ao abri");
//     }

//     Guarda pessoa;
//     ssize_t bytes_read;

//     lseek(fd1,0,SEEK_SET);

//     while ((bytes_read = read(fd1, &pessoa, sizeof(Guarda)))>0) {
//         printf("entrei\n");
//         printf("%ld\n",bytes_read);
//         printf("Nome: %s, Idade: %d\n", pessoa.aux, pessoa.ti);
//     }

//     if (bytes_read == -1) {
//         printf("Erro ao ler o arquivo!\n");
//     }

//     close(fd1);
// }

// void list(int fd) {
//     Guarda p;
    

//     printf("dentro do list\n");

//     lseek(fd,0,SEEK_SET);
//     int bytes_read;

//     while((bytes_read = read(fd, &p, sizeof(Guarda)))>0){
//         printf("%d",bytes_read);
//         printf("entrei no while\n");
//     }
//     printf("%s\n",p.nome);
//     printf("passei aqui\n");
//     close(fd);
// }



void insere(char *array[], struct Store* head) {
     struct Store * a = (struct Store *) malloc(sizeof(struct Store));
     a->aux = array[0];
     a->nome = array[1];
     a->ti = atoi(array[2]);
     a->tf = atoi(array[3]);

     char *auxiliar;
     double result;

     result= strtod(array[4],&auxiliar);
     a->tt = result;
     a->prox = head;
 }



void printList(struct Store* n)
{
    while (n != NULL) {
        printf(" %s ", n->aux);
        n = n->prox;
    }
}

void print1(struct Store* n)
{
    while (n != NULL) {
        printf(" %s ", n->aux);
    }
}

int main(int argc, char ** argv){

    while(1){

    int fd = open("fifo",O_RDONLY);

    if (fd < 0){
        perror("Error to open fifo\n");
    }

    int fd1 = open(FILENAME,O_CREAT | O_RDWR,0600);

    if(fd1 < 0){
        perror("Error to open file\n");
    }
    
    int bytes_read;
    
    char buffer[50];
    int i=0;
    char *exec_args[20];
    char * string;

    struct Store* head=NULL;
    struct Store* new = NULL;

    head = (struct Store*) malloc(sizeof(struct Store));
    new = (struct Store*) malloc(sizeof(struct Store));

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
        
        pid_t res = fork();

        if (res ==0){
        
        close(fd);

        char * array[6];
        char *nova_string;

        int k = 0;

        printf("----fork novo-----\n");

        while((nova_string=strsep(&exec_args[i]," "))!=NULL){
            array[k] = nova_string;
            printf("%s\n",array[k]);
            k++;
            }

        // aqui adicionar a estrutura (lista ligada) e fazer compare do primeiro elemento do array;
        if(strcmp("executaU",array[0])==0){
            printf("entrei no executaU\n");

            new = cria(array,head);
            printf("criei a lista\n");
            printf("%s %s\n",new->aux,new->nome);
            //Guarda prog;
            //prog = cria(array,prog);
            _exit(0);
            }

        else if(strcmp("status",array[0])==0){
            close(fd);
            close(fd1);
            printList(head);

            //list(fd1);
            printf("sai\n");
            unlink(FILENAME);
            _exit(0);
            }
        }
        else{

        }

        //print1(new);

        wait(NULL);

        i++;


        //tentar fazer o fork() aqui e o parsing para fazer com que mal leia o que tem a ler seja executado de imediato
    
    
    }
    //printList(head);
    close(fd1);
    close(fd);
    
    

    memset(buffer,0,sizeof(buffer));


    // for(int j=0;j<i;j++){
    //     pid_t res = fork();
    //     if (res ==0){
        
    //     char * array[6];
    //     char *nova_string;

    //     int k = 0;

    //     printf("----fork novo-----\n");

    //     while((nova_string=strsep(&exec_args[j]," "))!=NULL){
    //         array[k] = nova_string;
    //         printf("%s\n",array[k]);
    //         k++;
    //         }
        // aqui adicionar a estrutura (lista ligada) e fazer compare do primeiro elemento do array;




    //         printf("------fork seguinte-----\n");
    //         _exit(0);

    //     }
        
    // }

    // for(int j=0;j<i;j++){
    //     wait(NULL);
    // }

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