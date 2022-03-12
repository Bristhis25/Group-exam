#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc , char *argv[]){
   /// Initialisation de l'appel système "Fork();"
  pid_t pid = fork();
  if(pid < 0){
    fprintf(stderr, "Erreur de création du processus (%d) (%d)\n", pid, errno); ///Notification d'erreur de création du processus fils en cas de l'inexistance du père !
    return 1;
  }
  if(pid == 0){
    /// Le pid=0 symbolise l'entrée dans le processeur fils !
     printf("Processus fils (%d), le pid de mon père est (%d)\n", getpid(), getppid());
  }else if(pid!=0){
    ///Nous somme dans le processus père
    int status;
    pid_t pid2 = wait(&status);
    printf("Processus père (%d) le pid de mon fils que je viens de créer est: (%d)", getpid(), pid, status);
  }
  return 0;
}
