#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "world.h"
#include <time.h>
#include "animations.h"

#define SHORTTIME  200000
#define SHORTERTIME 100000
#define LONGTIME   2000000
#define TEXTTIME   80000

/*void  intr_writechar(Intr* intr, char c, int select, int row, int  col);*/
/*void intr_writechoppedstring(Intr* intr, char* str, int select, int row, int col);*/

/*You go inside  the EPS and the mysterious man gives you a copy oif the EDAT exam*/
void animation1(Intr* intr){
	int i;
	char * aux = NULL;

	intr_changemap(intr, 3);
	intr_cleargap(intr,3);
	intr_writechar(intr,'v', 0, 2, 40);

	intr_writechar(intr,'?', 0, 12, 39);

	usleep(LONGTIME);
	intr_writechar(intr,'<', 0, 11, 39);
	intr_writechar(intr,'3', 0, 11, 40);
	intr_writechar(intr,'<', 0, 12, 37);
	intr_writechar(intr,'3', 0, 12, 38);
	intr_writechar(intr,'<', 0, 13, 39);
	intr_writechar(intr,'3', 0, 13, 40);
	intr_writechar(intr,'<', 0, 12, 41);
	intr_writechar(intr,'3', 0, 12, 42);
	usleep(SHORTTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	intr_writechar(intr,' ', 0, 11, 40);
	intr_writechar(intr,' ', 0, 12, 37);
	intr_writechar(intr,' ', 0, 12, 38);
	intr_writechar(intr,' ', 0, 13, 39);
	intr_writechar(intr,' ', 0, 13, 40);
	intr_writechar(intr,' ', 0, 12, 41);
	intr_writechar(intr,' ', 0, 12, 42);
	usleep(SHORTTIME);

	intr_writechar(intr,'<', 0, 11, 39);
	intr_writechar(intr,'3', 0, 11, 40);
	intr_writechar(intr,'<', 0, 12, 37);
	intr_writechar(intr,'3', 0, 12, 38);
	intr_writechar(intr,'<', 0, 13, 39);
	intr_writechar(intr,'3', 0, 13, 40);
	intr_writechar(intr,'<', 0, 12, 41);
	intr_writechar(intr,'3', 0, 12, 42);
	usleep(SHORTTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	intr_writechar(intr,' ', 0, 11, 40);
	intr_writechar(intr,' ', 0, 12, 37);
	intr_writechar(intr,' ', 0, 12, 38);
	intr_writechar(intr,' ', 0, 13, 39);
	intr_writechar(intr,' ', 0, 13, 40);
	intr_writechar(intr,' ', 0, 12, 41);
	intr_writechar(intr,' ', 0, 12, 42);
	usleep(SHORTTIME);

	intr_writechar(intr,'<', 0, 11, 39);
	intr_writechar(intr,'3', 0, 11, 40);
	intr_writechar(intr,'<', 0, 12, 37);
	intr_writechar(intr,'3', 0, 12, 38);
	intr_writechar(intr,'<', 0, 13, 39);
	intr_writechar(intr,'3', 0, 13, 40);
	intr_writechar(intr,'<', 0, 12, 41);
	intr_writechar(intr,'3', 0, 12, 42);
	usleep(SHORTTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	intr_writechar(intr,' ', 0, 11, 40);
	intr_writechar(intr,' ', 0, 12, 37);
	intr_writechar(intr,' ', 0, 12, 38);
	intr_writechar(intr,' ', 0, 13, 39);
	intr_writechar(intr,' ', 0, 13, 40);
	intr_writechar(intr,' ', 0, 12, 41);
	intr_writechar(intr,' ', 0, 12, 42);
	usleep(SHORTTIME);

	intr_writechar(intr,'<', 0, 11, 39);
	intr_writechar(intr,'3', 0, 11, 40);
	intr_writechar(intr,'<', 0, 12, 37);
	intr_writechar(intr,'3', 0, 12, 38);
	intr_writechar(intr,'<', 0, 13, 39);
	intr_writechar(intr,'3', 0, 13, 40);
	intr_writechar(intr,'<', 0, 12, 41);
	intr_writechar(intr,'3', 0, 12, 42);
	usleep(SHORTTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	intr_writechar(intr,' ', 0, 11, 40);
	intr_writechar(intr,' ', 0, 12, 37);
	intr_writechar(intr,' ', 0, 12, 38);
	intr_writechar(intr,' ', 0, 13, 39);
	intr_writechar(intr,' ', 0, 13, 40);
	intr_writechar(intr,' ', 0, 12, 41);
	intr_writechar(intr,' ', 0, 12, 42);
	usleep(SHORTTIME);

	intr_writechar(intr,'!', 0, 11, 39);
	usleep(SHORTERTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	usleep(SHORTERTIME);
	intr_writechar(intr,'!', 0, 11, 39);
	usleep(SHORTERTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	usleep(SHORTERTIME);
	intr_writechar(intr,'!', 0, 11, 39);
	usleep(SHORTERTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	usleep(SHORTERTIME);


	for(i=38;i>=20;i--){
		intr_writechar(intr,' ', 0, 12, i+1);
		intr_writechar(intr,'?', 0, 12, i);
		usleep(SHORTTIME);
	}

	for(i=11;i>=6;i--){
		intr_writechar(intr,' ', 0, i+1, 20);
		intr_writechar(intr,'?', 0, i, 20);
		usleep(SHORTTIME);
	}

	for(i=21;i<=40;i++){
		intr_writechar(intr,' ', 0, 6, i-1);
		intr_writechar(intr,'?', 0, 6, i);
		usleep(SHORTTIME);
	}

	for(i=5;i>=3;i--){
		intr_writechar(intr,' ', 0, i+1, 40);
		intr_writechar(intr,'?', 0, i, 40);
		usleep(SHORTTIME);
	}


	aux = (char *) malloc(200 * sizeof(char));
	sprintf(aux, "Mysterious-man: Hey you, take this copy of the EDAT's exam, it may be useful for you...");
	for(i = 0; i < strlen(aux); i++){
		if(i / 80 == 1){
			intr_writechar(intr,aux[i], 3, 1,  i - 80);
		}else{
			intr_writechar(intr,aux[i], 3, 0,  i);
		}
		usleep(TEXTTIME);
	}

	sprintf(aux, "You: Who are you? Why should I trust you?");
	for(i = 0; i < strlen(aux); i++){
		if(i / 80 == 1){
			intr_writechar(intr,aux[i], 3, 4,  i - 80);
		}else{
			intr_writechar(intr,aux[i], 3, 3,  i);
		}
		usleep(TEXTTIME);
	}
	sprintf(aux, "Mysterious-man:  You'll have to answer those questions by yourself. See ya!");
	for(i = 0; i < strlen(aux); i++){
		if(i / 80 == 1){
			intr_writechar(intr,aux[i], 3, 6,  i - 80);
		}else{
			intr_writechar(intr,aux[i], 3, 5,  i);
		}
		usleep(TEXTTIME);
	}
	usleep(LONGTIME);

	intr_writechar(intr, ' ', 0, 3, 40);
	intr_writechar(intr,'?', 0, 3, 41);
	usleep(SHORTTIME);
	intr_writechar(intr, ' ', 0, 3, 41);
	intr_writechar(intr,'?', 0, 2, 41);
	usleep(SHORTTIME);
	intr_writechar(intr, ' ', 0, 2, 41);
	intr_writechar(intr,'?', 0, 1, 41);
	usleep(SHORTTIME);
	intr_writechar(intr, ' ', 0, 1, 41);

	intr_changemap(intr,3);
	intr_refresh(intr);

	return;

}


void animation2(Intr* intr){
	int i;
	char * aux = NULL;

	intr_changemap(intr, 3);
	intr_cleargap(intr,3);

	intr_writechar(intr,'>', 0, 13, 2);


	intr_writechar(intr,'?', 0, 12, 39);
	usleep(LONGTIME);

	intr_writechar(intr,'<', 0, 11, 39);
	intr_writechar(intr,'3', 0, 11, 40);
	intr_writechar(intr,'<', 0, 12, 37);
	intr_writechar(intr,'3', 0, 12, 38);
	intr_writechar(intr,'<', 0, 13, 39);
	intr_writechar(intr,'3', 0, 13, 40);
	intr_writechar(intr,'<', 0, 12, 41);
	intr_writechar(intr,'3', 0, 12, 42);
	usleep(SHORTTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	intr_writechar(intr,' ', 0, 11, 40);
	intr_writechar(intr,' ', 0, 12, 37);
	intr_writechar(intr,' ', 0, 12, 38);
	intr_writechar(intr,' ', 0, 13, 39);
	intr_writechar(intr,' ', 0, 13, 40);
	intr_writechar(intr,' ', 0, 12, 41);
	intr_writechar(intr,' ', 0, 12, 42);
	usleep(SHORTTIME);

	intr_writechar(intr,'<', 0, 11, 39);
	intr_writechar(intr,'3', 0, 11, 40);
	intr_writechar(intr,'<', 0, 12, 37);
	intr_writechar(intr,'3', 0, 12, 38);
	intr_writechar(intr,'<', 0, 13, 39);
	intr_writechar(intr,'3', 0, 13, 40);
	intr_writechar(intr,'<', 0, 12, 41);
	intr_writechar(intr,'3', 0, 12, 42);
	usleep(SHORTTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	intr_writechar(intr,' ', 0, 11, 40);
	intr_writechar(intr,' ', 0, 12, 37);
	intr_writechar(intr,' ', 0, 12, 38);
	intr_writechar(intr,' ', 0, 13, 39);
	intr_writechar(intr,' ', 0, 13, 40);
	intr_writechar(intr,' ', 0, 12, 41);
	intr_writechar(intr,' ', 0, 12, 42);
	usleep(SHORTTIME);

	intr_writechar(intr,'<', 0, 11, 39);
	intr_writechar(intr,'3', 0, 11, 40);
	intr_writechar(intr,'<', 0, 12, 37);
	intr_writechar(intr,'3', 0, 12, 38);
	intr_writechar(intr,'<', 0, 13, 39);
	intr_writechar(intr,'3', 0, 13, 40);
	intr_writechar(intr,'<', 0, 12, 41);
	intr_writechar(intr,'3', 0, 12, 42);
	usleep(SHORTTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	intr_writechar(intr,' ', 0, 11, 40);
	intr_writechar(intr,' ', 0, 12, 37);
	intr_writechar(intr,' ', 0, 12, 38);
	intr_writechar(intr,' ', 0, 13, 39);
	intr_writechar(intr,' ', 0, 13, 40);
	intr_writechar(intr,' ', 0, 12, 41);
	intr_writechar(intr,' ', 0, 12, 42);
	usleep(SHORTTIME);

	intr_writechar(intr,'<', 0, 11, 39);
	intr_writechar(intr,'3', 0, 11, 40);
	intr_writechar(intr,'<', 0, 12, 37);
	intr_writechar(intr,'3', 0, 12, 38);
	intr_writechar(intr,'<', 0, 13, 39);
	intr_writechar(intr,'3', 0, 13, 40);
	intr_writechar(intr,'<', 0, 12, 41);
	intr_writechar(intr,'3', 0, 12, 42);
	usleep(SHORTTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	intr_writechar(intr,' ', 0, 11, 40);
	intr_writechar(intr,' ', 0, 12, 37);
	intr_writechar(intr,' ', 0, 12, 38);
	intr_writechar(intr,' ', 0, 13, 39);
	intr_writechar(intr,' ', 0, 13, 40);
	intr_writechar(intr,' ', 0, 12, 41);
	intr_writechar(intr,' ', 0, 12, 42);
	usleep(SHORTTIME);


	intr_writechar(intr,'!', 0, 11, 39);
	usleep(SHORTERTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	usleep(SHORTERTIME);
	intr_writechar(intr,'!', 0, 11, 39);
	usleep(SHORTERTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	usleep(SHORTERTIME);
	intr_writechar(intr,'!', 0, 11, 39);
	usleep(SHORTERTIME);
	intr_writechar(intr,' ', 0, 11, 39);
	usleep(SHORTERTIME);


	for(i=12;i<=22;i++){
		intr_writechar(intr,' ', 0, i-1, 39);
		intr_writechar(intr,'?', 0, i, 39);
		usleep(SHORTTIME);
	}

	for(i=38;i>=30;i--){
		intr_writechar(intr,' ', 0, 22, i+1);
		intr_writechar(intr,'?', 0, 22, i);
		usleep(SHORTTIME);
	}
	
	for(i=29;i>=20;i--){
		intr_writechar(intr,' ', 0, 22, i+1);
		intr_writechar(intr,'?', 0, 22, i);
		usleep(SHORTTIME);
	}

	for(i=21;i>=13;i--){
		intr_writechar(intr,' ', 0, i+1, 20);
		intr_writechar(intr,'?', 0, i, 20);
		usleep(SHORTTIME);
	}

	for(i=19;i>=3;i--){
		intr_writechar(intr,' ', 0, 13, i+1);
		intr_writechar(intr,'?', 0, 13, i);
		usleep(SHORTTIME);
	}


	aux = (char *) malloc(200 * sizeof(char));
	sprintf(aux, "Mysterious-man: Listen to me... quick...");
	for(i = 0; i < strlen(aux); i++){
		if(i / 80 == 1){
			intr_writechar(intr,aux[i], 3, 1,  i - 80);
		}else{
			intr_writechar(intr,aux[i], 3, 0,  i);
		}
		usleep(TEXTTIME);
	}

	sprintf(aux, "You: You again?! I'm so thankful for the EDAT exam you gave me...");
	for(i = 0; i < strlen(aux); i++){
		if(i / 80 == 1){
			intr_writechar(intr,aux[i], 3, 4,  i - 80);
		}else{
			intr_writechar(intr,aux[i], 3, 3,  i);
		}
		usleep(TEXTTIME);
	}
	sprintf(aux, "Mysterious-man: Paq have failed, Yujiackers are asking everyone in Veggies to fail the next exam or they will be killed, go and tell your BOSS!");
	for(i = 0; i < strlen(aux); i++){
		if(i / 80 == 1){
			intr_writechar(intr,aux[i], 3, 6,  i - 80);
		}else{
			intr_writechar(intr,aux[i], 3, 5,  i);
		}
		usleep(TEXTTIME);
	}

	usleep(LONGTIME);

	intr_writechar(intr, ' ', 0, 13, 3);
	intr_writechar(intr,'?', 0, 12, 3);
	usleep(SHORTTIME);
	intr_writechar(intr, ' ', 0, 12, 3);
	intr_writechar(intr,'?', 0, 12, 2);
	usleep(SHORTTIME);
	intr_writechar(intr, ' ', 0, 12, 2);
	intr_writechar(intr,'?', 0, 12, 1);
	usleep(SHORTTIME);
	intr_writechar(intr, ' ', 0, 12, 1);

	intr_changemap(intr,3);
	intr_refresh(intr);

	return;

}
