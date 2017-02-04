#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "interface.h"
#include <assert.h>
#include "shoot.h"
#include <time.h>

#define TIME1 50000
#define TIME2 30000
#define TIME3 100000
#define TIME4 50000

typedef struct _Enemy{
	Intr* intr;
	char symbol;
   	int  lastdir;
    int  xcoord;
    int  ycoord;
}Enemy;


typedef struct _Icicle{
    int  xcoord; 
    int  ycoord;
    int  dir; 
    char symbol;
}Icicle;

typedef struct _Mixture{
	Intr* intr;
	Enemy** enemies;
	Icicle* icicle;
	int exit; /* 0 if win 1 if lost*/
} Mixture;


Enemy* Enemy_ini(){
	Enemy* en;
	en=(Enemy*)malloc(sizeof(Enemy));
	en->lastdir = 2;
	en->symbol='&';
	return en;
}


Icicle* Icicle_ini(int x, int y, int dir){
	Icicle* ici;

	ici= (Icicle*)malloc(sizeof(Icicle));

	ici->dir=dir;
	if(dir==0){
		ici->xcoord = x;
		ici->ycoord = y - 1;
		ici->symbol = '*';
	}
	if(dir==1){
		ici->xcoord = x;
		ici->ycoord = y + 1;
		ici->symbol = '*';
	}
	if(dir==2){
		ici->xcoord = x + 1;
		ici->ycoord = y;
		ici->symbol = '*';

	}
	if(dir==3){
		ici->xcoord = x - 1;
		ici->ycoord = y;
		ici->symbol = '*';
	}

	return ici;

}

void Icicle_obliterate(Icicle* icicle){
	free(icicle);
	return;
}




Mixture* mix_ini(Intr* intr, Enemy** enemies){
	Mixture* mix;
	mix=(Mixture*)malloc(sizeof(Mixture));	
	mix->intr=intr;
	mix->enemies=enemies;
	mix->exit=0;
	return mix;

}

void mix_free(Mixture* mix){
	free(mix);
}

void print_enemy(Intr* intr, Enemy* en){
	intr_writeenemy(intr, en->ycoord, en->xcoord, en->symbol);
	return;
}

void print_icicle(Intr* intr, Icicle* ici){
	FILE* f;
	f=fopen("printicicle.txt", "w");
	fprintf(f, "antes de printicicle");
	fclose(f);
	intr_writeici(intr, ici->ycoord, ici->xcoord, ici->symbol);
	return;
}

void * player_movement(void* intr){
	char c;

	while(1){

		c = fgetc(stdin);
    	if(c == 27){
        /*]*/
        	c = fgetc(stdin);
        /*A,B,C or D*/
        	c = fgetc(stdin);
			intr_moveplayer(intr, c);
        
		}

	}
	return NULL;
}

/*In the original idea, you were suposed to kill the enemies with the icicle gun, it did not work really good*/
void * enemies_movement(void* mix){
	Enemy* enemy0, *enemy1, *enemy2, *enemy3, *enemy4, *enemy5, *enemy6;
	Intr* intr;
	Icicle* icicle;
	char ** map;
	int l1 = 1, l2 = 1 ,l3 = 1 , l4=1, l5=1, l6=1, l7=1;
	int x,y,xi,yi, dir, time = 400 ;
	int flag1 = 0, flag2 = 2 ;
	
	enemy0 = ((Mixture*)mix)->enemies[0];
	enemy1 = ((Mixture*)mix)->enemies[1];
	enemy2 = ((Mixture*)mix)->enemies[2];
	enemy3 = ((Mixture*)mix)->enemies[3];
	enemy4 = ((Mixture*)mix)->enemies[4];
	enemy5 = ((Mixture*)mix)->enemies[5];
	enemy6 = ((Mixture*)mix)->enemies[6];

	intr = ((Mixture*)mix)->intr;
	map = intr_getmap(intr);
	icicle = ((Mixture*)mix)->icicle;

	print_enemy(intr,enemy0);
	print_enemy(intr,enemy1);
	print_enemy(intr,enemy2);
	print_enemy(intr,enemy3);
	print_enemy(intr,enemy4);
	print_enemy(intr,enemy5);
	print_enemy(intr,enemy6);
	
	sleep(3);

	while(1){
		
		
		usleep(TIME4);
		y = intr_playergetrow(intr);
		x = intr_playergetcol(intr);
		
		
		if(x==enemy0->xcoord && y==enemy0->ycoord){
			((Mixture*)mix)->exit=1;
			return NULL;
		}
		else if(x==enemy1->xcoord && y==enemy1->ycoord){
			((Mixture*)mix)->exit=1;
			return NULL;
		}
		else if(x==enemy2->xcoord && y==enemy2->ycoord){
			((Mixture*)mix)->exit=1;
			return NULL;
		}
		else if(x==enemy3->xcoord && y==enemy3->ycoord){
			((Mixture*)mix)->exit=1;
			return NULL;
		}
		else if(x==enemy4->xcoord && y==enemy4->ycoord){
			((Mixture*)mix)->exit=1;
			return NULL;
		}


			if(l1 == 1){
				
				y = intr_playergetrow(intr);
				x = intr_playergetcol(intr);
				if(enemy0->xcoord<=x && enemy0->ycoord<=y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy0->xcoord;
						yi=enemy0->ycoord+1;
					}
					if(dir==1){
						xi=enemy0->xcoord+1;
						yi=enemy0->ycoord;
					}
				}
				else if(enemy0->xcoord<x && enemy0->ycoord>y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy0->xcoord;
						yi=enemy0->ycoord-1;
					}
					if(dir==1){
						xi=enemy0->xcoord+1;
						yi=enemy0->ycoord;
					}
				}
				else if(enemy0->xcoord>x && enemy0->ycoord<y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy0->xcoord;
						yi=enemy0->ycoord+1;
					}
					if(dir==1){
						xi=enemy0->xcoord-1;
						yi=enemy0->ycoord;
					}
				}
				else if(enemy0->xcoord>=x && enemy0->ycoord>=y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy0->xcoord;
						yi=enemy0->ycoord-1;
					}
					if(dir==1){
						xi=enemy0->xcoord-1;
						yi=enemy0->ycoord;
					}
				}
				if(map[yi][xi] == ' '){
					intr_writechar(intr, ' ', 0, enemy0->ycoord,enemy0->xcoord);
					enemy0->xcoord=xi;
					enemy0->ycoord=yi;
					print_enemy(intr,enemy0);
				}
			}

		
			
			if(l2 == 1){
				y = intr_playergetrow(intr);
				x = intr_playergetcol(intr);
				if(enemy1->xcoord<=x && enemy1->ycoord<=y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy1->xcoord;
						yi=enemy1->ycoord+1;
					}
					if(dir==1){
						xi=enemy1->xcoord+1;
						yi=enemy1->ycoord;
					}
				}
				else if(enemy1->xcoord<x && enemy1->ycoord>y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy1->xcoord;
						yi=enemy1->ycoord-1;
					}
					if(dir==1){
						xi=enemy1->xcoord+1;
						yi=enemy1->ycoord;
					}
				}
				else if(enemy1->xcoord>x && enemy1->ycoord<y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy1->xcoord;
						yi=enemy1->ycoord+1;
					}
					if(dir==1){
						xi=enemy1->xcoord-1;
						yi=enemy1->ycoord;
					}
				}
				else if(enemy1->xcoord>=x && enemy1->ycoord>=y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy1->xcoord;
						yi=enemy1->ycoord-1;
					}
					if(dir==1){
						xi=enemy1->xcoord-1;
						yi=enemy1->ycoord;
					}
				}
				
				if(map[yi][xi] ==' '){
					intr_writechar(intr, ' ', 0, enemy1->ycoord,enemy1->xcoord);
					enemy1->xcoord=xi;
					enemy1->ycoord=yi;
					print_enemy(intr,enemy1);
				}
			}
		
		
			if(l3 == 1){
				y = intr_playergetrow(intr);
				x = intr_playergetcol(intr);
				if(enemy2->xcoord<=x && enemy2->ycoord<=y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy2->xcoord;
						yi=enemy2->ycoord+1;
					}
					if(dir==1){
						xi=enemy2->xcoord+1;
						yi=enemy2->ycoord;
					}
				}
				else if(enemy2->xcoord<x && enemy2->ycoord>y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy2->xcoord;
						yi=enemy2->ycoord-1;
					}
					if(dir==1){
						xi=enemy2->xcoord+1;
						yi=enemy2->ycoord;
					}
				}
				else if(enemy2->xcoord>x && enemy2->ycoord<y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy2->xcoord;
						yi=enemy2->ycoord+1;
					}
					if(dir==1){
						xi=enemy2->xcoord-1;
						yi=enemy2->ycoord;
					}
				}
				else if(enemy2->xcoord>=x && enemy2->ycoord>=y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy2->xcoord;
						yi=enemy2->ycoord-1;
					}
					if(dir==1){
						xi=enemy2->xcoord-1;
						yi=enemy2->ycoord;
					}
				}
				
				if(map[yi][xi] == ' '){
					intr_writechar(intr, ' ', 0, enemy2->ycoord,enemy2->xcoord);
					enemy2->xcoord=xi;
					enemy2->ycoord=yi;
					print_enemy(intr,enemy2);
				}
			}

			
			
			if(l4 == 1){
				
				y = intr_playergetrow(intr);
				x = intr_playergetcol(intr);
				if(enemy3->xcoord<=x && enemy3->ycoord<=y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy3->xcoord;
						yi=enemy3->ycoord+1;
					}
					if(dir==1){
						xi=enemy3->xcoord+1;
						yi=enemy3->ycoord;
					}
				}
				else if(enemy3->xcoord<x && enemy3->ycoord>y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy3->xcoord;
						yi=enemy3->ycoord-1;
					}
					if(dir==1){
						xi=enemy3->xcoord+1;
						yi=enemy3->ycoord;
					}
				}
				else if(enemy3->xcoord>x && enemy3->ycoord<y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy3->xcoord;
						yi=enemy3->ycoord+1;
					}
					if(dir==1){
						xi=enemy3->xcoord-1;
						yi=enemy3->ycoord;
					}
				}
				else if(enemy3->xcoord>=x && enemy3->ycoord>=y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy3->xcoord;
						yi=enemy3->ycoord-1;
					}
					if(dir==1){
						xi=enemy3->xcoord-1;
						yi=enemy3->ycoord;
					}
				}
				if(map[yi][xi] == ' '){
					intr_writechar(intr, ' ', 0, enemy3->ycoord,enemy3->xcoord);
					enemy3->xcoord=xi;
					enemy3->ycoord=yi;
					print_enemy(intr,enemy3);
				}
			}

			if(l5 == 1){
				
				y = intr_playergetrow(intr);
				x = intr_playergetcol(intr);
				if(enemy4->xcoord<=x && enemy4->ycoord<=y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy4->xcoord;
						yi=enemy4->ycoord+1;
					}
					if(dir==1){
						xi=enemy4->xcoord+1;
						yi=enemy4->ycoord;
					}
				}
				else if(enemy4->xcoord<x && enemy4->ycoord>y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy4->xcoord;
						yi=enemy4->ycoord-1;
					}
					if(dir==1){
						xi=enemy4->xcoord+1;
						yi=enemy4->ycoord;
					}
				}
				else if(enemy4->xcoord>x && enemy4->ycoord<y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy4->xcoord;
						yi=enemy4->ycoord+1;
					}
					if(dir==1){
						xi=enemy4->xcoord-1;
						yi=enemy4->ycoord;
					}
				}
				else if(enemy4->xcoord>=x && enemy4->ycoord>=y){
					dir=rand()%2;
					if(dir==0){
						xi=enemy4->xcoord;
						yi=enemy4->ycoord-1;
					}
					if(dir==1){
						xi=enemy4->xcoord-1;
						yi=enemy4->ycoord;
					}
				}
				if(map[yi][xi] == ' '){
					intr_writechar(intr, ' ', 0, enemy4->ycoord,enemy4->xcoord);
					enemy4->xcoord=xi;
					enemy4->ycoord=yi;
					print_enemy(intr,enemy4);
				}
			}
			if(l6 == 1){
				
				xi = enemy5->xcoord;
				yi = enemy5->ycoord;
				
				if(flag1 == 0 && map[yi][xi+1] == ' '){
					intr_writechar(intr, ' ', 0, enemy5->ycoord,enemy5->xcoord);
					enemy5->xcoord=xi+1;
					enemy5->ycoord=yi;
					print_enemy(intr,enemy5);
				}
				else if(map[yi][xi+1] != ' '){
					flag1 = 1;
				}
				if (map[yi+1][xi] == ' ' && flag1 == 1){
					intr_writechar(intr, ' ', 0, enemy5->ycoord,enemy5->xcoord);
					enemy5->xcoord=xi;
					enemy5->ycoord=yi+1;
					print_enemy(intr,enemy5);
				}
				else if(map[yi+1][xi] != ' '){
					flag1 = 2;
				}
				if (map[yi][xi-1] == ' ' && flag1 == 2){
					intr_writechar(intr, ' ', 0, enemy5->ycoord,enemy5->xcoord);
					enemy5->xcoord=xi-1;
					enemy5->ycoord=yi;
					print_enemy(intr,enemy5);
				}
				else if(map[yi][xi-1] != ' '){
					flag1 = 3;
				}
				if (map[yi-1][xi] == ' ' && flag1 == 3) {
					intr_writechar(intr, ' ', 0, enemy5->ycoord,enemy5->xcoord);
					enemy5->xcoord=xi;
					enemy5->ycoord=yi-1;
					print_enemy(intr,enemy5);
				}
				else if(map[yi-1][xi] != ' ') {
					flag1 = 0;
				}


			}
			if(l7 == 1){
				
				xi = enemy6->xcoord;
				yi = enemy6->ycoord;
				
				if(flag2 == 0 && map[yi][xi+2] == ' '){
					intr_writechar(intr, ' ', 0, enemy6->ycoord,enemy6->xcoord);
					enemy6->xcoord=xi+1;
					enemy6->ycoord=yi;
					print_enemy(intr,enemy6);
				}
				else if(map[yi][xi+2] != ' '){
					flag2 = 1;
				}
				if (map[yi+2][xi] == ' ' && flag2 == 1){
					intr_writechar(intr, ' ', 0, enemy6->ycoord,enemy6->xcoord);
					enemy6->xcoord=xi;
					enemy6->ycoord=yi+1;
					print_enemy(intr,enemy6);
				}
				else if(map[yi+2][xi] != ' '){
					flag2 = 2;
				}
				if (map[yi][xi-2] == ' ' && flag2 == 2){
					intr_writechar(intr, ' ', 0, enemy6->ycoord,enemy6->xcoord);
					enemy6->xcoord=xi-1;
					enemy6->ycoord=yi;
					print_enemy(intr,enemy6);
				}
				else if(map[yi][xi-2] != ' '){
					flag2 = 3;
				}
				if (map[yi-2][xi] == ' ' && flag2 == 3) {
					intr_writechar(intr, ' ', 0, enemy6->ycoord,enemy6->xcoord);
					enemy6->xcoord=xi;
					enemy6->ycoord=yi-1;
					print_enemy(intr,enemy6);
				}
				else if(map[yi-2][xi] != ' '){
					flag2 = 0;
				}


			}
		

		time --;
		if(time == 0)
			return NULL;
	}
}

void * icicle_movement(void* mix){
	char ** map;
	int x, y, dir;
	
	
	map = intr_getmap(((Mixture*)mix)->intr);
	
	
	while(1){

		sleep(0.2);
			
    	
        	
        	y = intr_playergetrow(((Mixture*)mix)->intr);
			x = intr_playergetcol(((Mixture*)mix)->intr);
			dir = intr_playergetdir(((Mixture*)mix)->intr);
			

        	((Mixture*)mix)->icicle= Icicle_ini(x, y, dir);
        	
        	y = ((Mixture*)mix)->icicle->ycoord;
        	x = ((Mixture*)mix)->icicle->xcoord;

        	if(map[y][x] == ' '){
        		print_icicle(((Mixture*)mix)->intr,((Mixture*)mix)->icicle);
        	
        		if(dir==0){

        			while(map[y-1][x] == ' '){
        				usleep(TIME1);
        				intr_writechar(((Mixture*)mix)->intr, ' ', 0, y, x);
        				((Mixture*)mix)->icicle->ycoord--;
        				y--;
        				print_icicle(((Mixture*)mix)->intr,((Mixture*)mix)->icicle);
        			}
        		}
        		else if (dir==1){
        			while(map[y+1][x] == ' '){
        				usleep(TIME1);
        				intr_writechar(((Mixture*)mix)->intr, ' ', 0, y, x);
        				((Mixture*)mix)->icicle->ycoord++;
        				y++;
        				print_icicle(((Mixture*)mix)->intr,((Mixture*)mix)->icicle);
        			}

        		}
        		else if (dir==2){
        			while(map[y][x+1] == ' '){
        				usleep(TIME2);
        				intr_writechar(((Mixture*)mix)->intr, ' ', 0, y, x);
        			
        				((Mixture*)mix)->icicle->xcoord++;
        				x++;
        				print_icicle(((Mixture*)mix)->intr,((Mixture*)mix)->icicle);
        			}

        		}
        		else if (dir==3){
        			while(map[y][x-1] == ' '){
        				usleep(TIME2);
        				intr_writechar(((Mixture*)mix)->intr, ' ', 0, y, x);
        				((Mixture*)mix)->icicle->xcoord--;
        				x--;
        				print_icicle(((Mixture*)mix)->intr,((Mixture*)mix)->icicle);
        			}

        		}
        	}
        	
        	Icicle_obliterate(((Mixture*)mix)->icicle);	
    }

	
}


/*nenemies will probably be 3 always*/
int iciclegame(Intr* intr){
	int i;
	Enemy** enemies;
	Mixture* mix;
	pthread_t movement[3]; /*Player, enemies, icicle*/

	assert(intr!=NULL);

	
	intr_changemap(intr,24);
	intr_refresh(intr);
	intr_printborders(intr);
	

	intr_teleportplayer(intr, 75, 13, 3);
	
	intr_writechoppedstring(intr, "Be careful with the poison red rats... your weapons are completely useless :)", 3, 1, 1);
	
	enemies=(Enemy**)malloc(7*sizeof(Enemy*));
	if(!enemies) return -1;
	for(i=0;i<7;i++){
		enemies[i]=Enemy_ini();
	}
	for(i=0; i<3;i++){
		enemies[i]->xcoord = 2;
		enemies[i]->ycoord = 12*i+2;
	}
	enemies[3]->xcoord = 74;
	enemies[3]->ycoord = 1;
	enemies[4]->xcoord = 74;
	enemies[4]->ycoord = 27;
	enemies[5]->xcoord = 74;
	enemies[5]->ycoord = 1;
	enemies[6]->xcoord = 65;
	enemies[6]->ycoord = 25;

	mix = mix_ini(intr,	enemies);
	
	/*player*/
    pthread_create(movement+0, NULL, player_movement, (void *) intr); 
    /*icicle*/
    /*icicle_movement((void*) mix);*/
    pthread_create(movement+1, NULL, icicle_movement, (void *) mix);   
    pthread_create(movement+2, NULL, enemies_movement, (void *) mix);
    
    


    pthread_join(movement[2], NULL);
    

    pthread_cancel(movement[0]);
    pthread_cancel(movement[1]);
    pthread_cancel(movement[2]);


    for(i=0;i<7;i++){
    	free(enemies[i]);
    }


    free(mix);

    intr_cleargap(intr, 3);

    if(mix->exit == 0){
    	intr_writestring(intr, "You won this time! It must be good enough distraction.", 3, 1, 1);
    	return 0;
    }

    if(mix->exit == 1){
    	intr_writestring(intr, "You lost this time! Try again!", 3, 1, 1);
    	return 1;
    }
    
    
    

	return 0; 

}

