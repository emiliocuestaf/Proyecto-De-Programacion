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
    char* descr1; // Rookie
    char* descr2; // Sergeant
    char* descr3; // Colonel
    char* descr4; // Lieutenant
    char* descr5; // Captain
    char symbol; 
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
    n->descr1=NULL;
    n->descr2=NULL;
    n->descr3=NULL;
    n->descr4=NULL;
    n->descr5=NULL;
    n->symbol= 'p'; //susceptible de cambioo !!!!!!!!!!!!!!!!! 
    
    return n;
    
}
//Objects memory freeing
void Npc_obliterate(Npc* n){
    
    assert(n!=NULL);
    
    if(n->name){
        free(n->name);}
    if(n->descr1){    
    free(n->descr1);}
    if(n->descr2){    
    free(n->descr2);}
    if(n->descr3){    
    free(n->descr3);}
    if(n->descr4){    
    free(n->descr4);}
    if(n->descr5){    
    free(n->descr5);}
    
    
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
    assert(id>0);
    
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


Status Npc_setdescription1(Npc * n, char * descr){
    
    assert(n!=NULL);
    assert(descr!=NULL);
    
    if(n->descr1) free(n->descr1);
    
    n->descr1=(char*)malloc(sizeof(char)*(strlen(descr)+1));
    if(!n->descr1) return ERROR;
    
    strcpy(n->descr1,descr);

    return OK;
}
Status Npc_setdescription2(Npc * n, char * descr){
    
    assert(n!=NULL);
    assert(descr!=NULL);
    
    if(n->descr2) free(n->descr2);
    
    n->descr2=(char*)malloc(sizeof(char)*(strlen(descr)+1));
    if(!n->descr2) return ERROR;
    
    strcpy(n->descr2,descr);

    return OK;
}
Status Npc_setdescription3(Npc * n, char * descr){
    
    assert(n!=NULL);
    assert(descr!=NULL);
    
    if(n->descr3) free(n->descr3);
    
    n->descr3=(char*)malloc(sizeof(char)*(strlen(descr)+1));
    if(!n->descr3) return ERROR;
    
    strcpy(n->descr3,descr);

    return OK;
}
Status Npc_setdescription4(Npc * n, char * descr){
    
    assert(n!=NULL);
    assert(descr!=NULL);
    
    if(n->descr4) free(n->descr4);
    
    n->descr4=(char*)malloc(sizeof(char)*(strlen(descr)+1));
    if(!n->descr4) return ERROR;
    
    strcpy(n->descr4,descr);

    return OK;
}
Status Npc_setdescription5(Npc * n, char * descr){
    
    assert(n!=NULL);
    assert(descr!=NULL);
    
    if(n->descr5) free(n->descr5);
    
    n->descr5=(char*)malloc(sizeof(char)*(strlen(descr)+1));
    if(!n->descr5) return ERROR;
    
    strcpy(n->descr5,descr);

    return OK;
}
//Gets objects description
char * Npc_getdescription1(Npc * n){
    
    assert(n!=NULL);
    assert(n->descr1!=NULL);
    
    return n->descr1;
}
char * Npc_getdescription2(Npc * n){
    
    assert(n!=NULL);
    assert(n->descr2!=NULL);
    
    return n->descr2;
}
char * Npc_getdescription3(Npc * n){
    
    assert(n!=NULL);
    assert(n->descr3!=NULL);
    
    return n->descr3;
}
char * Npc_getdescription4(Npc * n){
    
    assert(n!=NULL);
    assert(n->descr4!=NULL);
    
    return n->descr4;
}
char * Npc_getdescription5(Npc * n){
    
    assert(n!=NULL);
    assert(n->descr5!=NULL);
    
    return n->descr5;
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

//Copies an object
Npc * Npc_copy(Npc * n){
    Npc * n2;
    
    assert(n!=NULL);

    n2=Npc_ini();
    if(!n2) return NULL;
    
    if(Npc_setname(n2, n->name)==ERROR){
        return NULL;
    }
    
    Npc_setid(n2, n->id);
    Npc_setlocation(n2, n->locat);
    Npc_setcoordinatex(n2, n->coord[0]);
    Npc_setcoordinatey(n2, n->coord[1]);

    
    if(Npc_setdescription1(n2, n->descr1)==ERROR){
        return NULL;
    }
    if(Npc_setdescription2(n2, n->descr2)==ERROR){
        return NULL;
    }
    if(Npc_setdescription3(n2, n->descr3)==ERROR){
        return NULL;
    }
    if(Npc_setdescription4(n2, n->descr4)==ERROR){
        return NULL;
    }
    if(Npc_setdescription5(n2, n->descr5)==ERROR){
        return NULL;
    }
    
    Npc_setsymbol(n2, n->symbol);


    return n2;
}