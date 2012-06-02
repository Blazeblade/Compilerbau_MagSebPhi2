/**
 * @file 	symtab.h
 * @date	Created on: 20 Mar 2012
 * @author	Sebastian Boehm, Magnus Bruehl, Philipp Goetze
 * @brief	Structures of the symbol table and their function definitions
 *
 */

#ifndef SYMTAB_H_
#define SYMTAB_H_
#include "include/uthash.h"

enum type{							//Enumeration for Var and Func Types
	integer	=0,
	intarray=1,
	voidtype=2
}types;

typedef struct varentry				//Variables
{
	char *varname;					//name, key
	enum type vartype;				//0 - Integer, 1- Integer Array (, 2 - Void)
	int arrdim;						//Array Dimension
	struct funcentry *scope;		//Function Structure-local, NULL-global
	int val;						//Used for Var value and array stepping
	int offset;						//Offset of variable in symtab
	int memory;						//Necessary Memory for this variable
	int var_arr_loc;						//For array stepping
	struct varentry *var_arr_loc_struct;	//---"---
	int var_cpos;					//Position in IR Code
	int isfunccall;					//helper
    UT_hash_handle hh;				//Hash Table Handler
} varentry_t;

typedef struct funcentry			//Functions
{
	char *funcname;					//name, key
	enum type returntype;			//0 - Integer, (1- Integer Array,) 2 - Void
	int dim;						//Dimension
	int isPrototype;				//
	int offset_cnt;					//offset counter
	varentry_t *var; 				//Hash Table of Func Parameters
    UT_hash_handle hh;				//Hash Table Handler
}funcentry_t;

struct funccallparlist				//For checking the parameters in function calls
{
	varentry_t *var;				//Parameter list
	int count;						//Parameter counter
};

/********************   symtab.c functions   ********************/
void init_table ();
void add_var(char *varname, enum type vartype,int arrdim, int value);
void add_func(char *funcname, enum type returntype,int dim,varentry_t *var);
void add_funcpar(char *funcname,char *varname, enum type vartype, int arrdim);
struct varentry *find_var(char *var_name);
struct funcentry *find_func(char *func_name);
struct varentry *find_funcpar(char *var_name, char *func_name);
struct varentry *find_funcpar2(char *var_name);
void delete_var(struct varentry *var);
void delete_func(struct funcentry *func);
void delete_funcpar(struct varentry *var, char *func_name);
void delete_all_vars();
void delete_all_funcs();
void delete_all_pars(char *func_name);
unsigned int count_vars();
unsigned int count_funcs();
unsigned int count_pars(char *func_name);
void print_vars();
void print_funcs();
void print_pars(char *func_name);
int name_sort_vars(varentry_t *a, varentry_t *b);
void sort_vars();
int name_sort_funcs(funcentry_t *a, funcentry_t *b);
void sort_funcs();
unsigned int check_funccallpar(funcentry_t *func, struct funccallparlist *pars);
struct funccallparlist *create_pars_list(varentry_t *var);
struct varentry *temp_var (char *var_name);
int is_func_proto (funcentry_t *f);
void set_func_to_proto (funcentry_t *f);
void set_func_to_decl (char *func_name);
void set_func_scope (funcentry_t *f);
//void find_protos();
funcentry_t *get_func_scope ();
void set_scope_for_pars (funcentry_t *f);
void print_vars_ir();
void print_funcs_ir();
#endif /* SYMTAB_H_ */
