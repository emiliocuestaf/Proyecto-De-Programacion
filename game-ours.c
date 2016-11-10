#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "types.h"
#include "lineread.h"
#include "space.h"
#include "object.h"



Space**  game_readSpace(char *fname/*, int * nspaces*/){
  
  FILE *fp = fopen(fname, "r");
  
  char *buf;
  int i,j;
  
  /* *nspaces = atoi(buf = fgetll(fp));*/
  int nmaps = atoi(buf = fgetll(fp));
  
  Space ** spaces = Space_ini_array (nmaps/* *nspaces*/);
  
  assert(spaces);
  
  char*** maps= (char***) malloc (nmaps * sizeof(char**)); /* quiza nspaces en vez de nmaps*/

  assert(maps);
  int bdrow = atoi(buf = fgetll(fp));  
  int bdcol = atoi(buf = fgetll(fp));  
  
  
  for (i=0; i < nmaps/* *nspaces*/; i++){
    spaces[i] = Space_ini();
    assert(spaces[i]);
      
    int id = atoi(buf = fgetll(fp));
    if(id != i){
      printf("ESTAMOS HACIENDO ALGO MAL EN LOS MAPAS LOKO");
      
      for(; i <= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
      
      return NULL;
      
    }
    /*Luces*/
    char *name = fgetll(fp);
    char *desc = fgetll(fp);
    int locked = atoi(buf = fgetll(fp));
    
    if (Space_setAll(spaces[i], id, 0 /*pa que compile, aqui va la luz*/, name, desc, locked, bdrow, bdcol) == ERROR){
      for(; i <= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
      
      return NULL;
    }
    int j;
    int neighs[4];
    
    for (j = 0; j < 4; j++){
      neighs[j] = atoi(buf = fgetll(fp));
    } 
    
    if (Space_setAllNeigh(spaces[i], neighs) == ERROR){
      
      for(; i <= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
      
      return NULL;
    }
    
    char maps**[i] = (char**) malloc (bdrow*sizeof(char*));
    assert(maps[i]);
    
    for (int i=0; i<bdrow; i++) {
      maps[i] = fgetll(fp);
    }
    
    if (Space_setMap(spaces[i], maps**[i]) == ERROR){
      
      for(; i <= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
      
      return NULL;      
    }
    
  }
  
  free (maps);
  
  return maps;
}


Object ** game_readObject(char * file, /* int * nobjects*/){
  
  FILE *fp = fopen(file, "r");
  assert(fp);
  
  char *buf;
  int numaux;
  int i;
  Object **objs;
  
  /* *nobjects = atoi(buf = fgetll(fp));*/
  int nobjects = atoi(buf = fgetll(fp));
  
  objs = (Object **) malloc(nobjects /* *nobjects*/ * sizeof(objs[0]));
  assert(objs);
  for(i = 0; i < nobjects/* *nobjects*/; i++){
    objs[i] = Object_ini();
    assert(objs[i]);
    
    buf = fgetll(fp);
    Object_setname(objs[i], buf);/*Control de errores???*/
    numaux = atoi(buf = fgetll(fp));
    Object_setid(objs[i], numaux);/*Control de errores???*/
    numaux = atoi(buf = fgetll(fp));
    Object_setlocation(objs[i], numaux);/*Control de errores???*/
    numaux = atoi(buf = fgetll(fp));
    Object_setcoordinatex(objs[i], numaux);/*Control de errores???*/
    numaux = atoi(buf = fgetll(fp));
    Object_setcoordinatey(objs[i], numaux);/*Control de errores???*/
    buf = fgetll(fp);
    Object_setdescription(objs[i], buf);/*Control de errores???*/
    buf = fgetll(fp);
    Object_setsymbol(objs[i], buf[0]);/*Control de errores???*/
  }  
  buf = fgetll(fp);
  if(buf != EOF) return NULL;
  
  return objs;
}

Npc ** game_readNpc(char * file, /* *numnpc*/){
  
  FILE *fp = fopen(file, "r");
  assert(fp);
  
  char *buf;
  int numaux;
  int i;
  Npc **npcs;
  
  /* *numnpc = atoi(buf = fgetll(fp));*/
  int numnpc = atoi(buf = fgetll(fp));
  
  npcs = (Npc **) malloc(numnpc /* *numnpc*/ * sizeof(npcs[0]));
  assert(npcs);
  for(i = 0; i < numnpc /* *numnpc*/; i++){
    npcs[i] = Npc_ini();
    assert(objs[i]);
    
    buf = fgetll(fp);
    Npc_setname(npcs[i], buf);/*Control de errores???*/
    numaux = atoi(buf = fgetll(fp));
    Npc_setid(npcsi], numaux);/*Control de errores???*/
    numaux = atoi(buf = fgetll(fp));
    Npc_setlocation(npcs[i], numaux);/*Control de errores???*/
    numaux = atoi(buf = fgetll(fp));
    Npc_setcoordinatex(npcs[i], numaux);/*Control de errores???*/
    numaux = atoi(buf = fgetll(fp));
    Npc_setcoordinatey(npcs[i], numaux);/*Control de errores???*/
    buf = fgetll(fp);
    Npc_setdescription1(npcs[i], buf);/*Control de errores???*/
    buf = fgetll(fp);
    Npc_setdescription2(npcs[i], buf);/*Control de errores???*/
    buf = fgetll(fp);
    Npc_setdescription3(npcs[i], buf);/*Control de errores???*/
    buf = fgetll(fp);
    Npc_setdescription4(npcs[i], buf);/*Control de errores???*/
    buf = fgetll(fp);
    Npc_setdescription5(npcs[i], buf);/*Control de errores???*/
    buf = fgetll(fp);
    Npc_setsymbol(npcs[i], buf[0]);/*Control de errores???*/
  }  
  buf = fgetll(fp);
  if(buf != EOF) return NULL;
  
  return npcs;
}


/*
  Creates the interface reading the data from a text file (given as a
  parameter), and displays it. Returns the interface handle.
*/
intrf *_intrf_ini(char *fname) {
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
}
