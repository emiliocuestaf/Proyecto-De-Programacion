#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "object.h"
#include "npc.h"
/*#define NDEBUG*/

    
struct _Npc {
    char* name;
    int id;  // Each kind of object has its own id. (-1 if not defined)
    int locat; // If -1 the npc is dead or doesn't exist any more, otherwise the number is the space where the objects is. -2=not defined 
    int coord[2]; //(-1,-1)=not defined
    Desc* desc[100];
    int number_desc;
    char symbol; 
};

struct _Desc{
    int mission;
    int phase;
    char* description;


};

//Initialization of the structure Npc
Npc* Npc_ini(){
    Npc * n;
    
    n = (Npc *)malloc(sizeof(Npc));
    
    n->name=NULL;
    n->id=-1;
    n->locat=-2;
    n->coord[0]=-1;
    n->coord[1]=-1;
    n->symbol= '@'; 
    n->number_desc=0;
    for(int i=0; i<100; i++)
        n->desc[i]=NULL;

    
    return n;
    
}
//Objects memory freeing
void Npc_obliterate(Npc* n){
    int i;
    
    assert(n!=NULL);
    
    if(n->name){
        free(n->name);}

    for(i=0; i < n->number_desc; i++){
        free(n->desc[i]->description);
        free(n->desc[i]);
    }
    
    free(n);
    
    return;
    
}

//Sets the name of an object
Status Npc_setname(Npc * n, char * name){
    
    assert(n!=NULL);
    assert(name!=NULL);
    
    if(n->name){
         free(n->name);
    }
    
    n->name=(char*)malloc(sizeof(char)*(strlen(name)+1));
    if(!n->name) return ERROR;
    
    strcpy(n->name,name);
    
    return OK;
}
//Gets the name of an object
char* Npc_getname(Npc * n){
    
    assert(n!=NULL);
    assert(n->name!=NULL);
    
    
    return n->name;
    
}

//Sets the id of an object
Status Npc_setid(Npc * n, int id){
    assert(n!=NULL);
    assert(id>=0);
    
    n->id=id;
    
    return OK;
}
//Gets the id of an object
int Npc_getid(Npc * n){
    
    assert(n!=NULL);
    
    return n->id;
}

//Sets objects location
Status Npc_setlocation(Npc * n, int location){
    
    assert(n!=NULL);
    assert(location>=-1);
    
    n->locat=location;
    
    return OK;
}
//Gets objects location 
int Npc_getlocation(Npc * n){
    
    assert(n!=NULL);
    return n->locat;
}


Status Npc_setcoordinatex(Npc * n, int c1){
    assert(n!=NULL);
    assert(c1>=-1);
    
    n->coord[0]=c1;
    return OK;
}



Status Npc_setcoordinatey(Npc * n, int c2){
    assert(n!=NULL);
    assert(c2>=-1);
    
    n->coord[1]=c2;
    return OK;
}



int Npc_getcoordinatex(Npc * n){
    
    assert(n!=NULL);
    return n->coord[0];
    
}

int Npc_getcoordinatey(Npc * n){
   
    assert(n!=NULL);
    return n->coord[1];

}

/*******************************************
Descriptions
********************************************/

Status Npc_setdescription(Npc * n, int mission, int phase, char * descr){
    
    assert(n!=NULL);
    assert(descr!=NULL);

    char* aux;


    n->desc[n->number_desc]=(Desc*)malloc(sizeof(Desc));

    /*Finds description Struct*/
    Desc* desc=(n->desc[n->number_desc]);
        
    
    /*Sets numeric parameters for Description Struct*/
    desc->mission=mission;
    desc->phase=phase;
    
    /*Set char description*/
    aux=(char*)malloc(sizeof(char)*(strlen(descr)+1));
    if(!aux) return ERROR;
    
    strcpy(aux,descr);

    n->desc[n->number_desc]->description = aux;
    
    n->number_desc++;

    return OK;
}

//Gets objects description
char * Npc_getdescription(Npc * n, int mission, int phase){
    int i;
    assert(n!=NULL);
 
    Desc** desc;
    desc=n->desc;
    for(i = 0; i < 100; i++)
        if(desc[i] != NULL && desc[i]->mission == mission && desc[i]->phase == phase){
            /* da pérdidas de memoria
            char* aux;
            aux= (char*) malloc(strlen(desc[i]->description)+1);
            strcpy(aux, desc[i]->description);
            return aux;*/
            return desc[i]->description;
            }
        
    
    return NULL;
}


//Sets objects power
Status Npc_setsymbol(Npc * n, char sym){
    
    assert(n!=NULL);
    
    n->symbol=sym;
    return OK;
}
//Gets objects power
char Npc_getsymbol(Npc * n){
        
    assert(n!=NULL);
    
    return n->symbol;
}
