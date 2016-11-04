
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


/*typedef struct{
    int coord x;
    int coord y;
    char entity;
} Space_entity;*/


struct _Space{
    /*Identification*/
    int id; /*id of the Space*/
    Bool light_on; /*True if I can see the Space*/
    char* name; 
    char* desc; /*description of the Space*/
    Bool locked; /* if the room is locked->TRUE*/   
    
    /*Adjointed rooms*/
    struct _Space* neigh[4];  /*id of neigh rooms*/

    /*Map*/
    int heigh;
    int width;
    char** map;
};


Space* Space_ini(){
    Space* s;
    int i;
    
    s = (Space*) malloc (sizeof(Space));
    if(!Space)
        return NULL;
        
    s->id=0;
    s->light_on = FALSE;
    s->name = NULL;
    s->desc = NULL;
    s->locked = TRUE;
    
    for(i=0; i<4 ;i++){
        s->neigh[i]=NULL;
    }
    
    s->heigh = 0;
    s->width = 0;
    s->map = NULL;
    
    return s;
}

Space** Space_ini_array(int tamanio){
    
    Space** space = (Space**)malloc(tamanio*sizeof(Space*));
    
    if (space == NULL)
        return NULL;
    
    return space;
}


Status Space_obliterate(Space* s){
    int i;
    
    if(s == NULL)
        return ERROR;
    free(s->name);
    free(s->desc);
    for(i=0; i<4; i++){
        if(s->neigh[i] != NULL)
            Space_obliterate(s->neigh[i]);
    }
    free(s->neigh);
    
    /*FREE Space MAP????????*/
    
    free(s);
    return OK;
}

    /*Identification*/
    
Status Space_setID(Space*s, int id){
    if(s==NULL)
        return ERROR;
    
    s->id = id;
    return OK;
}

int Space_getID(Space*s){
    if(s==NULL)
        return -1;
        
    return s->id;
}

Status Space_setLight(Space*s, Bool l){
    if(s == NULL)
        return ERROR;
    s->light_on = l;
    
    return OK;
}

Bool Space_getLight(Space*s){
    if(s == NULL)
        return -1;
    return s->light_on;
}

Status Space_setName(Space*s, char* name){
    int aux;
    
    if (s == NULL || name == NULL)
        return ERROR;
    else if (s->name != NULL)
        free(s->name);
    
    aux = strlen(name) + 1;
    
    s->name = (char*) malloc(aux * sizeof (char));
    
    if(!(s->name))
        return ERROR;
    
    strcpy(s->name, name);
    
    return OK;
}

char* Space_getName(Space*s){
    if(s == NULL)
        return NULL;
        
    return s->name;
}

Status Space_setDesc(Space*s, char* desc){
    int aux;
    
    if (s == NULL || desc == NULL)
        return ERROR;
    else if (s->desc != NULL)
        free(s->desc);
    
    aux = strlen(desc) + 1;
    
    s->desc = (char*) malloc(aux * sizeof (char));
    
    if(!(s->desc))
        return ERROR;
    
    strcpy(s->desc, desc);
    
    return OK;
}

char* Space_getDesc(Space*s){
    if (s ==  NULL)
        return NULL;
    return s->desc;
}

Status Space_setIsLocked(Space*s, Bool b){
    if(s == NULL)
        return ERROR;
    s->locked = b;
    
    return OK;
}
Bool Space_getIsLocked(Space*s){
    if(s == NULL)
        return ERROR;
    
    return s->locked;
}

    /*Adjointed rooms*/
    
Status Space_setNeighRoom(Space*s1, Space*s2, Move m){
    Move aux;
    
    if(s1 == NULL || s2 == NULL || m < 0 || m > 4)
        return ERROR;
        
    s1->neigh[m] = s2;
    
    /*Miramos que vecino es s1 con respecto a s2*/
    
    switch(m){
        case(up):
           aux = down;
            break;
            
        case(down):
            aux= up;
            break;
            
        case(left):
            aux = right;
            break;
            
        default:
            aux = left;
    }
    
    s2->neigh[aux] = s1;
    
    return OK;
    
}
Space* Space_getNeighRoom(Space*s, Move m){
    if(s == NULL || s->neigh[m] == NULL)
        return NULL;
    return s->neigh[m];
}

    /*Map*/
    
Status Space_setHeigh(Space*s, int h){
    if(s == NULL || h < 0)
        return ERROR;
        
    s->heigh = h;
    return OK;
}
int Space_getHeigh(Space*s){
    if(s == NULL)
        return -1;
        
    return s->heigh;
}

Status Space_setWidth(Space*s, int w){
    if(s == NULL || w < 0)
        return ERROR;
        
    s->width = w;
    return OK;
}
int Space_getWidth(Space*s){
    if(s == NULL)
        return -1;
        
    return s->width;
}

Status Space_setMap(Space*s, char* mapName);
Status Space_drawMap(Space*s);

    /*Helpful function*/
    
Status Space_setAll(Space*s, int id, Bool lights, char* name, char* desc, Bool isLock, int heigh, int width){
    if(s == NULL)
        return ERROR;
    if(Space_setID(s, id) == ERROR || Space_setLight(s, lights) == ERROR || Space_setName(s,desc) == ERROR ||
    Space_setDesc(s, desc) == ERROR || Space_setIsLocked(s, isLock) == ERROR || Space_setHeigh(s, heigh) == ERROR || 
    Space_setWidth(s, width) == ERROR )
        return ERROR;
        
    return OK;
}

    /*Move*/
    
Status Space_move(Space*s, Move m);

    /*Space_entity*/
    
/*Status Space_entitySet(int coordX, int coordY, char entity);*/