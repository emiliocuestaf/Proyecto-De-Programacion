#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <types.h>
#include <file.h>

#define MAXLINE 200

/*#define NDEBUG*/
Status readfile(char * file, int n_spaces, int n_objects){
    FILE * f;
    char buff[MAXLINE], c;
    assert(file);
    
    f = fopen(file, "r");
    assert(f);
    gets(buff);
    while(buff!=EOF){
        if(!strcmp(buff, "object")){
            gets;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }else if(!strcmp(buff, "player")){
        
        }else if(!strcmp(buff, "space")){
        
        }
    }
}
Object ** readObject(char * file){
    char buf[MAXLINE];
    char * aux;
    int
    if(!f) return NULL;
    
    f = fopen(file, "r");
    if(!f) return NULL;
    
    fgets(buf, MAXLINE - 1, f);
    aux = atoi (strtok(buf, ));
    caca = aux (strcpy)
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
}
//dejadme esto a mi (Alejo) voy a probar una cosa este finde
/*{
    int neigh[4];
}
{
    Space * neigder;
    
}*/