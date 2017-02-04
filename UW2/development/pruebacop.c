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
#include "copfunctions.h"
#include <assert.h>

int main() {

Intr* intr;
World* w;
Space** spaces;
Object** objects;
Npc** npcs;
int nsp, nob, nnpc;
int i, j;
int flag = 0;
char command[50];
char firstchar;
Cop* c; 

FILE * f;
f= fopen("pruebaalejo.txt", "w");
fprintf(f, "main\n");

c = cop_create("cop.txt");

if(ERROR == cop_assoc(c, "talk_i", talk)){
        printf("No se ha hecho la asociación TALK");
        return 0;
}
if(ERROR == cop_assoc(c, "drop_i", drop)){
        printf("No se ha hecho la asociación DROP");
        return 0;
}
if(ERROR == cop_assoc(c, "pick_i", pick)){
        printf("No se ha hecho la asociación PICK");
        return 0;
}
if(ERROR == cop_assoc(c, "sing_i", sing)){
        printf("No se ha hecho la asociación SING");
        return 0;
}
if(ERROR == cop_assoc(c, "give_i", give)){
        printf("No se ha hecho la asociación GIVE");
        return 0;
}
if(ERROR == cop_assoc(c, "askfor_i", askfor)){
        printf("No se ha hecho la asociación ASKFOR");
        return 0;
}
if(ERROR == cop_assoc(c, "openwith_i", openwith)){
        printf("No se ha hecho la asociación OPENWITH");
        return 0;
}
if(ERROR == cop_assoc(c, "read_i", read)){
        printf("No se ha hecho la asociación READ");
        return 0;
}
if(ERROR == cop_assoc(c, "take_i", take)){
        printf("No se ha hecho la asociación READ");
        return 0;
}
if(ERROR == cop_assoc(c, "jump_i", jump)){
        printf("No se ha hecho la asociación READ");
        return 0;
}
if(ERROR == cop_assoc(c, "get_i", get)){
        printf("No se ha hecho la asociación READ");
        return 0;
}
if(ERROR == cop_assoc(c, "cut_i", cut)){
        printf("No se ha hecho la asociación READ");
        return 0;
}
if(ERROR == cop_assoc(c, "error", error)){
        printf("No se ha hecho la asociación ERROR");
        return 0;
}
system ("export PS1=\"\"");
system ("/bin/stty raw");
system("setterm -cursor off");
system("stty -echo");
system("resize -s 100 200");
system("clear");


/*World lee y carga todo*/
spaces = game_readSpace("maps.txt", &nsp);
objects = game_readObject("objetos.txt", &nob);
npcs = game_readNpc("npcs.txt", &nnpc);

w = World_create(objects , spaces, npcs, &nob, &nsp, &nnpc);
if(w == NULL) return 0;
fprintf(f, "main world creado no nulo\n");




intr = intr_ini();
intr_setspaces(intr, spaces);
intr_setobjects(intr, objects);
intr_setnpcs(intr,npcs);
intr_changemap(intr,22);
intr_refresh(intr);
intr_printborders(intr);
intr_printcmdhelp(intr);

 
World_add_interface(w, intr);

while(1){

	firstchar= fgetc(stdin);
    if(firstchar == 27){
        /*]*/
        firstchar = fgetc(stdin);
        /*A,B,C or D*/
        firstchar = fgetc(stdin);
		intr_moveplayer(intr, firstchar);
        
	}

	else if(firstchar == 'q')
		break;
	
	else{
        flag = 0;
		intr_writechar(intr, firstchar, 2, 0, 0);
		i = 1;
        command[0]=firstchar;
		while(i < 50 /* maxchar */){
			firstchar = fgetc(stdin);
            /* 127 es el delete */
			if(firstchar == 127){
				//reduces i "borras" reduces otra vez i porque si no luego escribirias mal
				if(i > 0){
					i--;
				}
				// '00' NULL en ASCII
				command[i] = 0;
				intr_writechar(intr, 32, 2, 0, i);
				i--;
			}else if(firstchar != 13){
				command[i] = firstchar;
				intr_writechar(intr, firstchar, 2, 0, i);
			}else {
				// 'enter'
                for(j = i; j >= 0; j--){
                    if(command[j] == ' ') flag = 1;
                }
                
				// creo que esto (v) no es necesario ya que command es memoria estatica
				command[i] = '\0';
                intr_cleargap(intr, 2);
                intr_cleargap(intr, 3);
				break;
			}
			
			
			i++;
		}
		if (flag == 1){

            cop_execute(c, command, (void *)w);
            intr_refresh(intr);
        }
	}


}


fclose(f);

intr_obliterate(intr); 
Spaces_free(spaces, nsp);
Objects_free(objects, nob);
cop_obliterate(c);
system("setterm -cursor on");
system("reset");
return 0;    

}
