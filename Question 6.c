///Ici nous allons utiliser les threads pour accélerer le processus de calcul le md5 des 1000 fichiers !

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "md5.h"
#include <pthread.h>
void* maFonction(void* data)
{
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

  while( ( bytes = fread( buf, sizeof( char ), sizeof( buf ) - 1, fp ) ) <=1000 )
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
bool hash_md5_file(const char *file)
{
     /*                  ****Lire les fichiers
                         ***retourner un pointeur qui contient
                         les donnees
                         ***md5 hashage
                         ***save le hex dans le fichier CHECKSUM.MD5
                         */
     FILE                *fp,*out;
     char                *data;
     char                output[]="CHECKSUM.MD5";
     static  char   HEX_DATA[31];
     md5_state_t     state;
     md5_byte_t      digest[16];
     if(file==NULL){
                    return false;
                    }
     fp=fopen(file,"rb");
     if(fp==NULL){
                  return false;
                  }
     data=readFile(fp); //malloc and memset sont effectuer dans ===>readFile()
     if(data==NULL){
                    return false;
                    }
            //MD5 HASH ALGORITHM
            md5_init(&state);
            md5_append(&state,(const md5_byte_t  *)data,strlen(data));
            md5_finish(&state,digest);
            int i=0;
            for(i;i<16;i++){
                 snprintf(HEX_DATA+i*2,sizeof(HEX_DATA),"%02x",digest[i]);
                 }
                 fclose(fp);

              out=fopen(output,"a+");
              if(out==NULL){
                            return false;
                            }
                            fprintf(out,"MD5 (%s)= ",file);
                            fprintf(out,"%s\n",HEX_DATA);
                            //clean && close
                            fflush(out);
                            fclose(out);

     return true;
}
char *strCopy( char * str )
{
  if( !str )
  {
    return NULL;
  }

  char *n = ( char * )malloc( strlen( str ) + 1 );
  memcpy( n, str, strlen( str ) + 1 );

  return n;
}

}

int main(int argc, char *argv[])
{
pthread_t thread;// On crée un thread
pthread_create(&thread, NULL, maFonction, NULL);// Permet d'exécuter le fonction maFonction
en parallèle
while(i=0 ; i<=1000 ; i++)
{

    if(!hash_md5_file("../main.c"))
        {
         perror("fichier:");
        }else
        {
         puts("Hashage...OK");
        }
pthread_join(thread, NULL);
return EXIT_SUCCESS;
}
  return 0;
}
