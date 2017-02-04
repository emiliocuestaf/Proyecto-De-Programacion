#ifndef COPFUNCTIONS_H
#define COPFUNCTIONS_H
#include <stdio.h>
#include "cop.h"
#include <string.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "world.h"
#include "loading.h"
#include "shoot.h"
#include "animations.h"
#include <assert.h>



Status take(void * world, char * objeto, int n_ans, char ** answers);
Status pick(void * world, char * objeto, int n_ans, char ** answers);
Status drop(void * world, char * objeto, int n_ans, char ** answers);
Status give(void * world, char * objeto, int n_ans, char ** answers);
Status openwith(void * world, char * objeto, int n_ans, char ** answers);
Status askfor(void * world, char * objeto, int n_ans, char ** answers);
Status talk(void * world, char * objeto, int n_ans, char ** answers);
Status sing(void * world, char * objeto, int n_ans, char ** answers);
Status cut(void * world, char * objeto, int n_ans, char ** answers);
Status read(void * world, char * objeto, int n_ans, char ** answers);
Status jump(void * world, char * objeto, int n_ans, char ** answers);
Status get(void * world, char * objeto, int n_ans, char ** answers);
Status error(void * world, char * objeto, int n_ans, char ** answers);











#endif /* COPFUNCTIONS_H */