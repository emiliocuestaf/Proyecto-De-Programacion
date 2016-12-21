#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "loading.h"
#include "types.h"
#include "lineread.h"
#include "space.h"
#include "object.h"
#include "npc.h"



Space**  game_readSpace(char *fname){
  
  FILE *fp = fopen(fname, "r");
  if(fp == NULL)
    return NULL;
  
  char *buf;
  int i,j,id;
  
  int nmaps = atoi(buf = fgetll(fp));
  free(buf);
  
  Space ** spaces = Space_ini_array (nmaps);
  if(spaces == NULL) return NULL;
  char*** maps= (char***) malloc (nmaps * sizeof(char**)); 
  if(maps == NULL){
    free(spaces);
    return NULL;
  }

  int bdrow = atoi(buf = fgetll(fp));
  free(buf);
  int bdcol = atoi(buf = fgetll(fp));
  free(buf);
  
  
  
  for (i=0; i < nmaps/* *nspaces*/; i++){
    int ndoors = atoi(buf = fgetll(fp));
    free(buf);
    spaces[i] = Space_ini(ndoors);
    if(spaces[i] == NULL){
      for(i--; i <= 0; i--)
        Space_obliterate(spaces[i]);
      return NULL;
    }
      
    id = atoi(buf = fgetll(fp));
    free(buf);
        
    if(id != i){
      printf("Something went wrongggg (Hint = game_readSpace)\n");
      
      for(; i >= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
      
      return NULL;
      
    }
    
    char *name = fgetll(fp);
    char *desc = fgetll(fp);
    
    for(j=0; j < ndoors; j++){
      int dir = atoi(buf = fgetll(fp));
      free(buf);
      int drow = atoi(buf = fgetll(fp));
      free(buf);
      int dcol = atoi(buf = fgetll(fp));
      free(buf);
      int locked = atoi(buf = fgetll(fp));
      free(buf);
      int ndoor = atoi(buf = fgetll(fp));
      free(buf);
      if(Space_doorSetOne(spaces[i], j, dir, drow, dcol, locked, ndoor) == ERROR) {
       for(; i >= 0 ; i--){
         Space_obliterate(spaces[i]);
        }
      return NULL;
      }
    }
    
    if (Space_setAll(spaces[i], id, 0, name, desc, bdrow, bdcol) == ERROR){
      for(; i >= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
      
      return NULL;
    }
    free(name);
    free(desc);
    
    maps[i] = (char**) malloc (bdrow*sizeof(char*));
    if(maps[i] == NULL){
      for(; i >= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
    }
    
    
    for (j=0; j<bdrow; j++) {
      buf = fgetll(fp);
      maps[i][j] = buf;
    }
    

    if (Space_setMap(spaces[i], (char**) maps[i]) == ERROR){
      for(; i >= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
      return NULL;      
    }
    
    for (j=0; j<bdrow; j++) {
      free(maps[i][j]);
    }
    free(maps[i]);
  }
  free(maps);
  fclose(fp);
  return spaces;
}


Object ** game_readObject(char * file/*,  int * nobjects*/){
  
  FILE *fp = fopen(file, "r");
  assert(fp);
  
  char *buf;
  int numaux;
  int i;
  Object **objs;
  
  /* *nobjects = atoi(buf = fgetll(fp));*/
  int nobjects = atoi(buf = fgetll(fp));
  free(buf);
  
  objs = (Object **) malloc(nobjects /* *nobjects*/ * sizeof(objs[0]));
  assert(objs);
  for(i = 0; i < nobjects/* *nobjects*/; i++){
    objs[i] = Object_ini();
    assert(objs[i]);
    
    buf = fgetll(fp);
    Object_setname(objs[i], buf);/*Control de errores???*/
    free(buf);
    numaux = atoi(buf = fgetll(fp));
    Object_setid(objs[i], numaux);/*Control de errores???*/
    free(buf);
    numaux = atoi(buf = fgetll(fp));
    Object_setlocation(objs[i], numaux);/*Control de errores???*/
    free(buf);
    numaux = atoi(buf = fgetll(fp));
    Object_setcoordinatex(objs[i], numaux);/*Control de errores???*/
    free(buf);
    numaux = atoi(buf = fgetll(fp));
    Object_setcoordinatey(objs[i], numaux);/*Control de errores???*/
    free(buf);
    buf = fgetll(fp);
    Object_setdescription(objs[i], buf);/*Control de errores???*/
    free(buf);
    buf = fgetll(fp);
    Object_setsymbol(objs[i], buf[0]);/*Control de errores???*/
    free(buf);
  }  
 
  fclose(fp);
  
  return objs;
}

Npc ** game_readNpc(char * file/*,  *numnpc*/){
  
  FILE *fp = fopen(file, "r");
  assert(fp);
  
  char *buf;
  int numaux;
  int i;
  Npc **npcs;
  
  /* *numnpc = atoi(buf = fgetll(fp));*/
  int numnpc = atoi(buf = fgetll(fp));
  free(buf);
  
  npcs = (Npc **) malloc(numnpc /* *numnpc*/ * sizeof(npcs[0]));
  assert(npcs);
  for(i = 0; i < numnpc /* *numnpc*/; i++){
    npcs[i] = Npc_ini();
    assert(npcs[i]);
    
    buf = fgetll(fp);
    Npc_setname(npcs[i], buf);/*Control de errores???*/
    free(buf);
    numaux = atoi(buf = fgetll(fp));
    Npc_setid(npcs[i], numaux);/*Control de errores???*/
    free(buf);
    numaux = atoi(buf = fgetll(fp));
    Npc_setlocation(npcs[i], numaux);/*Control de errores???*/
    free(buf);
    numaux = atoi(buf = fgetll(fp));
    Npc_setcoordinatex(npcs[i], numaux);/*Control de errores???*/
    free(buf);
    numaux = atoi(buf = fgetll(fp));
    Npc_setcoordinatey(npcs[i], numaux);/*Control de errores???*/
    free(buf);
    buf = fgetll(fp);
    Npc_setdescription1(npcs[i], buf);/*Control de errores???*/
    free(buf);
    buf = fgetll(fp);
    Npc_setdescription2(npcs[i], buf);/*Control de errores???*/
    free(buf);
    buf = fgetll(fp);
    Npc_setdescription3(npcs[i], buf);/*Control de errores???*/
    free(buf);
    buf = fgetll(fp);
    Npc_setdescription4(npcs[i], buf);/*Control de errores???*/
    free(buf);
    buf = fgetll(fp);
    Npc_setdescription5(npcs[i], buf);/*Control de errores???*/
    free(buf);
    buf = fgetll(fp);
    Npc_setsymbol(npcs[i], buf[0]);/*Control de errores???*/
    free(buf);
  }  
  
  fclose(fp);
  
  return npcs;
}


Status AllocateObjects(Space** spaces, Object** objects, int nobjects){
  int i;
  int id;
  char c;
  int row, col;
  assert(spaces != NULL);
  assert(objects != NULL);
  
  for(i=0; i < nobjects; i++){
    id = Object_getlocation(objects[i]);
    if(id < 0) return ERROR;
    c = Object_getsymbol(objects[i]);
    row = Object_getcoordinatey(objects[i]);
    col = Object_getcoordinatey(objects[i]);
    if(row < 0 || col < 0) return ERROR;
    if(Space_changeChar(spaces[id], c, row, col) == ERROR) return ERROR;
  }
}

Status AllocateNpcs(Space** spaces, Npc** npcs, int nNpcs){
  int i;
  int id;
  char c;
  int row, col;
  assert(spaces != NULL);
  assert(npcs != NULL);
  
  for(i=0; i < nNpcs; i++){
    id = Npc_getlocation(npcs[i]);
    if(id < 0) return ERROR;
    c = Npc_getsymbol(npcs[i]);
    row = Npc_getcoordinatey(npcs[i]);
    col = Npc_getcoordinatey(npcs[i]);
    if(row < 0 || col < 0) return ERROR;
    if(Space_changeChar(spaces[id], c, row, col) == ERROR) return ERROR;
  }
}

/*
  Creates the interface reading the data from a text file (given as a
  parameter), and displays it. Returns the interface handle.
*/

/*intrf *_intrf_ini(char *fname) {
  FILE *fp = fopen(fname, "r");

  char *buf;

  int rows = atoi(buf = fgetll(fp));  //free(buf);
  int cols = atoi(buf = fgetll(fp));  //free(buf);
  int field = atoi(buf = fgetll(fp));  //free(buf);
  intrf *itf = i_create(rows, cols, field);

  char *caption = fgetll(fp);
  int crow = atoi(buf = fgetll(fp));  //free(buf);
  int ccol = atoi(buf = fgetll(fp));  //free(buf);
  int srow = atoi(buf = fgetll(fp));  //free(buf);
  int scol = atoi(buf = fgetll(fp));  //free(buf);

  i_set_info_caption(itf, caption, crow, ccol, srow, scol);
  
   *caption = fgetll(fp);
   crow = atoi(buf = fgetll(fp));  //free(buf);
   ccol = atoi(buf = fgetll(fp));  //free(buf);
   srow = atoi(buf = fgetll(fp));  //free(buf);
   scol = atoi(buf = fgetll(fp));  //free(buf);

  i_set_info_caption(itf, caption, crow, ccol, srow, scol);
  
  
  int nmaps = atoi(buf = fgetll(fp));

  char player = (buf = fgetll(fp))[0];  //free(buf);
  int prow = atoi(buf = fgetll(fp));  //free(buf);
  int pcol = atoi(buf = fgetll(fp));  //free(buf);
  
  ppp= atoi(buf = fgetll(fp));  //free(buf);
  
  i_set_play_data(itf, player, prow, pcol, pellet, pellet_no);

  int bdrow = atoi(buf = fgetll(fp));  //free(buf);
  int bdcol = atoi(buf = fgetll(fp));  //free(buf);
  
  
  char ***map = (char **) malloc(bdrow*sizeof(char *));
  for (int i=0; i<bdrow; i++) {
    map[i] = fgetll(fp);
  }
  i_set_board(itf, bdrow, bdcol, map);

  fclose(fp);
  
  return itf;
}*/
