
char*** maps_ini(char *fname){
  FILE *fp = fopen(fname, "r");
  
  char *buf;
  int i,j;
  
  int nmaps = atoi(buf = fgetll(fp));
  
  char*** maps = (char***)malloc(nmaps*sizeof(char**));
  
  assert(maps);
  
  int bdrow = atoi(buf = fgetll(fp));  
  int bdcol = atoi(buf = fgetll(fp));  
  
  
  for (i=0; i < nmaps; i++){
    maps**[i] = (char**) malloc (bdrow*sizeof(char*));
    assert(maps[i]);
    
    for (int i=0; i<bdrow; i++) {
    map[i] = fgetll(fp);
    }
    
  }
  
  return maps;
}



/*
  Creates the interface reading the data from a text file (given as a
  parameter), and displays it. Returns the interface handle.
*/
intrf *_intrf_ini(char *fname) {
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

  i_set_info_caption(itf, caption, crow, ccol, srow, scol);
  
   *caption = fgetll(fp);
   crow = atoi(buf = fgetll(fp));  //free(buf);
   ccol = atoi(buf = fgetll(fp));  //free(buf);
   srow = atoi(buf = fgetll(fp));  //free(buf);
   scol = atoi(buf = fgetll(fp));  //free(buf);

  i_set_info_caption(itf, caption, crow, ccol, srow, scol);
  
  
  int nmaps = atoi(buf = fgetll(fp));

  char player = (buf = fgetll(fp))[0];  //free(buf);
  int prow = atoi(buf = fgetll(fp));  //free(buf);
  int pcol = atoi(buf = fgetll(fp));  //free(buf);
  
  ppp= atoi(buf = fgetll(fp));  //free(buf);
  
  i_set_play_data(itf, player, prow, pcol, pellet, pellet_no);

  int bdrow = atoi(buf = fgetll(fp));  //free(buf);
  int bdcol = atoi(buf = fgetll(fp));  //free(buf);
  
  
  char ***map = (char **) malloc(bdrow*sizeof(char *));
  for (int i=0; i<bdrow; i++) {
    map[i] = fgetll(fp);
  }
  i_set_board(itf, bdrow, bdcol, map);

  fclose(fp);
  
  return itf;
}
