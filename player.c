#include <string-h>
#include "player.h"
#include "object.h"
#include "space.h"

typedef struct{
    int space; // ID of space where you are at the moment
    int x;
    int y;
    int max_object; 
    int health; 
    char* name;
}Player;

Player* player_ini(int space, int max_object, int health, int X, int Y){
    Player* p;
    p= (player*) malloc(sizeof(Player));
    assert(p!=NULL);
    p->space= space;
    p->max_object=max_object;
    p->health=health;
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
    return OK
}


Status player_changeHealth(int health){
    assert (p!=NULL);
    p->health=health;
}


Status player_isAlive(Player* p){
    if(p->health>0)
        return TRUE;
    else
        return FALSE;
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

Status player_move_InSpace (Player* p, int incrX, int incrY){
    Space *s; 
    int i, Xmax, Ymax;
    assert(p!=NULL);
    
    ID= player_whereIsPlayer(p);
    
    //Search for the pointer to the space your in
    for (i=0; i<world->n_places&&flag=0; i++){
        if (Space_getID(world->places[i])== ID)
            flag =1;
    }
    
    s= world->places[i];
    
    Xmax= Space_getHeigh(s);
    Ymax = Space_getWidth(s);
    
    if (p->x+incrX<=Xmax)
        p->x+=incrX;
        
    if (p->y+incrY<=Ymax)
        p->y+=incrY;
        
    return OK;
    
}


//Player OBJCT functions
Object** player_getInventory(World* w){
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
}

int player_getNoObjects(World* w){
    assert (w!=NULL);
    int i, j=0;
    for (i=0; i<w->n_objects; i++){
        if (-1==object_getid(w->stuff[i])){
            j++;
        }
    }
    return J;
}

Bool player_overencumbered(Player* p, World* w){
    assert(p!=NULL);
    assert(w!=NULL);
    if(p->max_object=player_getNoObjects(w))
        return TRUE;
    else 
        return FALSE;
} 
Status player_PickUp(Player* p,, object *o){
    assert(p!=NULL);
    assert(!=NULL);
    object_setlocation(o, -1);
    return OK;
}

Status player_useObject(Player* p,object* );

Status player_Drop(Player* p, object* o ){
    assert(p!=NULL);
    assert(0!=NULL);
    object_setlocation(o, p->space);
    return OK;
}