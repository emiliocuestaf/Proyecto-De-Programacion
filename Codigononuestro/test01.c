#include <world.h>
#include "space.h"
#include <stdio.h>

int dir() {
    char buf[10];
    while(1) {
        fgets(buf, 10, stdin);
        if (buf[0] == 'n')
            return NORTH;
        else if (buf[0] == 's')
            return SOUTH;
        else if (buf[0] == 'e')
            return EAST;
        else if (buf[0] == 'w')
            return WEST;
    }
}


main(int argc, char **argv) {

    world *w;
    
    w = world_create(argv[1]);
    player *p = w_get_p(w);

    while(1) {
        int cur_sp = player_whereIsPlayer(p);
        space *sp = w_getSpaceById(w, cur_sp);
        printf("%s\n", Space_getDesc(sp);
        
        Move d = dir();
        space *nx = Space_getNeighRoom(sp, d);
        if (!nx) {
            printf("oops...\n");
        }
        else {
            player_moveSpaces(p, Space_getID(nx);
        }
    }
    
}
