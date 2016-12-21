#ifndef LOADING_H
#define LOADING_H

#include "types.h"
#include "space.h"
#include "object.h"
#include "npc.h"

Space**  game_readSpace(char *fname);
Object ** game_readObject(char * file);
Npc ** game_readNpc(char * file);

#endif /*LOADING_H*/