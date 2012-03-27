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

void add_var(int id, char *varname, enum type *vartype,int *memory,int *adress) {
    varentry_t *v;
    v = malloc(sizeof(varentry_t));
    strcpy(v->varname, varname);
    strcpy(v->vartype, vartype);
    v->memory= memory;
    v->adress= adress;
    symentries->id=id;
    HASH_ADD_STR(symentries, varname, v);
}

void add_func(int id, char *funcname, enum type *returntype,int *dim,struct varentry *args) {
    funcentry_t *f;
    f = malloc(sizeof(funcentry_t));
    symentries->id = id;
    strcpy(f->funcname, funcname);
    strcpy(f->returntype, returntype);
    f->dim = dim;
    //TODO: add args
    HASH_ADD_INT(symentries, funcname, f);
    /*struct varentry *v = malloc(sizeof(*v));
      v->id= args->id;
      strcpy(v->varname, args->varname);
      strcpy(v->vartype, args->vartype);
      v->memory= args->memory;
      v->adress= args->adress;
      HASH_ADD_INT(f->args, args->id, v);
      */
}



/**************************************        FIND ITEMS          *******************************************/

struct varentry *find_var(char var_name[]) {
    struct varentry *v;

    HASH_FIND_STR(symentries, &var_name, v);  /* v: output pointer */
    return v;
}

struct funcentry *find_func(char func_name[]) {
    struct funcentry *f;

    HASH_FIND_STR(symentries, &func_name, f);  /* f: output pointer */
    return f;
}



/**************************************        DELETE ITEMS          *******************************************/

void delete_var(struct varentry *var) {
    HASH_DEL(varentries, var);  	/* var: pointer to delete */
    free(var);             			 /* optional; it's up to you! */
}
void delete_func(struct funcentry *func) {
    HASH_DEL(funcentries, func);  	/* var: pointer to delete */
    free(func);             			 /* optional; it's up to you! */
}
