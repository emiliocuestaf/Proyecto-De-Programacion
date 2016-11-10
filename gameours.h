#ifndef GAMEOURS_H
#define GAMEOURS_H

#include "types.h"
#include "space.h"
#include "object.h"
#include "npc.h"

Space**  game_readSpace(char *fname);
Object ** game_readObject(char * file);
Npc ** game_readNpc(char * file);




#endif /*GAME_OURS_H*/