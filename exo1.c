#include <stdlib.h> /*exit, atoi */
#include <stdio.h>  /*printf */
#include <unistd.h> /*getpid, fork */
#include <wait.h>   /*wait */

void arbre(int n) {
int i;
printf("Lance %d processus en arbre\n\n",n);
printf("proc %d fils de %d (shell)\n",getpid(),getppid());
for (i=0; i<n; i++) {
if (fork() == 0) { /* fils */
printf("proc %d fils de %d\n",getpid(),getppid());
} else {
// wait(NULL); pas de wait, ou les pères quitent pas assez vite
exit(0);
}
}
}
void chaine(int n) {
int i;
printf("Lance %d processus en chaine\n\n",n);
printf("proc %d fils de %d (shell)\n",getpid(),getppid());

for (i=0; i<n; i++) {
if (fork() == 0) { /* fils */
printf("proc %d fils de %d\n",getpid(),getppid());
exit(0);
}
}
for (i=0; i<n; i++)
wait(NULL);
}
int main(int argc, char *argv[ ]) {
if (argc<2) {
printf("Usage:\n%s 1 <n> pour lancer <n> processus en arbre\n%s 2 <n> pour lancer <n> processus en chaine\n",argv[0], argv[0]);
exit(1);
}
switch(atoi(argv[1])) {
case 1: arbre(atoi(argv[2])); break;
case 2: chaine(atoi(argv[2])); break;
}
return 0;
}
