#include <stdio.h>
#include "object.h"
#include "lineread.h" 
#include <assert.h>
#include <stdlib.h>


static void Objects_free(Object ** o, int n_objects){
    int i;
    assert(o != NULL);
    
    for(i = 0; i < n_objects; i++){
        Object_obliterate(o[i]);
    }
    free(o);
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

int main (){
  Object** o;
  int i;
  
  o = game_readObject("objetos.txt");
  if(o == NULL){
    printf("mal");
    return -1;
  }
  
  for(i=0; i < 3; i++){
    printf(" %s %d %d %d %d %s %c\n", Object_getname(o[i]), Object_getid(o[i]), Object_getlocation(o[i]), Object_getcoordinatex(o[i]), Object_getcoordinatey(o[i]), Object_getdescription(o[i]), Object_getsymbol(o[i]));
  }
  Objects_free(o, 3);
  
  return 0;
}