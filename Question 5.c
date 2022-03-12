#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <md5.h>
char *readFile( FILE *fp )
{
  if( !fp )
  {
    return NULL;
  }

  char *output = NULL;
  char buf[ MAX_BUF ];
  int bytes, byteCount = 0;

  memset( buf, 0, sizeof( buf ) );

  while( ( bytes = fread( buf, sizeof( char ), sizeof( buf ) - 1, fp ) ) > 0 )
  {
    if( !output )
    {
      /* allocate output */
      output = ( char * )malloc( bytes + 1 );
      memcpy( output, buf, bytes + 1 );
    }
    else
    {
      /* deja existe - reallocate! */


      char *oldStr = strCopy( output );
      output = ( char * )realloc( output, byteCount + bytes + 1 );
      memcpy( output, oldStr, byteCount );

      free( oldStr );
      memcpy( output + byteCount, buf, bytes + 1 );
    }

    byteCount += bytes;
    memset( buf, 0, sizeof( buf ) );
  }

  return output;
}
int main(int argc, char *argv)
{
    ///Déclaration des variables
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
    ///appel système pour la création et l'ouverture du fichier f2
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
        {   ///En cas d'errreur d'écriture dun fichier f2, envoyer un message d'erreur et quitter le programme
            perror("write");
            exit(1);
        }
        if(a!=1)
        {
            fprintf(stderr, "écriture interrompue");
            exit(1);
        }
    }
    ///Fermeture des deux programmes à la fin d'exécution des instructions !
    close(f1);
    close(f2);
    return 0;
}
