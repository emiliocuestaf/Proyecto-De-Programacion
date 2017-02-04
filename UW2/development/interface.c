#include "interface.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "animations.h"

#define OBJECTNUM 12
#define NPCSNUM 26
#define MAXTAM 100


#define SHORTTIME  200000
#define LONGTIME   2000000
#define TEXTTIME   80000



struct _intr{
  
  int nrows;
  int ncols;    
  Rectangle* playingfield;  /*ncols and nrows are data from rectangles structure*/
  Rectangle* playerdata; /*data includes players info, objects and useful commands*/
  Rectangle* inventory;
  Rectangle* cmdhelp;
  Rectangle* aux;
  Rectangle* insertgap;
  Rectangle* textgap;

  /*Show where the player is (inside the playing field)*/
  int xcoord;
  int ycoord;
  int dir;
  /*Depends on the map displayed at the moment*/
  /*char **map;*/
  Space** spaces;
  int spid;
  char** map;

  Object** objects;
  Npc** npcs;

  int miss[2];

};

int Intr_get_mission(Intr * intr){
    assert(intr != NULL);
    return intr->miss[0];
}
Status Intr_set_mission(Intr * intr, int miss){
    assert(intr != NULL);
    assert(miss >= 0);
    intr->miss[0] = miss;
    return OK;
}
/* Phase */
int Intr_get_phase(Intr * intr){
    assert(intr != NULL);
    return intr->miss[1];
}
Status Intr_set_phase(Intr * intr, int phase){
    assert(intr != NULL);
    assert(phase >= 0);
    intr->miss[1] = phase;
    return OK;
}

/*Equivalent to intrf_create but set without arguments. Doesn't set map*/

Intr* intr_ini(){
    
    Intr* intr;
    
    intr=(Intr*)malloc(sizeof(Intr));
    intr->ncols=125; /*Default values*/
    intr->nrows=52;
    
    /*reminder: rec_create(frow, fcol,  nrows, ncols, backgcol, foregcol) */
    
    intr->playingfield=rec_create(1,1, 31, 82, 40, 32); /*Default values*/
    intr->playerdata=rec_create(1, 83, 12, 40, 40, 31);
    intr->inventory=rec_create(13, 83, 18, 40, 40, 33);
    intr->cmdhelp=rec_create(31, 83, 13,40,40, 36);
    intr->aux=rec_create(32,1,2, 17,40,37);
    intr->insertgap=rec_create(32, 18,2, 65, 40,37);
    intr->textgap=rec_create(34,1,10,82,40,37);
    
    intr->playingfield->lastrow=5;
    intr->playingfield->lastcol=5;

    intr->xcoord=5;
    intr->ycoord=5;

    intr->miss[0]=1;
    intr->miss[1]=1;

    intr_clearall(intr);
    intr_cleargap(intr, 4);
    intr_writestring(intr, "Insert command:", 4, 1, 1);
    



    return intr;
    
}

void intr_setspaces(Intr* intr, Space** spaces){
    intr->spaces=spaces;
    intr->spid = 0;
    intr->map = Space_getMap(intr->spaces[0]);
    return;
}

void intr_setobjects(Intr* intr, Object** objects){
    intr->objects=objects;
    return;
}

void intr_setnpcs(Intr* intr, Npc** npcs){
    intr->npcs=npcs;
    return;
}

void intr_printborders(Intr* intr){
    rec_style(intr->playingfield);
    rec_printborder(intr->playingfield);
    rec_printborder(intr->playerdata);
    rec_printborder(intr->inventory);
    rec_printborder(intr->cmdhelp);
    rec_printborder(intr->aux);
    rec_printborder(intr->insertgap);
    rec_printborder(intr->textgap);
    return;
    
}
void intr_obliterate(Intr* intr){
    
    if(intr!=NULL){
        /*rec_clear(intrf->playingfield); */
        rec_obliterate(intr->playingfield);
        /*rec_clear(intrf->data); */
        rec_obliterate(intr->playerdata);
        rec_obliterate(intr->inventory);
        rec_obliterate(intr->cmdhelp);
        /*rec_clear(intrf->insertgap);*/
        rec_obliterate(intr->insertgap);
        /*rec_clear(intrf->textgap);*/
        rec_obliterate(intr->textgap);
        
        
        free(intr);
    }
    
    return;
    
}
void chop_print(Intr* intr, int select, int row, int col, char* str){
    char buff1[MAXTAM], buff2[MAXTAM], buff[MAXTAM], buff4[MAXTAM], buff5[MAXTAM], buff6[MAXTAM], buff7[MAXTAM], buff8[MAXTAM], buff9[MAXTAM];
    int i, j, k = 0, tam;
    Rectangle* rec;
    if (select==0)
        rec=intr->playingfield;
    else if (select==1)
        rec= intr->playerdata;
    else if (select==2)
        rec=intr->insertgap;
    else if(select==3)
        rec=intr->textgap;
    else if(select==4)
        rec=intr->aux;
    else if(select ==5)
        rec=intr->inventory;
    else if(select == 6)
        rec=intr->cmdhelp;

    tam=rec->ncols-1;
    if(strlen(str) > tam){
        for(i = strlen(str) - 1; i >= 0; i--){
            if(str[i] == ' ' && i <= tam){
                strcpy(buff1, str);
                buff1[i] = 0;
                for(j = i+1, k = 0 ; str[j] != 0 ; k++, j++){
                    buff2[k] = str[j];
                }
                buff2[k] = 0;
                intr_writestring(intr, buff1, select,  row,  col);
                intr_writestring(intr, buff2, select,  row+1,  col);
                return;
            }
        }
    } 
    else
        intr_writestring(intr, str, select,  row,  col);
}

void intr_writechoppedstring(Intr* intr, char* str, int select, int row, int col){
    chop_print(intr, select, row, col, str);
    return;
}
void intr_writestring(Intr* intr, char* str, int select, int row, int  col){
    Rectangle* rec;
    if (select==0)
        rec=intr->playingfield;
    else if (select==1)
        rec= intr->playerdata;
    else if (select==2)
        rec=intr->insertgap;
    else if(select==3)
        rec=intr->textgap;
    else if(select==4)
        rec=intr->aux;
    else if(select ==5)
        rec=intr->inventory;
    else if(select == 6)
        rec=intr->cmdhelp;

    rec_writestring_v2(rec, row, col, str);
    rec=intr->playingfield;
    printf("%c[%d;%dH",27, rec->lastrow, rec->lastcol);
    return;
}

void intr_writechar(Intr* intr, char c, int select, int row, int  col){
    Rectangle* rec;
    if (select==0)
        rec=intr->playingfield;
    else if (select==1)
        rec= intr->playerdata;
    else if (select==2)
        rec=intr->insertgap;
    else if(select==3)
        rec=intr->textgap;
    else if(select==4)
        rec=intr->aux;
    else if(select ==5)
        rec=intr->inventory;
    else if(select == 6)
        rec=intr->cmdhelp;

    rec_writechar(rec, row, col, c);
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

void intr_allocobjects(Intr* intr){
    int i, cx, cy, c1, r1;
    int nobjs;
    Rectangle* rec;

    rec=intr->playingfield;
    c1=rec->firstcol-1;
    r1=rec->firstrow-1;


    nobjs=OBJECTNUM;

    for (i = 0; i < nobjs; i++){
        if(intr->miss[0]>=Object_get_mission(intr->objects[i])){
            if(Object_getlocation(intr->objects[i])==intr->spid){
                cx=Object_getcoordinatex(intr->objects[i]);
                cy=Object_getcoordinatey(intr->objects[i]);
                rec_writechar(rec, r1+cy, c1+cx, intr->map[cy][cx] = Object_getsymbol(intr->objects[i]));
            }
        }
    }

    return;
}

void intr_allocnpcs(Intr* intr){
    int i, cx, cy, c1, r1;
    int nnpcs;
    Rectangle* rec;

    rec=intr->playingfield;
    c1=rec->firstcol-1;
    r1=rec->firstrow-1;


    nnpcs=NPCSNUM;

    for (i = 0; i < nnpcs; i++){
        if(Npc_getlocation(intr->npcs[i])==intr->spid){
            cx=Npc_getcoordinatex(intr->npcs[i]);
            cy=Npc_getcoordinatey(intr->npcs[i]);
            rec_writechar(rec, r1+cy, c1+cx, intr->map[cy][cx] = Npc_getsymbol(intr->npcs[i]));
        }
    }

    return;
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
    intr_allocobjects(intr);
    intr_allocnpcs(intr);
    
    return;
    
}


int can_move(Intr* intr, int row, int col){
    char c;
    char** map;

    map=intr->map;

    if(row<0 || col<0||row>28||col>83)
	    return 0;
	    
    c=map[row][col]; //Adjust position in terminal to position in map[][] (space)

    if(c=='v'||c=='^'||c=='<'||c=='>' )
	    return 1;

    if(c=='o'||c=='n')
        return 0;

    if(c==' ')
        return 1;

    else
	    return 0;
}

void intr_moveplayer(Intr* intr, char c){

    Rectangle* rec;
    int r1, c1, aux, newrow = 0, newcol = 0, ndoor=-1;
    char doorchar;
    char* msn;
    
     
    rec = intr->playingfield;
    c1 = rec->firstcol-1;
    r1 = rec->firstrow-1;
    msn=(char*)malloc(200*sizeof(char));
    


    if(c=='A' &&  can_move(intr, intr->ycoord-1, intr->xcoord)){
        rec_writechar(rec, r1+intr->ycoord, c1+intr->xcoord, ' ');
        intr->ycoord--;
        
            
        aux = doIleave(intr->spaces[intr->spid], intr->ycoord, intr->xcoord, &ndoor); /*-1 if closed*/
        if(aux != -1 && aux < 50){
                
                newcol = Space_doorGetCol(intr->spaces[aux], ndoor);
                newrow = Space_doorGetRow(intr->spaces[aux],  ndoor);
                doorchar= intr->map[intr->ycoord][intr->xcoord];
          
                if(doorchar == '>'){
                    intr->xcoord=newcol+1;
                    intr->ycoord=newrow;
                }
                else if (doorchar == '^'){
                    intr->xcoord=newcol;
                    intr->ycoord=newrow-1;
                }
                else if(doorchar == 'v'){
                    intr->xcoord=newcol;
                    intr->ycoord=newrow+1;
                }
                else if(doorchar == '<'){
                    intr->xcoord=newcol-1;
                    intr->ycoord=newrow;
                }        
                intr_changemap(intr, aux);
                if(intr->spid == 3 && intr->miss[0] == 2 && intr->miss[1] == 3){
                    animation1(intr);
                    intr->miss[0] = 3;
                    intr->miss[1] = 1;
                }
                if(intr->spid == 3 && intr->miss[0] == 5 && intr->miss[1] == 1){
                    animation2(intr);
                    intr->miss[0] = 5;
                    intr->miss[1] = 2;
                }
                sprintf(msn, "%s", Space_getDesc(intr->spaces[aux]));
                intr_cleargap(intr, 3);
                intr_writechoppedstring(intr, msn, 3, 1, 1);
                intr_reloaddata(intr);
       
            }
        else if(aux>=100)
            intr->ycoord++;

        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '^');
        intr->dir = 0;
    }
    else if (c=='A'){
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '^');
        intr->dir = 0;
    }
        
    else if(c=='B' &&  can_move(intr, intr->ycoord+1, intr->xcoord)){
        rec_writechar(rec, r1+intr->ycoord, c1+intr->xcoord, ' ');
        intr->ycoord++;
        
            
            
        aux = doIleave(intr->spaces[intr->spid], intr->ycoord, intr->xcoord, &ndoor); /*-1 if closed*/
        if(aux != -1 && aux < 50){
                
                newcol =  Space_doorGetCol(intr->spaces[aux], ndoor);
                newrow = Space_doorGetRow(intr->spaces[aux],  ndoor);
                doorchar= intr->map[intr->ycoord][intr->xcoord];                    
                doorchar= intr->map[intr->ycoord][intr->xcoord];
              
                if(doorchar == '>'){
                    intr->xcoord=newcol+1;
                    intr->ycoord=newrow;
                }
                else if (doorchar == '^'){
                    intr->xcoord=newcol;
                    intr->ycoord=newrow-1;
                }
                else if(doorchar == 'v'){
                    intr->xcoord=newcol;
                    intr->ycoord=newrow+1;
                }
                else if(doorchar == '<'){
                    intr->xcoord=newcol-1;
                    intr->ycoord=newrow;
                }                   

                intr_changemap(intr, aux);
                 if(intr->spid == 3 && intr->miss[0] == 2 && intr->miss[1] == 3){
                    animation1(intr);
                    intr->miss[0] = 3;
                    intr->miss[1] = 1;
                }
                if(intr->spid == 3 && intr->miss[0] == 5 && intr->miss[1] == 1){
                    animation2(intr);
                    intr->miss[0] = 5;
                    intr->miss[1] = 2;
                }
                sprintf(msn, "%s", Space_getDesc(intr->spaces[aux]));
                intr_cleargap(intr, 3);
                intr_writechoppedstring(intr, msn, 3, 1, 1);
                intr_reloaddata(intr);
       
        }
        else if(aux>=100)
            intr->ycoord--;
  
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , 'v');
        intr->dir= 1;
    }
    else if (c=='B'){
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , 'v');
        intr->dir = 1;
    }
        
    else if(c=='C' &&  can_move(intr, intr->ycoord, intr->xcoord+1)){
        rec_writechar(rec, r1+intr->ycoord, c1+intr->xcoord, ' ');
        intr->xcoord++;
    
            
        aux = doIleave(intr->spaces[intr->spid], intr->ycoord, intr->xcoord, &ndoor); /*-1 if closed*/
        if(aux != -1 && aux < 50){
                
                newcol =  Space_doorGetCol(intr->spaces[aux], ndoor);
                newrow = Space_doorGetRow(intr->spaces[aux],  ndoor);
                doorchar= intr->map[intr->ycoord][intr->xcoord];                    
                
                if(doorchar == '>'){
                    intr->xcoord=newcol+1;
                    intr->ycoord=newrow;
                }
                else if (doorchar == '^'){
                    intr->xcoord=newcol;
                    intr->ycoord=newrow-1;
                }
                else if(doorchar == 'v'){
                    intr->xcoord=newcol;
                    intr->ycoord=newrow+1;
                }
                else if(doorchar == '<'){
                    intr->xcoord=newcol-1;
                    intr->ycoord=newrow;
                }                         

                intr_changemap(intr, aux);
                   if(intr->spid == 3 && intr->miss[0] == 2 && intr->miss[1] == 3){
                    animation1(intr);
                    intr->miss[0] = 3;
                    intr->miss[1] = 1;
                }
                if(intr->spid == 3 && intr->miss[0] == 5 && intr->miss[1] == 1){
                    animation2(intr);
                    intr->miss[0] = 5;
                    intr->miss[1] = 2;
                }
                sprintf(msn, "%s", Space_getDesc(intr->spaces[aux]));
                intr_cleargap(intr, 3);
                intr_writechoppedstring(intr, msn, 3, 1, 1);
                intr_reloaddata(intr);       
        }
        else if(aux>=100)
            intr->xcoord--;

        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '>');
   
  
        intr->dir = 2;
    }
    else if (c=='C'){
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '>');
        intr->dir = 2;
    }
        
    else if(c=='D' &&  can_move(intr, intr->ycoord, intr->xcoord-1)){
        rec_writechar(rec, r1+intr->ycoord, c1+intr->xcoord, ' ');
        intr->xcoord--;

        aux = doIleave(intr->spaces[intr->spid], intr->ycoord, intr->xcoord, &ndoor); /*-1 if closed*/
        if(aux != -1 && aux < 50){
                
                newcol =  Space_doorGetCol(intr->spaces[aux], ndoor);
                newrow = Space_doorGetRow(intr->spaces[aux],  ndoor);
                doorchar= intr->map[intr->ycoord][intr->xcoord];
              

                if(doorchar == '>'){
                    intr->xcoord=newcol+1;
                    intr->ycoord=newrow;
                }
                else if (doorchar == '^'){
                    intr->xcoord=newcol;
                    intr->ycoord=newrow-1;
                }
                else if(doorchar == 'v'){
                    intr->xcoord=newcol;
                    intr->ycoord=newrow+1;
                }
                else if(doorchar == '<'){
                    intr->xcoord=newcol-1;
                    intr->ycoord=newrow;
                }                       

                intr_changemap(intr, aux);
                 if(intr->spid == 3 && intr->miss[0] == 2 && intr->miss[1] == 3){
                    animation1(intr);
                    intr->miss[0] = 3;
                    intr->miss[1] = 1;
                }
                if(intr->spid == 3 && intr->miss[0] == 5 && intr->miss[1] == 1){
                    animation2(intr);
                    intr->miss[0] = 5;
                    intr->miss[1] = 2;
                }
                sprintf(msn, "%s", Space_getDesc(intr->spaces[aux]));
                intr_cleargap(intr, 3);
                intr_writechoppedstring(intr, msn, 3, 1, 1);
                intr_reloaddata(intr);
       
        }
        else if(aux>=100)
            intr->xcoord++;

        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '<');
        intr->dir = 3;
    }
    else if (c=='D'){
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '<');
        intr->dir = 3;
    }

    free(msn);
}




void intr_refresh(Intr* intr){
    int c1, r1;
    Rectangle* rec;
    
    intr_printplayerinfo(intr);
    intr_printinventory(intr);
    intr_changemap(intr, intr->spid);
    rec = intr->playingfield;
    c1 = rec->firstcol-1;
    r1 = rec->firstrow-1;

    if(intr->dir==0)
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '^');
    else if(intr->dir==1)
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , 'v');
    else if(intr->dir==2)
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '>');
    else if(intr->dir==3)
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '<');

    return;
    
}

void intr_cleargap(Intr* intr, int select){
    char* buf;
    int i;
    Rectangle* rec;
    
    if (select==0)
        rec=intr->playingfield;
    else if (select==1)
        rec= intr->playerdata;
    else if (select==2)
        rec=intr->insertgap;
    else if(select==3)
        rec=intr->textgap;
    else if(select==4)
        rec=intr->aux;
    else if(select ==5)
        rec=intr->inventory;
    else if(select == 6)
        rec=intr->cmdhelp;
    
    rec_style(rec);
    buf=(char*) malloc ((rec->ncols+1)*sizeof(char));
    memset((void*) buf, ' ', rec->ncols);
    buf[rec->ncols]=0;
    for (i=0; i<rec->nrows; i++){
        intr_writestring(intr, buf, select , i, 0);
    }
    intr_printborders(intr);
    return;
}

void intr_clearall(Intr* intr){
    int i;

    for(i=0; i<4; i++){
        intr_cleargap(intr, i);
    }
    for(i=5; i<7; i++){
        intr_cleargap(intr, i);
    }
    return;
}

void intr_printplayerinfo(Intr* intr){
    int i;
    char aux[50];
    

    intr_cleargap(intr, 1);
    intr_writestring(intr, "PLAYER DATA:", 1, 2, 2);

    sprintf(aux,"You are at: %s", Space_getName(intr->spaces[intr->spid]));
    intr_writechoppedstring(intr, aux, 1, 4, 2);
    sprintf(aux,"Current Mission: %d", intr->miss[0]);
    intr_writechoppedstring(intr, aux, 1, 5, 2);
    sprintf(aux,"Current Phase: %d", intr->miss[1]);
    intr_writechoppedstring(intr, aux, 1, 6, 2);
    
    intr_writechoppedstring(intr, "SEGFAULTSEGFAULTSEGFAULT", 1, 8, 2);
    intr_writechoppedstring(intr, "Have a nice game!!", 1, 11, 2);
    intr_writechoppedstring(intr, "LUIS CARABE, EMILIO CUESTA", 1, 9, 2);
    intr_writechoppedstring(intr, "P.ALEJO POLANIA, SIMON VALCARCEL", 1, 10, 2);
    
    return;
}

void intr_printinventory(Intr* intr){
    int i;
    char aux[50];

    intr_cleargap(intr, 5);

    intr_writestring(intr, "INVENTORY:", 5, 1, 2);

    for (i=0; i<OBJECTNUM; i++){
        sprintf(aux,"*%s",Object_getname(intr->objects[i]));
        if(Object_getlocation(intr->objects[i])==-1)
            intr_writestring(intr, aux, 5, 3+i, 2);
    }
    return;
}

void intr_printcmdhelp(Intr* intr){
    int i;
    
    intr_writestring(intr, "COMMAND SUMMARY:", 6, 1, 2);

    intr_writechoppedstring(intr, "-pick o", 6, 3, 2);
    intr_writechoppedstring(intr, "-drop <o.name>", 6, 4, 2);
    intr_writechoppedstring(intr, "-sing <whatever>", 6, 5, 2);
    intr_writechoppedstring(intr, "-talk @", 6, 6, 2);
    intr_writechoppedstring(intr, "-askfor <o.name>", 6, 7, 2);
    intr_writechoppedstring(intr, "-give <o.name>", 6, 8, 2);
    intr_writechoppedstring(intr, "-openwith <o.name>", 6, 9, 2);
    intr_writechoppedstring(intr, "-read <o.name>", 6, 10, 2);


    
   
    
    return;
}

void intr_reloaddata(Intr* intr){
    intr_printplayerinfo(intr);
    intr_printinventory(intr);
    return;
}

int intr_playergetrow(Intr* intr){
    return intr->ycoord;
}
void intr_playersetrow(Intr* intr, int y){
    intr->ycoord=y;
    return;
}

int intr_playergetcol(Intr* intr){
    return intr->xcoord;
}
void intr_playersetcol(Intr* intr, int x){
    intr->xcoord=x;
    return;
}

int intr_playergetdir(Intr* intr){
    return intr->dir;
}

void intr_playersetdir(Intr* intr, int dir){
    intr->dir=dir;
    return;
}

int intr_playergetspid(Intr* intr){
    return intr->spid;
}

void intr_teleportplayer(Intr* intr, int x, int y, int dir){
    Rectangle* rec;
    int r1,c1;

    rec = intr->playingfield;
    c1 = rec->firstcol-1;
    r1 = rec->firstrow-1;

    rec_writechar(intr->playingfield, intr->ycoord, intr->xcoord , ' ');

    intr_playersetrow(intr, y);
    intr_playersetcol(intr, x);
    intr_playersetdir(intr, dir);

    if(dir==0)
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '^');
    else if(dir==1)
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , 'v');
    else if(dir==2)
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '>');
    else if(dir==3)
        rec_writeplayer(rec, r1+intr->ycoord, c1+intr->xcoord , '<');

    return;
}

void intr_writeenemy(Intr* intr, int y, int x, char c ){

    rec_writeenemy(intr->playingfield, y, x , c);
    return;
}

void intr_writeici(Intr* intr, int y, int x, char c){
    rec_writeici(intr->playingfield, y, x , c);
    return;
}

void intr_writeblood(Intr* intr, int y, int x, char c){
    rec_writeblood(intr->playingfield, y, x, c);
    return;
}

char ** intr_getmap(Intr* intr){
    return intr->map;
}


