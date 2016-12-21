#include <stdio.h>
#include "cop.h"

// FUNCIONES PARA ENCONTRAR OBJETOS Y NPCS

// psid = id of the Space where you are
Object * Object_find(Object ** ob, int nobj, int x, int y, int psid){
    int i;
    
    assert(spid >= 0);
    assert(x >= 0);
    assert(y >= 0);
    
    i = 0;
    while(i < nobj){
        if(psid == Object_getlocation(ob[i])){
            if(x == Object_getcoordinatex(ob[i])){
                if(y == Object_getcoordinatey(ob[i]))
                    return ob[i];
            }
        }
        i++;
    }
    
    return NULL;
}

Npc * Npc_find(Npc ** npc, int n_npc, int x, int y, int psid){
    int i;
    
    assert(spid >= 0);
    assert(x >= 0);
    assert(y >= 0);
    
    i = 0;
    while(i < n_npc){
        if(psid == Npc_getlocation(npc[i])){
            if(x == Npc_getcoordinatex(npc[i])){
                if(y == Npc_getcoordinatey(npc[i]))
                    return ob[i];
            }
        }
        i++;
    }
    
    return NULL;
}

/* typedef int (*pfun) (void * world, char * objeto, int n_ans, char ** answers);*/

/* The "objeto" is the symbol tah you see in screen */
Status examine(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    Player * p;
    World * w;
    Object ** obs;
    Object * o;
    Npc ** npcs;
    Npc* n;
    Space * s;
    char ** map;
    Intr * intr;
    int flag = 0; // Tells if the object/npc exists in the world
    int dir; // Direction of the player
    int x; // Coordinate x of the object or npc
    int y; // Coordinate y of the object or npc
    int numobj; // Number of objects
    int numnpc; // Number of npcs
    int psid; // Id of the space where are you
    
    w = (World *) world;
    p = World_get_player(w);
    /* Por definir  esta función */
    dir = Player_get_direction(p);
    x = Player_get_coordinatex(p);
    y = Player_get_coordinatey(p);
    psid = Player_get_location(p);
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);
    s = World_get_space(w, psid);
    map = Space_getMap(s);
    intr = World_get_interface(w);
    
    /* UP, DOWN, LEFT, RIGHT */
    if(dir == 0){
        y--;
        if(map[x][y] == ' '){
            //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
            /* Genius. You are examining the air. Here is a tip: it's useful to breath*/
            printf("%s",answers[2]);
            return OK;
        }else if(map[x][y] == '<' || map[x][y] == '^' || map[x][y] == '>' || map[x][y] == 'v'){
            //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
            /* Well. You are examining a door, you know? That thing that conects diferent rooms.
            You can open it, close it.. or use it to crush your head an make a favour to all of us, you dumb!*/
            printf("%s",answers[2]);
            return OK;
        }else{
            o = Object_find(obs, numobj, x, y, psid);
            if(o != NULL){
                if(!strcmp(objeto, Object_getsymbol(o))){
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                    /* You are examining an object. It's a "getname" */
                    printf("%s",answers[2]);
                    return OK;
                }
                printf("ERROR: el objeto no está bien colocado");
            }
            n = Npc_find(npcs, numnpc, x, y, psid);
            if(n != NULL){
                if(!strcmp(objeto, Npc_getsymbol(n))){
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                    /* You are examining a person: "getname" */
                    /*  To interactuate: speak <name>, kick <name>, hit <name>, yell <name> ...*/
                    printf("%s",answers[2]);
                    return OK;
                }
            }
            printf("ERROR: el npc no está bien colocado");
        }
    }else if(dir == 1){
        y++;
        if(map[x][y] == ' '){
            //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
            /* Genius. You are examining the air. Here is a tip: it's useful to breath*/
            printf("%s",answers[2]);
            return OK;
        }else if(map[x][y] == '<' || map[x][y] == '^' || map[x][y] == '>' || map[x][y] == 'v'){
            //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
            /* Well. You are examining a door, you know? That thing that conects diferent rooms.
            You can open it, close it.. or use it to crush your head an make a favour to all of us, you dumb!*/
            printf("%s",answers[2]);
            return OK;
        }else{
            o = Object_find(obs, numobj, x, y, psid);
            if(o != NULL){
                if(!strcmp(objeto, Object_getsymbol(o))){
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                    /* You are examining an object. It's a "getname" */
                    /*  To interactuate: pick <name>, drop <name> ...*/
                    printf("%s",answers[2]);
                    return OK;
                }
                printf("ERROR: el objeto no está bien colocado");
            }
            n = Npc_find(npcs, numnpc, x, y, psid);
            if(n != NULL){
                if(!strcmp(objeto, Npc_getsymbol(n))){
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                    /* You are examining a person: "getname" */
                    /*  To interactuate: speak <name>, kick <name>, hit <name>, yell <name> ...*/
                    printf("%s",answers[2]);
                    return OK;
                }
            }
            printf("ERROR: el npc no está bien colocado");
        }
    }else if(dir == 2){
        x--;
        if(map[x][y] == ' '){
            //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
            /* Genius. You are examining the air. Here is a tip: it's useful to breath*/
            printf("%s",answers[2]);
            return OK;
        }else if(map[x][y] == '<' || map[x][y] == '^' || map[x][y] == '>' || map[x][y] == 'v'){
            //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
            /* Well. You are examining a door, you know? That thing that conects diferent rooms.
            You can open it, close it.. or use it to crush your head an make a favour to all of us, you dumb!*/
            printf("%s",answers[2]);
            return OK;
        }else{
            o = Object_find(obs, numobj, x, y, psid);
            if(o != NULL){
                if(!strcmp(objeto, Object_getsymbol(o))){
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                    /* You are examining an object. It's a "getname" */
                    printf("%s",answers[2]);
                    return OK;
                }
                printf("ERROR: el objeto no está bien colocado");
            }
            n = Npc_find(npcs, numnpc, x, y, psid);
            if(n != NULL){
                if(!strcmp(objeto, Npc_getsymbol(n))){
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                    /* You are examining a person: "getname" */
                    /*  To interactuate: speak <name>, kick <name>, hit <name>, yell <name> ...*/
                    printf("%s",answers[2]);
                    return OK;
                }
            }
            printf("ERROR: el npc no está bien colocado");
        }
    }else if(dir == 3){
        y--;
        if(map[x][y] == ' '){
            //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
            /* Genius. You are examining the air. Here is a tip: it's useful to breath*/
            printf("%s",answers[2]);
            return OK;
        }else if(map[x][y] == '<' || map[x][y] == '^' || map[x][y] == '>' || map[x][y] == 'v'){
            //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
            /* Well. You are examining a door, you know? That thing that conects diferent rooms.
            You can open it, close it.. or use it to crush your head an make a favour to all of us, you dumb!*/
            printf("%s",answers[2]);
            return OK;
        }else{
            o = Object_find(obs, numobj, x, y, psid);
            if(o != NULL){
                if(!strcmp(objeto, Object_getsymbol(o))){
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                    /* You are examining an object. It's a "getname" */
                    printf("%s",answers[2]);
                    return OK;
                }
                printf("ERROR: el objeto no está bien colocado");
            }
            n = Npc_find(npcs, numnpc, x, y, psid);
            if(n != NULL){
                if(!strcmp(objeto, Npc_getsymbol(n))){
                    //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                    /* You are examining a person: "getname" */
                    /*  To interactuate: speak <name>, kick <name>, hit <name>, yell <name> ...*/
                    printf("%s",answers[2]);
                    return OK;
                }
            }
            printf("ERROR: el npc no está bien colocado");
        }
    }
    /* else */
    /* Examining something irrelevant */
    printf("%s", answers[6]);
    return OK;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Los segundos get suymbol podrían ser coordenadas del mapa no se.
Status pick(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    Player * p;
    World * w;
    Object ** obs;
    Object * o;
    Space * s;
    char ** map;
    Intr * intr;
    int flag = 0; // Tells if the object exists in the world
    int dir; // Direction of the player
    int x; // Coordinate x of the object
    int y; // Coordinate y of the object
    int numobj; // Number of objects
    int psid; // Id of the space where are you
    
    w = (World *) world;
    p = World_get_player(w);
    /* Por definir  esta función */
    dir = Player_get_direction(p);
    x = Player_get_coordinatex(p);
    y = Player_get_coordinatey(p);
    psid = Player_get_location(p);
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);
    s = World_get_space(w, psid);
    map = Space_getMap(s);
    intr = World_get_interface(w);
    
    for(i = 0; i < numobj; i++){
        if(!strcmp(objeto, Object_getname(obs[i]))){
            flag = 1;
        }
    }
    
    if(flag == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* The object doesn't exist */
        printf("%s",answers[2]);
        return OK;
    }
    /* UP, DOWN, LEFT, RIGHT */
    if(dir == 0){
        y--;
        o = Object_find(obs, numobj, x, y, psid);
        if(o != NULL){
            if(strcmp(objeto, Object_getname(o))){
                //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                /* The object is not in your range */
                printf("%s",answers[2]);
                return OK;
            }
            // Actualizamos la estructura del objeto
            Object_setlocation(o, -1);
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            intr_refresh(intr);
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            return OK;
        }
    }else if(dir == 1){
        y++;
        o = Object_find(obs, numobj, x, y, psid);
        if(o != NULL){
            if(strcmp(objeto, Object_getname(o))){
                //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                /* The object is not in your range */
                printf("%s",answers[2]);
                return OK;
            }
            // Actualizamos la estructura del objeto
            Object_setlocation(o, -1);
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            intr_refresh(intr);
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            return OK;
        }
    }else if(dir == 2){
        x--;
        o = Object_find(obs, numobj, x, y, psid);
        if(o != NULL){
            if(strcmp(objeto, Object_getname(o))){
                //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                /* The object is not in your range */
                printf("%s",answers[2]);
                return OK;
            }
            // Actualizamos la estructura del objeto
            Object_setlocation(o, -1);
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            intr_refresh(intr);
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            return OK;
        }
    }else if(dir == 3){
        y--;
        o = Object_find(obs, numobj, x, y, psid);
        if(o != NULL){
            if(strcmp(objeto, Object_getname(o))){
                //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                /* The object is not in your range */
                printf("%s",answers[2]);
                return OK;
            }
            // Actualizamos la estructura del objeto
            Object_setlocation(o, -1);
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            intr_refresh(intr);
            /* imprimir que se ha cogido con éxito */
            /* Descripción del objeto????? */
            return OK;
        }
    }
    /* else */
    
    return OK;
}

Status drop(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    Player * p;
    World * w;
    Object ** obs;
    Object * o;
    Space * s;
    char ** map;
    Intr * intr;
    int ret = 0; // Flag that says if you have the object to drop
    int flag = 0; // Tells if the object exists in the world
    int x; // Coordinate x of the object
    int y; // Coordinate y of the object
    int numobj; // Number of objects
    int psid; // Id of the space where are you
    
    w = (World *) world;
    p = World_get_player(w);
    x = Player_get_coordinatex(p);
    y = Player_get_coordinatey(p);
    psid = Player_get_location(p);
    numobj = World_get_numberObject(w);
    obs = World_get_objectS(w);
    s = World_get_space(w, psid);
    map = Space_getMap(s);
    intr = World_get_interface(w);
    
    for(i = 0; i < numobj; i++){
        if(!strcmp(objeto, Object_getname(obs[i]))){
            flag = 1;
            if(Object_getlocation(obs[i] == -1)){
                ret = 1;
                o = obs[i];
            }
        }
    }
    
    if(flag == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* The object doesn't exist */
        printf("%s",answers[2]);
        return OK;
    }
    if(ret == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* You don't have that object */
        printf("%s",answers[1]);
        return OK;
    }
    
    if(map[x+1][y-1] == ' '){
        /* UP, RIGHT */
        Object_setlocation(o, psid);
        Object_setcoordinatex(o, x+1);
        Object_setcoordinatey(o, y-1);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        intr_refresh(intr);
        /* You dropped the object */
        printf("%s",answers[1]);
        return OK;
    }else if(map[x+1][y] == ' '){
        /* RIGHT */
        Object_setlocation(o, psid);
        Object_setcoordinatex(o, x+1);
        Object_setcoordinatey(o, y);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        intr_refresh(intr);
        /* You dropped the object */
        printf("%s",answers[1]);
        return OK;
    }else if(map[x+1][y+1] == ' '){
        /* DOWN, RIGHT */
        Object_setlocation(o, psid);
        Object_setcoordinatex(o, x+1);
        Object_setcoordinatey(o, y+1);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        intr_refresh(intr);
        /* You dropped the object */
        printf("%s",answers[1]);
        return OK;
    }else if(map[x][y+1] == ' '){
        /* DOWN */
        Object_setlocation(o, psid);
        Object_setcoordinatex(o, x);
        Object_setcoordinatey(o, y+1);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        intr_refresh(intr);
        /* You dropped the object */
        printf("%s",answers[1]);
        return OK;
    }else if(map[x-1][y+1] == ' '){
        /* DOWN, LEFT */
        Object_setlocation(o, psid);
        Object_setcoordinatex(o, x-1);
        Object_setcoordinatey(o, y+1);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        intr_refresh(intr);
        /* You dropped the object */
        printf("%s",answers[1]);
        return OK;
    }else if(map[x-1][y] == ' '){
        /* LEFT */
        Object_setlocation(o, psid);
        Object_setcoordinatex(o, x-1);
        Object_setcoordinatey(o, y);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        intr_refresh(intr);
        /* You dropped the object */
        printf("%s",answers[1]);
        return OK;
    }else if(map[x-1][y-1] == ' '){
        /* UP, LEFT */
        Object_setlocation(o, psid);
        Object_setcoordinatex(o, x-1);
        Object_setcoordinatey(o, y-1);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        intr_refresh(intr);
        /* You dropped the object */
        printf("%s",answers[1]);
        return OK;
    }else if(map[x][y-1] == ' '){
        /* UP */
        Object_setlocation(o, psid);
        Object_setcoordinatex(o, x);
        Object_setcoordinatey(o, y-1);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        intr_refresh(intr);
        /* You dropped the object */
        printf("%s",answers[1]);
        return OK;
    }
    /*else*/
    /* You can't drop it here */
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    printf("%s",answers[1]);
    return OK;
}

Status speak(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    Player * p;
    World * w;
    Npc ** npcs;
    Npc * n;
    Space * s;
    char ** map;
    Intr * intr;
    int ret = 0; // Flag that says if you have the object to drop
    int flag = 0; // Tells if the object exists in the world
    int x; // Coordinate x of the npc
    int y; // Coordinate y of the npc
    int numnpc; // Number of npcs
    int psid; // Id of the space where are you
    
    w = (World *) world;
    p = World_get_player(w);
    /* Por definir  esta función */
    dir = Player_get_direction(p);
    x = Player_get_coordinatex(p);
    y = Player_get_coordinatey(p);
    psid = Player_get_location(p);
    numnpc = World_get_numberNpc(w);
    npcs = World_get_npcS(w);
    s = World_get_space(w, psid);
    map = Space_getMap(s);
    intr = World_get_interface(w);
    
    for(i = 0; i < numnpc; i++){
        if(!strcmp(objeto, Npc_getname(npcs[i]))){
            flag = 1;
        }
    }
    
    if(flag == 0){
        //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
        /* That person doesn't exist. Maybe it's your imaginary friend... OR Do you know... speaking alone is something strange... */
        printf("%s",answers[2]);
        return OK;
    }
    /* UP, DOWN, LEFT, RIGHT */
    if(dir == 0){
        y--;
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){
            if(strcmp(objeto, Npc_getsymbol(n))){
                //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                /* The person is not in your range. Maybe you should try to yell... */
                printf("%s",answers[2]);
                return OK;
            }
            /* You started a talk with "name" "description". It seems that you are not as neerdy as you seem. */
            //ÁRBOL DE CONVERSACIÓN
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
    }else if(dir == 1){
        y++;
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){
            if(strcmp(objeto, Npc_getsymbol(n))){
                //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                /* The person is not in your range. Maybe you should try to yell... */
                printf("%s",answers[2]);
                return OK;
            }
            /* You started a talk with "name" "description". It seems that you are not as neerdy as you seem. */
            //ÁRBOL DE CONVERSACIÓN
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
    }else if(dir == 2){
        x--;
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){
            if(strcmp(objeto, Npc_getsymbol(n))){
                //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                /* The person is not in your range. Maybe you should try to yell... */
                printf("%s",answers[2]);
                return OK;
            }
            /* You started a talk with "name" "description". It seems that you are not as neerdy as you seem. */
            //ÁRBOL DE CONVERSACIÓN
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
            
    }else if(dir == 3){
        y--;
        n = Npc_find(npcs, numnpc, x, y, psid);
        if(n != NULL){
            if(strcmp(objeto, Npc_getsymbol(n))){
                //!!!!!!!!!!!!!!!!!!!!!!!!!!INDICES
                /* The person is not in your range. Maybe you should try to yell... */
                printf("%s",answers[2]);
                return OK;
            }
            /* You started a talk with "name" "description". It seems that you are not as neerdy as you seem. */
            //ÁRBOL DE CONVERSACIÓN
            //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        }
    }else{
        // no estoy seguro de si es necesario
        /* mensaje de error: no hay objeto que coger o algo así */
    }
    return OK;
}

Status sing(void * world, char * objeto, int n_ans, char ** answers){
    World * w;
    Intr * intr
    
    w = (World *) world;
    intr = World_get_interface(w);
    printf("%s", answers[0]);
}

Status yell(void * world, char * objeto, int n_ans, char ** answers){
    int i;
    World * w;
    Npc ** npcs;
    Intr * intr;
    int flag = 0; // Tells if the person exists in the world
    int numnpc; // Number of npcs
    int psid; // Id of the space where are you
    
    w = (World *) world;
    numnpc = World_get_numberNpc(w);
    npcs = World_get_npcS(w);
    intr = World_get_interface(w);
    for(i = 0; i < numnpc; i++){
        if(!strcmp(objeto, Npc_getname(npcs[i]))){
            flag = 1;
        }
    }
    if(flag == 0){
        prntf();
    }
}

int main(){
    Cop * cop;
    
    
    cop = cop_create("cop.txt");
    if(!cop){
        printf("No se ha creado el Cop\n");
        return 0;
    }
    if(ERROR == cop_assoc(cop, "move", /*Función move*/)){
        printf("No se ha hecho la asociación Move");
        return 0;
    }
    if(ERROR == cop_assoc(cop, "drop", /*Función move*/)){
        printf("No se ha hecho la asociación Drop");
        return 0;
    }
    if(ERROR == cop_assoc(cop, "pick", /*Función move*/)){
        printf("No se ha hecho la asociación Pick");
        return 0;
    }
    if(ERROR == cop_assoc(cop, "", /*Función move*/)){
        printf("No se ha hecho la asociación Move");
        return 0;
    }
    if(ERROR == cop_assoc(cop, "move", /*Función move*/)){
        printf("No se ha hecho la asociación Move");
        return 0;
    }
}