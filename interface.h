
#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "rectangles.h"
#include "colors.h"  

#define BACKGROUND   40  /* Black background */
#define FOREGROUND   32  /* Green foreground... for a "retro" look */

#define NORTH    0
#define SOUTH    1
#define EAST     2
#define WEST     3
#define HERE     4



typedef struct _intrf Intrf;


Intrf* intrf_create(char**map, );

intrf_obliterate();

intrf_print();

intrf_writechar();

intrf_writestring();

intrf_playerini();

intrf_moveplayer();

intrf_setfieldbgcolor();

intrf_setfieldfgcolor();

intrf_setmap();

intrf_printmap();

intrf_fieldrefresh();

intrf_setmap();

intrf_setobjectsbgcolor();

intrf_setobjectsfgcolor();

intrf_printobjects();

intrf_objectsrefresh();

intrf_setpinfobgcolor();

intrf_setpinfofgcolor();

intrf_printpinfo();

intrf_inforefresh();

intrf_setcommandsbgcolor();

intrf_setcommandsfgcolor();

intrf_printcommands();

intrf_setinsertgapbgcolor();

intrf_setinsertgapfgcolor();


#endif


