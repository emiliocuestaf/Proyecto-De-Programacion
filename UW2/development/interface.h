#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "rectangles.h"
#include "space.h"
#include "object.h"
#include "npc.h"


#define NORTH    0
#define SOUTH    1
#define EAST     2
#define WEST     3
#define HERE     4


typedef struct _intr Intr;

/* Mission and phase */
int Intr_get_mission(Intr * intr);
Status Intr_set_mission(Intr * intr, int miss);
int Intr_get_phase(Intr * intr);
Status Intr_set_phase(Intr * intr, int phase);

/*posibles funciones*/
Intr* intr_ini();

void intr_setspaces(Intr* intr, Space** spaces);
void intr_setobjects(Intr* intr, Object** objects);
void intr_setnpcs(Intr* intr, Npc** npcs);

void intr_printborders(Intr* intr);
/*Intrf* intrf_create(int nrows, int ncols, char **map);*/

void intr_obliterate(Intr* intr);

void  intr_writestring(Intr* intr, char* str, int select, int row, int  col);
void  intr_writechar(Intr* intr, char c, int select, int row, int  col);
void intr_writechoppedstring(Intr* intr, char* str, int select, int row, int col);


void intr_changemap(Intr* intr, int id);
char ** intr_getmap(Intr* intr);

void intr_moveplayer(Intr* intr, char c);

void intr_allocobjects(Intr* intr);

void intr_refresh(Intr* intr);
void intr_reloaddata(Intr* intr);
void intr_printcmdhelp(Intr* intr);
void intr_teleportplayer(Intr* intr, int x, int y, int dir);

void intr_cleargap(Intr* intr, int select);
void intr_clearall(Intr* intr);
/*Player movement*/
int intr_playergetrow(Intr* intr);
int intr_playergetcol(Intr* intr);
int intr_playergetdir(Intr* intr);
int intr_playergetspid(Intr* intr);

void intr_writeenemy(Intr* intr, int y, int x, char c );

void intr_writeici(Intr* intr, int y, int x, char c);

void intr_writeblood(Intr* intr, int y, int x, char c);


#endif
