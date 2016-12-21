#ifndef COP_H
#define COP_H

typedef struct _cop Cop;

typedef int (*pfun) (void * world, char * objeto, int n_ans, char ** answers); 

int cop_execute(CoP * c, char * cmd, void * world);
Cop * cop_create(char * file);
void cop_obliterate(Cop * cop);
Status cop_assoc(CoP * c, char * name, pfun f);

#endif /*COP_H*/