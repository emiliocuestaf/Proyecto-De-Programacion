
#ifndef space_H
#define space_H

#include "types.h"


/*typedef struct{
    int coord x;
    int coord y;
    char entity;
} Space_entity;*/


typedef struct _Space Space;

    /*Doors*/
int doIleave(Space *s, int r, int c, int* ndoor);
Status Space_doorSetLock(Space *s, int ndoor, Bool locked);
Status Space_doorSetCoord(Space *s, int ndoor, int row, int col);
Status Space_doorSetDir(Space *s, int ndoor, int dir);
Status Space_SetnumberDoors(Space*s, int ndoors);
Status Space_doorSetNdoor(Space*s, int ndoor, int ndoor2);
Status Space_doorSetOne(Space *s, int ndoor, int dir, int row, int col, Bool locked, int ndoor2);
int Space_doorGetCol(Space *s, int ndoor);
int Space_doorGetRow(Space *s, int ndoor);
int Space_getNdoors(Space*s);

    
Space* Space_ini(int ndoors);
Space** Space_ini_array(int tamanio);
Status Space_obliterateMap(Space* s);
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

Status Space_changeChar(Space* s, char symbol, int row, int col);
Status Space_eraseChar(Space* s, int row, int col);

    /*Helpful function*/
    
Status Space_setAll(Space*s, int id, Bool lights, char* name, char* desc, /*Bool isLock,*/ int heigh, int width);

    /*Move*/
    
Status Space_move(Space*s, Move m);

    /*Space_entity*/
    
/*Status Space_entitySet(int coordX, int coordY, char entity);*/




#endif