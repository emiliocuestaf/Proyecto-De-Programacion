
#ifndef space_H
#define space_H

#include "types.h"


/*typedef struct{
    int coord x;
    int coord y;
    char entity;
} Space_entity;*/


typedef struct _Space Space;

Space* Space_ini();
Space** Space_ini_array(int tamanio);
Status Space_obliterate(Space* s);

    /*Identification*/
    
Status Space_setID(Space*s, int id);
int Space_getID(Space*s);

Status Space_setLight(Space*s, Bool l);
Bool Space_getLight(Space*s);

Status Space_setName(Space*s, char* name);
char* Space_getName(Space*s);

Status Space_setDesc(Space*s, char* desc);
char* Space_getDesc(Space*s);

Status Space_setIsLocked(Space*s, Bool b);
Bool Space_getIsLocked(Space*s);

    /*Adjointed rooms*/
    
Status Space_setNeighRoom(Space*s1, int idSpace2, Move m);
Status Space_setAllNeigh(Space* s, int id[]);
int Space_getNeighRoom(Space*s, Move m);

    /*Map*/
    
Status Space_setHeigh(Space*s, int h);
int Space_getHeigh(Space*s);

Status Space_setWidth(Space*s, int w);
int Space_getWidth(Space*s);

Status Space_setMap(Space*s, char** map);
char** Space_getMap(Space*s);
Status Space_drawMap(Space*s);

    /*Helpful function*/
    
Status Space_setAll(Space*s, int id, Bool lights, char* name, char* desc, Bool isLock, int heigh, int width);

    /*Move*/
    
Status Space_move(Space*s, Move m);

    /*Space_entity*/
    
/*Status Space_entitySet(int coordX, int coordY, char entity);*/




#endif