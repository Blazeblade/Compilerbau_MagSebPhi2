/*
 * symtab.c
 *
 *  Created on: 20 Mar 2012
 *      Author: Philipp Goetze
 *
 *  Comments:
 *  	Iterating with next/prev
 *  		s=(struct my_struct*)s->hh.next
 *  		s=(struct my_struct*)s->hh.prev
 *
 *
 */
#include "symtab.h"
#include <assert.h>
#include <stdio.h>   /* gets,printf */
#include <stdlib.h>  /* atoi, malloc */
#include <string.h>  /* strcpy */

varentry_t *varentries;
funcentry_t *funcentries;
symentry_t *symentries;

/**************************************      Initialise Tables     *******************************************/

void init_table ()
{
	varentries=NULL;
	funcentries=NULL;
	symentries=NULL;
	//printf("Symbol Table was initialised.\n");
}

/**************************************        ADD ITEMS          *******************************************/

void add_var(char *varname, enum type vartype,int arrdim,int scope, int value) {
    varentry_t *v;
    symentry_t *s;
    v = malloc(sizeof(varentry_t));
    v->varname = malloc(sizeof(varname));
    strcpy(v->varname, varname);
    v->vartype=vartype;
    v->arrdim=arrdim;
    v->scope=scope;
    v->var=value;
    //HASH_ADD_STR(varentries, varname, v);
    HASH_ADD_KEYPTR(hh, varentries, v->varname, strlen(v->varname), v );
    s = malloc(sizeof(symentry_t));
    s->name = malloc(sizeof(varname));
    strcpy(s->name, varname);
    s->type=0;							//0=var, 1=func
    s->arrdim=arrdim;
    s->sym.var=v;
    //HASH_ADD_STR(symentries, name, s);
    HASH_ADD_KEYPTR(hh, symentries, s->name, strlen(s->name), s );
    return;
}

void add_func(char *funcname, enum type returntype,int dim, int arrdim,varentry_t *var) {
    funcentry_t *f;
    symentry_t *s;
    f = malloc(sizeof(funcentry_t));
	f->funcname = malloc(sizeof(funcname));
    strcpy(f->funcname, funcname);
    f->returntype= returntype;
    f->dim = dim;
    f->arrdim=arrdim;
    f->var = var;
    //HASH_ADD_STR(funcentries, funcname, f);
    HASH_ADD_KEYPTR(hh, funcentries, f->funcname, strlen(f->funcname), f );
    s = malloc(sizeof(symentry_t));
	s->name = malloc(sizeof(funcname));
    strcpy(s->name,funcname);
    s->type=1;	//0=var, 1=func
    s->arrdim=arrdim;
    s->sym.func=f;
    //HASH_ADD_STR(symentries, name, s);
    HASH_ADD_KEYPTR(hh, symentries, s->name, strlen(s->name), s );
    return;

}
void add_funcpar(char *funcname,char *varname, enum type vartype, int arrdim) {
	 varentry_t *p;
	 funcentry_t *f;
	 p = malloc(sizeof(varentry_t));
	 p->varname = malloc(sizeof(varname));
	 strcpy(p->varname, varname);
	 p->vartype=vartype;
	 p->arrdim=arrdim;
	 HASH_FIND(hh,funcentries, funcname,strlen(funcname), f);
	assert(f!=NULL);
	 //HASH_ADD_STR(f->var, name, p);
     HASH_ADD_KEYPTR(hh, f->var, p->varname, strlen(p->varname), p);
     return;
}


/**************************************        FIND ITEMS          *******************************************/

struct varentry *find_var(char *var_name) {
    struct varentry *v;
    HASH_FIND(hh,varentries, var_name,strlen(var_name), v); 	/* v: output pointer */
    return v;
}

struct funcentry *find_func(char *func_name) {
    struct funcentry *f;
    HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);  	/* f: output pointer */
    return f;
}

struct varentry *find_funcpar(char *var_name, char *func_name) {
    struct varentry *v;
    struct funcentry *f;
    HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);  	/* f: output pointer */
    HASH_FIND(hh,f->var, var_name,strlen(var_name), v);  		/* P: output pointer */
    return v;
}

struct symentry *find_sym(char *sym_name) {
    symentry_t *s;
    HASH_FIND(hh,symentries, sym_name,strlen(sym_name), s);  	/* s: output pointer */
    return s;
}



/**************************************        DELETE ITEMS        *******************************************/

void delete_var(struct varentry *var) {
    struct symentry *s;
    HASH_FIND(hh,symentries,var->varname,strlen(var->varname),s);
    HASH_DEL(symentries, s);
    free(s);
    HASH_DEL(varentries,var);		/* var: pointer to delete */
    free(var);             			 /* optional; it's up to you! */

}
void delete_func(struct funcentry *func) {
    struct symentry *s;
    HASH_FIND(hh,symentries,func->funcname,strlen(func->funcname),s);
    HASH_DEL(symentries, s);
    free(s);
    HASH_DEL(funcentries,func);		/* func: pointer to delete */
    free(func);						/* optional; it's up to you! */
}
void delete_funcpar(struct varentry *var, char *func_name) {
    struct funcentry *f;
    HASH_FIND(hh,funcentries, func_name, strlen(func_name), f);  	/* f: output pointer */
    HASH_DEL(f->var, var);
    free(var);
}



/**************************************     DELETE ALL ITEMS       *******************************************/

void delete_all_vars() {
  varentry_t *v, *tmp;
  HASH_ITER(hh, varentries, v, tmp) {
	HASH_DEL(symentries,v);
    HASH_DEL(varentries,v);  /* delete; varentries advances to next */
    free(v);
  }
}

void delete_all_funcs() {
  funcentry_t *f, *tmp;
  HASH_ITER(hh, funcentries, f, tmp) {
	HASH_DEL(symentries,f);
    HASH_DEL(funcentries,f);  /* delete; funcentries advances to next */
    free(f);
  }
}
void delete_all_pars(char *func_name) {
  varentry_t *v, *tmp;
  struct funcentry *f;
  HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);  	/* f: output pointer */
  HASH_ITER(hh, f->var, v, tmp) {
    HASH_DEL(f->var,v);  		/* delete; f->var advances to next */
    free(v);
  }
}

void delete_all() {
  symentry_t *s, *tmp;
  HASH_ITER(hh, symentries, s, tmp) {
    HASH_DEL(symentries,s);  /* delete; symentries advances to next */
    free(s);
  }
}



/**************************************       Count ITEMS         *******************************************/

unsigned int count_vars(){
	return HASH_COUNT(varentries);
}

unsigned int count_funcs(){
	return HASH_COUNT(funcentries);
}

unsigned int count_pars(char *func_name) {
	struct funcentry *f;
	HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);
	assert(f!=NULL);
	return HASH_COUNT(f->var);
}

unsigned int count_all(){
	return HASH_COUNT(symentries);
}



/**************************************       PRINT ITEMS         *******************************************/

void print_vars(){
	if(varentries==NULL)
		{
			printf("No variables in table.\n");
			return;
		}
	else{
		varentry_t *v, *tmp;
		char* type;
		HASH_ITER(hh, varentries, v, tmp) {
			switch (v->vartype){
							case 0:type="Integer"; break;
							case 1:type="Integer Array";;break;
							case 2:type="Void";;break;
						}
			if(v->arrdim==-1)
				printf("Variable: %s, type: %s\n", v->varname, type);
			else
				printf("Variable: %s, type: %s[%d]\n", v->varname, type,v->arrdim);
		}
	}
}

void print_funcs(){
	if(funcentries==NULL)
			{
				printf("No Functions in table.\n");
				return;
			}
	else{
		funcentry_t *f, *tmp;
		char* type;
		HASH_ITER(hh, funcentries, f, tmp) {
			switch (f->returntype){
							case 0:type="Integer"; break;
							case 1:type="Integer Array";;break;
							case 2:type="Void";;break;
						}
			printf("Function: %s(), type: %s, dimension: %d\n", f->funcname, type,f->dim);
			varentry_t *v, *tmp;
			HASH_ITER(hh, f->var, v, tmp) {
				switch (f->var->vartype){
								case 0:type="Integer"; break;
								case 1:type="Integer Array";;break;
								case 2:type="Void";;break;
							}
				if(v->arrdim==-1)
					printf("\tParameter of %s: %s, type: %s\n",f->funcname ,v->varname, type);
				else
					printf("\tParameter of %s: %s, type: %s[%d]\n",f->funcname ,v->varname, type,v->arrdim);
			}
		}
	}
}

void print_pars(char *func_name){
	struct funcentry *f;
	HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);
	if(f->var==NULL)
			{
				printf("No Parameters in table for %s.\n",func_name);
				return;
			}
	else{
		varentry_t *v, *tmp;
		char* type;
		HASH_ITER(hh, f->var, v, tmp) {
			switch (v->vartype){
				case 0:type="Integer"; break;
				case 1:type="Integer Array";;break;
				case 2:type="Void";;break;
			}
			if(v->arrdim==-1)
				printf("Parameter of %s: %s, type: %s\n",func_name ,v->varname, type);
			else
				printf("Parameter of %s: %s, type: %s[%d]\n",func_name ,v->varname, type,v->arrdim);
		}
	}
}

void print_all(){
	if(symentries==NULL)
			{
				printf("No Symbols in table.\n");
				return;
			}
	else{
		symentry_t *s, *tmp;
		char* type;
		HASH_ITER(hh, symentries, s, tmp) {
			if(s->type==0){
				switch (s->sym.var->vartype){
								case 0:type="Integer"; break;
								case 1:type="Integer Array";;break;
								case 2:type="Void";;break;
							}
				if(s->sym.var->arrdim==-1)
					printf("Variable: %s, type: %s\n", s->sym.var->varname, type);
				else
					printf("Variable: %s, type: %s[%d]\n", s->sym.var->varname, type,s->sym.var->arrdim);
			}
			else {
				switch (s->sym.func->returntype){
								case 0:type="Integer"; break;
								case 1:type="Integer Array";;break;
								case 2:type="Void";;break;
							}
				printf("Function: %s(), type: %s, dimension: %d\n",
						s->sym.func->funcname,  type, s->sym.func->dim);
			}

		}
	}
}

/**************************************       SORT ITEMS         *******************************************/

//Not sure whether this should do the trick...

int name_sort_vars(varentry_t *a, varentry_t *b) {
    return strcmp(a->varname,b->varname);
}
void sort_vars() {
    HASH_SORT(varentries, name_sort_vars);
}

int name_sort_funcs(funcentry_t *a, funcentry_t *b) {
    return strcmp(a->funcname,b->funcname);
}
void sort_funcs() {
    HASH_SORT(funcentries, name_sort_funcs);
}

int name_sort_all(symentry_t *a, symentry_t *b) {
    return strcmp(a->name,b->name);
}
void sort_all() {
    HASH_SORT(symentries, name_sort_all);
}



/**************************************       CHECK ITEMS         *******************************************/

unsigned int check_funccallpar(funcentry_t *func0, struct funccallparlist *params){
	if(func0->dim != params->count){
		return 0;
	}
	varentry_t *param0 = func0->var;
	varentry_t *param1 = params->var;
	for(int i=0;i<func0->dim;i++){
		if(param0->arrdim != param1->arrdim){
			return 0;
		}
		if(param0->vartype != param1->vartype){
			return 0;
		}
		if(param0->hh.next!=NULL){
			param0 = param0->hh.next;
		}
		else{
			break;
		}
		if(param1->hh.next!=NULL){
			param1 = param1->hh.next;
		}
		else{
			break;
		}
	}
	return 1;
}
struct funccallparlist *createParamList(varentry_t *var)
{
	struct funccallparlist *ptr;
	ptr = (struct funccallparlist *) malloc (sizeof (struct funccallparlist));
	ptr->count = 1;
	ptr->var = var;
	return ptr;
}
/**************************************       TEMP VAR         *******************************************/

struct varentry *tempInt (char const *name)
{
	struct varentry *ptr;
	//set name
    ptr = malloc(sizeof(varentry_t));
    ptr->varname = malloc(sizeof(name));
	strcpy (ptr->varname,name);

	ptr->arrdim = -1;
	ptr->scope = 0;
//
//	ptr->isParam = 0;
//	ptr->stackpos = 0;
//	ptr->isTemp = 1;
	ptr->tempArrPos = -1;
	ptr->tempArrPos2=NULL;
	ptr->tempCodePos=-1;

//	ptr->next = 137; //Temp Var Marker...

	return ptr;
}
