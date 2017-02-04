#ifndef COP_H
#define COP_H

#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct _cop Cop;

typedef Status (*pfun) (void * world, char * objeto, int n_ans, char ** answers); 

int cop_execute(Cop * c, char * cmd, void * world);
Cop * cop_create(char * file);
void cop_obliterate(Cop * cop);
Status cop_assoc(Cop * c, char * name, pfun f);

#endif /*COP_H*/