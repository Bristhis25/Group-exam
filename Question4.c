#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<errno.h>
#include<ctype.h>
#include<sys/types.h>
#include<md5.h>
///buffer maximal
#define MAX_BUF 1024
///lire le fichier
char *readFile(FILE *fp);
///generer le hash
bool hash_md5_file(const char *file);
char *strCopy(char *str);
int main(int argc, char *argv[])
{
    if(!hash_md5_file("../main.c"))
    {
        perror("fichier:")
    }
    else
    {
        puts("Hashage...OK")
    }
    #ifdef WIN32
    getch();
    #endif // WIN32
    return 0;
}
char *readFile(FILE *fp)
{
    if(!fp)
    {
        return NULL;
    }
    char *output = NULL;
    char buff[MAX_BUF];
    int bytes, byteCount = 0;
    memset(buff,0,sizeof(buff));
    while(bytes = fread(buff, sizeof(char),sizeof(buff)-1,fp))>0)
    {
        if(!output)
            {
                output = (char *)malloc(bytes + 1);
                memcpy(output,buff,bytes + 1);
            }

    else
    {
        char *oldstr = strCopy(output);
        output = (char*)realloc(output, byteCount + bytes + 1);
        memcpy(output, oldstr, byteCount);
        free (oldstr);
        memcpy(output + byteCount,buff,bytes + 1);
    }
    byteCount+= bytes;
    memset(buff,0,sizeof(buff));
    }
    return output;
}
bool hash_md5_file(const char *file);
{
    FILE *fp,*out;
    char *data;
    char output[]="CHECKSUM.MD5";
    static char HEX_DATA[31];
    md5_state_t state;
    md5_byte_t digest[16];
    if(file==NULL)
    {
        return false;
    }
    fp=fopen(file,"rb");
    if(fp==NULL)
    {
        return false;
    }
    data=readFile(fp);
    if(data==NULL)
    {
        return false;
    }
    md5_init(&state);
    md5_append(&state,(const md5_byte_t *)data,strlen(data));
    md5_finish(&state,digest);
    int i=0;
    for(i;i<16;i++)
    {
        snprintf(HEX_DATA+i*2,sizeof(HEX_DATA),"%02x"digest[i]);
    }
    fclose(fp);
    out=fopen(output,"a+");
    if(out==NULL)
    {
        return false;
    }
    fprintf(out,"MD5(%s))=",file);
    fprintf(out, "%s\n",HEX_DATA);
    fflush(out);
    fclose(out);
    return true;
}
char *strCopy(char *str)
{
    if(!str)
    {
        return NULL;
    }
    char *n = (char *)malloc(strlen(str)+1);
    memcpy(n,str,strlen(str)+1);
    return n;
}
