#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv)
{
    ///D?claration des variables
    int f1,f2,a;
    char buf;
    if(argc!=3)
    {
        fprintf(stderr, "Syntaxe:%s f1 f2\n",argv[0]);
        exit(1);
    }
    f1=open(argv[1], O_RDONLY);
    if(f1<0)
    {   ///En cas d'ouverture du fichier f1, envoyer un  message d'erreur et quitter le programme
        perror("open(f1)");
        exit(1);
    }
    ///appel syst?me pour la cr?ation et l'ouverture du fichier f2
    f2=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if(f2<0)
    {   ///En cas d'erreur, envoyer un message d'erreur et quitter le programme
        perror("open(f2)");
        exit(1);
    }
    while(1)
    {
        a = read(f1,&buf,1);
        if(a<0)
        {   ///Message d'erreur en cas erreur de lecture du fichier et quitter le programme
            perror("read");
            exit(1);
        }
        if(a==0)
            break;
            ///Ecriture du fichier f2
        a = write(f2,&buf,1);
        if(a<0)
        {   ///En cas d'errreur d'?criture dun fichier f2, envoyer un message d'erreur et quitter le programme
            perror("write");
            exit(1);
        }
        if(a!=1)
        {
            fprintf(stderr, "?criture interrompue");
            exit(1);
        }
    }
    ///Fermeture des deux programmes ? la fin d'ex?cution des instructions !
    close(f1);
    close(f2);
    return 0;
}
