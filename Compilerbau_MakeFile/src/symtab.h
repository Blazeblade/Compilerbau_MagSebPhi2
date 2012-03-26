/*
 * symtab.h
 *
 *  Created on: 20 Mar 2012
 *      Author: philipp
 */

#ifndef SYMTAB_H_
#define SYMTAB_H_


enum type{
	integer,intarray,voidtype
};

typedef struct varentry
{
	int id;				//key
	char varname[];		//name
	enum type vartype;	//type
	int memory; 		//size
	int adress;			//offset
    UT_hash_handle hh;
};

typedef struct funcentry
{
	int id;					//key
	char funcname[];		//name
	enum type returntype;	//type
	int dim;				//dimension
	struct varentry *args[]; //name, type and order of function args
	//Reference to IR of function
    UT_hash_handle hh;
};


#endif /* SYMTAB_H_ */
