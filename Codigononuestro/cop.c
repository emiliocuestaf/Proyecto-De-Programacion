/*cop.c*/
#include <types.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


typedef struct{
    char * internal;
    dfunk f;
}assoc;
/*esta es la que se rellena desde fichero:*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!RARO dos formatos?
typedef struct {
char * cmd;
char *internal;
int  n_msg;
char **msg;
} ext_cmd;

typedef struct {
ext_cmd **e_lst;  /* The list with the "normal" commands... */
int     ext_no;   /* ...and the number of elements in it    */
ext_cmd *error;   /* The "special" error command            */
assoc **i_lst;  /* List with associations between internal commands and functions */
int     int_no;   /* and the number of elements it contains (0 at the beginning) */
int     int_max;  /* The number of pointers i_lst that are actually allocated    */
} CoP;

CoP * cop_create(){
    CoP * c = (CoP *) malloc(sizeof(CoP));
    c->n_assoc = 0;
    c->a = NULL;
}

Status cop_assoc(CoP * c, char * name, dfunk f){
    assoc * ass = (assoc *) malloc(sizeof(assoc));
    ass->name = name;
    ass->f = f;
    
    c->a = realloc(c->a, (c->n_assoc + 1) * sizeof(c->a[0]));
    c->a[c->n_assoc++] = ass;
    return OK;
}

double cop_execute(CoP * c, char * name, double x, double y){
    int i;
    for(i = 0; i <= c->n_assoc; i++){
        if (!strcmp(name, c->a[i]->name)){
            return(*(c->a[i]->f))(x,y);
        }
    }
}