#include "world.h"
#include "space.h"
#include "object.h"
#include "space.h"
#include "player.h"
#include "game_ours.h"
#include "types.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/*#define NDEBUG*/

struct _World{
    Space **places;  // World's places
    int n_spaces; // Number of the world's places
    Object **stuff; // Objects around the world
    int n_objects; // Number of objects
    npc **npcs; // People around the world
    int n_npcs; // Number of npcs
    Player *me; // Who the fuck are you!
};

// Initialization of the structure "World" 
World * World_Ini(){
    World * w;
    w = (World *)malloc(sizeof(World));
    assert(w != NULL);
    w->n_npcs = 0;
    w->n_objects = 0;
    w->n_spaces = 0;
    w->places = NULL;
    w->stuff = NULL;
    w->npcs = NULL;
    w->me = NULL;
    return w;
}

// Free the structure "World"
void World_Obliterate(World * w){
    int i;
    assert(w != NULL);
    for(i = 0; i < w->n_spaces; i++){
        Space_Obliterate(w->places[i]);
    }
    for(i = 0; i < w->n_npcs; i++){
        Npc_Obliterate(w->n_npcs[i]);
    }
    for(i = 0; i < w->n_objects; i++){
        Object_Obliterate(w->object[i]);
    }
    Player_Oblaterate(w->player);
    free(w);
}
Player * World_get_player(World * w){
    assert(w != NULL);
    return w->me;
}
Space * World_get_space(World * w, int s_id){
    int i;
    assert(w != NULL);
    for(i = 0; i < w->n_spaces; i++){
        if(Space_getID(w->places[i]) == s_id) return w->places[i];
    }
    return NULL;
}
Object * World_get_object(World * w, int o_id){
    int i;
    assert(w != NULL);
    for(i = 0; i < w->n_objects; i++){
        if(Object_getID(w->stuff[i]) == o_id) return w->stuff[i];
    }
    return NULL;
}
NPC * World_get_N(World * w, int npc_id){
    int i;
    assert(w != NULL);
    for(i = 0; i < w->n_npcs; i++){
        if(NPC_getID(w->npcs[i]) == o_id) return w->npcs[i];
    }
    return NULL;
}

// Fill the structure World ("create" it). This function will be public
World * World_create(char * objectfile, char * npcfile, char * spacefile){
    World * w = NULL;
    
    assert(playerfile != NULL);
    assert(objectfile != NULL);
    assert(npcfile != NULL);
    assert(spacefile != NULL);
    
    w = World_Ini();
    if(w != NULL) return NULL;
    
    /*w->me = game_readPlayer(playerfile);*/
    /*w-me = Player_create(atributos);*/
    w->stuff = game_readObject(objectfile/*, &(w->n_objects)*/);
    if(w->stuff == NULL){
        World_Obliterate(w);
        return NULL;
    }
    w->npcs = game_readNpc(npcfile/*, &(w->n_npcs)*/);
    if(w->npcs == NULL){
        World_Obliterate(w);
        return NULL;
    }
    w->places = game_readSpace(spacefile/*, &(w->n_spaces)*/);
    if(w->places == NULL){
        World_Obliterate(w);
        return NULL;
    }
}
#endif