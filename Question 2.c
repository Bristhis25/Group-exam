#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc , char *argv[]){
   /// Initialisation de l'appel syst�me "Fork();"
  pid_t pid = fork();
  if(pid < 0){
    fprintf(stderr, "Erreur de cr�ation du processus (%d) (%d)\n", pid, errno); ///Notification d'erreur de cr�ation du processus fils en cas de l'inexistance du p�re !
    return 1;
  }
  if(pid == 0){
    /// Le pid=0 symbolise l'entr�e dans le processeur fils !
     printf("Processus fils (%d), le pid de mon p�re est (%d)\n", getpid(), getppid());
  }else if(pid!=0){
    ///Nous somme dans le processus p�re
    int status;
    pid_t pid2 = wait(&status);
    printf("Processus p�re (%d) le pid de mon fils que je viens de cr�er est: (%d)", getpid(), pid, status);
  }
  return 0;
}
