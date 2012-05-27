/**
 * @file 	symtab.c
 * @date	Created on: 20 Mar 2012
 * @author	Sebastian Boehm, Magnus Bruehl, Philipp Goetze
 * @brief	Functions of the symbol table
 *
 */
/* Comments:
 *  	Iterating with next/prev
 *  		s=(struct my_struct*)s->hh.next
 *  		s=(struct my_struct*)s->hh.prev
 */

#include "symtab.h"
#include "ir_code_gen.h"
#include <assert.h>
#include <stdio.h>   /* gets,printf */
#include <stdlib.h>  /* atoi, malloc */
#include <string.h>  /* strcpy */

/*
 * The Pointer to the beginning of the symbol table (variables)
 */
varentry_t *varentries;
/*
 * The Pointer to the beginning of the symbol table (functions)
 */
funcentry_t *funcentries;
/*
 * The current function scope
 */
funcentry_t *currfunc;
/*
 * Offset counter
 */
int offset_=0;

/**************************************      Initialise Tables     *******************************************/

/**
* Initialises the symbol table(Variables, Functions, sets them to NULL).
*/
void init_table (){
	varentries=NULL;
	funcentries=NULL;
	currfunc=NULL;
}

/**************************************        ADD ITEMS          *******************************************/

/**
* Creates a variable in symbol table.
* @param varname The name of the variable
* @param vartype The type of the variable (int, int[] (, void))
* @param arrdim Gives the size of the array, (No array, then arrdim = -1)
* @param value The value of the variable, also used for array stepping
* @return nothing
*/
void add_var(char *varname, enum type vartype,int arrdim, int value) {
    varentry_t *v;
    v = malloc(sizeof(varentry_t));
	assert(v!=NULL);
    v->varname = malloc(strlen(varname)+1);
	assert(v->varname!=NULL);
    strcpy(v->varname, varname);
    v->vartype=vartype;
    v->arrdim=arrdim;
    v->scope=currfunc;
    v->val=value;
	v->tempArrPos=-1;
	v->tempArrPos2=NULL;
	v->tempCodePos=-1;
	v->isfunccall=0;
	if(arrdim>-1)
		v->memory=arrdim*4;
	else
		v->memory=4;
	if(v->scope){
		v->offset=v->scope->offset_cnt;
		v->scope->offset_cnt+=v->memory;
	}
	else{
		v->offset=offset_;
		offset_+=v->memory;
	}
    HASH_ADD_KEYPTR(hh, varentries, v->varname, strlen(v->varname), v );
    return;
}

/**
* Creates a function in symbol table.
* @param funcname The name of the function
* @param returntype The type of the function (int (, int[]), void)
* @param dim Gives the amount of parameters of the function
* @param var Hash table of parameters
* @return nothing
*/
void add_func(char *funcname, enum type returntype,int dim,varentry_t *var) {
    funcentry_t *f;
    f = malloc(sizeof(funcentry_t));
	assert(f!=NULL);
	f->funcname = malloc(strlen(funcname)+1);
	assert(f->funcname!=NULL);
    strcpy(f->funcname, funcname);
    f->returntype= returntype;
    f->dim = dim;
    f->var = var;
    f->offset_cnt=0;
    HASH_ADD_KEYPTR(hh, funcentries, f->funcname, strlen(f->funcname), f );
    currfunc=f;
    return;

}

/**
* Creates a parameter for the specified function in a separate hash table.
* @param funcname The name of the function
* @param varname The name of the parameter
* @param vartype The type of the parameter (int , int[] (, void))
* @param arrdim Gives the size of the array, (No array, then arrdim = -1)
* @return nothing
*/
void add_funcpar(char *funcname,char *varname, enum type vartype, int arrdim) {
	varentry_t *p;
	funcentry_t *f;
	p = malloc(sizeof(varentry_t));
	assert(p!=NULL);
	p->varname = malloc(strlen(varname)+1);
	assert(p->varname!=NULL);
	strcpy(p->varname, varname);
	p->vartype=vartype;
	p->arrdim=arrdim;
	p->scope=currfunc;
	p->tempArrPos=-1;
	p->tempArrPos2=NULL;
	p->tempCodePos=-1;
	if(arrdim>-1)
		p->memory=arrdim*4;
	else
		p->memory=4;
	p->offset=p->scope->offset_cnt;
	p->scope->offset_cnt+=p->memory;
	HASH_FIND(hh,funcentries, funcname,strlen(funcname), f);
	assert(f!=NULL);
    HASH_ADD_KEYPTR(hh, f->var, p->varname, strlen(p->varname), p);
    return;
}


/**************************************        FIND ITEMS          *******************************************/

/**
* Finds a specified variable in symbol table.
* @param var_name The name of the variable
* @return v The variable structure
*/
struct varentry *find_var(char *var_name) {
    struct varentry *v;
    HASH_FIND(hh,varentries, var_name,strlen(var_name), v);
    return v;
}

/**
* Finds a specified function in symbol table.
* @param func_name The name of the function
* @return f The function structure
*/
struct funcentry *find_func(char *func_name) {
    struct funcentry *f;
    HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);
    return f;
}

/**
* Finds a specified parameter for a specific function in symbol table.
* @param var_name The name of the parameter
* @param func_name The name of the function
* @return v The variable (parameter) structure
*/
struct varentry *find_funcpar(char *var_name, char *func_name) {
    struct varentry *v;
    struct funcentry *f;
    HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);
    HASH_FIND(hh,f->var, var_name,strlen(var_name), v);
    return v;
}

/**
* Finds a specified parameter in symbol table (searches in all functions).
* @param var_name The name of the parameter
* @return v The variable (parameter) structure
*/
struct varentry *find_funcpar2(char *var_name) {
    struct varentry *v;
    funcentry_t *f, *tmp;
    HASH_ITER(hh, funcentries, f, tmp) {
    	HASH_FIND(hh,f->var, var_name,strlen(var_name), v);
    }
    return v;
}


/**************************************        DELETE ITEMS        *******************************************/

/**
* Deletes a specified variable from symbol table.
* @param var The pointer to the structure of the variable
*/
void delete_var(struct varentry *var) {
	HASH_DEL(varentries,var);
    free(var);
}

/**
* Deletes a specified function from symbol table.
* @param func The pointer to the structure of the function
*/
void delete_func(struct funcentry *func) {
    HASH_DEL(funcentries,func);
    free(func);
}

/**
* Deletes a specified parameter of a specific function from symbol table.
* @param var The pointer to the structure of the parameter
* @param func_name The name of the function
*
*/
void delete_funcpar(struct varentry *var, char *func_name) {
    struct funcentry *f;
    HASH_FIND(hh,funcentries, func_name, strlen(func_name), f);
    HASH_DEL(f->var, var);
    free(var);
}


/**************************************     DELETE ALL ITEMS       *******************************************/

/**
* Deletes all variables from symbol table.
*/
void delete_all_vars() {
  varentry_t *v, *tmp;
  HASH_ITER(hh, varentries, v, tmp) {
    HASH_DEL(varentries,v);  /* delete; varentries advances to next */
    free(v);
  }
}

/**
* Deletes all functions from symbol table.
*/
void delete_all_funcs() {
  funcentry_t *f, *tmp;
  HASH_ITER(hh, funcentries, f, tmp) {
    HASH_DEL(funcentries,f);  /* delete; funcentries advances to next */
    free(f);
  }
}

/**
* Deletes all parameters of a function from symbol table.
* @param func_name The name of the function
*/
void delete_all_pars(char *func_name) {
  varentry_t *v, *tmp;
  struct funcentry *f;
  HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);  	/* f: output pointer */
  HASH_ITER(hh, f->var, v, tmp) {
    HASH_DEL(f->var,v);  		/* delete; f->var advances to next */
    free(v);
  }
}


/**************************************       Count ITEMS         *******************************************/

/**
* Counts the number of variables in the symbol table.
* @return number of variables
*/
unsigned int count_vars(){
	return HASH_COUNT(varentries);
}

/**
* Counts the number of functions in the symbol table.
* @return number of functions
*/
unsigned int count_funcs(){
	return HASH_COUNT(funcentries);
}

/**
* Counts the number of parameters of a function in the symbol table.
* @param func_name The name of the function
* @return number of parameters
*/
unsigned int count_pars(char *func_name) {
	struct funcentry *f;
	HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);
	assert(f!=NULL);
	return HASH_COUNT(f->var);
}


/**************************************       PRINT ITEMS         *******************************************/

/**
* Prints all variables from the symbol table to the console.
*/
void print_vars(){
	if(varentries==NULL){
			printf("No variables in table.\n");
			return;
	}
	else{
		varentry_t *v, *tmp;
		char* type;
		char* scope;
		HASH_ITER(hh, varentries, v, tmp) {
			switch (v->vartype){
							case 0:type="Integer"; break;
							case 1:type="Integer Array";;break;
							case 2:type="Void";;break;
			}
			if(v->scope==NULL) scope= "global";
				else scope=v->scope->funcname;

			if(v->arrdim==-1)
				printf("Variable: %s, type: %s, Scope: %s, Memory: %d, Offset: %d, Value: %d\n",
						v->varname, type,scope, v->memory,v->offset,v->val);
			else
				printf("Variable: %s, type: %s[%d], Scope: %s, Memory: %d, Offset: %d, Value: %d\n",
						v->varname, type,v->arrdim,scope, v->memory,v->offset,v->val);
		}
	}
}

/**
* Prints all functions from the symbol table to the console.
*/
void print_funcs(){
	if(funcentries==NULL){
				printf("No Functions in table.\n");
				return;
	}
	else{
		funcentry_t *f, *tmp;
		char* type;
		char* scope;
		HASH_ITER(hh, funcentries, f, tmp) {
			switch (f->returntype){
							case 0:type="Integer"; break;
							case 1:type="Integer Array";;break;
							case 2:type="Void";;break;
			}
			printf("Function: %s(), type: %s, dimension: %d\n", f->funcname, type,f->dim);
			varentry_t *v, *tmp;
			HASH_ITER(hh, f->var, v, tmp) {
				switch (v->vartype){
								case 0:type="Integer"; break;
								case 1:type="Integer Array";;break;
								case 2:type="Void";;break;
				}
				if(v->scope==NULL) scope="global";
					else scope=v->scope->funcname;
				if(v->arrdim==-1)
					printf("\tParameter of %s: %s, type: %s, Memory: %d, Offset: %d\n",
							f->funcname ,v->varname, type,v->memory,v->offset);
				else
					printf("\tParameter of %s: %s, type: %s[%d], Memory: %d, Offset: %d\n",
							f->funcname ,v->varname, type,v->arrdim,v->memory,v->offset);
			}
		}
	}
}

/**
* Prints all parameters of a function from the symbol table to the console.
* @param func_name The name of the function
*/
void print_pars(char *func_name){
	struct funcentry *f;
	HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);
	if(f->var==NULL){
				printf("No Parameters in table for %s.\n",func_name);
				//add_str(s);
				return;
	}
	else{
		varentry_t *v, *tmp;
		char* type;
		char* scope;
		HASH_ITER(hh, f->var, v, tmp) {
			switch (v->vartype){
				case 0:type="Integer"; break;
				case 1:type="Integer Array";;break;
				case 2:type="Void";;break;
			}
			if(v->scope==NULL)scope="global";
			else scope="local";
			if(v->arrdim==-1)
				printf("Parameter of %s: %s, type: %s, scope: %s\n",func_name ,v->varname, type,scope);
			else
				printf("Parameter of %s: %s, type: %s[%d]\n",func_name ,v->varname, type,v->arrdim);
		}
	}
}


/**************************************       SORT ITEMS         *******************************************/

//Not sure whether this should do the trick...
//Not in Use, yet

/**
* Compares two variables for sort_vars().
* @param a Variable 1 for comparison
* @param b Variable 2 for comparison
*/
int name_sort_vars(varentry_t *a, varentry_t *b) {
    return strcmp(a->varname,b->varname);
}

/**
* Sorts variables in symbol table.
*/
void sort_vars() {
    HASH_SORT(varentries, name_sort_vars);
}

/**
* Compares two functions for sort_funcs().
* @param a Function 1 for comparison
* @param b Function 2 for comparison
*/
int name_sort_funcs(funcentry_t *a, funcentry_t *b) {
    return strcmp(a->funcname,b->funcname);
}

/**
* Sorts functions in symbol table.
*/
void sort_funcs() {
    HASH_SORT(funcentries, name_sort_funcs);
}


/**************************************       CHECK Function Call         *******************************************/

/**
* Checks whether a function call was correct or not.
* @param func The pointer to the structure of the function
* @param pars The parameter list, given to the call
* @return 0 If there was an incorrect function call
* @return 1 If function call was correct
*/
unsigned int check_funccallpar(funcentry_t *func, struct funccallparlist *pars){
	if(func->dim != pars->count){
		printf("dimension, dim: %d, count: %d",func->dim,pars->count);
		return 0;
	}
	varentry_t *par0 = func->var;
	varentry_t *par1 = pars->var;
	for(int i=0;i<func->dim;i++){
		if(par1->isfunccall){
			if(par0->vartype != par1->vartype)
						return 0;
		}
		else{
			if(par0->arrdim != par1->arrdim)
				return 0;
			if(par0->vartype != par1->vartype)
				return 0;
			if(par0->hh.next!=NULL)
				par0 = par0->hh.next;
			else
				break;
			if(par1->hh.next!=NULL)
				par1 = par1->hh.next;
			else
				break;
		}
	}
	return 1;
}

/**
* Creates a parameter list for checking a function call.
* @param var The pointer to the structure of the parameter
* @return The pointer to the parameter list
*/
struct funccallparlist *create_pars_list(varentry_t *var){
	struct funccallparlist *par;
	par = (struct funccallparlist *) malloc (sizeof (struct funccallparlist));
	assert(par!=NULL);
	par->count = 1;
	par->var = var;
	return par;
}


/**************************************       TEMP VAR         *******************************************/

/**
* Creates a temporary variable in the symbol table and returns its pointer.
* @param var_name The name of the temporary variable
* @return The pointer to the structure of the temporary variable
*/
struct varentry *temp_var (char *var_name){
	struct varentry *v;
    v = malloc(sizeof(varentry_t));
	assert(v!=NULL);
    v->varname = malloc(strlen(var_name)+1);
	assert(v->varname!=NULL);
	strcpy (v->varname,var_name);
	v->arrdim = -1;
	v->scope = NULL;
	v->tempArrPos = -1;
	v->tempArrPos2=NULL;
	v->tempCodePos=-1;
	return v;
}

/*************************************       Check for Prototype         ******************************************/

/**
* Checks whether a function is a prototype.
* @param f The pointer to the structure of the function
* @return 0 If function is not a prototype or function was not found in symbol table
* @return 1 If function is a prototype
*/
int is_func_proto (funcentry_t *f){
		return f->isPrototype;
}


/**************************************       Setter Functions         *******************************************/

/**
* Sets the function to prototype.
* @param f The pointer to the structure of the function
*/
void set_func_to_proto (funcentry_t *f){
	f->isPrototype = 1;
}

/**
* Sets the function to declared.
* @param func_name The name of the function
*/
void set_func_to_decl (char *func_name){
	if(find_func(func_name)){
		funcentry_t *ptr = find_func(func_name);
		ptr->isPrototype = 1;
	}
}

/**
* Sets the current function (scope) to the passed function
* @param f The pointer to the structure of the function
*/
void set_func_scope (funcentry_t *f){
	currfunc = f;
}

/**
* Gets the current function (scope) to the passed function
* @return The pointer to the structure of the function or NULL
*/
funcentry_t *get_func_scope (){
	return currfunc;
}

/**
* Sets the scope of all pars of the passed function to this function
* @param f The pointer to the structure of the function
*/
void set_scope_for_pars (funcentry_t *f){
	varentry_t *par = f->var;
	if(par==NULL){
		return;
	}
	for(int i=0;i<f->dim;i++){
		par->scope = f;
		if(par->hh.next!=NULL){
			par = par->hh.next;
		}
		else{
			break;
		}

	}
}
/**
* Prints all variables from the symbol table to the ir file.
*/
void print_vars_ir(){
	char s [200];
	if(varentries==NULL){
			sprintf(s,"No variables in table.\n");
			add_str(s);
			return;
	}
	else{
		varentry_t *v, *tmp;
		char* type;
		char* scope;
		HASH_ITER(hh, varentries, v, tmp) {
			switch (v->vartype){
							case 0:type="Integer"; break;
							case 1:type="Integer Array";;break;
							case 2:type="Void";;break;
			}
			if(v->scope==NULL) scope= "global";
				else scope=v->scope->funcname;

			if(v->arrdim==-1){
				sprintf(s,"Variable: %s, type: %s, Scope: %s, Memory: %d, Offset: %d, Value: %d\n",
									v->varname, type,scope, v->memory,v->offset,v->val);
				add_str(s);
			}
			else{
				sprintf(s,"Variable: %s, type: %s[%d], Scope: %s, Memory: %d, Offset: %d, Value: %d\n",
									v->varname, type,v->arrdim,scope, v->memory,v->offset,v->val);
				add_str(s);
			}
		}
	}
}

/**
* Prints all functions from the symbol table to the ir file.
*/
void print_funcs_ir(){
	char s [200];
	if(funcentries==NULL){
				sprintf(s,"No Functions in table.\n");
				add_str(s);
				return;
	}
	else{
		funcentry_t *f, *tmp;
		char* type;
		char* scope;
		HASH_ITER(hh, funcentries, f, tmp) {
			switch (f->returntype){
							case 0:type="Integer"; break;
							case 1:type="Integer Array";;break;
							case 2:type="Void";;break;
			}
			sprintf(s,"Function: %s(), type: %s, dimension: %d\n", f->funcname, type,f->dim);
			add_str(s);
			varentry_t *v, *tmp;
			HASH_ITER(hh, f->var, v, tmp) {
				switch (v->vartype){
								case 0:type="Integer"; break;
								case 1:type="Integer Array";;break;
								case 2:type="Void";;break;
				}
				if(v->scope==NULL) scope="global";
					else scope=v->scope->funcname;
				if(v->arrdim==-1){
					sprintf(s,"\tParameter of %s: %s, type: %s, Memory: %d, Offset: %d\n",
							f->funcname ,v->varname, type, v->memory,v->offset);
					add_str(s);
				}
				else{
					sprintf(s,"\tParameter of %s: %s, type: %s[%d], Memory: %d, Offset: %d\n",
							f->funcname ,v->varname, type,v->arrdim, v->memory,v->offset);
					add_str(s);
				}
			}
		}
	}
}
