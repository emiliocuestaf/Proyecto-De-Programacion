#include "world.h"
#include "space.h"
#include "object.h"
#include "space.h"
#include "player.h"
#include "gameours.h"
#include "types.h"
#include "interface.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/*#define NDEBUG*/

struct _World{
    Space **places;  // World's places
    int n_spaces; // Number of the world's places
    Object **stuff; // Objects around the world
    int n_objects; // Number of objects
    Npc **npcs; // People around the world
    int n_npcs; // Number of npcs
    Player *me; // Who the fuck are you!
    Intr *interface;
    
};
 void Spaces_free(Space ** s, int n_spaces){
    int i;
    assert(s != NULL);
    
    for(i = 0; i < n_spaces; i++){
        Space_obliterate(s[i]);
    }
    free(s);
}
static void Objects_free(Object ** o, int n_objects){
    int i;
    assert(o != NULL);
    
    for(i = 0; i < n_objects; i++){
        Object_obliterate(o[i]);
    }
    free(o);
}
static void Npcs_free(Npc ** n, int n_npcs){
    int i;
    assert(n != NULL);
    
    for(i = 0; i < n_npcs; i++){
        Npc_obliterate(n[i]);
    }
    free(n);
}

// Initialization of the structure "World" 
World * World_Ini(){
    World * w;
    w = (World *)malloc(sizeof(World));
    assert(w != NULL);
    w->n_npcs = 0;
    w->n_objects = 0;
    w->n_spaces = 0;
    w->interface = NULL;
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
    
    Spaces_free(w->places, w->n_spaces);
    
    Objects_free(w->stuff, w->n_objects);
    
    
    Npcs_free(w->npcs, w->n_npcs);
    
    player_obliterate(w->me);
    free(w);
}
Player * World_get_player(World * w){
    assert(w != NULL);
    return w->me;
}
Intr * World_get_interface(World * w){
    assert(w != NULL);
    return w->interface;
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
        if(Object_getid(w->stuff[i]) == o_id) return w->stuff[i];
    }
    return NULL;
}
Npc * World_get_npc(World * w, int npc_id){
    int i;
    assert(w != NULL);
    for(i = 0; i < w->n_npcs; i++){
        if(Npc_getid(w->npcs[i]) == npc_id) return w->npcs[i];
    }
    return NULL;
}
Space ** World_get_spaceS(World * w){
    assert(w != NULL);
    return w->places;
}
Object ** World_get_objectS(World * w){
    assert(w != NULL);
    return w->stuff;
}
Npc ** World_get_npcS(World * w){
    assert(w != NULL);
    return w->npcs;
}
/* Number of Npcs */
int World_get_numberNpc(World * w){
    assert(w != NULL);
    return w->n_npcs;
}
/* Number of Objects */
int World_get_numberObject(World * w){
    assert(w != NULL);
    return w->n_objects;
}
/* Number of Spaces */
int World_get_numberSpace(World * w){
    assert(w != NULL);
    return w->n_spaces;
}

//INTERFAZ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Fill the structure World ("create" it). This function will be public
World * World_create(char * objectfile, char * npcfile, char * spacefile, char * playerfile){
    World * w = NULL;
    
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