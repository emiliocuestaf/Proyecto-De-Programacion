#include <stdio.h>
#include <stdlib.h>    
#include <stdio.h>    
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <lineread.h>
#include <intrf.h>
#include <qrnd.h>
#include <termios.h>


struct termios initial;

/*
  Initializes the terminal in such a way that we can read the input
  without echo on the screen
*/
void _term_init() {
	struct termios new;	          /*a termios structure contains a set of attributes about 
					  how the terminal scans and outputs data*/
		
	tcgetattr(fileno(stdin), &initial);    /*first we get the current settings of out 
						 terminal (fileno returns the file descriptor 
						 of stdin) and save them in initial. We'd better 
						 restore them later on*/
	new = initial;	                      /*then we copy them into another one, as we aren't going 
						to change ALL the values. We'll keep the rest the same */
	new.c_lflag &= ~ICANON;	              /*here we are setting up new. This line tells to stop the 
						canonical mode (which means waiting for the user to press 
						enter before sending)*/
	new.c_lflag &= ~ECHO;                 /*by deactivating echo, we tell the terminal NOT TO 
						show the characters the user is pressing*/
	new.c_cc[VMIN] = 1;                  /*this states the minimum number of characters we have 
					       to receive before sending is 1 (it means we won't wait 
					       for the user to press 2,3... letters)*/
	new.c_cc[VTIME] = 0;	              /*I really have no clue what this does, it must be somewhere in the book tho*/
	new.c_lflag &= ~ISIG;                 /*here we discard signals: the program won't end even if we 
						press Ctrl+C or we tell it to finish*/

	tcsetattr(fileno(stdin), TCSANOW, &new);  /*now we SET the attributes stored in new to the 
						    terminal. TCSANOW tells the program not to wait 
						    before making this change*/
}

/*
  Creates the interface reading the data from a text file (given as a
  parameter), and displays it. Returns the interface handle.
*/
intrf *_intrf_init(char *fname) {
  FILE *fp = fopen(fname, "r");

  char *buf;

  int rows = atoi(buf = fgetll(fp));  //free(buf);
  int cols = atoi(buf = fgetll(fp));  //free(buf);
  int field = atoi(buf = fgetll(fp));  //free(buf);
  intrf *itf = i_create(rows, cols, field);

  char *caption = fgetll(fp);
  int crow = atoi(buf = fgetll(fp));  //free(buf);
  int ccol = atoi(buf = fgetll(fp));  //free(buf);
  int srow = atoi(buf = fgetll(fp));  //free(buf);
  int scol = atoi(buf = fgetll(fp));  //free(buf);

  i_set_score_caption(itf, caption, crow, ccol, srow, scol);

  char player = (buf = fgetll(fp))[0];  //free(buf);
  int prow = atoi(buf = fgetll(fp));  //free(buf);
  int pcol = atoi(buf = fgetll(fp));  //free(buf);
  pellet = (buf = fgetll(fp))[0];  //free(buf);
  pellet_no= atoi(buf = fgetll(fp));  //free(buf);
  ppp= atoi(buf = fgetll(fp));  //free(buf);
  
  i_set_play_data(itf, player, prow, pcol, pellet, pellet_no);

  int bdrow = atoi(buf = fgetll(fp));  //free(buf);
  int bdcol = atoi(buf = fgetll(fp));  //free(buf);
  
  char **map = (char **) malloc(bdrow*sizeof(char *));
  for (int i=0; i<bdrow; i++) {
    map[i] = fgetll(fp);
  }
  i_set_board(itf, bdrow, bdcol, map);

  fclose(fp);
  
  return itf;
}


/*
  Adds a pellet in a random position of the board in which there is a
  blank space
*/
int _add_pellet(intrf *itf) {
  rnd_state *rndgen = r_init((long) time(NULL));
  while(1) {
    int r = (int) (i_rnd(rndgen) % itf->map_rows);
    int c = (int) (i_rnd(rndgen) % itf->map_cols);
    int q = i_add_pellet(itf, r, c);
    if (q < 0) {
      r_end(rndgen);
      return 0;
    }
    else if (q > 0) {
      r_end(rndgen);
      return 1;      
    }
  }
}


/*
  Reads a key from the keyboard. If the key is a "regular" key it
  returns its ascii code; if it is an arrow key, it returns one of the
  four interface directions with the "minus" sign
*/
int _read_key() {
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

int main(int argc, char **argv) {

  intrf *iq = _intrf_init(argv[1]);
  i_draw_board(iq, 0);

  for (int i=0; i<pellet_no; i++)
    _add_pellet(iq);

  _term_init();


  while(1) {
    int c = _read_key();
    if (c == 'q') {
      tcsetattr(fileno(stdin), TCSANOW, &initial);	/*We now restore the settings we back-up'd 
							  so that the termial behaves normally when 
							  the program ends */
      exit(0);
    }
    else if (c <= 0) {
      i_move(iq, -c);
      if (i_is_on_pellet(iq)) {
	i_remove_pellet(iq, iq->p_row,iq->p_col);
	_add_pellet(iq);
	i_set_score(iq, score += ppp);
      }
    }

  }

} 