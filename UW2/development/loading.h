#ifndef LOADING_H
#define LOADING_H

#include "types.h"
#include "space.h"
#include "object.h"
#include "npc.h"

Space**  game_readSpace(char *fname, int * nsp);
Object ** game_readObject(char * file, int * nob);
Npc ** game_readNpc(char * file, int * nnpc);

#endif /*LOADING_H*/