
#include "interface.h"

struct _intrf{
  
  int nrows;
  int ncols;    
  int fieldcols; 
  int fieldrows;                      
  Rectangle *playingfield;
  int datacols;
  int datarows;       
  Rectangle *data;
  int insertrows;
  int insertcols;
  Rectangle* insertgap;
  int map_rows;             
  int map_cols;             
  char **map;                 
};



intrf_create()