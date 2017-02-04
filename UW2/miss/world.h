#ifndef WORLD_H
#define WORLD_H
#include "space.h"
#include "object.h"
#include "player.h"
#include "npc.h"
#include "types.h"
#include "interface.h"
typedef struct _World World;

/***************************************************
* Function: world_Ini  Fecha: 15-10-2016     
* Autores: Segmentation Fault                     
*                                                 
* Initialization of the structure "World"                                                  
* Arguments: -                   
*                                                
* Returns: World* without information                           
***************************************************/
World * World_Ini();

/***************************************************
* Function: world_Obliterate Fecha: 15-10-2016     
* Autores: Segmentation Fault                     
*                                                
* Free the structure "World"                                               
* Arguments:  World* o!=NULL                     
*                                                
* Returns: -                          
***************************************************/
void World_Obliterate(World * w);

// Add a Space to the World
//Status add_Space(World * w);

// Add an Object to the World
//Status add_Object(World * w);

// Add the Player to the World
//Status add_Player(World * w);

// Set n spaces to the World
//Status set_N_Spaces(World * w, int n_spaces);

// Set the number of objects into the structure 
//Status * set_N_Objects(World * w, int n_objects);

// Set the number of objects into the structure 
//Status * set_Npcs(World * w, int n_npcs);

/***************************************************
* Function: world_Create Fecha: 15-10-2016     
* Autores: Segmentation Fault                     
*                                                 
* Fill the structure World ("create" it) with the information of two given files
* This function will be public                                                
* Arguments:  char* spacefile, char objfile              
*                                                
* Returns: World* with its information                         
***************************************************/
World * World_create(Object** objects, Space ** spaces, Npc ** npcs, int * nob, int * nsp, int * nnpc);
Player * World_get_player(World * w);
Space * World_get_space(World * w, int s_id);
Object * World_get_object(World * w, int o_id);
Npc * World_get_npc(World * w, int npc_id);
Space ** World_get_spaceS(World * w);
Object ** World_get_objectS(World * w);
Npc ** World_get_npcS(World * w);
Intr * World_get_interface(World * w);
int World_get_numberObject(World * w);
int World_get_numberNpc(World * w);
int World_get_numberSpace(World * w);
int World_get_mission(World * w);
Status World_set_mission(World * w, int miss);
int World_get_phase(World * w);
Status World_set_phase(World * w, int phase);

Status World_actualize(World * w, int miss, int phase);

void Spaces_free(Space ** s, int n_spaces);
void Objects_free(Object ** o, int n_objects);
void Npcs_free(Npc ** n, int n_npcs);
void World_add_interface(World * w, Intr * intr);
#endif