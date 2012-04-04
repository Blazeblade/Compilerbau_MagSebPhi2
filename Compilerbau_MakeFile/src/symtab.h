/*
 * symtab.h
 *
 *  Created on: 20 Mar 2012
 *      Author: philipp
 */

#ifndef SYMTAB_H_
#define SYMTAB_H_
#include "include/uthash.h"


/*enum type{
	integer,intarray,voidtype
}types;
*/

typedef struct funcpar{
	int type;
	char *name;
}functpar_t;


typedef struct varentry
{
	char *varname;		//name, key
	int vartype;		//type (enum type vartype;)
						//0 - integer, 1- integerarray, 2 - void
	int memory; 		//size
	int adress;			//offset
    UT_hash_handle hh;
} varentry_t;

typedef struct funcentry
{
	char *funcname;		//name, key
	int returntype;	//type (enum type returntype;)
							//0 - integer, 1- integerarray, 2 - void
	int dim;				//dimension
	varentry_t *par; 		//name, type and order of function parameters
							//TODO: Reference to IR of function
    UT_hash_handle hh;
}funcentry_t;

typedef struct symentry
{
	int id;				//identifier for var or func
	union {
		varentry_t *var;
		funcentry_t *func;
	} sym;
    UT_hash_handle hh;
}symentry_t;


#endif /* SYMTAB_H_ */
