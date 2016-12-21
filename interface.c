#include "interface.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>




struct _intr{
  
  int nrows;
  int ncols;    
  Rectangle* playingfield;  /*ncols and nrows are data from rectangles structure*/
  Rectangle* data; /*data includes players info, objects and useful commands*/
  Rectangle* insertgap;
  Rectangle* textgap;
  
  /*Depends on the map displayed at the moment*/
  /*char **map;*/
  Space** spaces;
  int spid;
  char** map;

};

/*Equivalent to intrf_create but set without arguments. Doesn't set map*/

Intr* intr_ini(){
    
    Intr* intr;
    
    intr=(Intr*)malloc(sizeof(Intr));
    intr->ncols=125; /*Default values*/
    intr->nrows=52;
    
    /*reminder: rec_create(frow, fcol,  nrows, ncols, backgcol, foregcol) */
    
    intr->playingfield=rec_create(1,1, 31, 82, 40, 32); /*Default values*/
    intr->data=rec_create(1, 83, 31, 40, 40, 32);
    intr->insertgap=rec_create(32,1,10,82,40,32);
    intr->textgap=rec_create(32,83,10,40,40,32);
    
    intr->playingfield->lastrow=5;
    intr->playingfield->lastcol=5;

    return intr;
    
}

void intr_setspaces(Intr* intr, Space** spaces){
    intr->spaces=spaces;
    intr->spid = 0;
    intr->map = Space_getMap(intr->spaces[0]);
    return;
}

void intr_printborders(Intr* intr){
    
    rec_printborder(intr->playingfield);
    rec_printborder(intr->data);
    rec_printborder(intr->insertgap);
    rec_printborder(intr->textgap);
    return;
    
}
void intr_obliterate(Intr* intr){
    
    if(intr!=NULL){
        /*rec_clear(intrf->playingfield); */
        rec_obliterate(intr->playingfield);
        /*rec_clear(intrf->data); */
        rec_obliterate(intr->data);
        /*rec_clear(intrf->insertgap);*/
        rec_obliterate(intr->insertgap);
        /*rec_clear(intrf->textgap);*/
        rec_obliterate(intr->textgap);
        
        
        free(intr);
    }
    
    return;
    
}

 void intr_writestring(Intr* intr, char* str, int select, int row, int  col){
    Rectangle* rec;
    if (select==0)
        rec=intr->playingfield;
    if (select==1)
        rec= intr->data;
    if (select==2)
        rec=intr->insertgap;
    if(select==3)
        rec=intr->textgap;
    rec_writestring_v2(rec, row, col, str);
    rec=intr->playingfield;
    printf("%c[%d;%dH",27, rec->lastrow, rec->lastcol);
    return;
}


void map_print(char**c, int filas, int col){
    int i;
    for(i=0; i<filas; i++){
        printf("%s", c[i]);
    }
}



void intr_setmap(Intr* intr, int id){
    
    assert(intr != NULL);
    assert(id>=0);
    
    intr->spid = id;
    intr->map = Space_getMap(intr->spaces[intr->spid]);
    
    return;
}

void intr_drawmap(Intr* intr){
    int nrows, i;
    assert(intr != NULL);
    
    nrows = Space_getHeigh(intr->spaces[intr->spid]);
    
    for(i=0; i< nrows; i++){
        /*Third argument: 0=playing board, 1=other*/
	    intr_writestring(intr, intr->map[i], 0,  i+1, 1);
    }
    return;
}

/*DOESNT MAKE A COPY, THE CHANGES IN THE INTERFACE WILL BE DONE AT THE SPACES ARRAY*/
void intr_changemap(Intr* intr, int id){
    assert(intr!=NULL);
    assert(id>=0);
    
    rec_clear(intr->playingfield);
    intr_setmap(intr, id);
    intr_drawmap(intr);
    
    return;
    
}


int can_move(char** map, int row, int col){
    char c;

    if(row-2<0 || col-2<0||row-2>28||col-2>83)
	    return 0;
	    
    c=map[row-2][col-2]; //Adjust position in terminal to position in map[][] (space)
    if(c==' ' || c=='v'||c=='^'||c=='<'||c=='>' )
	    return 1;
    else
	    return 0;
}

void intr_moveplayer(Intr* intr){

    Rectangle* rec;
    char** map;
    int r1, c1, aux, newrow = 0, newcol = 0, ndoor=-1;
    char c, doorchar;
    char* msn;
    
     
    rec = intr->playingfield;
    c1 = rec->firstcol;
    r1 = rec->firstrow;
    msn=(char*)malloc(200*sizeof(char));
    

    printf("%c[%d;%dH",27,r1+rec->lastrow,c1+rec->lastcol);

    while(1){

        map = intr->map; 
        /*27*/
        c = fgetc(stdin);
        
        if(c=='q'){
            free(msn);
            return;
        }
        if(c!=27)
            continue;

        /*]*/
        c = fgetc(stdin);
    
        /*A,B,C or D*/
        c = fgetc(stdin);

        if(c=='A' &&  can_move(map, r1+rec->lastrow-1, c1+rec->lastcol)){
	        rec->lastrow--;
            printf("%c[%d;%dH",27,r1+rec->lastrow,c1+rec->lastcol);
            aux = doIleave(intr->spaces[intr->spid], rec->lastrow-1, rec->lastcol-1, &ndoor); /*-1 if closed*/
            doorchar=intr->map[rec->lastrow-1][rec->lastcol-1];
            if(aux != -1 && aux < 30){
                
                    newcol =  Space_doorGetCol(intr->spaces[aux], ndoor);
                    newrow = Space_doorGetRow(intr->spaces[aux],  ndoor);
                    sprintf(msn, "Nos movemos a newcol: %d y newrow: %d", newcol, newrow);
                    intr_writestring(intr, msn, 2, 1, 1);
                    rec->lastcol=newcol+2;
                    rec->lastrow=newrow+2;
                    printf("%c[%d;%dH",27, rec->lastrow+1,rec->lastcol);
                    intr_changemap(intr, aux);
                    sprintf(msn, "La posicion actual es %d %d", rec->lastcol, rec->lastrow);
                    intr_writestring(intr, msn, 2, 2, 1);
                    
                    sprintf(msn, "%s", Space_getDesc(intr->spaces[aux]));
                    intr_writestring(intr, msn, 2, 3, 1);
                 
            }
        }
	    
        else if(c=='B' &&  can_move(map, r1+rec->lastrow+1, c1+rec->lastcol)){
	        rec->lastrow++;
            printf("%c[%d;%dH",27,r1+rec->lastrow,c1+rec->lastcol);
            aux = doIleave(intr->spaces[intr->spid], rec->lastrow-1, rec->lastcol-1, &ndoor); /*-1 if closed*/
            if(aux != -1 && aux<30){
                
                    newcol =  Space_doorGetCol(intr->spaces[aux], ndoor);
                    newrow = Space_doorGetRow(intr->spaces[aux],  ndoor);
                    sprintf(msn, "Nos movemos a newcol: %d y newrow: %d", newcol, newrow);
                    intr_writestring(intr, msn, 2, 1, 1);
                    rec->lastcol=newcol+2;
                    rec->lastrow=newrow+2;
                    intr_changemap(intr, aux);
                    printf("%c[%d;%dH",27, rec->lastrow,rec->lastcol);
                    
                    sprintf(msn, "%s", Space_getDesc(intr->spaces[aux]));
                    intr_writestring(intr, msn, 2, 3, 1);
                    
                 
            }
        }
        
        else if(c=='C' &&  can_move(map, r1+rec->lastrow, c1+rec->lastcol+1)){
            rec->lastcol++;
            printf("%c[%d;%dH",27,r1+rec->lastrow,c1+rec->lastcol);
            aux = doIleave(intr->spaces[intr->spid], rec->lastrow-1, rec->lastcol-1, &ndoor); /*-1 if closed*/
            if(aux != -1 && aux < 30){
                
                    newcol =  Space_doorGetCol(intr->spaces[aux], ndoor);
                    newrow = Space_doorGetRow(intr->spaces[aux],  ndoor);
                    sprintf(msn, "Nos movemos a newcol: %d y newrow: %d", newcol, newrow);
                    intr_writestring(intr, msn, 2, 1, 1);
                    rec->lastcol=newcol+2;
                    rec->lastrow=newrow+2;
                    intr_changemap(intr, aux);
                    printf("%c[%d;%dH",27, rec->lastrow,rec->lastcol);
                    
                    sprintf(msn, "%s", Space_getDesc(intr->spaces[aux]));
                    intr_writestring(intr, msn, 2, 3, 1);
                 
            }
        }
        
        else if(c=='D' &&  can_move(map, r1+rec->lastrow, c1+rec->lastcol-1)){
	        rec->lastcol--;
            printf("%c[%d;%dH",27,r1+rec->lastrow,c1+rec->lastcol);
            aux = doIleave(intr->spaces[intr->spid], rec->lastrow-1, rec->lastcol-1, &ndoor); /*-1 if closed*/
            if(aux != -1 && aux < 30){
                
                    newcol =  Space_doorGetCol(intr->spaces[aux], ndoor);
                    newrow = Space_doorGetRow(intr->spaces[aux],  ndoor);
                    sprintf(msn, "Nos movemos a newcol: %d y newrow: %d ", newcol, newrow);
                    intr_writestring(intr, msn, 2, 1, 1);
                    rec->lastcol=newcol+2;
                    rec->lastrow=newrow+2;
                    intr_changemap(intr, aux);
                    printf("%c[%d;%dH",27, rec->lastrow,rec->lastcol);
                    
                    sprintf(msn, "%s", Space_getDesc(intr->spaces[aux]));
                    intr_writestring(intr, msn, 2, 3, 1);
                 
            }
        }
    }
}

void intr_refresh(Intr* intr){
    
    intr_changemap(intr, intr->spid);
    return;
    
}
