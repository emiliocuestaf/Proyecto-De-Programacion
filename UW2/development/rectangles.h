/*Highly inspired on Simone Santini's Code*/
#ifndef RECTANGLE_H
#define RECTANGLE_H
 
#include <stdio.h>
#include <stdlib.h>  
#include "types.h"  
 
struct _Rectangle{
    
  int  firstcol;     /* column on the recreen where the window begins */
  int  ncols;     /* number of column in the window  */
  
  int  firstrow;     /* row on the recreen where the window begins */
  int  nrows;     /* number of rows in the window  */
  
  int  lastcol; /*Last available gap*/   
  int  lastrow;	
  
  int  last_line; /*Last point where you wrote*/


  int  backgcol; /* the background colour for this window */
  int  foregcol; /* the foreground colour for this window */
 
};

typedef struct _Rectangle Rectangle;


Rectangle* rec_create(int frow, int fcol, int nrows, int ncols, int backcol, int forecol);

void rec_obliterate(Rectangle* rec);

void rec_clear(Rectangle* rec);

int rec_getbackgcol(Rectangle* rec);

Status rec_setbackgcol(Rectangle* rec, int color);

int rec_getforegcol(Rectangle* rec);

Status rec_setforegcol(Rectangle* rec, int color);

void rec_style(Rectangle* rec);



Status rec_writechar(Rectangle* rec, int row, int col , char c);
Status rec_writeplayer(Rectangle* rec, int row, int col , char c);
Status rec_writeenemy(Rectangle* rec, int row, int col , char c);
Status rec_writeici(Rectangle* rec, int row, int col , char c);
Status rec_writeblood(Rectangle* rec, int row, int col, char c);

Status rec_writestring(Rectangle* rec, int row, int col, char* str);

Status rec_writestring_v2(Rectangle* rec, int row, int col, char* str);

void rec_printborder(Rectangle* rec);

#endif
