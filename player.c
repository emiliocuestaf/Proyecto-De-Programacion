#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include <assert.h>

/*#define NDEBUG*/


struct _Player{
    int space; // ID of space where you are at the moment
    int x;
    int y;
    int rank; 
    char* name;
} ;

Player* player_ini(int space, int max_object, int rank, int X, int Y){
    Player* p;
    p = (Player*) malloc(sizeof(Player));
    assert(p!=NULL);
    p->space= space;
    p->rank=rank;
    p->x= X;
    p->y=Y;
    
    return p;
}

//Player INI functions
Status player_setName(Player* p, char* c){
    assert(p!=NULL);
    assert(c!=NULL);
    strcpy(p->name, c);
    return OK;
}

Status player_obliterate(Player* p){
    assert (p!=NULL);
    free(p);
    p=NULL;
    return OK;
}


Status player_changeRank(Player* p, int rank){
    assert (p != NULL);
    p->rank=rank;
    return OK;
}




//PLayer SPACE functions
Status player_moveSpaces(Player* p, int SpaceID){
    assert(p!=NULL);
    p->space= SpaceID;
    return OK;
} 

Bool player_isIn (Player* p, int SpaceID ){
    assert(p!=NULL);
    if (p->space==SpaceID)
        return TRUE;
    else
        return FALSE;

}

int player_whereIsPlayer (Player* p){
    assert(p!=NULL);
    return p->space;
}


//Player OBJCT functions

/*Object** player_getInventory(World* w){
    assert (w!=NULL);
    Object** o;
    int i, j=0;
    for (i=0; i<w->n_objects; i++){
        if (-1==object_getid(w->stuff[i])){
            o[j]=w->stuff;
            j++;
        }
    }
    return o;
} */

/* int player_getNoObjects(World* w){
    assert (w!=NULL);
    int i, j=0;
    for (i=0; i<w->n_objects; i++){
        if (-1==object_getid(w->stuff[i])){
            j++;
        }
    }
    return J;
} */

/*Bool player_overencumbered(Player* p, World* w){
    assert(p!=NULL);
    assert(w!=NULL);
    if(p->max_object=player_getNoObjects(w))
        return TRUE;
    else 
        return FALSE;
} */

/*Status player_PickUp(Player* p, Object *o){
    assert(p !=NULL);
    assert(o !=NULL);
    Object_setlocation(o, -1);
    return OK;
}

Status player_useObject(Player* p, Object* );

Status player_Drop(Player* p, Object* o ){
    assert(p != NULL);
    assert(o != NULL);
    Object_setlocation(o, p->space);
    return OK;
}*/