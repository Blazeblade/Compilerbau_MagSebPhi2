/*
 * symtab.h
 *
 *  Created on: 20 Mar 2012
 *      Author: philipp
 */

#ifndef SYMTAB_H_
#define SYMTAB_H_
#include "include/uthash.h"


enum type{
	integer,intarray,voidtype
};

typedef struct functpar{
	int type;
	char *name;
}functpar_t;


typedef struct varentry
{
	char *varname;		//name, key
	enum type vartype;	//type
	int memory; 		//size
	int adress;			//offset
    UT_hash_handle hh;
} varentry_t;

typedef struct funcentry
{
	char *funcname;		//name, key
	enum type returntype;	//type
	int dim;				//dimension
	varentry_t *args; 		//name, type and order of function args
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
