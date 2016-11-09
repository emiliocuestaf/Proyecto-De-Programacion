#include "world.h"



int _dir() {
  char choice;
  choice = fgetc(stdin);


  if (choice == 27 && fgetc(stdin) == '[') { /* The key is an arrow key */
    choice = fgetc(stdin);

    switch(choice) {
    case('A'):
      return -NORTH;
    case('B'):
      return -SOUTH;
    case('C'):
      return -EAST;
    case('D'):
      return -WEST;
    default:
      return -HERE;
    }
  }
  else
    return choice;
}

main(int argc, char **argv){
  
  world * w;
  
  w = world_create(argv[1]);
  player *p = w_get_p(w);
  
  while(1){
    
  }
}