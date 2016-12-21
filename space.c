
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "types.h"
#include "space.h"

typedef struct {
    int r, c;
    int dir,ndoor;
    Bool locked;
} door;


struct _Space{
    /*Identification*/
    int id; /*id of the Space*/
    Bool light_on; /*True if I can see the Space*/
    char* name; 
    char* desc; /*description of the Space*/
    /*Bool locked;  if the room is locked->TRUE*/   
    
    /*Adjointed rooms*/
    /*int neigh[4];  id of neigh rooms*/

    /*Map*/
    int heigh;
    int width;
    char** map;

    int n_doors;
    door **dlist;
    
};

/*doors*/

int doIleave(Space *s, int r, int c, int* ndoor) {
    int i;
    assert(s != NULL);
    *ndoor = -1;
    for (i=0; i<s->n_doors; i++) {
        if (s->dlist[i]->r == r && s->dlist[i]->c == c){
            if (s->dlist[i]->locked == TRUE) {
                return 100+s->dlist[i]->dir;
            }    
            else{
                *(ndoor) = s->dlist[i]->ndoor;
                return s->dlist[i]->dir;
            }
        }
    }
    return -1;
}

Status Space_doorSetLock(Space *s, int ndoor, Bool locked){
    assert(s != NULL);
    if(s->dlist == NULL || s->dlist[ndoor] == NULL) return ERROR;
    s->dlist[ndoor]->locked = locked;
    return OK;
}

Status Space_doorSetCoord(Space *s, int ndoor, int row, int col){
    assert(s != NULL);
    if(s->dlist == NULL || s->dlist[ndoor] == NULL) return ERROR; 
    s->dlist[ndoor]->r = row;
    s->dlist[ndoor]->c = col;
    return OK;
}

Status Space_doorSetDir(Space *s, int ndoor, int dir){
    assert(s != NULL);
    if(s->dlist == NULL || s->dlist[ndoor] == NULL) return ERROR; 
    s->dlist[ndoor]->dir = dir;
    return OK;
}

Status Space_doorSetNdoor(Space*s, int ndoor, int ndoor2){
    assert(s != NULL);
    if(s->dlist == NULL || s->dlist[ndoor] == NULL) return ERROR;
    s->dlist[ndoor]->ndoor = ndoor2;
    return OK;
}

Status Space_doorSetOne(Space*s, int ndoor, int dir, int row, int col, Bool locked, int ndoor2){
    assert(s != NULL);
    if(s->dlist == NULL || s->dlist[ndoor] == NULL) return ERROR;
    if(Space_doorSetCoord(s, ndoor, row, col) == ERROR) return ERROR;
    if(Space_doorSetLock(s, ndoor, locked) == ERROR) return ERROR;
    if(Space_doorSetDir(s, ndoor, dir) == ERROR) return ERROR;
    if(Space_doorSetNdoor(s, ndoor, ndoor2) == ERROR) return ERROR;
    
    return OK;
}

int Space_doorGetRow(Space *s, int ndoor){
    assert(s != NULL);
    if(s->dlist == NULL || s->dlist[ndoor] == NULL) return -1;
    return s->dlist[ndoor]->r;
}

int Space_doorGetCol(Space *s, int ndoor){
    assert(s != NULL);
    if(s->dlist == NULL || s->dlist[ndoor] == NULL) return -1;
    return s->dlist[ndoor]->c;
}


Status Space_SetnumberDoors(Space*s, int ndoors){
    assert(s != NULL);
    s->n_doors = ndoors;
    return OK;
}

Status doors_ini(Space*s){
    int i;
    assert(s != NULL);
    s->dlist = (door**) malloc (s->n_doors*sizeof(door*));
    if(s->dlist == NULL) return ERROR;
    
    for(i=0; i < s->n_doors; i++){
        s->dlist[i] = (door*) malloc (sizeof(door));
        if(s->dlist[i] == NULL){
            for(i--;i>=0; i--){
                free(s->dlist[i]);
            }
            free(s->dlist);
            return ERROR;
        }
        s->dlist[i]->r = 0;
        s->dlist[i]->c = 0;
        s->dlist[i]->locked = TRUE;
        s->dlist[i]->dir = 0;
    }
    return OK;
}

Status doors_obliterate(Space*s){
    int i;
    assert(s != NULL);
    if(s->dlist == NULL || s->n_doors == 0) return OK;
    
    for(i=0; i< s->n_doors; i++){
        free(s->dlist[i]);
    }
    free (s->dlist);
    return OK;
}

int Space_getNdoors(Space* s){
    assert(s != NULL);
    return s->n_doors;
}


Space* Space_ini(int ndoors){
    Space* s;
    
    assert(ndoors >= 0);
    
    s = (Space*) malloc (sizeof(Space));
    if(!s)
        return NULL;
        
    s->id=0;
    s->light_on = FALSE;
    s->name = NULL;
    s->desc = NULL;
    s->heigh = 0;
    s->width = 0;
    s->map = NULL;
    s->n_doors = ndoors;
    
    if(doors_ini(s) == ERROR){
        free(s);
        return NULL;
    }
    /*
    for(i=0; i<4 ;i++){
        s->neigh[i]=-1;  si cogemos la segunda opción seria "==-1"
    }*/
    
    return s;
}

Space** Space_ini_array(int tamanio){
    
    Space** space = (Space**)malloc(tamanio*sizeof(Space*));
    
    if (space == NULL)
        return NULL;
    
    return space;
}

Status Space_obliterateMap(Space* s){
    int i;
    assert(s != NULL);
    
    if(s->map == NULL) return OK;
        
    for(i=0; i < (s->heigh) ; i++){
        free(s->map[i]);
    }    
    
    free(s->map);
    
    return OK;
}


Status Space_obliterate(Space* s){
    assert(s != NULL);
    
    free(s->name);
    free(s->desc);
    
    if(Space_obliterateMap(s) == ERROR){
        doors_obliterate(s);
        free(s);
        return ERROR;}
    if(doors_obliterate(s) == ERROR){
        free(s);
        return ERROR;}
    
    free(s);
    return OK;
}

    /*Identification*/
    
Status Space_setID(Space*s, int id){
    assert(s != NULL);
    
    s->id = id;
    return OK;
}

int Space_getID(Space*s){
    assert(s != NULL);
        
    return s->id;
}

Status Space_setLight(Space*s, Bool l){
    assert(s != NULL);
    s->light_on = l;
    
    return OK;
}

Bool Space_getLight(Space*s){
    assert(s != NULL);
    return s->light_on;
}

Status Space_setName(Space*s, char* name){
    int aux;
    
    assert(s != NULL || name != NULL);
    if (s->name != NULL)
        free(s->name);
    
    aux = strlen(name) + 1;
    
    s->name = (char*) malloc(aux * sizeof (char));
    
    if(!(s->name))
        return ERROR;
    
    strcpy(s->name, name); 
    
    return OK;
}

char* Space_getName(Space*s){
    assert(s != NULL);
        
    return s->name;
}

Status Space_setDesc(Space*s, char* desc){
    int aux;
    
    assert(s != NULL || desc != NULL);
    if (s->desc != NULL)
        free(s->desc);
    
    aux = strlen(desc) + 1;
    
    s->desc = (char*) malloc(aux * sizeof (char));
    
    if(!(s->desc))
        return ERROR;
    
    strcpy(s->desc, desc);
    
    return OK;
}

char* Space_getDesc(Space*s){
    assert(s != NULL);
    return s->desc;
}

    /*Map*/
    
Status Space_setHeigh(Space*s, int h){
    assert(s != NULL || h > 0);
        
    s->heigh = h;
    return OK;
}
int Space_getHeigh(Space*s){
    assert(s != NULL);
        
    return s->heigh;
}

Status Space_setWidth(Space*s, int w){
    assert(s != NULL || w > 0);
        
    s->width = w;
    return OK;
}
int Space_getWidth(Space*s){
    assert(s != NULL);
        
    return s->width;
}

Status Space_setMap(Space*s, char** map){
    char** copymap;
    int i;
    assert(s != NULL || map != NULL);
    
    /*If the space already has a map, we obliterate it*/
    if (s->map != NULL)
        Space_obliterateMap(s);
    
    copymap = (char**) malloc ((s->heigh)*sizeof(char*));
    if(copymap == NULL) return ERROR;
    for (i=0; i < s->heigh; i++){
        copymap[i] = (char*) malloc ((s->width +1)*sizeof(char));
        if(copymap[i] == NULL) return ERROR;
        copymap[i] = strcpy(copymap[i], map[i]);
    }
    s->map = copymap;    
    return OK;
}

char** Space_getMap(Space*s){
    assert(s != NULL);
        
    return s->map;
        
}
Status Space_drawMap(Space*s){
    int i, rows;
    
    assert(s != NULL);
    
    if(s->map == NULL) return ERROR;
        
    rows = Space_getHeigh(s);
    if(rows == -1) return ERROR;
    
    for(i=0; i < rows; i++){
        printf("%s", s->map[i]);
    }
    
    return OK;
}

Status Space_changeChar(Space* s, char symbol, int row, int col){
    assert(s != NULL);
    if(s->map == NULL) return ERROR;
    if(row >= s->heigh || col >= s->width) return ERROR;
    s->map[row][col] = symbol;
    return OK;
}

Status Space_eraseChar(Space* s, int row, int col){
    assert(s != NULL);
    if(s->map == NULL) return ERROR;
    if(row >= s->heigh || col >= s->width) return ERROR;
    s->map[row][col] = ' ';
    return OK;
}

    /*Helpful function*/
    
Status Space_setAll(Space*s, int id, Bool lights, char* name , char* desc, /*Bool isLock,*/ int heigh, int width){
    assert(s != NULL);
    if(Space_setID(s, id) == ERROR || Space_setLight(s, lights) == ERROR || Space_setName(s,name) == ERROR ||
    Space_setDesc(s, desc) == ERROR/* || Space_setIsLocked(s, isLock) == ERROR */ || Space_setHeigh(s, heigh) == ERROR || 
    Space_setWidth(s, width) == ERROR)
        return ERROR;
        
    return OK;
}

    /*Move*/
    
/*Status Space_move(Space*s, Move m);*/

    /*Space_entity*/
    
/*Status Space_entitySet(int coordX, int coordY, char entity);*/
