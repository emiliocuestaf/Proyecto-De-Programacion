#include <stdio.h>
#include "npc.h"
#include "lineread.h" 
#include <assert.h>
#include <stdlib.h>




static void Npcs_free(Npc ** n, int n_npcs){
    int i;
    assert(n != NULL);
    
    for(i = 0; i < n_npcs; i++){
        Npc_obliterate(n[i]);
    }
    free(n);
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

int main (){
  Npc** o;
  int i;
  
  o = game_readNpc("npcs.txt");
  if(o == NULL){
    printf("mal");
    return -1;
  }
  
  for(i=0; i < 3; i++){
    printf(" %s %d %d %d %d %s %s %s %s %s %c\n", Npc_getname(o[i]), Npc_getid(o[i]), 
    Npc_getlocation(o[i]), Npc_getcoordinatex(o[i]), Npc_getcoordinatey(o[i]),
    Npc_getdescription1(o[i]), Npc_getdescription2(o[i]), Npc_getdescription3(o[i]), 
    Npc_getdescription4(o[i]), Npc_getdescription5(o[i]),Npc_getsymbol(o[i]));
  }
  Npcs_free(o, 3);
  
  return 0;
}