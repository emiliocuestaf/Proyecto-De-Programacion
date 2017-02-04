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



Space**  game_readSpace(char *fname, int * nsp){
  
  FILE *fp = fopen(fname, "r");
  if(fp == NULL)
    return NULL;
  
  char *buf;
  int i,j,id;
  
  int nmaps = atoi(buf = fgetll(fp));
  free(buf);
  
  /* Pasamos como argumento el número de mapas */
  *nsp = nmaps;

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


Object ** game_readObject(char * file,  int * nob){
  
  FILE *fp = fopen(file, "r");
  assert(fp);
  
  char *buf;
  int numaux;
  int i;
  int miss[2] = {0,0};
  Object **objs;
  
  /* *nobjects = atoi(buf = fgetll(fp));*/
  int nobjects = atoi(buf = fgetll(fp));
  free(buf);
  
  *nob = nobjects;

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
    miss[0] = atoi(buf = fgetll(fp));
    Object_set_mission(objs[i], miss[0]);
    free(buf);
    miss[1] = atoi(buf = fgetll(fp));
    Object_set_phase(objs[i], miss[1]);
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

Npc ** game_readNpc(char * file, int * nnpc){
  
  FILE *fp = fopen(file, "r");
  assert(fp);
  
  char *buf;
  int numaux;
  int i,j;
  Npc **npcs;
  
  int numnpc = atoi(buf = fgetll(fp));
  free(buf);
  
  *nnpc = numnpc;
  
  npcs = (Npc **) malloc(numnpc /* *numnpc*/ * sizeof(npcs[0]));
  if(npcs == NULL) return NULL;
  
  for(i = 0; i < numnpc; i++){
    npcs[i] = Npc_ini();
    if(npcs[i] == NULL){
      for(;i<=0;i--){
        Npc_obliterate(npcs[i]);
      }
      free(npcs);
      return NULL;
    }
    
    int numdesc = atoi(buf = fgetll(fp));
    free(buf);
    buf = fgetll(fp);
    Npc_setname(npcs[i], buf);/*Control de errores???*/
    free(buf);
    numaux = atoi(buf = fgetll(fp));
    if(numaux != i){
      fprintf(stdout, "Error en game_readNpc (i != id)");
      return NULL;
    }
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
    for(j=0; j<numdesc ; j++){
      int mission = atoi(buf = fgetll(fp));
      int phase = atoi(buf = fgetll(fp));
      buf = fgetll(fp);
      Npc_setdescription(npcs[i], mission, phase, buf);/*Control de errores???*/
      free(buf);
      
    }
  }  
  
  fclose(fp);
  
  return npcs;
}

