#include <stdio.h>
#include "player.h"
#include "lineread.h" 
#include <assert.h>
#include <stdlib.h>


Player * game_readPlayer(char * file/*,  *numnpc*/){
  
  FILE *fp = fopen(file, "r");
  assert(fp);
  
  char *buf;
  int numaux;
  Player *me;
  
  
  
  me = (Player *) malloc(sizeof(me));
  assert(me);
  
  
  numaux = atoi(buf = fgetll(fp));
  Player_setlocation(me, numaux);/*Control de errores???*/
  free(buf);
  numaux = atoi(buf = fgetll(fp));
  Player_setcoordinatex(me, numaux);/*Control de errores???*/
  free(buf);
  numaux = atoi(buf = fgetll(fp));
  Player_setcoordinatey(me, numaux);/*Control de errores???*/
  free(buf);
  numaux = atoi(buf = fgetll(fp));
  Player_setrank(me, numaux);/*Control de errores???*/
  free(buf);
  buf = fgetll(fp);
  Player_setname(me, buf);/*Control de errores???*/
  free(buf);
   
  
  fclose(fp);
  
  return me;
}