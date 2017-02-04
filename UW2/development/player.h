#ifndef PLAYER_H
#define PLAYER_H
#include "space.h"
#include "object.h"
    
// ESTARÍA BIEN CREAR  GET"DATO" DE TODAS Y ESO XD

typedef struct _Player Player;

//Initialization Functions

Player* player_ini(int space, int max_object, int rank, int X, int Y); //create Player
Status player_obliterate( Player* p); //Destroy Player

//Player Functions

int Player_get_coordinatex(Player* p);
int Player_get_coordinatey(Player* p);
int Player_get_locartion(Player* p);
Status player_changeRank(Player* p, int rank);//modify health
Bool player_isAlive(Player* p);
Status player_setName(Player* p, char* c);


//Space related functions
Status player_moveSpaces(Player* p, int SpaceID); //modify space 
Bool player_isIn (Player* p, int SpaceID ); //is the player in that space?
int  player_whereIsPlayer (Player* p);//Gets the space ID where the player is at
Status player_move_InSpace (Player* p, int coordX, int coordY); //move within a space


//Object Related Functions
/*
Object**  player_getInventory(World* w);
int player_getNoObjects(World* w); */


Bool player_overencumbered(Player* p); // Checks if you are full of objects
Status player_PickUp(Player* p, Object * o);
Status player_useObject(Player* p, Object* o);
Status player_Drop(Player* p, Object* o);

#endif