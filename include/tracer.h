#include <sys/types.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <sys/time.h>
#include <time.h>
#include <string.h>

int exec_command(char * cmd);
int executaU(char* comando);
int executaP(char* comando);
int status();
void stats_time(char *command);
void stats_uniq(char *command);
void stats_command(char *comando1,char* comando2);
int main(int argc, char **argv);