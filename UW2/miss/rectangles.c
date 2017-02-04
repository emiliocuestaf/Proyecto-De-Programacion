#include "rectangles.h"
#include <string.h>
#include <memory.h>
#include "colors.h"



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
    rec_style(rec);
   move_cursor(rec,col,row);
   printf("%c",c);
   fflush(stdout);
   return OK;
}

Status rec_writeplayer(Rectangle* rec, int row, int col , char c){
   if(rec==NULL) return ERROR;
   rec_style(rec);
   move_cursor(rec,col,row);
   printf(ANSI_COLOR_YELLOW "%c" ANSI_COLOR_GREEN,c);
   fflush(stdout);
   return OK;
}

Status rec_writeenemy(Rectangle* rec, int row, int col , char c){
   if(rec==NULL) return ERROR;
   rec_style(rec);
   move_cursor(rec,col,row);
   printf(ANSI_COLOR_RED "%c" ANSI_COLOR_GREEN,c);
   fflush(stdout);
   return OK;
}

Status rec_writeici(Rectangle* rec, int row, int col , char c){
   if(rec==NULL) return ERROR;
   rec_style(rec);
   move_cursor(rec,col,row);
   printf(ANSI_COLOR_CYAN "%c" ANSI_COLOR_GREEN,c);
   fflush(stdout);
   return OK;
}

Status rec_writeblood(Rectangle* rec, int row, int col, char c){
  if(rec==NULL) return ERROR;
   rec_style(rec);
   move_cursor(rec,col,row);
   printf(ANSI_COLOR_BGRED "%c" ANSI_COLOR_GREEN,c);
   fflush(stdout);
   return OK;
}
/*Also copied*/
Status rec_writestring(Rectangle* rec, int row, int col, char* str){
	char *nl_p;
    char save, av_space;

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
    } 
    else{
        if (nl_p) *nl_p = '\n';
        rec->last_line = row;
    }
    return OK;
}


Status rec_writestring_v2(Rectangle* rec, int row, int col, char* str){
 	int r1, c1;
 	rec_style(rec);
	c1= rec->firstcol;
	r1= rec->firstrow;
	printf("%c[%d;%dH",27,row+r1,col+c1);
	printf("%s", str);
    return OK;
}


void rec_printborder(Rectangle* rec){

int i, r1, c1, rn, cn;
r1= rec->firstrow;
c1=rec ->firstcol;
rn=rec->nrows;
cn=rec->ncols;

printf("%c[%d;%dH", 27, r1, c1);
printf("+");	
fflush(stdout);



for (i=1; i<rn; i++){
	printf("%c[%d;%dH", 27, i+r1, c1);
	printf("|");
}

printf("%c[%d;%dH", 27, rn+r1, c1);
printf("+");



for (i=1; i<cn; i++){
	printf("%c[%d;%dH", 27, r1+rn, i+c1);
	printf("-");
}

printf("%c[%d;%dH", 27, rn+r1, c1+cn);
printf("+");

for (i=1; i<rn; i++){
	printf("%c[%d;%dH", 27, r1+i, cn+c1);
	printf("|");
}


printf("%c[%d;%dH", 27, r1, c1+cn);
printf("+");

for (i=1; i<cn; i++){
	printf("%c[%d;%dH", 27, r1, i+c1);
	printf("-");
}

return;
}