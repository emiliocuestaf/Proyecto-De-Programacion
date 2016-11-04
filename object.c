#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "types.h"
#include "space.h"
#include "object.h"

/*#define NDEBUG*/

    
struct _Object {
    char* name;
    int id;  // Each kind of object has its own id. (-1 if not defined)
    int locat; // If -1 the player owns the object, otherwise the number is the space where the objects is. -2=not defined 
    int coord[2]; //(-1,-1)=not defined
    char* descr;
    int power; //Indicator of usefulness
};

//Initialization of the structure Object
Object* Object_ini(){
    Object* o;
    
    o=(Object*)malloc(sizeof(Object));
    
    o->name=NULL;
    o->id=-1;
    o->locat=-2;
    o->coord=(-2,-2);
    o->quant=0;
    o->descr=NULL;
    o->power=0;
    
    return o;
    
    
}
//Objects memory freeing
void Object_obliterate(Object* o){
    
    assert(o!=NULL);
    
    if(o->name){
        free(o->name);}
    if(o->descr){    
    free(o->descr);}
    
    free(o);
    
    return;
    
}

//Sets the name of an object
Status Object_setname(Object* o, char*name){
    
    assert(o!=NULL);
    assert(name!=NULL);
    
    if(o->name){
         free(o->name);
    }
    
    o->name=(char*)malloc(sizeof(char)*(strlen(name)+1));
    if(!o->name) return ERR;
    
    strcpy(o->name,name);
    
    return OK;
}
//Gets the name of an object
char* Object_getname(Object* o){
    
    assert(o!=NULL);
    assert(o->name!=NULL);
    
    
    return o->name;
    
}

//Sets the id of an object
Status Object_setid(Object* o, int id){
    assert(o!=NULL);
    assert(id>0);
    
    o->id=id;
    
    return OK;
}
//Gets the id of an object
int Object_getid(Object* o){
    
    assert(o!=NULL);
    
    return o->id;
}

//Sets objects location
Status Object_setlocation(Object* o, int location){
    
    assert(o!=NULL);
    assert(location>=-1);
    
    o->locat=location;
    
    return OK;
}
//Gets objects location 
int Object_getlocation(Object* o){
    
    assert(o!=NULL);
    return o->locat;
}


Status Object_setcoordinatex(Object* o, int c1){
    assert(o!=NULL);
    assert(c1>=-1);
    
    o->coord[0]=c1;
    return OK
}



Status Object_setcoordinatey(Object* o, int c2){
    assert(o!=NULL);
    assert(c2>=-1);
    
    o->coord[1]=c2;
    return OK
}



int Object_getcoordinatex(Object* o){
    
    assert(o!=NULL);
    return o->coord[0];
    
}

int Object_getcoordinatey(Object* o){
   
    assert(o!=NULL);
    return o->coord[1];

}


Status Object_setdescription(Object* o, char*descr){
    
    assert(o!=NULL);
    assert(descr!=NULL);
    
    if(o->descr) free(o->descr);
    
    o->descr=(char*)malloc(sizeof(char)*(strlen(descr)+1))
    if(!o->descr) return ERR;
    
    strcpy(o->descr,descr);

    return OK;
}

//Gets objects description
char* Object_getdescription(Object* o){
    
    assert(o!=NULL);
    assert(o->descr!=NULL);
    
    return o->descr;
}



//Sets objects power
Status Object_setpower(Object* o, int pw){
    
    assert(o!=NULL);
    
    o->power=pw;
    return OK;
}
//Gets objects power
int Object_getpower(Object* o){
        
    assert(o!=NULL);
    
    return o->power;
}

//Copies an object
Object* Object_copy(Object* o1){
    Object* o2;
    
    assert(o!=NULL);

    o2=Object_ini();
    if(!o2) return NULL;
    
    if(object_setname(o2, o1->name)==ERR){
        return NULL;
    }
    
    Object_setid(o2, o1->id):
    Object_setlocation(o2, o1->locat):
    Object_setcoordinatex(o2, o1->coord[0]);
    Object_setcoordinatey(o2, o1->coord[1]);

    
    if(Object_setdescription(o2, o1->descr)==ERR){
        return NULL;
    }
    
    Object_setpower(o2, o1->power);


    return o2;
}

Object* Object_create(char*name, int id, int location, int cx, int cy, char* descr, 
                       int power){
    
    Object* o;
    
    
    o=Object_ini();
    if(!o) return NULL,
    
    if(Object_setname(o,name)==ERR){
        return NULL
    }
    
    Object_setid(o,id);
    Object_setlocation(o,location);
    Object_setcoordinatex(o2, cx);
    Object_setcoordinatey(o2, cy);

    if(Object_setdescription(o,descr)==ERR){
        return NULL
    }
    
    
    Object_setpower(o,power);
    
    
    return o;
}


