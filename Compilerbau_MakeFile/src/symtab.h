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

typedef struct
{
	char varname[];
	enum type vartype;
	int memory;
	int adress;
} varentry ;

typedef struct
{
	char funcname[];
	enum type returntype;
	int dim;
	//hashtable
	//Reference to IR
} funcentry ;


#endif /* SYMTAB_H_ */
