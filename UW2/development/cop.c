/*cop.c*/
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
// esto esta mal v
#include "interface.h"
#include "lineread.h"
#include "cop.h"
#define NDEBUG 

typedef struct{
    char * internal; /* Internal name */
    pfun f; /* Function associated */
}Assoc;
char * strdup(char*);
int isspace(char);

typedef struct {
char * cmd; /* Comand */
char *internal; /* Internal name */
int  n_ans; /* Number of answers */
char **answers; /* Answers to a comand */
}Ext;

struct _cop {
Ext **exts;  /* The list with the "normal" commands... */
int     n_exts;   /* ...and the number of elements in it    */
Ext *error;   /* The "special" error command            */
pfun error_f; /* Se debe crear por separado */
Assoc **ass;  /* List with associations between internal commands and functions */
int     n_ass;   /* and the number of elements it contains (0 at the beginning) */
};

/* Creates an association */
static Assoc * assoc_ini(char * name, pfun f){
    Assoc * ass;
    
    ass = (Assoc *) malloc(sizeof(Assoc));
    if(!ass) return NULL;
    
    ass->internal = strdup(name);
    ass->f = f;
    
    return ass;
}

static void assoc_free(Assoc * a){
    if(!a)
        return;
    free(a->internal);
    free(a);
}

/* Seeks the function associated to an internal name*/
pfun assoc_search(Cop * c, char * internal){
    int i;
    
    assert(c);
    assert(internal);
    
    for(i = 0; i < c->n_ass; i++){
        if(!strcmp(internal, c->ass[i]->internal))
            return c->ass[i]->f;
    }
    return NULL;
}

 /* Create an Ext */
static Ext * ext_create(FILE * f){
    char * buf;
    int i;
    
    assert(f);
    
    Ext * ext = (Ext *) malloc(sizeof(Ext));
    if(!ext) return NULL;
    
    /* Comand */
    buf = fgetll(f);
    ext->cmd = (char *) malloc(sizeof(char)*(strlen(buf) + 1));
    strcpy(ext->cmd, buf);
    free(buf);
    /* Internal name */
    buf = fgetll(f);
    ext->internal =  (char *) malloc(sizeof(char)*(strlen(buf) + 1));
    strcpy(ext->internal, buf);
    free(buf);
    /* Number of answers */
    ext->n_ans = atoi(buf = fgetll(f));
    free(buf);
    /* Setting answers */
    ext->answers = (char **) malloc(sizeof(ext->answers[0]) * ext->n_ans);
    if(!(ext->answers)){
        free(ext);
        return NULL;
    }
    for(i = 0; i < ext->n_ans; i++){
        buf = fgetll(f);
        ext->answers[i] = (char *) malloc(sizeof(char)*(strlen(buf) + 1));
        strcpy(ext->answers[i], buf);
        free(buf);
    }
    
    return ext;
}

/* Frees an Ext*/
static void ext_free(Ext * e){
    int i;
    
    assert(e);
    
    if(e->cmd) free(e->cmd);
    if(e->internal) free(e->internal);
    if(e->answers){
        for(i = 0; i < e->n_ans; i++){
            if(e->answers[i]) free(e->answers[i]);
        }
        free(e->answers);
    }
    
    free(e);
}
/* Seeks an Ext with a comand */
static Ext * ext_search(Cop * c, char * cmd){
    FILE* fg;
    int i;
    
    assert(c);
    assert(cmd);
    fg=fopen("error_log_search.txt", "w" );
    fprintf(fg, "\ncmd is:%s", cmd);
    
    for(i = 0; i < c->n_exts; i++){
            fprintf(fg, "\n%s", c->exts[i]->cmd);
        if(!strcmp(cmd, c->exts[i]->cmd)){
            fprintf(fg, "Match Found");
            return c->exts[i];}

    }
    fclose(fg);
    return NULL;
}

/* Creates the structure Cop without the associations */
Cop * cop_create(char * file){
    FILE * f;
    int i;
    char *buf;
    Cop * c = (Cop *) malloc(sizeof(Cop));
    if(!c) return NULL;
    
    c->n_ass = 0;
    c->ass = NULL;
    c->error_f = NULL;
    f = fopen(file, "r");
    /* rellenas todo lo referente a externaldesde fichero y luego llamas a assoc para
    rellenar internal-assoc */
    
    /* Number of Ext */
    c->n_exts = atoi(buf = fgetll(f));
    free(buf);
    /* Fill Ext */
    c->exts = (Ext **) malloc(sizeof(c->exts[0]) * c->n_exts);
    for(i = 0; i < c->n_exts; i++){
        c->exts[i] = ext_create(f);
    }
    /* Special Ext error */
    c->error = ext_create(f);
    return c;
}

/* Frees the Cop */
void cop_obliterate(Cop * c){
    int i;
    
    if(!c)
        return;
    /* Free associations */
    if(c->ass){
        for(i = 0; i < c->n_ass; i++){
            if(c->ass[i]) assoc_free(c->ass[i]);
        }
        free(c->ass);
    }
    /* Free externals */
    if(c->exts){
        for(i = 0; i < c->n_exts; i++){
            if(c->exts[i]) ext_free(c->exts[i]);
        }
        free(c->exts);
    }
    /* Free error */
    ext_free(c->error);
    /* Free Cop */
    free(c);
}

/* Makes the association between an internal name and a function pointer */
Status cop_assoc(Cop * c, char * name, pfun f){
    int i;
    Assoc * ass = NULL;
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    FILE * fj;

    fj = fopen("pruebaalejo1.txt", "w");
    fprintf(fj, "estas en cop assoc\n");
    
    if(!strcmp("error", name)){
        fprintf(fj, "es error. hace la asociación se supone.\n");
        c->error_f = f;
        fclose(fj);
        return OK;
    }
    fclose(fj);
    for (i = 0; i < c->n_ass; i++) 
        if (!strcmp(c->ass[i]->internal, name))
            return ERROR;

    ass = assoc_ini(name, f);
    if(!ass){
        printf("Error. no memoria reser Assoc\n");
        return ERROR;
    }
    c->n_ass++;
    c->ass = (Assoc *) realloc(c->ass, (c->n_ass) * sizeof(c->ass[0]));
    c->ass[c->n_ass - 1] = ass;
    return OK;
}

/* Prepares and returns an answer to a comand*/
static char *unpack(char *ans, char *repl) {
    char *ret, *p;
    int n = 0;

    /* count the number of stars in the first string */
    for (p=ans; *p; p++)
        if (*p == '*') n++;
        
    /* allocates the array with enough space for the final string (I add
    1 to store the final zero) */
    ret = (char *) malloc(strlen(ans) + n*strlen(repl) + 1);
    p = ret;
    while (*ans) {
        if (*ans!='*') {
            *p++ = *ans++;
        }
        else {
            strcpy(p, repl);
            p += strlen(repl);
            ans++;
        }
    }
    *p = *ans;
    return ret;
}

/*
Prepares the strings of an external command for execution: returns
an array of prepared strings with the starts removed and replaced
by the name of the predicate
*/
static char ** unpack_answers(Ext *e, char *obj) {
    int i;
    char **ans = (char **) malloc(e->n_ans*sizeof(char *));
    for (i = 0; i < e->n_ans; i++)
        ans[i] = unpack(e->answers[i], obj);
    return ans;
}

/* Executes the comand */
int cop_execute(Cop * c, char * cmd, void * world){
    FILE* f;
    int i;
    char *verb = cmd;
    char **ans;
    int ret;
    int k;
    char *ch;
    Ext *e;

    f=fopen("error_log.txt", "w" );
    fprintf(f, "Starting error log:");

    
    ch = strchr(verb, ' ');
    *ch = 0;
    ch++;
    while(isspace(*ch))
        ch++;
    char *object = ch;
    if(*ch == 0) return 0;
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    e = ext_search(c, verb);
    if (!e) {
        fprintf(f, "\nFunction not found!");
        
        ans = unpack_answers(c->error, verb);
        fprintf(f, "\n%s, %s", verb, ans[0]);
        fclose(f);
        ret = (c->error_f)(world, verb, 0, ans);
        free(ans[0]);
        free(ans);
        return ret;
    }
    else {
        /* Take the possible answers to the comand */
        fprintf(f, "\nUnpacking in process");

        ans = unpack_answers(e, object);
        /* Check if there is any function associated to the internal name */
        for(i = 0; i <= c->n_ass; i++){

            if (!strcmp(e->internal, c->ass[i]->internal)){
                /* Result of the comand */
                    fprintf(f, "\nCommand found");
                    fprintf(f, "\nObject is: %s", object);
                    fclose(f);
                ret = (c->ass[i]->f)(world, object, e->n_ans, ans);

                for ( k=0; k<e->n_ans; k++)
                    free(ans[k]);
                free(ans);
                return ret;
            }
        }
    
    }/* else */
        fprintf(stderr, "Fatal error: internal command %s has no function\n", e->internal);
        exit(1);
    
    //Santini dice que tenemos todo el código mal :) yisus
       
}
