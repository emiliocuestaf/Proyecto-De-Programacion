#include <stdio.h>
#include "interface.h"
#include "world.h"
#include "loading.h"

int main() {

Intr* intr;
Space** spaces;

system ("export PS1=\"\"");
system ("/bin/stty raw");
system("stty -echo");
system("resize -s 100 200");
system("clear");

/*World lee y carga todo*/
spaces = game_readSpace("maps.txt");
/*Imi + Impr bordes de interfaz*/

intr = intr_ini();
intr_setspaces(intr, spaces);
intr_changemap(intr,0);
intr_printborders(intr);


intr_moveplayer(intr);
intr_obliterate(intr);
Spaces_free(spaces, 14);
system("reset");
return 0;    

}


/*Cambios que tenemos que hacer:
1. 
1. modificar funciones de intr con id
2. modificar func. para que lean puertas
*/