#include "world.h"
#include "space.h"
#include "object.h"
#include "space.h"
#include "player.h"
#include "loading.h"
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

void World_add_interface(World* w, Intr* intr){
    assert(w != NULL);
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    FILE * f;
    f = fopen("pruebaalejo.txt", "w");
    fprintf(f, "add_interface antes assert\n");
    

    fprintf(f, "add_interface después assert\n");
    w->interface = intr;
    if(!w->interface){
        fprintf(f, "add_interface interfaz no asignada\n");
    }
    fprintf(f, "add_interface despues asignación\n");
    fclose(f);
}

 void Spaces_free(Space ** s, int n_spaces){
    int i;
    assert(s != NULL);
    
    for(i = 0; i < n_spaces; i++){
        Space_obliterate(s[i]);
    }
    free(s);
}
void Objects_free(Object ** o, int n_objects){
    int i;
    assert(o != NULL);
    
    for(i = 0; i < n_objects; i++){
        Object_obliterate(o[i]);
    }
    free(o);
}
void Npcs_free(Npc ** n, int n_npcs){
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
    w = (World *)malloc(sizeof(w[0]));
    if(w == NULL) return NULL;
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
    int i, id;
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    FILE * f;
    f = fopen("pruebaalejo2.txt", "w");
    assert(w != NULL);
    fprintf(f, "Estamos en World get space. id: %d\n", s_id);
    fprintf(f, "numero espacios: %d\n", w->n_spaces);

    for(i = 0; i < w->n_spaces; i++){
        id = Space_getID(w->places[i]);
        fprintf(f, "Estamos en World get space. id: %d\n", id);
        if(id == s_id){
            fprintf(f, "Id coincide\n");
            fclose(f);
            return w->places[i];
        }
        
    }
    fclose(f);
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


Status World_actualize(World * w, int miss, int phase){
    assert(w != NULL);
    assert(miss >= 0);
    assert(phase >= 0);

    Intr_set_mission(w->interface, miss);
    Intr_set_phase(w->interface, phase);
    
    return OK;
}


// Fill the structure World ("create" it). This function will be public
World * World_create(Object** objects, Space ** spaces, Npc ** npcs, int * nob, int * nsp, int * nnpc){
    World * w = NULL;
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    
    assert(objects != NULL);
    assert(spaces != NULL);
    

    w = World_Ini();
    if(w == NULL) return NULL;
    
    w->stuff = objects/*, &(w->n_objects)*/;
    if(w->stuff == NULL){
        World_Obliterate(w);
        return NULL;
    }
    w->n_objects = *nob;
    /*w->npcs = npcs , &(w->n_npcs) ;
    if(w->npcs == NULL){
        World_Obliterate(w);
        return NULL;
    } */
    w->places = spaces/*, &(w->n_spaces)*/;
    if(w->places == NULL){
        World_Obliterate(w);
        return NULL;
    }
    w->n_spaces = *nsp;

    w->npcs = npcs/*, &(w->n_spaces)*/;
    if(w->npcs == NULL){
        World_Obliterate(w);
        return NULL;
    }
    w->n_npcs = *nnpc;
    
    return w;
}
