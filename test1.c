#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "types.h"
#include "lineread.h"
#include "space.h"



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

int main (){
  Space** s;
  int i,j, aux=0;
  int r,c;
  char** mapas;
  
  s = game_readSpace("maps.txt");
  if(s == NULL){
    printf("mal");
    return -1;
  }
  r=0;
  c=0;
  
  for(i=0; i < 14; i++){
    printf("Estamos en el espacio %d: \n %d \n %s \n %s \n", i, Space_getID(s[i]), Space_getName(s[i]), Space_getDesc(s[i]));
    printf("Con mapa: \n");
    mapas = Space_getMap(s[i]);
    for(j=0; j < 30; j++){
      printf("%s\n", mapas[j]);
     }
    aux = Space_getNdoors(s[i]);
    printf("\n Num puertas: %d\n", aux);
    for(j=0; j<aux; j++){
      r = Space_doorGetRow(s[i], j);
      c = Space_doorGetCol(s[i], j);
      printf("Coordenadas puerta: %d, %d \n", r, c);
      Space_changeChar(s[i], 'p', r, c);
    }
    mapas = Space_getMap(s[i]);
    for(j=0; j < 30; j++){
      printf("%s\n", mapas[j]);
    }
  }
  
  
  for(i=0; i < 14; i++){
    Space_obliterate(s[i]);
  }
  free(s);
  
  return 0;
}
