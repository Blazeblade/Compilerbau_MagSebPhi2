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

void add_var(char *varname, enum type vartype,int arrdim,int scope) {
    varentry_t *v;
    symentry_t *s;
    v = malloc(sizeof(varentry_t));
    v->varname = malloc(sizeof(varname));
    strcpy(v->varname, varname);
    v->vartype=vartype;
    v->arrdim=arrdim;
    v->scope=scope;
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

void add_func(char *funcname, enum type returntype,int dim, int arrdim,funcpar_t *par) {
    funcentry_t *f;
    symentry_t *s;
    f = malloc(sizeof(funcentry_t));
	f->funcname = malloc(sizeof(funcname));
    strcpy(f->funcname, funcname);
    f->returntype= returntype;
    f->dim = dim;
    f->arrdim=arrdim;
    f->par = par;
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
void add_funcpar(char *funcname,char *parname, enum type partype, int arrdim) {
	 funcpar_t *p;
	 funcentry_t *f;
	 p = malloc(sizeof(funcpar_t));
	 p->name = malloc(sizeof(parname));
	 strcpy(p->name, parname);
	 p->type=partype;
	 p->arrdim=arrdim;
	 HASH_FIND(hh,funcentries, funcname,strlen(funcname), f);
	 //HASH_ADD_STR(f->par, name, p);
     HASH_ADD_KEYPTR(hh, f->par, p->name, strlen(p->name), p);
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

struct funcpar *find_funcpar(char *par_name, char *func_name) {
    struct funcpar *p;
    struct funcentry *f;
    HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);  	/* f: output pointer */
    HASH_FIND(hh,f->par, par_name,strlen(par_name), p);  		/* P: output pointer */
    return p;
}

struct symentry *find_sym(char *sym_name) {
    symentry_t *s;
    HASH_FIND(hh,symentries, sym_name,strlen(sym_name), s);  	/* s: output pointer */
    return s;
}



/**************************************        DELETE ITEMS        *******************************************/

void delete_var(struct varentry *var) {
    HASH_DEL(symentries, var);  	/* var: pointer to delete */
    free(var);             			 /* optional; it's up to you! */
}
void delete_func(struct funcentry *func) {
    HASH_DEL(funcentries, func);  	/* var: pointer to delete */
    free(func);             			 /* optional; it's up to you! */
}
void delete_funcpar(struct funcpar *par, char *func_name) {
    struct funcentry *f;
    HASH_FIND(hh,funcentries, func_name, strlen(func_name), f);  	/* f: output pointer */
    HASH_DEL(f->par, par);
    free(par);
}



/**************************************     DELETE ALL ITEMS       *******************************************/

void delete_all_vars() {
  varentry_t *v, *tmp;
  HASH_ITER(hh, varentries, v, tmp) {
    HASH_DEL(varentries,v);  /* delete; varentries advances to next */
    free(v);
  }
}

void delete_all_funcs() {
  funcentry_t *f, *tmp;
  HASH_ITER(hh, funcentries, f, tmp) {
    HASH_DEL(funcentries,f);  /* delete; funcentries advances to next */
    free(f);
  }
}
void delete_all_pars(char *func_name) {
  funcpar_t *p, *tmp;
  struct funcentry *f;
  HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);  	/* f: output pointer */
  HASH_ITER(hh, f->par, p, tmp) {
    HASH_DEL(f->par,p);  		/* delete; f->par advances to next */
    free(p);
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
	return HASH_COUNT(f->par);
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
		HASH_ITER(hh, varentries, v, tmp) {
			printf("Variable: %s, type: %d, [%d]\n", v->varname, v->vartype,v->arrdim);
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
		HASH_ITER(hh, funcentries, f, tmp) {
			printf("Function: %s(), type: %d, dimension: %d\n", f->funcname, f->returntype,f->dim);
			funcpar_t *p, *tmp;
			HASH_ITER(hh, f->par, p, tmp) {
				printf("\tParameter of %s: %s, type: %d, [%d]\n",f->funcname ,p->name, p->type,p->arrdim);
			}
		}
	}
}

void print_pars(char *func_name){
	struct funcentry *f;
	HASH_FIND(hh,funcentries, func_name,strlen(func_name), f);
	if(f->par==NULL)
			{
				printf("No Parameters in table for %s.\n",func_name);
				return;
			}
	else{
		funcpar_t *p, *tmp;
		HASH_ITER(hh, f->par, p, tmp) {
			printf("Parameter of %s: %s, type: %d, [%d]\n",func_name ,p->name, p->type,p->arrdim);
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
		HASH_ITER(hh, symentries, s, tmp) {
			if(s->type==0)
				printf("Variable: %s, type: %d, [%d]\n", s->sym.var->varname, s->sym.var->vartype,s->sym.var->arrdim);
			else
				printf("Function: %s(), type: %d, dimension: %d\n",
						s->sym.func->funcname,  s->sym.func->returntype, s->sym.func->dim);
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
	funcpar_t *param0 = func0->par;
	funcpar_t *param1 = params->par;
	for(int i=0;i<func0->dim;i++){
		if(param0->arrdim != param1->arrdim){
			return 0;
		}
		if(param0->type != param1->type){
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
struct funccallparlist *createParamList(funcpar_t *par)
{
	struct funccallparlist *ptr;
	ptr = (struct funccallparlist *) malloc (sizeof (struct funccallparlist));
	ptr->count = 1;
	ptr->par = par;
	return ptr;
}
