#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "types.h"
#include "lineread.h"
#include "space.h"



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
      
      for(; i >= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
      
      return NULL;
      
    }
    /*Luces*/
    char *name = fgetll(fp);
    char *desc = fgetll(fp);
    int locked = atoi(buf = fgetll(fp));
    
    if (Space_setAll(spaces[i], id, 0 /*pa que compile, aqui va la luz*/, name, desc, locked, bdrow, bdcol) == ERROR){
      for(; i >= 0 ; i--){
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
      
      for(; i >= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
      
      return NULL;
    }
    
    char maps[i] = (char**) malloc (bdrow*sizeof(char*));
    assert(maps[i]);
    
    for (int i=0; i<bdrow; i++) {
      maps[i] = fgetll(fp);
    }
    
    if (Space_setMap(spaces[i], maps[i]) == ERROR){
      
      for(; i >= 0 ; i--){
        Space_obliterate(spaces[i]);
      }
      
      return NULL;      
    }
    
  }
  
  free (maps);
  
  return maps;
}

int main (){
  Space** s;
  int i;
  
  s = game_readSpace("mapas.txt");
  if(s == NULL){
    printf("mal");
    return -1;
  }
  
  for(i=0; i < 3; i++){
    printf(" %d %s %s %d", Space_getID(s[i]), Space_getName(s[i]), Space_getDesc(s[i]), Space_getIsLocked(s[i]));
    
  }
  
  return 0;
}