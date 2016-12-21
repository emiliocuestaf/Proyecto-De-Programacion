#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "rectangles.h"
#include "space.h"


#define NORTH    0
#define SOUTH    1
#define EAST     2
#define WEST     3
#define HERE     4


typedef struct _intr Intr;

/*posibles funciones*/
Intr* intr_ini();

void intr_setspaces(Intr* intr, Space** spaces);

void intr_printborders(Intr* intr);
/*Intrf* intrf_create(int nrows, int ncols, char **map);*/

void intr_obliterate(Intr* intr);

void  intr_writestring(Intr* intr, char* str, int select, int row, int  col);


void intr_changemap(Intr* intr, int id);

void intr_moveplayer(Intr* intr);

void intr_refresh(Intr* intr);

/*
intrf_print()


Status intrf_writechar(int x, int y, Rectangle* rec)
    
intrf_playerini();

intrf_moveplayer();

intrf_setfieldbgcolor();

intrf_setfieldfgcolor();

intrf_setmap();

intrf_printmap();

intrf_fieldrefresh();

intrf_setddatabgcolor();

intrf_setdatafgcolor();

intrf_printdata();

intrf_datarefresh();

intrf_setinsertgapbgcolor();

intrf_setinsertgapfgcolor();

intrf_printinsertgap();

intrf_insertgapread();

intrf_settextgapbgcolor();

intrf_settextgapfgcolor();

intrf_printextgap();

intrf_textgaprefresh();
*/


#endif



