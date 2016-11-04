
#ifndef INTERFACE_H
#define INTERFACE_H
 
#include <rectangles.h>  


#define BACKGROUND   40  /* Black background */
#define FOREGROUND   32  /* Green foreground... for a "retro" look */

#define NORTH    0
#define SOUTH    1
#define EAST     2
#define WEST     3
#define HERE     4



typedef struct {
  
  int row_n;                 
  int column_n;                 
  int usefulcols;           
  rectangle *playingfield;      
  rectangle *objects;      
  rectangle *playerinfo;
  int map_rows;             
  int map_cols;             
  char **map;              
  char playerchar;             
  int  pl_ycoord, pl_xcoord;     
  int  objects_number;           
  char *object_chars;        
  int *o_xcoord,*o_ycoord
  int  npcs_number;         
  char *npcs_chars;          
  int *npc_xcoord,*npc_ycoord;
  char *range;      
  int  range_x, range_y;       
  char* openmenu;
  int  opmen_x, openm_y;
  char* interact;
  int  intract_x, intract_y;
  char* save;
  int save_x, save_y;
  
} intrf;


intrf* = i_create(int rows,int  cols,int field);
int i_set_info_caption(intrf *itf, char *caption, int r_cap, int c_cap, int r_info, int c_info);