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
	integer=0,
	intarray=1,
	voidtype=2
}types;


typedef struct funcpar{
	char *name;
	enum type type;	//0 - integer, 1- intarray, 2 - void
    UT_hash_handle hh;
}funcpar_t;


typedef struct varentry
{
	char *varname;		//name, key
	enum type vartype;	//0 - integer, 1- intarray, 2 - void
	int arrdim;			//array dimension
	//int memory; 		//size
	//int adress;		//offset
	funcpar_t *var;		//if varentry == array
    UT_hash_handle hh;
} varentry_t;

typedef struct funcentry
{
	char *funcname;			//name, key
	enum type returntype;	//0 - integer, 1- intarray, 2 - void
	int dim;				//dimension
	funcpar_t *par; 		//name, type and order of function parameters
							//TODO: Reference to IR of function
    UT_hash_handle hh;
}funcentry_t;

typedef struct symentry
{
	char *name;
	int type;			//identifier for var or func
	int arrdim;			//array dimension
	union {
		varentry_t *var;
		funcentry_t *func;
	} sym;
    UT_hash_handle hh;
}symentry_t;

void init_table();
void add_var(char *varname, enum type vartype,int arrdim);
void add_func(char *funcname, enum type returntype,int dim);
void add_funcpar(char *funcname,char *parname, enum type partype);
struct varentry *find_var(char *var_name);
struct funcentry *find_func(char *func_name);
struct funcpar *find_funcpar(char *par_name, char *func_name);
struct symentry *find_sym(char *sym_name);
void delete_var(struct varentry *var);
void delete_func(struct funcentry *func);
void delete_funcpar(struct funcpar *par, char *func_name) ;
void delete_all_vars();
void delete_all_funcs();
void delete_all_pars(char *func_name);
void delete_all();
unsigned int count_vars();
unsigned int count_funcs();
unsigned int count_pars(char *func_name);
unsigned int count_all();
void print_vars();
void print_funcs();
void print_pars(char *func_name);
void print_all();
int name_sort_vars(varentry_t *a, varentry_t *b);
void sort_vars();
int name_sort_funcs(funcentry_t *a, funcentry_t *b);
void sort_funcs();
int name_sort_all(symentry_t *a, symentry_t *b);
void sort_all();

#endif /* SYMTAB_H_ */
