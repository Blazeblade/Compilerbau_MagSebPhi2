/*
 * symtab.c
 *
 *  Created on: 20 Mar 2012
 *      Author: philipp
 */
#include "symtab.h"
#include <stddef.h>

struct varentry *varentries = NULL;
struct funcentry *funcentries = NULL;



/**************************************        ADD ITEMS          *******************************************/

void add_var(int varid, char *varname, enum type *vartype,int *memory,int *adress) {
    struct varentry *v;
    v = malloc(sizeof(struct varentry));
    v->id = varid;
    strcpy(v->varname, varname);
    strcpy(v->vartype, vartype);
    v->memory= memory;
    v->adress= adress;
    HASH_ADD_INT(varentries, varid, v);
}

void add_func(int funcid, char *funcname, enum type *returntype,int *dim,struct varentry *args) {
    struct funcentry *f;
    f = malloc(sizeof(struct funcentry));
    f->id = funcid;
    strcpy(f->funcname, funcname);
    strcpy(f->returntype, returntype);
    f->dim = dim;
    //TODO: add args
    HASH_ADD_INT(funcentries, funcid, f);
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

struct varentry *find_var(int var_id) {
    struct varentry *v;

    HASH_FIND_INT(varentries, &var_id, v);  /* v: output pointer */
    return v;
}

struct funcentry *find_func(int func_id) {
    struct funcentry *f;

    HASH_FIND_INT(funcentries, &func_id, f);  /* f: output pointer */
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
