/*cop.c*/
#include <types.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


typedef struct{
    char * name;
    dfunk f;
}assoc;
struct _cop{
    int n_assoc;
    assoc **a;
};

cop * cop_create(){
    cop c = (cop *) malloc(sizeof(cop));
    c->n_assoc = 0;
    c->a = NULL;
}

Status cop_assoc(cop * c, char * name, dfunk f){
    assoc ass = (assoc *) malloc(sizeof(assoc));
    ass->name = name;
    ass->f = f;
    
    c->a = realloc(c->a, (c->n_assoc + 1) * sizeof(c->a[0]));
    c->a[c->n_assoc++] = ass;
    return OK;
}

double cop_execute(cop * c, char * name, double x, double y){
    int i;
    for(i = 0; i <= c->n_assoc; i++){
        if (!strcmp(name, c->a[i]->name)){
            return(*(c->a[i]->f))(x,y);
        }
    }
}