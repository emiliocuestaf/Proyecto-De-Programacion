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

int Player_get_coordinatex(Player* p){
    
    assert(p!=NULL);
    return p->x;
    
}

int Player_get_coordinatey(Player* p){
    
    assert(p!=NULL);
    return p->y;
    
}

int Player_get_location(Player* p){
    
    assert(p!=NULL);
    return p->space;
    
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

