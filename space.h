/*Esto es un little example*/

typefed struct{
    int id; //identificador del espasio
    char* name; //nombre del spasio
    char* desc; //description
    int light_on; //luces
    int neigh[4];  //vecinitos
    int locked[4]; //caminos bloqueaos por vacas
} space


getID(space*s);
char* name(space*s);    //komo me iamo
char* desc(space*s);   //Dame una descripcion
int canIsee(space*s);  //Puedo ver???
int move(space*s,int status); //Permite moverse en una direccion(o no)
int go(space*s, int dir); // -1 no space. -2 space locked, >=0 indica el id dell espacio al que vamos
int locked(space*s, int dir, int slot); //