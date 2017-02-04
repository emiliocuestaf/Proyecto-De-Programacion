#include "copfunctions.h"
#include <stdio.h>
#include "cop.h"
#include <string.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "world.h"
#include "shoot.h"
#include "animations.h"
#include <assert.h>


Object * Object_find(Object ** ob, int nobj, int x, int y, int spid){
    int i;
    
    
    assert(x >= 0);
    assert(y >= 0);
    
    i = 0;
    while(i < nobj){
        if(spid == Object_getlocation(ob[i])){
            if(x == Object_getcoordinatex(ob[i])){
                if(y == Object_getcoordinatey(ob[i]))
                    return ob[i];
            }
        }
        i++;
    }
    
    return NULL;
}

Npc * Npc_find(Npc ** npc, int n_npc, int x, int y, int spid){
    int i;
    
    assert(spid >= 0);
    assert(x >= 0);
    assert(y >= 0);
    
    i = 0;
    while(i < n_npc){
        if(spid == Npc_getlocation(npc[i])){
            if(x == Npc_getcoordinatex(npc[i])){
                if(y == Npc_getcoordinatey(npc[i]))
                    return npc[i];
            }
        }
        i++;
    }
    
    return NULL;
}

/* typedef int (*pfun) (void * world, char * objeto, int n_ans, char ** answers);*/

/* The "objeto" is the symbol that you see in screen */


Status take(void * world, char * objeto, int n_ans, char ** answers){
    World * w;
    Intr * intr;
    int psid; // Id of the space where are you
    int miss[2];

    w = (World *) world;
    intr = World_get_interface(w);
    /* Por definir  esta función */
    
    psid = intr_playergetspid(intr);
    
    miss[0] = Intr_get_mission(intr);
    miss[1] = Intr_get_phase(intr);
    
    

    if(strcmp(objeto, "exam")){
        /* You can only take exams in this universe */
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        return OK;
    }
    if( psid != 10 && psid != 17){
        /* You can only take exams in classrooms */
        intr_writechoppedstring(intr, answers[1], 3, 1, 1);
        return OK;
    }
    if(psid == 17){
        /* There isn't any exam in this classrom today. */
        intr_writechoppedstring(intr, answers[2], 3, 1, 1);
        return OK;
    }
    if(psid == 10){
        /* Examen Edat */
        if(miss[0] == 3 && miss[1] == 2){
            /* M 3 P 2 -> M 3 P 3 */
            World_actualize(w, 3, 3);
            intr_allocobjects(intr);
            intr_writechoppedstring(intr, answers[3], 3, 1, 1);
            return OK;
        }
        /* Examen Cirel */
        if(miss[0] == 7 && miss[1] == 3){
            /* M 7 P 3 -> M 8 P 1 */
            World_actualize(w, 8, 1);
            intr_allocobjects(intr);
            intr_teleportplayer(intr, 1, 1, 1);
            intr_changemap(intr, 25);
            
            return OK;
        }
        /* There isn't any exam in this classrom today. */
        intr_writechoppedstring(intr, answers[2], 3, 1, 1);
        return OK;
    }
    intr_writechoppedstring(intr, "No debería llegar aquí", 3, 2, 1);
    return OK;
}

Status pick(void * world, char * objeto, int n_ans, char ** answers){
    World * w;
    Object ** obs;
    Object * o;
    Space * s;
    char ** map;
    Intr * intr;
    int dir; // Direction of the player
    int x; // Coordinate x of the object
    int y; // Coordinate y of the object
    int numobj; // Number of objects
    int psid; // Id of the space where are you
    int miss[2];
    char * aux;
    char * name;    
    
    w = (World *) world;
    intr = World_get_interface(w);

    dir = intr_playergetdir(intr);
    
    x = intr_playergetcol(intr);
    
    y = intr_playergetrow(intr);
    
    psid = intr_playergetspid(intr);
    
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);
    miss[0] = Intr_get_mission(intr);
    miss[1] = Intr_get_phase(intr);
    
    s = World_get_space(w, psid);
    
    map = Space_getMap(s);
    
    
    
    
    aux = (char *) malloc(200 * sizeof(char));

    if(strlen(objeto) > 1 || objeto[0] != 'o'){
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        free(aux);
        return OK;
    }
    /* UP, DOWN, RIGHT, LEFT */
    if(dir == 0){
        y--;
        if(map[y][x] != 'o'){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            free(aux);
            return 0;
        }
        o = Object_find(obs, numobj, x, y, psid);
        if(o != NULL){
            
            name = Object_getname(o);
            // Actualizamos la estructura del objeto
            if(!strcmp(name, "Charm Book") && miss[0] == 9 && miss[1] == 1){
                /* M 9 P 1 -> M 9 P 2 */
                World_actualize(w, 9, 2);
                intr_allocobjects(intr);
                s = World_get_space(w, 16);
                Space_doorSetLock(s, 0, FALSE);
            }
            Object_setlocation(o, -1);
            
            sprintf(aux, "%s %s.", answers[2], Object_getname(o));
            map[y][x] = ' ';
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            intr_refresh(intr);
            /* You pick "whatever" */
            intr_writechoppedstring(intr, aux, 3, 1, 1);
            /* Description of the object */
            intr_writechoppedstring(intr, Object_getdescription(o), 3, 2, 1);
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            free(aux);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        free(aux);
        return ERROR;
    }else if(dir == 1){
        y++;
        if(map[y][x] != 'o'){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            free(aux);
            return 0;
        }
        o = Object_find(obs, numobj, x, y, psid);
        if(o != NULL){
            
            name = Object_getname(o);
            // Actualizamos la estructura del objeto
            if(!strcmp(name, "Charm Book") && miss[0] == 9 && miss[1] == 1){
                /* M 9 P 1 -> M 9 P 2 */
                World_actualize(w, 9, 2);
                intr_allocobjects(intr);
                s = World_get_space(w, 16);
                Space_doorSetLock(s, 0, FALSE);
            }
            Object_setlocation(o, -1);
            
            sprintf(aux, "%s %s.", answers[2], Object_getname(o));
            map[y][x] = ' ';
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            intr_refresh(intr);
            /* You pick "whatever" */
            intr_writechoppedstring(intr, aux, 3, 1, 1);
            /* Description of the object */
            intr_writechoppedstring(intr, Object_getdescription(o), 3, 2, 1);
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            free(aux);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        free(aux);
        return ERROR;
    }else if(dir == 2){
        x++;
        if(map[y][x] != 'o'){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            free(aux);
            return 0;
        }
        o = Object_find(obs, numobj, x, y, psid);
        if(o != NULL){
            
            name = Object_getname(o);
            // Actualizamos la estructura del objeto
            if(!strcmp(name, "Charm Book") && miss[0] == 9 && miss[1] == 1){
                /* M 9 P 1 -> M 9 P 2 */
                World_actualize(w, 9, 2);
                intr_allocobjects(intr);
                s = World_get_space(w, 16);
                Space_doorSetLock(s, 0, FALSE);
            }
            Object_setlocation(o, -1);
            
            sprintf(aux, "%s %s.", answers[2], Object_getname(o));
            map[y][x] = ' ';
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            intr_refresh(intr);
            /* You pick "whatever" */
            intr_writechoppedstring(intr, aux, 3, 1, 1);
            /* Description of the object */
            intr_writechoppedstring(intr, Object_getdescription(o), 3, 2, 1);
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            free(aux);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        free(aux);
        return ERROR;
    }else if(dir == 3){
        x--;
        if(map[y][x] != 'o'){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            free(aux);
            return 0;
        }
        o = Object_find(obs, numobj, x, y, psid);
        if(o != NULL){
            
            name = Object_getname(o);
            // Actualizamos la estructura del objeto
            if(!strcmp(name, "Charm Book") && miss[0] == 9 && miss[1] == 1){
                /* M 9 P 1 -> M 9 P 2 */
                World_actualize(w, 9, 2);
                intr_allocobjects(intr);
                s = World_get_space(w, 16);
                Space_doorSetLock(s, 0, FALSE);
            }
            Object_setlocation(o, -1);
            
            sprintf(aux, "%s %s.", answers[2], Object_getname(o));
            map[y][x] = ' ';
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            intr_refresh(intr);
            /* You pick "whatever" */
            intr_writechoppedstring(intr, aux, 3, 1, 1);
            /* Description of the object */
            intr_writechoppedstring(intr, Object_getdescription(o), 3, 2, 1);
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            free(aux);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        free(aux);
        return ERROR;
    }

    intr_writechoppedstring(intr, answers[3], 3, 1, 1);
    /* else */
    
    free(aux);
    return OK;
}

Status drop(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    World * w;
    Object ** obs;
    Object * o;
    Space * s;
    char aux;
    char ** map;
    Intr * intr;
    int ret = 0; // Flag that says if you have the object to drop
    int flag = 0; // Tells if the object exists in the world
    int x; // Coordinate x of the object
    int y; // Coordinate y of the object
    int numobj; // Number of objects
    int psid; // Id of the space where are you
    int dir;
    
    w = (World *) world;
    intr = World_get_interface(w);
    dir = intr_playergetdir(intr);
    x = intr_playergetcol(intr);
    y = intr_playergetrow(intr);
    psid = intr_playergetspid(intr);
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);
    s = World_get_space(w, psid);
    map = Space_getMap(s);
    
    for(i = 0; i < numobj; i++){
        if(!strcmp(objeto, Object_getname(obs[i]))){
            flag = 1;
            if(Object_getlocation(obs[i]) == -1){
                ret = 1;
                o = obs[i];
            }
        }
    }
    
    if(flag == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* The object doesn't exist */
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        return OK;
    }
    if(ret == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* You don't have that object */
        intr_writechoppedstring(intr, answers[1], 3, 1, 1);
        return OK;
    }
    
    aux = Object_getsymbol(o);

    /* UP, DOWN, RIGHT, LEFT */
    if(dir == 0){
        if(map[y-1][x] == ' '){
            Object_setlocation(o, psid);
            Object_setcoordinatex(o, x);
            Object_setcoordinatey(o, y-1);
            map[y-1][x] = aux;

            intr_refresh(intr);
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            return OK;
        }else{
            intr_writechoppedstring(intr, answers[3], 3, 1, 1);
            return OK;
        }
    }else if(dir == 1){
        if(map[y+1][x] == ' '){
            Object_setlocation(o, psid);
            Object_setcoordinatex(o, x);
            Object_setcoordinatey(o, y+1);
            map[y+1][x] = aux;

            intr_refresh(intr);
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            return OK;
        }else{
            intr_writechoppedstring(intr, answers[3], 3, 1, 1);
            return OK;
        }
    }else if(dir == 2){
        if(map[y][x+1] == ' '){
            Object_setlocation(o, psid);
            Object_setcoordinatex(o, x+1);
            Object_setcoordinatey(o, y);
            map[y][x+1] = aux;

            intr_refresh(intr);
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            return OK;
        }else{
            intr_writechoppedstring(intr, answers[3], 3, 1, 1);
            return OK;
        }
    }else if(dir == 3){
        if(map[y][x-1] == ' '){
            Object_setlocation(o, psid);
            Object_setcoordinatex(o, x-1);
            Object_setcoordinatey(o, y);
            map[y][x-1] = aux;

            intr_refresh(intr);
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            return OK;
        }else{
            intr_writechoppedstring(intr, answers[3], 3, 1, 1);
            return OK;
        }
    }
    
    
    printf("%s",answers[1]);
    return OK;
}

Status give(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    World * w;
    Npc ** npcs;
    Npc * n;
    Object ** obs;
    Object * o;
    Space * s;
    char ** map;
    Intr * intr;
    int ret = 0; // Flag that says if you have the object to drop
    int flag = 0; // Tells if the object exists in the world
    int dir;
    int x; // Coordinate x of the npc
    int y; // Coordinate y of the npc
    int numnpc; // Number of npcs
    int numobj;
    int psid; // Id of the space where are you
    char * name = NULL;
    char * aux = NULL;
    int miss[2];
    int idnpc;

    w = (World *) world;
    intr = World_get_interface(w);
    /* Por definir  esta función */
    dir = intr_playergetdir(intr);
    x = intr_playergetcol(intr);
    y = intr_playergetrow(intr);
    psid = intr_playergetspid(intr);
    numnpc = World_get_numberNpc(w);
    npcs = World_get_npcS(w);
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);
    miss[0] = Intr_get_mission(intr);
    miss[1] = Intr_get_phase(intr);
    s = World_get_space(w, psid);
    map = Space_getMap(s);

    name = (char *) malloc(200 * sizeof(char));

    for(i = 0; i < numobj; i++){
        if(!strcmp(objeto, Object_getname(obs[i]))){
            flag = 1;
            if(Object_getlocation(obs[i]) == -1){
                ret = 1;
                o = obs[i];
            }
        }
    }
    
    if(flag == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* The object doesn't exist */
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        free(name);
        return OK;
    }
    if(ret == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* You don't have that object */
        intr_writechoppedstring(intr, answers[1], 3, 1, 1);
        free(name);
        return OK;
    }
    /* UP, DOWN, RIGHT, LEFT */
    if(dir == 0){
        y--;
        if(map[y][x] != '@'){
            /* There is no person to interactuate */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            free(name);
            return OK;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){

            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            idnpc = Npc_getid(n);
            aux = Npc_getname(n);
            // EJEMPLO!!!!!!! DEBEMOS PONER LOS ID'S CORRECTOS!!!!
            if(!strcmp(aux, "Nuria (Happy Woman)") && miss[0] == 2 && miss[1] == 2){
                /* M 2 P 2 -> M 2 P 3 */
                World_actualize(w, 2, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Mr D. Pool (THE BOSS)") && miss[0] == 8 && miss[1] == 1){
                /* M 8 P 1 -> M 8 P 2 */
                World_actualize(w, 8, 2);
                intr_allocobjects(intr);
            }


            idnpc = 0 - (2 + idnpc);
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // for each npc is diferent
            Object_setlocation(o, idnpc);
            Object_setcoordinatex(o, 0);
            Object_setcoordinatey(o, 0);
            
            intr_refresh(intr);
            
            /* You gave "object" to */
            sprintf(name, "%s \"%s\". Try to remember it.", answers[3], Npc_getname(n));
            intr_writechoppedstring(intr, name, 3, 1, 1);
            free(name);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }else if(dir == 1){
        y++;
        if(map[y][x] != '@'){
            /* There is no person to interactuate */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            free(name);
            return OK;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){

            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            idnpc = Npc_getid(n);
            aux = Npc_getname(n);
            // EJEMPLO!!!!!!! DEBEMOS PONER LOS ID'S CORRECTOS!!!!
            if(!strcmp(aux, "Nuria (Happy Woman)") && miss[0] == 2 && miss[1] == 2){
                /* M 2 P 2 -> M 2 P 3 */
                World_actualize(w, 2, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Mr D. Pool (THE BOSS)") && miss[0] == 8 && miss[1] == 1){
                /* M 8 P 1 -> M 8 P 2 */
                World_actualize(w, 8, 2);
                intr_allocobjects(intr);
            }


            idnpc = 0 - (2 + idnpc);
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // for each npc is diferent
            Object_setlocation(o, idnpc);
            Object_setcoordinatex(o, 0);
            Object_setcoordinatey(o, 0);
            
            intr_refresh(intr);
            
            /* You gave "object" to */
            sprintf(name, "%s \"%s\". Try to remember it.", answers[3], Npc_getname(n));
            intr_writechoppedstring(intr, name, 3, 1, 1);
            free(name);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }else if(dir == 2){
        x++;
        if(map[y][x] != '@'){
            /* There is no person to interactuate */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            free(name);
            return OK;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){

            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            idnpc = Npc_getid(n);
            aux = Npc_getname(n);
            // EJEMPLO!!!!!!! DEBEMOS PONER LOS ID'S CORRECTOS!!!!
            if(!strcmp(aux, "Nuria (Happy Woman)") && miss[0] == 2 && miss[1] == 2){
                /* M 2 P 2 -> M 2 P 3 */
                World_actualize(w, 2, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Mr D. Pool (THE BOSS)") && miss[0] == 8 && miss[1] == 1){
                /* M 8 P 1 -> M 8 P 2 */
                World_actualize(w, 8, 2);
                intr_allocobjects(intr);
            }


            idnpc = 0 - (2 + idnpc);
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // for each npc is diferent
            Object_setlocation(o, idnpc);
            Object_setcoordinatex(o, 0);
            Object_setcoordinatey(o, 0);
            
            intr_refresh(intr);
            
            /* You gave "object" to */
            sprintf(name, "%s \"%s\". Try to remember it.", answers[3], Npc_getname(n));
            intr_writechoppedstring(intr, name, 3, 1, 1);
            free(name);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }else if(dir == 3){
        x--;
        if(map[y][x] != '@'){
            /* There is no person to interactuate */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            free(name);
            return OK;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){

            idnpc = Npc_getid(n);
            aux = Npc_getname(n);

            if(!strcmp(aux, "Nuria (Happy Woman)") && miss[0] == 2 && miss[1] == 2){
                /* M 2 P 2 -> M 2 P 3 */
                World_actualize(w, 2, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Mr D. Pool (THE BOSS)") && miss[0] == 8 && miss[1] == 1){
                /* M 8 P 1 -> M 8 P 2 */
                World_actualize(w, 8, 2);
                intr_allocobjects(intr);
            }


            idnpc = 0 - (2 + idnpc);

            // for each npc is diferent
            Object_setlocation(o, idnpc);
            Object_setcoordinatex(o, 0);
            Object_setcoordinatey(o, 0);
            
            intr_refresh(intr);
            
            /* You gave "object" to */
            sprintf(name, "%s \"%s\". Try to remember it.", answers[3], Npc_getname(n));
            intr_writechoppedstring(intr, name, 3, 1, 1);
            free(name);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }

    intr_writechoppedstring(intr, answers[3], 3, 1, 1);
    /* else */
    
    free(name);
    return OK;
}
Status openwith(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    World * w;
    Object ** obs;
    Space * s;
    char ** map;
    Intr * intr;
    int ret = 0; // Flag that says if you have the object to drop
    int flag = 0; // Tells if the object exists in the world
    int dir;
    int x; // Coordinate x of the npc
    int y; // Coordinate y of the npc
    int numobj;
    int psid; // Id of the space where are you

    w = (World *) world;
    intr = World_get_interface(w);
    /* Por definir  esta función */
    dir = intr_playergetdir(intr);
    x = intr_playergetcol(intr);
    y = intr_playergetrow(intr);
    psid = intr_playergetspid(intr);
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);
    s = World_get_space(w, psid);
    map = Space_getMap(s);


    for(i = 0; i < numobj; i++){
        if(!strcmp(objeto, Object_getname(obs[i]))){
            flag = 1;
            if(Object_getlocation(obs[i]) == -1){
                ret = 1;
            }
        }
    }

    if(flag == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* The object doesn't exist */
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        
        return OK;
    }
    if(ret == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* You don't have that object */
        intr_writechoppedstring(intr, answers[1], 3, 1, 1);
        
        return OK;
    }

    /* UP, DOWN, RIGHT, LEFT */
    if(dir == 0){
        y--;
        if(map[y][x] != '^' && map[y][x] != 'v' && map[y][x] != '<' && map[y][x] != '>'){
            /* There is no door to be opened */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            
            return OK;
        }
        
        if(strcmp(objeto, "Key 1") && strcmp(objeto, "Key 2") && strcmp(objeto, "Swiss Knife")){
            /* The object doesn't open doors */
            intr_writechoppedstring(intr, answers[3], 3, 1, 1);
            return OK;
        }else {
            if(!strcmp(objeto, "Key 1")){
                if(psid == 2 && map[y][x] == 'v'){
                    if(Space_doorGetLock(s, 2) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 2, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }else if(!strcmp(objeto, "Key 2")){
                if(psid == 16 && map[y][x] == 'v'){
                    if(Space_doorGetLock(s, 3) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 3, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }else if(!strcmp(objeto, "Swiss Knife")){
                if(psid == 6 && map[y][x] == '^'){
                    if(Space_doorGetLock(s, 0) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 0, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }

        }
        
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }else if(dir == 1){
        y++;
        if(map[y][x] != '^' && map[y][x] != 'v' && map[y][x] != '<' && map[y][x] != '>'){
            /* There is no door to be opened */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            
            return OK;
        }
        
        if(strcmp(objeto, "Key 1") && strcmp(objeto, "Key 2") && strcmp(objeto, "Swiss Knife")){
            /* The object doesn't open doors */
            intr_writechoppedstring(intr, answers[3], 3, 1, 1);
            return OK;
        }else {
            if(!strcmp(objeto, "Key 1")){
                if(psid == 2 && map[y][x] == 'v'){
                    if(Space_doorGetLock(s, 2) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 2, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }else if(!strcmp(objeto, "Key 2")){
                if(psid == 16 && map[y][x] == 'v'){
                    if(Space_doorGetLock(s, 3) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 3, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }else if(!strcmp(objeto, "Swiss Knife")){
                if(psid == 6 && map[y][x] == '^'){
                    if(Space_doorGetLock(s, 0) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 0, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }

        }
        
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }else if(dir == 2){
        x++;
        if(map[y][x] != '^' && map[y][x] != 'v' && map[y][x] != '<' && map[y][x] != '>'){
            /* There is no door to be opened */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            
            return OK;
        }
        
        if(strcmp(objeto, "Key 1") && strcmp(objeto, "Key 2") && strcmp(objeto, "Swiss Knife")){
            /* The object doesn't open doors */
            intr_writechoppedstring(intr, answers[3], 3, 1, 1);
            return OK;
        }else {
            if(!strcmp(objeto, "Key 1")){
                if(psid == 2 && map[y][x] == 'v'){
                    if(Space_doorGetLock(s, 2) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 2, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }else if(!strcmp(objeto, "Key 2")){
                if(psid == 16 && map[y][x] == 'v'){
                    if(Space_doorGetLock(s, 3) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 3, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }else if(!strcmp(objeto, "Swiss Knife")){
                if(psid == 6 && map[y][x] == '^'){
                    if(Space_doorGetLock(s, 0) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 0, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }

        }
        
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }else if(dir == 3){
        x--;
        if(map[y][x] != '^' && map[y][x] != 'v' && map[y][x] != '<' && map[y][x] != '>'){
            /* There is no door to be opened */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            
            return OK;
        }
        
        if(strcmp(objeto, "Key 1") && strcmp(objeto, "Key 2") && strcmp(objeto, "Swiss Knife")){
            /* The object doesn't open doors */
            intr_writechoppedstring(intr, answers[3], 3, 1, 1);
            return OK;
        }else {
            if(!strcmp(objeto, "Key 1")){
                if(psid == 2 && map[y][x] == 'v'){
                    if(Space_doorGetLock(s, 2) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 2, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }else if(!strcmp(objeto, "Key 2")){
                if(psid == 16 && map[y][x] == 'v'){
                    if(Space_doorGetLock(s, 3) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 3, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }else if(!strcmp(objeto, "Swiss Knife")){
                if(psid == 6 && map[y][x] == '^'){
                    if(Space_doorGetLock(s, 0) == FALSE){
                        /* Opened door */
                        intr_writechoppedstring(intr, answers[4], 3, 1, 1);
                        return OK;
                    }
                    Space_doorSetLock(s, 0, FALSE);
                    /* Success */
                    intr_writechoppedstring(intr, answers[5], 3, 1, 1);
                    return OK;
                }
                intr_writechoppedstring(intr, answers[6], 3, 1, 1);
                return OK;
            }

        }
        
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }
    /* else */
    
    return OK;

}
Status askfor(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    World * w;
    Npc ** npcs;
    Npc * n;
    Object ** obs;
    Object * o;
    Space * s;
    char ** map;
    Intr * intr;
    int ret = 0; // Flag that says if you have the object to drop
    int flag = 0; // Tells if the object exists in the world
    int dir;
    int x; // Coordinate x of the npc
    int y; // Coordinate y of the npc
    int numnpc; // Number of npcs
    int numobj;
    int psid; // Id of the space where are you
    char * name = NULL;
    char * aux = NULL;
    int idnpc;
    int miss[2];

    w = (World *) world;
    intr = World_get_interface(w);
    /* Por definir  esta función */
    dir = intr_playergetdir(intr);
    x = intr_playergetcol(intr);
    y = intr_playergetrow(intr);
    psid = intr_playergetspid(intr);
    numnpc = World_get_numberNpc(w);
    npcs = World_get_npcS(w);
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);
    s = World_get_space(w, psid);
    map = Space_getMap(s);

    miss[0] = Intr_get_mission(intr);
    miss[1] = Intr_get_phase(intr);

    name = (char *) malloc(200 * sizeof(char));

    for(i = 0; i < numobj; i++){
        if(!strcmp(objeto, Object_getname(obs[i]))){
            flag = 1;
            if(Object_getlocation(obs[i]) == -1){
                ret = 1;
                o = obs[i];
            }
        }
    }
    
    if(flag == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* The object doesn't exist */
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        free(name);
        return OK;
    }
    if(ret == 1){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* You have that object */
        intr_writechoppedstring(intr, answers[1], 3, 1, 1);
        free(name);
        return OK;
    }
    /* UP, DOWN, RIGHT, LEFT */
    if(dir == 0){
        y--;
        if(map[y][x] != '@'){
            /* There is no person to interactuate */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            free(name);
            return OK;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){

            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            idnpc = Npc_getid(n);
            // Calculamos si ownea el objeto.
            idnpc = 0 - (2 + idnpc);
            o = Object_find(obs, numobj, 0, 0, idnpc);
            if(o == NULL){
                sprintf(name, "\"%s\" %s", Npc_getname(n), answers[3]);
                intr_writechoppedstring(intr, name, 3, 1, 1);
                free(name);
                return OK;
            }
            aux = Npc_getname(n);
            if(!strcmp(aux, "GR7") && miss[0] == 2 && miss[1] == 1){
                /* M 2 P 1 -> M 2 P 2 */
                World_actualize(w, 2, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Mr D. Pool (THE BOSS)") && miss[0] == 5 && miss[1] == 2){
                /* M 5 P 2 -> M 6 P 1 */
                World_actualize(w, 6, 1);
                intr_allocobjects(intr);
                s = World_get_space(w, 9);
                Space_doorSetLock(s, 1, FALSE);
            }else if(!strcmp(aux, "Richi") && miss[0] == 6 && miss[1] == 1){
                /* M 6 P 1 -> M 6 P 2 */
                World_actualize(w, 6, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Fons") && miss[0] == 6 && miss[1] == 3){
                /* M 6 P 3 -> M 6 P 4 */
                World_actualize(w, 6, 4);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Santi (Chandal-man)") && miss[0] == 7 && miss[1] == 2){
                /* M 7 P 2 -> M 7 P 3 */
                World_actualize(w, 7, 3);
                intr_allocobjects(intr);
            }



            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // se lo damos al objeto
            Object_setlocation(o, -1);
            
            intr_refresh(intr);
            
            /* You gave "object" to */
            sprintf(name, "\"%s\" %s", Npc_getname(n), answers[4]);
            intr_writechoppedstring(intr, name, 3, 1, 1);
            free(name);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }else if(dir == 1){
        y++;
        if(map[y][x] != '@'){
            /* There is no person to interactuate */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            free(name);
            return OK;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){

            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            idnpc = Npc_getid(n);
            // Calculamos si ownea el objeto.
            idnpc = 0 - (2 + idnpc);
            o = Object_find(obs, numobj, 0, 0, idnpc);
            if(o == NULL){
                sprintf(name, "\"%s\" %s", Npc_getname(n), answers[3]);
                intr_writechoppedstring(intr, name, 3, 1, 1);
                free(name);
                return OK;
            }
            aux = Npc_getname(n);
            if(!strcmp(aux, "GR7") && miss[0] == 2 && miss[1] == 1){
                /* M 2 P 1 -> M 2 P 2 */
                World_actualize(w, 2, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Mr D. Pool (THE BOSS)") && miss[0] == 5 && miss[1] == 2){
                /* M 5 P 2 -> M 6 P 1 */
                World_actualize(w, 6, 1);
                intr_allocobjects(intr);
                s = World_get_space(w, 9);
                Space_doorSetLock(s, 1, FALSE);
            }else if(!strcmp(aux, "Richi") && miss[0] == 6 && miss[1] == 1){
                /* M 6 P 1 -> M 6 P 2 */
                World_actualize(w, 6, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Fons") && miss[0] == 6 && miss[1] == 3){
                /* M 6 P 3 -> M 6 P 4 */
                World_actualize(w, 6, 4);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Santi (Chandal-man)") && miss[0] == 7 && miss[1] == 2){
                /* M 7 P 2 -> M 7 P 3 */
                World_actualize(w, 7, 3);
                intr_allocobjects(intr);
            }



            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // se lo damos al objeto
            Object_setlocation(o, -1);
            
            intr_refresh(intr);
            
            /* You gave "object" to */
            sprintf(name, "\"%s\" %s", Npc_getname(n), answers[4]);
            intr_writechoppedstring(intr, name, 3, 1, 1);
            free(name);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }else if(dir == 2){
        x++;
        if(map[y][x] != '@'){
            /* There is no person to interactuate */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            free(name);
            return OK;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){

            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            idnpc = Npc_getid(n);
            // Calculamos si ownea el objeto.
            idnpc = 0 - (2 + idnpc);
            o = Object_find(obs, numobj, 0, 0, idnpc);
            if(o == NULL){
                sprintf(name, "\"%s\" %s", Npc_getname(n), answers[3]);
                intr_writechoppedstring(intr, name, 3, 1, 1);
                free(name);
                return OK;
            }
            aux = Npc_getname(n);
            if(!strcmp(aux, "GR7") && miss[0] == 2 && miss[1] == 1){
                /* M 2 P 1 -> M 2 P 2 */
                World_actualize(w, 2, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Mr D. Pool (THE BOSS)") && miss[0] == 5 && miss[1] == 2){
                /* M 5 P 2 -> M 6 P 1 */
                World_actualize(w, 6, 1);
                intr_allocobjects(intr);
                s = World_get_space(w, 9);
                Space_doorSetLock(s, 1, FALSE);
            }else if(!strcmp(aux, "Richi") && miss[0] == 6 && miss[1] == 1){
                /* M 6 P 1 -> M 6 P 2 */
                World_actualize(w, 6, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Fons") && miss[0] == 6 && miss[1] == 3){
                /* M 6 P 3 -> M 6 P 4 */
                World_actualize(w, 6, 4);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Santi (Chandal-man)") && miss[0] == 7 && miss[1] == 2){
                /* M 7 P 2 -> M 7 P 3 */
                World_actualize(w, 7, 3);
                intr_allocobjects(intr);
            }



            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // se lo damos al objeto
            Object_setlocation(o, -1);
            
            intr_refresh(intr);
            
            /* You gave "object" to */
            sprintf(name, "\"%s\" %s", Npc_getname(n), answers[4]);
            intr_writechoppedstring(intr, name, 3, 1, 1);
            free(name);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }else if(dir == 3){
        x--;
        if(map[y][x] != '@'){
            /* There is no person to interactuate */
            intr_writechoppedstring(intr, answers[2], 3, 1, 1);
            free(name);
            return OK;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){

            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            idnpc = Npc_getid(n);
            // Calculamos si ownea el objeto.
            idnpc = 0 - (2 + idnpc);
            o = Object_find(obs, numobj, 0, 0, idnpc);
            if(o == NULL){
                sprintf(name, "\"%s\" %s", Npc_getname(n), answers[3]);
                intr_writechoppedstring(intr, name, 3, 1, 1);
                free(name);
                return OK;
            }
            aux = Npc_getname(n);
            if(!strcmp(aux, "GR7") && miss[0] == 2 && miss[1] == 1){
                /* M 2 P 1 -> M 2 P 2 */
                World_actualize(w, 2, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Mr D. Pool (THE BOSS)") && miss[0] == 5 && miss[1] == 2){
                /* M 5 P 2 -> M 6 P 1 */
                World_actualize(w, 6, 1);
                intr_allocobjects(intr);
                s = World_get_space(w, 9);
                Space_doorSetLock(s, 1, FALSE);
            }else if(!strcmp(aux, "Richi") && miss[0] == 6 && miss[1] == 1){
                /* M 6 P 1 -> M 6 P 2 */
                World_actualize(w, 6, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Fons") && miss[0] == 6 && miss[1] == 3){
                /* M 6 P 3 -> M 6 P 4 */
                World_actualize(w, 6, 4);
                intr_allocobjects(intr);
            }else if(!strcmp(aux, "Santi (Chandal-man)") && miss[0] == 7 && miss[1] == 2){
                /* M 7 P 2 -> M 7 P 3 */
                World_actualize(w, 7, 3);
                intr_allocobjects(intr);
            }



            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            // se lo damos al objeto
            Object_setlocation(o, -1);
            
            intr_refresh(intr);
            
            /* You gave "object" to */
            sprintf(name, "\"%s\" %s", Npc_getname(n), answers[4]);
            intr_writechoppedstring(intr, name, 3, 1, 1);
            free(name);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        return ERROR;
    }

    intr_writechoppedstring(intr, answers[3], 3, 1, 1);
    /* else */
    
    free(name);
    return OK;
}

Status talk(void * world, char * objeto, int n_ans, char ** answers){
    World * w;
    Npc ** npcs;
    Npc * n;
    Space * s;
    char ** map;
    Intr * intr;
    int dir;
    int x; // Coordinate x of the npc
    int y; // Coordinate y of the npc
    int numnpc; // Number of npcs
    int psid; // Id of the space where are you
    int miss[2];
    char * aux = NULL;
    char * name = NULL;
    
    w = (World *) world;
    intr = World_get_interface(w);
    /* Por definir  esta función */
    dir = intr_playergetdir(intr);
    x = intr_playergetcol(intr);
    y = intr_playergetrow(intr);
    psid = intr_playergetspid(intr);
    numnpc = World_get_numberNpc(w);
    npcs = World_get_npcS(w);
    s = World_get_space(w, psid);
    map = Space_getMap(s);
    /* Diferent speeches due to the mission-phase */
    miss[0] = Intr_get_mission(intr);
    miss[1] = Intr_get_phase(intr);
    
    
    

    if(strlen(objeto) > 1 || objeto[0] != '@'){
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        return OK;
    }
    aux = (char *) malloc(200 * sizeof(char));
    /* UP, DOWN, RIGHT, LEFT */
    if(dir == 0){
        y--;
        if(map[y][x] != '@'){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            free(aux);
            return 0;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){
            
            name = Npc_getname(n);
            sprintf(aux, "%s: %s",name, Npc_getdescription(n, miss[0], miss[1]) );
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if(aux == NULL){
                intr_writechoppedstring(intr, answers[2], 3, 2, 1);
                free(aux);
                return OK;
            }
            /* You pick "whatever" */
            intr_writechoppedstring(intr, aux, 3, 1, 1);
            if(!strcmp(name, "Lucía (Cadis)") && miss[0] == 1 && miss[1] == 1){
                /* M 1 P 1 -> M 1 P 2 */
                World_actualize(w, 1, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Blanca A") && miss[0] == 1 && miss[1] == 2){
                /* M 1 P 2 -> M 1 P 3 */
                World_actualize(w, 1, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Aitormenta") && miss[0] == 1 && miss[1] == 3){
                /* M 1 P 3 -> M 1 P 4 */
                World_actualize(w, 1, 4);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Nuria (Happy Woman)") && miss[0] == 1 && miss[1] == 4){
                /* M 1 P 4 -> M 2 P 1 */
                World_actualize(w, 2, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Villar") && miss[0] == 3 && miss[1] == 1){
                /* M 3 P 1 -> M 3 P 2 */
                World_actualize(w, 3, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "The Great Mike") && miss[0] == 3 && miss[1] == 3){
                /* M 3 P 3 -> M 4 P 1 */
                World_actualize(w, 4, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Andrea") && miss[0] == 4 && miss[1] == 1){
                /* M 4 P 1 -> M 4 P 2 */
                World_actualize(w, 4, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Víctor") && miss[0] == 6 && miss[1] == 2){
                /* M 6 P 2 -> M 6 P 3 */
                World_actualize(w, 6, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "SuperJuan260") && miss[0] == 6 && miss[1] == 4){
                /* M 6 P 4 -> M 7 P 1 */
                World_actualize(w, 7, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Mr D. Pool (THE BOSS)") && miss[0] == 7 && miss[1] == 1){
                /* M 7 P 1 -> M 7 P 2 */
                World_actualize(w, 7, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Mr D. Pool (THE BOSS)") && miss[0] == 8 && miss[1] == 2){
                /* M 8 P 2 -> M 9 P 1 */
                World_actualize(w, 9, 1);
                intr_allocobjects(intr);
            }
            /* Description of the object */
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            free(aux);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        free(aux);
        return ERROR;
    }else if(dir == 1){
        y++;
        if(map[y][x] != '@'){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            free(aux);
            return 0;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){
            
            name = Npc_getname(n);
            sprintf(aux, "%s: %s",name, Npc_getdescription(n, miss[0], miss[1]) );
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if(aux == NULL){
                intr_writechoppedstring(intr, answers[2], 3, 2, 1);
                free(aux);
                return OK;
            }
            /* You pick "whatever" */
            intr_writechoppedstring(intr, aux, 3, 1, 1);
            if(!strcmp(name, "Lucía (Cadis)") && miss[0] == 1 && miss[1] == 1){
                /* M 1 P 1 -> M 1 P 2 */
                World_actualize(w, 1, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Blanca A") && miss[0] == 1 && miss[1] == 2){
                /* M 1 P 2 -> M 1 P 3 */
                World_actualize(w, 1, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Aitormenta") && miss[0] == 1 && miss[1] == 3){
                /* M 1 P 3 -> M 1 P 4 */
                World_actualize(w, 1, 4);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Nuria (Happy Woman)") && miss[0] == 1 && miss[1] == 4){
                /* M 1 P 4 -> M 2 P 1 */
                World_actualize(w, 2, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Villar") && miss[0] == 3 && miss[1] == 1){
                /* M 3 P 1 -> M 3 P 2 */
                World_actualize(w, 3, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "The Great Mike") && miss[0] == 3 && miss[1] == 3){
                /* M 3 P 3 -> M 4 P 1 */
                World_actualize(w, 4, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Andrea") && miss[0] == 4 && miss[1] == 1){
                /* M 4 P 1 -> M 4 P 2 */
                World_actualize(w, 4, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Víctor") && miss[0] == 6 && miss[1] == 2){
                /* M 6 P 2 -> M 6 P 3 */
                World_actualize(w, 6, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "SuperJuan260") && miss[0] == 6 && miss[1] == 4){
                /* M 6 P 4 -> M 7 P 1 */
                World_actualize(w, 7, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Mr D. Pool (THE BOSS)") && miss[0] == 7 && miss[1] == 1){
                /* M 7 P 1 -> M 7 P 2 */
                World_actualize(w, 7, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Mr D. Pool (THE BOSS)") && miss[0] == 8 && miss[1] == 2){
                /* M 8 P 2 -> M 9 P 1 */
                World_actualize(w, 9, 1);
                intr_allocobjects(intr);
            }
            /* Description of the object */
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            free(aux);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        free(aux);
        return ERROR;
    }else if(dir == 2){
        x++;
        if(map[y][x] != '@'){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            free(aux);
            return 0;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){
            
            name = Npc_getname(n);
            sprintf(aux, "%s: %s",name, Npc_getdescription(n, miss[0], miss[1]) );
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if(aux == NULL){
                intr_writechoppedstring(intr, answers[2], 3, 2, 1);
                free(aux);
                return OK;
            }
            /* You pick "whatever" */
            intr_writechoppedstring(intr, aux, 3, 1, 1);
            if(!strcmp(name, "Lucía (Cadis)") && miss[0] == 1 && miss[1] == 1){
                /* M 1 P 1 -> M 1 P 2 */
                World_actualize(w, 1, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Blanca A") && miss[0] == 1 && miss[1] == 2){
                /* M 1 P 2 -> M 1 P 3 */
                World_actualize(w, 1, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Aitormenta") && miss[0] == 1 && miss[1] == 3){
                /* M 1 P 3 -> M 1 P 4 */
                World_actualize(w, 1, 4);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Nuria (Happy Woman)") && miss[0] == 1 && miss[1] == 4){
                /* M 1 P 4 -> M 2 P 1 */
                World_actualize(w, 2, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Villar") && miss[0] == 3 && miss[1] == 1){
                /* M 3 P 1 -> M 3 P 2 */
                World_actualize(w, 3, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "The Great Mike") && miss[0] == 3 && miss[1] == 3){
                /* M 3 P 3 -> M 4 P 1 */
                World_actualize(w, 4, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Andrea") && miss[0] == 4 && miss[1] == 1){
                /* M 4 P 1 -> M 4 P 2 */
                World_actualize(w, 4, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Víctor") && miss[0] == 6 && miss[1] == 2){
                /* M 6 P 2 -> M 6 P 3 */
                World_actualize(w, 6, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "SuperJuan260") && miss[0] == 6 && miss[1] == 4){
                /* M 6 P 4 -> M 7 P 1 */
                World_actualize(w, 7, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Mr D. Pool (THE BOSS)") && miss[0] == 7 && miss[1] == 1){
                /* M 7 P 1 -> M 7 P 2 */
                World_actualize(w, 7, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Mr D. Pool (THE BOSS)") && miss[0] == 8 && miss[1] == 2){
                /* M 8 P 2 -> M 9 P 1 */
                World_actualize(w, 9, 1);
                intr_allocobjects(intr);
            }
            /* Description of the object */
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            free(aux);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        free(aux);
        return ERROR;
    }else if(dir == 3){
        x--;
        if(map[y][x] != '@'){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            free(aux);
            return 0;
        }
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){
            
            name = Npc_getname(n);
            sprintf(aux, "%s: %s",name, Npc_getdescription(n, miss[0], miss[1]) );
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if(aux == NULL){
                intr_writechoppedstring(intr, answers[2], 3, 2, 1);
                free(aux);
                return OK;
            }
            /* You pick "whatever" */
            intr_writechoppedstring(intr, aux, 3, 1, 1);
            if(!strcmp(name, "Lucía (Cadis)") && miss[0] == 1 && miss[1] == 1){
                /* M 1 P 1 -> M 1 P 2 */
                World_actualize(w, 1, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Blanca A") && miss[0] == 1 && miss[1] == 2){
                /* M 1 P 2 -> M 1 P 3 */
                World_actualize(w, 1, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Aitormenta") && miss[0] == 1 && miss[1] == 3){
                /* M 1 P 3 -> M 1 P 4 */
                World_actualize(w, 1, 4);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Nuria (Happy Woman)") && miss[0] == 1 && miss[1] == 4){
                /* M 1 P 4 -> M 2 P 1 */
                World_actualize(w, 2, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Villar") && miss[0] == 3 && miss[1] == 1){
                /* M 3 P 1 -> M 3 P 2 */
                World_actualize(w, 3, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "The Great Mike") && miss[0] == 3 && miss[1] == 3){
                /* M 3 P 3 -> M 4 P 1 */
                World_actualize(w, 4, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Andrea") && miss[0] == 4 && miss[1] == 1){
                /* M 4 P 1 -> M 4 P 2 */
                World_actualize(w, 4, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Víctor") && miss[0] == 6 && miss[1] == 2){
                /* M 6 P 2 -> M 6 P 3 */
                World_actualize(w, 6, 3);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "SuperJuan260") && miss[0] == 6 && miss[1] == 4){
                /* M 6 P 4 -> M 7 P 1 */
                World_actualize(w, 7, 1);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Mr D. Pool (THE BOSS)") && miss[0] == 7 && miss[1] == 1){
                /* M 7 P 1 -> M 7 P 2 */
                World_actualize(w, 7, 2);
                intr_allocobjects(intr);
            }else if(!strcmp(name, "Mr D. Pool (THE BOSS)") && miss[0] == 8 && miss[1] == 2){
                /* M 8 P 2 -> M 9 P 1 */
                World_actualize(w, 9, 1);
                intr_allocobjects(intr);
            }
            /* Description of the object */
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            free(aux);
            return OK;
        }
        intr_writechoppedstring(intr, "Error raro. no cohesion entre interfaz y mapa.", 3, 2, 1);
        free(aux);
        return ERROR;
    }

    intr_writechoppedstring(intr, answers[3], 3, 1, 1);
    /* else */
    
    free(aux);
    return OK; 
}

Status sing(void * world, char * objeto, int n_ans, char ** answers){
    World * w;
    Intr * intr;
    /*char * aux;*/
    
    w = (World *) world;
    intr = World_get_interface(w);
    /*aux = (char *) malloc(500 * sizeof(char));

    sprintf(aux, "\"espeak %s\"", answers[1]);*/
    intr_writechoppedstring(intr, answers[0], 3, 1, 1);
    system("espeak \"lalalalalalala\"");
    return OK;
}

Status cut(void * world, char * objeto, int n_ans, char ** answers){
    World * w;
    Intr * intr;
    int psid; // Id of the space where are you
    int x;
    int y;
    int dir;
    int miss[2];
    int ret = 1;
    
    w = (World *) world;
    intr = World_get_interface(w);
    dir = intr_playergetdir(intr);
    x = intr_playergetcol(intr);
    y = intr_playergetrow(intr);
    psid = intr_playergetspid(intr);

    miss[0] = Intr_get_mission(intr);
    miss[1] = Intr_get_phase(intr);

    if(strcmp(objeto, "Water Supply")){
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        return OK;
    }
    if(psid != 12){
        /* Not the correct room */
        intr_writechoppedstring(intr, answers[1], 3, 1, 1);
        return OK;
    }
    if(psid == 12){
        ret =iciclegame(intr);

        intr_teleportplayer(intr, x, y, dir);
        intr_changemap(intr, 12);
        if(miss[0] == 4 && miss[1] == 2 && ret == 0){
            /* M 4 P 2 -> M 5 P 1 */
            World_actualize(w, 5, 1);
            intr_allocobjects(intr);
        }
        return OK;
    }
    intr_writechoppedstring(intr, "Si llega aquí raro.", 3, 1, 1);
    return OK;
}


Status read(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    World * w;
    Object ** obs;
    Object * o;
    Intr * intr;
    int numobj; // Number of objects
    int ret = 0; // Flag that says if you have the object to drop
    int flag = 0; // Tells if the object exists in the world
    char * aux = NULL;
    
    w = (World *) world;
    intr = World_get_interface(w);
    
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);
    

    for(i = 0; i < numobj; i++){
        if(!strcmp(objeto, Object_getname(obs[i]))){
            flag = 1;
            if(Object_getlocation(obs[i]) == -1){
                ret = 1;
                o = obs[i];
            }
        }
    }

    if(flag == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* The object doesn't exist */
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        return OK;
    }
    if(ret == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* You don't have that object */
        intr_writechoppedstring(intr, answers[1], 3, 1, 1);
        return OK;
    }

    aux = (char *) malloc(200 * sizeof(char));

    if(strcmp(objeto, "Mysterious Note") && strcmp(objeto, "Secret Documents") && strcmp(objeto, "USB")){
        /* You can't read this object */
        intr_writechoppedstring(intr, answers[2], 3, 1, 1);
        free(aux);
        return OK;
    }

    if(!strcmp(objeto, "Mysterious Note")){
        /* You can't read this object */

        sprintf(aux, "%s %s", answers[3], Object_getdescription(o));
        intr_writechoppedstring(intr, aux, 3, 1, 1);
        free(aux);
        return OK;
    }
    if(!strcmp(objeto, "Secret Documents")){
        /* You can't read this object */

        sprintf(aux, "%s %s", answers[3], Object_getdescription(o));
        intr_writechoppedstring(intr, aux, 3, 1, 1);
        free(aux);
        return OK;
    }
    if(!strcmp(objeto, "USB")){
        /* You can't read this object */

        sprintf(aux, "%s: 2 DO -> Create a chemical factory at sciences building.",Object_getdescription(o));
        intr_writechoppedstring(intr, aux, 3, 1, 1);
        free(aux);
        return OK;
    }

    intr_writechoppedstring(intr, "ERROR raro", 3, 2, 1);
    free(aux);
    return OK;
}
Status jump(void * world, char * objeto, int n_ans, char ** answers){
    World * w;
    Intr * intr;
    int ret = 0; // Flag that says if you have the object to drop
    char * aux = NULL;
    int aux1;
    int aux2;

    w = (World *) world;
    intr = World_get_interface(w);

    if(strlen(objeto) > 2){
        /* Tamaño no valido */
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        return OK;
    }
    ret = atoi(objeto);
    aux1 = ret / 10;
    aux2 = ret % 10;

    if(ret <= 10 || ret >= 93 || aux1 <= 0 || aux1 >= 10 || aux2 <= 0 || aux2 >= 5){
        /* No son numeros o algo por el estilo */
        intr_writechoppedstring(intr, answers[1], 3, 1, 1);
        return OK;
    }
    if(aux1 == 1){
        if(aux2 > 4){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            return OK;
        }
    }
    if(aux1 == 2){
        if(aux2 > 3){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            return OK;
        }
    }
    if(aux1 == 3){
        if(aux2 > 2){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            return OK;
        }
    }
    if(aux1 == 4){
        if(aux2 > 2){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            return OK;
        }
    }
    if(aux1 == 5){
        if(aux2 > 2){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            return OK;
        }
    }
    if(aux1 == 6){
        if(aux2 > 4){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            return OK;
        }
    }
    if(aux1 == 7){
        if(aux2 > 3){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            return OK;
        }
    }
    if(aux1 == 8){
        if(aux2 > 2){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            return OK;
        }
    }
    if(aux1 == 9){
        if(aux2 > 2){
            intr_writechoppedstring(intr, answers[1], 3, 1, 1);
            return OK;
        }
    }
    aux = (char *) malloc(200 * sizeof(char));
    sprintf(aux,"Change. M %d P %d %s", aux1, aux2, answers[2]);

    World_actualize(w, aux1, aux2);
    intr_writechoppedstring(intr, aux, 3, 1, 1);

    free(aux);
    return OK;
}

Status get(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    World * w;
    Object ** obs;
    Object * o = NULL;
    Intr * intr;
    int ret = 0; // Flag that says if you have the object to drop
    int flag = 0; // Tells if the object exists in the world
    int numobj;

    w = (World *) world;
    intr = World_get_interface(w);
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);


    for(i = 0; i < numobj; i++){
        if(!strcmp(objeto, Object_getname(obs[i]))){
            flag = 1;
            o = obs[i];
            if(Object_getlocation(obs[i]) == -1){
                ret = 1;
                o = obs[i];
            }
        }
    }

    if(flag == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* The object doesn't exist */
        intr_writechoppedstring(intr, answers[0], 3, 1, 1);
        return OK;
    }
    if(ret == 1){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* You already have that object */
        intr_writechoppedstring(intr, answers[1], 3, 1, 1);
        return OK;
    }
    
    if(o == NULL){
        intr_writechoppedstring(intr, "Cagada rara", 3, 2, 1);
        return OK;
    }
    Object_setlocation(o, -1);
    intr_refresh(intr);

    intr_writechoppedstring(intr, answers[2], 3, 1, 1);
    /* else */
    
    return OK;
} 

Status error(void * world, char * objeto, int n_ans, char ** answers){
    World * w;
    Intr * intr;

    w = (World *)world;
    intr = World_get_interface(w);
    intr_writechoppedstring(intr, answers[0], 3, 1, 1);
    return OK;
    
}
