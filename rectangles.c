
typedef struct {
    
  int  firstcolumn;     /* column on the screen where the window begins */
  int  columns_no;     /* number of column in the window  */
  
  int  firstrow;     /* row on the screen where the window begins */
  int  rows_no;     /* number of rows in the window  */
  
  int  lastrow, lastcol; /*Last available gap*/   
  
  int  last_line;
  int  bg_color; /* the background colour for this window */
  int  fg_color; /* the foreground colour for this window */
 
  int  ch_effect; /* the character effect for this window */
} _Rectangles