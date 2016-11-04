#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
#include "space.h"
    
    
typedef struct _Object Object;
    

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
Object* Object_ini();


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
void Object_obliterate(Object* o);


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
Status Object_setname(Object* o, char*name);


/***************************************************/
/* Function: object_getname  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets the name of an object                                                 
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: char* with the name or NULL                           
/***************************************************/
char* Object_getname(Object* o);

/***************************************************/
/* Function: object_setid  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets the id of an object
/* Arguments:  Object* o!=NULL int id >0                     
/*                                                
/* Returns: ERR or OK                           
/***************************************************/
Status Object_setID(Object* o, int id);

/***************************************************/
/* Function: object_getid  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets the id of an object
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: int with the id of the object or -1 if it has not been asigned yet                           
/***************************************************/
int Object_getID(Object* o);

/***************************************************/
/* Function: object_setlocation  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets objects location
/* Arguments:  -Object* o!=NULL -int location >=-1                  
/*                                                
/* Returns: ERR or OK                           
/***************************************************/
Status Object_setlocation(Object* o, int location);

/***************************************************/
/* Function: object_getlocation Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects location 
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: int with the location or -2 if it has not been asigned yet                           
/***************************************************/
int Object_getlocation(Object* o);

/***************************************************/
/* Function: object_setcoordinatex Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects location 
/* Arguments:  Object* o!=NULL  -c1>=-1 (x coord)                   
/*                                                
/* Returns: ERR or OK                          
/***************************************************/
Status Object_setcoordinatex(Object* o, int c1);


/***************************************************/
/* Function: object_setcoordinatey Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects location 
/* Arguments:  Object* o!=NULL  -c2>=-1 (y coord)                   
/*                                                
/* Returns: ERR or OK                          
/***************************************************/
Status Object_setcoordinatey(Object* o, int c2);


/***************************************************/
/* Function: object_getcoordinatex Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects location 
/* Arguments:  Object* o!=NULL    
/*                                                
/* Returns: int=x coord                         
/***************************************************/
int Object_getcoordinatex(Object* o);

/***************************************************/
/* Function: object_getcoordinatey Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects location 
/* Arguments:  Object* o!=NULL    
/*                                                
/* Returns: int with the y coord                         
/***************************************************/
int Object_getcoordinatey(Object* o);

/***************************************************/
/* Function: object_setdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets objects description
/* Arguments:  Object* o!=NULL char*descr!=NULL                    
/*                                                
    /* Returns: ERR or OK                          
/***************************************************/
Status Object_setdescription(Object* o, char*descr);


/***************************************************/
/* Function: object_getdescription  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Gets objects description
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: char* with the descr or NULL                           
/***************************************************/
char* Object_getdescription(Object* o);


/***************************************************/
/* Function: object_setpower Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Sets objects power
/* Arguments:  Object* o!=NULL -int pw (power)                   
/*                                                
/* Returns: ERR or OK                          
/***************************************************/
Status Object_setpower(Object* o, int pw);


/***************************************************/
/* Function: object_getpower  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/*Gets objects power
/* Arguments:  Object* o!=NULL                     
/*                                                
/* Returns: int with objects power (can be negative)                           
/***************************************************/
int Object_getpower(Object* o);


/***************************************************/
/* Function: object_copy  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/*Copies an object
/* Arguments:  Object* o1!=NULL                     
/*                                                
/* Returns: Object* with a copy of o1 or NULL                          
/***************************************************/
Object* Object_copy(Object* o1);


/***************************************************/
/* Function: object_create  Fecha: 15-10-2016     
/* Autores: Segmentation Fault                     
/*                                                 
/* Creates a complete object calling some of the functions above
/* Arguments: -char* name!=NULL -int id>0 -int location>=-1  -int cx>=-1 -int cy>=-1                  
/*            -char* descr!=NULL -int quant>=0 -int power                                     
/* Returns: Object* with a new object :D                         
/***************************************************/
Object* Object_create(char*name, int id, int location, int cx, int cy, char* descr, 
                        int power);


#endif