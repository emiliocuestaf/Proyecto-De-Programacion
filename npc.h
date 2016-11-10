/*Comentarios mal, referentes a object xD*/

#ifndef NPC_H
#define NPC_H

#include "types.h"
#include "space.h"
    
    
typedef struct _Npc Npc;
    

/***************************************************/
/* Function: object_ini  Fecha: 15-10-2016         */
/* Autores: Segmentation Fault                     */
/*                                                 */
/* Initialization of the structure Object          */      
/*                                                 */
/* Arguments.-                                     */
/*                                                 */
/* Returns:                                        */
/*  (Object*) NULL or pointer to object            */
/***************************************************/
Npc* Npc_ini();


/***************************************************/
/* Function: object_obliterate  Fecha: 15-10-2016  */
/* Autores: Segmentation Fault                     */
/*                                                 */
/* Objects memory freeing                          */      
/*                                                 */
/* Arguments:  Object* o!=NULL                     */
/*                                                 */
/* Returns: void                                   */
/***************************************************/
void Npc_obliterate(Npc* n);


/***************************************************/
/* Function: object_setname  Fecha: 15-10-2016     */
/* Autores: Segmentation Fault                     */
/*                                                 */
/* Sets the name of an object                      */      
/*                                                 */
/* Arguments:   Object* o!=NULL                    */
/*              char* name!=NULL                   */
/*                                                 */
/* Returns: ERR or OK                              */
/***************************************************/
Status Npc_setname(Npc * n, char * name);


/***************************************************/
/* Function: object_getname  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets the name of an object                                                 
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: char* with the name or NULL                           
/***************************************************/
char* Npc_getname(Npc * n);

/***************************************************/
/* Function: object_setid  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets the id of an object
/* Arguments:  Object* o!=NULL int id >0                     
/*                                                
/* Returns: ERR or OK                           
/***************************************************/
Status Npc_setid(Npc * n, int id);

/***************************************************/
/* Function: object_getid  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets the id of an object
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: int with the id of the object or -1 if it has not been asigned yet                           
/***************************************************/
int Npc_getid(Npc * n);

/***************************************************/
/* Function: object_setlocation  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets objects location
/* Arguments:  -Object* o!=NULL -int location >=-1                  
/*                                                
/* Returns: ERR or OK                           
/***************************************************/
Status Npc_setlocation(Npc * n, int location);

/***************************************************/
/* Function: object_getlocation Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects location 
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: int with the location or -2 if it has not been asigned yet                           
/***************************************************/
int Npc_getlocation(Npc * n);

/***************************************************/
/* Function: object_setcoordinatex Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects location 
/* Arguments:  Object* o!=NULL  -c1>=-1 (x coord)                   
/*                                                
/* Returns: ERR or OK                          
/***************************************************/
Status Npc_setcoordinatex(Npc * n, int c1);


/***************************************************/
/* Function: object_setcoordinatey Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects location 
/* Arguments:  Object* o!=NULL  -c2>=-1 (y coord)                   
/*                                                
/* Returns: ERR or OK                          
/***************************************************/
Status Npc_setcoordinatey(Npc * n, int c2);


/***************************************************/
/* Function: object_getcoordinatex Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects location 
/* Arguments:  Object* o!=NULL    
/*                                                
/* Returns: int=x coord                         
/***************************************************/
int Npc_getcoordinatex(Npc * n);

/***************************************************/
/* Function: object_getcoordinatey Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects location 
/* Arguments:  Object* o!=NULL    
/*                                                
/* Returns: int with the y coord                         
/***************************************************/
int Npc_getcoordinatey(Npc * n);

/***************************************************/
/* Function: object_setdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets objects description
/* Arguments:  Object* o!=NULL char*descr!=NULL                    
/*                                                
    /* Returns: ERR or OK                          
/***************************************************/
Status Npc_setdescription1(Npc * n, char * descr);

/***************************************************/
/* Function: object_setdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets objects description
/* Arguments:  Object* o!=NULL char*descr!=NULL                    
/*                                                
    /* Returns: ERR or OK                          
/***************************************************/
Status Npc_setdescription2(Npc * n, char * descr);

/***************************************************/
/* Function: object_setdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets objects description
/* Arguments:  Object* o!=NULL char*descr!=NULL                    
/*                                                
    /* Returns: ERR or OK                          
/***************************************************/
Status Npc_setdescription3(Npc * n, char * descr);

/***************************************************/
/* Function: object_setdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets objects description
/* Arguments:  Object* o!=NULL char*descr!=NULL                    
/*                                                
    /* Returns: ERR or OK                          
/***************************************************/
Status Npc_setdescription4(Npc * n, char * descr);

/***************************************************/
/* Function: object_setdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets objects description
/* Arguments:  Object* o!=NULL char*descr!=NULL                    
/*                                                
    /* Returns: ERR or OK                          
/***************************************************/
Status Npc_setdescription5(Npc * n, char * descr);


/***************************************************/
/* Function: object_getdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects description
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: char* with the descr or NULL                           
/***************************************************/
char * Npc_getdescription1(Npc * n);

/***************************************************/
/* Function: object_getdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects description
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: char* with the descr or NULL                           
/***************************************************/
char * Npc_getdescription2(Npc * n);

/***************************************************/
/* Function: object_getdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects description
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: char* with the descr or NULL                           
/***************************************************/
char * Npc_getdescription3(Npc * n);

/***************************************************/
/* Function: object_getdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects description
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: char* with the descr or NULL                           
/***************************************************/
char * Npc_getdescription4(Npc * n);

/***************************************************/
/* Function: object_getdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects description
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: char* with the descr or NULL                           
/***************************************************/
char * Npc_getdescription5(Npc * n);


/***************************************************/
/* Function: object_setpower Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets objects power
/* Arguments:  Object* o!=NULL -int pw (power)                   
/*                                                
/* Returns: ERR or OK                          
/***************************************************/
Status Npc_setsymbol(Npc * n, char sym);


/***************************************************/
/* Function: object_getpower  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/*Gets objects power
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: int with objects power (can be negative)                           
/***************************************************/
char Npc_getsymbol(Npc * n);


/***************************************************/
/* Function: object_copy  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/*Copies an object
/* Arguments:  Object* o1!=NULL                     
/*                                                
/* Returns: Object* with a copy of o1 or NULL                          
/***************************************************/
Npc * Npc_copy(Npc * n);


/***************************************************/
/* Function: object_create  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Creates a complete object calling some of the functions above
/* Arguments: -char* name!=NULL -int id>0 -int location>=-1  -int cx>=-1 -int cy>=-1                  
/*            -char* descr!=NULL -int quant>=0 -int power                                     
/* Returns: Object* with a new object :D                         
/***************************************************/
/* Npc * Npc_create(char*name, int id, int location, int cx, int cy, char* descr, int power); */


#endif