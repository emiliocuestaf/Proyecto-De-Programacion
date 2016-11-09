/*Highly inspired on Simone Santini's Code*/
#ifndef RECTANGLE_H
#define RECTANGLE_H
 
#include <stdio.h>
#include <stdlib.h>    
  

typedef struct _Rectangle Rectangle;


Rectangle* rec_create(int frow, int fcol, int nrows, int ncols, int backcol, int forecol);

void rec_obliterate(Rectangle* rec);

void rec_clear(Rectangle* rec);

int rec_getbackgcol(Rectangle* rec);

Status rec_setbackgcol(Rectangle* rec, int color);

int rec_getforegcol(Rectangle* rec);

Status rec_setforegcol(Rectangle* rec, int color);

Status rec_writechar(Rectangle* rec, int row, int col , char c);

Status rec_writestring(Rectangle* rec, int row, int col, char* str);

#endif
