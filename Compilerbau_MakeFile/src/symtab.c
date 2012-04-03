/*
 * symtab.c
 *
 *  Created on: 20 Mar 2012
 *      Author: philipp
 */
#include "symtab.h"
#include <stddef.h>

varentry_t *varentries = NULL;
funcentry_t *funcentries = NULL;
symentry_t *symentries = NULL;



/**************************************        ADD ITEMS          *******************************************/

void add_var(char *varname, enum type vartype,int memory,int adress) {
    varentry_t *v;
    symentry_t *s;
    v = malloc(sizeof(varentry_t));
    strcpy(v->varname, varname);
    v->vartype=vartype;
    v->memory= memory;
    v->adress= adress;
    HASH_ADD_STR(varentries, varname, v);
    s = malloc(sizeof(symentry_t));
    s->id=0;							//0=var, 1=func
    s->sym.var=v;
    HASH_ADD_INT(symentries, id, s);
}

void add_func(char *funcname, enum type returntype,int dim,struct varentry *par) {
    funcentry_t *f;
    symentry_t *s;
    f = malloc(sizeof(funcentry_t));
    strcpy(f->funcname, funcname);
    f->returntype= returntype;
    f->dim = dim;
    HASH_ADD_STR(funcentries, funcname, f);
    //TODO: ADD Arguments
    /*struct varentry *v = malloc(sizeof(*v));
      v->id= args->id;
      strcpy(v->varname, args->varname);
      strcpy(v->vartype, args->vartype);
      v->memory= args->memory;
      v->adress= args->adress;
      HASH_ADD_INT(f->args, args->id, v);
      */
    s = malloc(sizeof(symentry_t));
    s->id=1;							//0=var, 1=func
    s->sym.func=f;
    HASH_ADD_INT(symentries, id, s);
}



/**************************************        FIND ITEMS          *******************************************/

struct varentry *find_var(char *var_name) {
    struct varentry *v;

    HASH_FIND_PTR(symentries, &var_name, v);  /* v: output pointer */
    return v;
}

struct funcentry *find_func(char *func_name) {
    struct funcentry *f;

    HASH_FIND_PTR(symentries, &func_name, f);  /* f: output pointer */
    return f;
}



/**************************************        DELETE ITEMS          *******************************************/

void delete_var(struct varentry *var) {
    HASH_DEL(symentries, var);  	/* var: pointer to delete */
    free(var);             			 /* optional; it's up to you! */
}
void delete_func(struct funcentry *func) {
    HASH_DEL(symentries, func);  	/* var: pointer to delete */
    free(func);             			 /* optional; it's up to you! */
}
