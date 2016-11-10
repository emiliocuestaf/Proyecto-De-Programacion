#include "rectangles.h"
#include <string.h>
#include <memory.h>

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


/*Important private functions*/
/*87% copied from Santini's*/
void move_cursor(Rectangle* rec, int col, int row){
    if(row < 0) row=0;                            /*Here we work using the internal coordinates of the rectangle*/  
    if(col < 0) col=0;                            
    if(col >= rec->ncols) col= rec->ncols-1;      
    if(row >= rec->nrows) row= rec->nrows-1;

    row+=(rec->firstrow)+1;  /*We pass them to global coordinates of the terminal*/
    col+=(rec->firstcol)+1;  /*We add 1 because te erecape cope begins in 0*/   

                
	printf("%c[%d;%dH",27,row,col); /*This is an ANSI Erecape Code to move the cursor to the coord [row,col]*/
}

/*This function "initialice" the printstyle of a rectangle*/
void rec_style(Rectangle* rec){
	printf("%c[%d;%dm", 27, rec->backgcol, rec->foregcol);
}

Bool rec_isvisible(Rectangle* rec){
	if(rec==NULL) return FALSE;
	if(rec->firstrow<0||rec->firstcol < 0 || rec->nrows <= 0 || rec->ncols <= 0) return FALSE;
	return TRUE;
}




/*Public functions*/

Rectangle* rec_create(int frow, int fcol, int nrows, int ncols, int backgcol, int foregcol){

	Rectangle* rec;

	rec=(Rectangle*)malloc(sizeof(Rectangle));
	if(rec==NULL) return NULL;

	rec->firstcol=fcol;
	rec->ncols=ncols;
	rec->firstrow=frow;
	rec->nrows=nrows;
	rec->backgcol=backgcol;
	rec->foregcol=foregcol;

	rec->lastcol=fcol+ncols-1;
	rec->lastrow=frow+nrows-1;

	return rec;
}

  
  
void rec_obliterate(Rectangle* rec){
	if(rec!=NULL)
		free(rec);
	return;
}

/*100% copied*/
void rec_clear(Rectangle* rec){
    char *buf;
    int i;
  
    rec->last_line = 0;
    if(rec_isvisible(rec)==FALSE) return;

    buf = (char *) malloc((rec->ncols + 1) * sizeof (char));
    memset(buf, ' ', rec->ncols); /*Fills the string with " " */
    buf[rec->ncols] = 0;  /*End of string character*/
    rec_style(rec);    
    for (i = rec->firstrow; i < rec->firstrow + rec->nrows; i++) { /*prints on each row*/
        move_cursor(rec, i - rec->firstrow, 0); 
        printf("%s", buf);
    }
    fflush(stdout);
    free(buf);
    return;
}

int rec_getbackgcol(Rectangle* rec){
	if(rec!=NULL)
		return rec->backgcol;
	return ERROR;
}

Status rec_setbackgcol(Rectangle* rec, int color){
    if(rec!=NULL)
    	rec->backgcol=color;
    	return OK;
    return ERROR;	
}

int rec_getforegcol(Rectangle* rec){
	if(rec!=NULL)
		return rec->foregcol;
	return ERROR;
}

Status rec_setforegcol(Rectangle* rec, int color){
	if(rec!=NULL)
    	rec->foregcol=color;
    	return OK;
    return ERROR;	
}


Status rec_writechar(Rectangle* rec, int row, int col , char c){
   if(rec==NULL) return ERROR;
   move_cursor(rec,col,row);
   printf("%c",c);
   fflush(stdout);
   return OK;
}

/*Also copied*/
Status rec_writestring(Rectangle* rec, int row, int col, char* str){
	char *nl_p;
    char save, av_space, ret;

    if (!rec_isvisible(rec)) return ERROR;
    if (row >= rec->nrows || col >= rec->ncols) return ERROR;

    nl_p = strchr(str, '\n');
    if (nl_p) *nl_p = 0;

    av_space = rec->ncols - col;
    save = -1;

    if (strlen(str) > av_space) {
        save = str[av_space - 1];
        str[av_space - 1] = 0; /*Sets the string end*/
    }
  
    rec_style(rec);
    move_cursor(rec, row, col);
    printf("%s", str);
    fflush(stdout);
    if (save > 0) {
        str[av_space - 1] = save;
        ret = av_space;
    } else
        ret = strlen(str);

    if (nl_p) *nl_p = '\n';
    rec->last_line = row;
    return OK;

}