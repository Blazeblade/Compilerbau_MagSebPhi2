/**
 * @file 	ir_code_gen.c
 * @date	Created on: 10 Apr 2012
 * @author	Sebastian Boehm, Magnus Bruehl, Philipp Goetze
 * @brief	Functions for intermediate code generation
 * Remark: 	We decided to print the IR Code to the file (if p arg is given),
 * 			even if there was an error!
 *
 */
#include "ir_code_gen.h"
#include "symtab.h"
#include "parser.h"
#include "diag.h"
#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>

extern void yyerror (const char *msg);

/*
 * Constant (Mark/Identifier)
 */
#define MARK1 -2

/*
 * Structure to store the Code
 */
struct code_struct  *code=NULL;
/*
 * Code "line number"
 */
int code_count = 0;
/*
 * Counter for temporary Register/Variables (.t0,.t1,[...])
 */
int temp_reg_count = -1;
/*
 * Label counter (.l0,.l1,[...])
 */
int jmpLabel_count=-1;
/*
 * Char array for file output (fprintf)
 */
char s [200];
/*
 * Destination file handler
 */
FILE *ir_file;




/***********************************      Code Generations         ***********************************/



/**
* Generates the code at current position and stores it into the code variable
* @param operation The operation of this "code snippet", necessary
* @param var0 The pointer to the structure of a first variable (if variable is necessary)[NULLable]
* @param var1 The pointer to the structure of a second variable (if variable is necessary)[NULLable]
* @param var2 The pointer to the structure of a third variable (if variable is necessary)[NULLable]
* @param func The pointer to the structure of the function (if a function is used in this code) [NULLable]
* @param jmpTo For Marking, otherwise = -1 (processed in backpatching)
*/
void gencode(enum code_operations operation, varentry_t *var0, varentry_t *var1, varentry_t *var2, funcentry_t *func, int jmpTo){
	code_count += 1;
	struct code_struct *codebuffer = (struct code_struct*) realloc (code, code_count * sizeof(struct code_struct));
	if (codebuffer == NULL) {
		FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "codebuffer -> realloc");
		return;
	}
	//assert(codebuffer!=NULL);
	code = codebuffer;
	code[code_count-1].op = operation;
	code[code_count-1].var0 = var0;
	code[code_count-1].var1 = var1;
	code[code_count-1].var2 = var2;
	code[code_count-1].func = func;
	code[code_count-1].jmpTo = jmpTo;
	code[code_count-1].jmpLabel = -1;
}

/**
* Prepares the code at current position for assignments and calls then the gencode(...)
* @param var0 The pointer to the structure of the variable left of the assignment
* @param var1 The pointer to the structure of the variable right of the assignment
*/
void gencode_ass(varentry_t *var0, varentry_t *var1){
	if(var0->var_arr_loc>-1)
		gencode(MEM_ST_IR, (struct varentry *) var0->hh.next,var0->var_arr_loc_struct , var1 , NULL, -1);
	else{
		if((var0->vartype==1) && (var1->vartype!=1))
			yyerror ("Type mismatch! Array without indexing can not get assigned a value");
		if(var1->vartype==1)
			if(var0->vartype==0 && var1->var_arr_loc==-1)
				yyerror ("Type mismatch! Array without indexing can not be assigned an Integer");
		if(var1->vartype==2)
						yyerror ("Operands can not be of type VOID");
		gencode(ASSIGN_IR, var0, var1, NULL, NULL, -1);
	}
	temp_reg_count = 0;
}

/**
* Prepares the code at current position for expressions with one operand and calls then the gencode(...)
* @param operation The operation of this expression
* @param var1 The pointer to the structure of the affected variable
* @return The pointer to the structure of the variable, which got the altered value of var1
*/
varentry_t *gencode_op1exp(enum code_operations operation, varentry_t *var1){
	varentry_t *v;
	v = ir_temp_var();
	if(var1->vartype==2)
		yyerror ("Operands can not be of type VOID");
	if(var1->vartype==1){
		varentry_t *temp;
		temp=(struct varentry *) var1->hh.next;
		if(temp->var_arr_loc==-1)
			yyerror ("Operand must have an array index");
	}
	gencode(operation, v, var1, NULL, NULL, -1);
	return v;
}

/**
* Prepares the code at current position for expressions with two operands and calls then the gencode(...)
* @param operation The operation of this expression
* @param var1 The pointer to the structure of the first operand
* @param var2 The pointer to the structure of the second operand
* @return The pointer to the structure of the variable, which got the altered value of var1 and var2
*/
varentry_t *gencode_op2exp(enum code_operations operation, varentry_t *var1, varentry_t *var2){
	varentry_t *v;
	v = ir_temp_var();
	if(var1->vartype==2 || var2->vartype==2)
		yyerror ("Operands can not be of type VOID");
	varentry_t *temp;
	if(var1->vartype==1){
		temp=(struct varentry *) var1->hh.next;
		if(temp->var_arr_loc==-1)
			yyerror ("First Operand must have an array index");
	}
	if(var2->vartype==1){
		temp=(struct varentry *) var2->hh.next;
		if(temp->var_arr_loc==-1)
			yyerror ("Second Operand must have an array index");
	}
	gencode(operation, v, var1, var2, NULL, -1);
	return v;
}

/**
* Prepares the code at current position for Returns and Parameter storing and calls then the gencode(...)
* @param operation The operation of this expression
* @param var0 The pointer to the structure of the affected variable
*/
void gencode_op1(enum code_operations operation, varentry_t *var0){
	if(operation==RETURN_IR)
		gencode(operation, var0, NULL, NULL, NULL, MARK1);
	else if(operation==PARAM_IR)
		gencode(operation, var0, NULL, NULL, NULL, -1);
}

/**
* Prepares the code at current position for Arrays and calls then the gencode(...)
* @param var1 The pointer to the structure of the first variable (the Array ID)
* @param var2 The pointer to the structure of the second variable (the array index)
* @return The pointer to the structure of the variable, which gets the altered value of var1 and var2
*/
varentry_t * gencode_load_arr(varentry_t *var1, varentry_t *var2){
	varentry_t *v;
	v = ir_temp_var();
	var1->var_arr_loc =	var2->val;
	v->hh.next = var1;
	gencode(MEM_LD_IR, v, var1, var2, NULL, -1);
	v->var_cpos = code_count -1 ;
	return v;
}

/**
* Prepares the code at current position for function definitions and calls then the gencode(...)
* @param operation The operation of this statement (should be FuncDef)
* @param var0 The pointer to the structure of the parameter list
* @param func The pointer to the structure of the function
*/
void gencode_opfunc(enum code_operations operation, varentry_t *var0, funcentry_t*func){
	gencode(operation, var0, NULL, NULL, func, -1);
}

/**
* Prepares the code at current position for If statements and calls then the gencode(...)
* @param var0 The pointer to the structure of the affected variable (contains if-expression)
*/
void genif(varentry_t *var0){
	gencode(IF_IR, var0, NULL, NULL, NULL, code_count+2);
}

/**
* Prepares the code at current position for GOTO statements after IF and calls then the gencode(...)
* The GOTO Label will be defined via backpatching, there for the marker(MARK1)
*/
void genif_goto(){
	gencode(GOTO_IR, NULL, NULL, NULL, NULL, MARK1);
}

/**
* Prepares the code at current position for While statements and calls then the gencode(...)
* @param var0 The pointer to the structure of the affected variable (contains if-expression)
*/
void genwhile(varentry_t *var0){
	gencode(IF_IR, var0, NULL, NULL, NULL, code_count+2);
}

/**
* Prepares the code at current position for While Begin and calls then the gencode(...)
*/
void genwhile_begin(){
	gencode(WHILE_BEGIN_IR, NULL, NULL, NULL, NULL, MARK1);
}

/**
* Prepares the code at current position for While Begin and calls then the gencode(...)
* The GOTO Label will be defined via backpatching, there for the marker(MARK1)
*/
void genwhile_gotobegin(){
	gencode(GOTO_IR, NULL, NULL, NULL, NULL, MARK1);
}

/**
* Prepares the code at current position for Do While Begin and calls then the gencode(...)
*/
void gendowhile(){
	gencode(DO_WHILE_BEGIN_IR, NULL, NULL, NULL, NULL, MARK1);
}

/**
* Checks the code for Do While Begin and set back the jump adresses
* @param var0 The pointer to the structure of the affected variable (for the if-expression at the end of do_while)
*/
void gendowhile_end(varentry_t *var0){
	struct code_struct  *c;
	int i;
	for(i=code_count-1;i>=0;i--){
		c = &code[i];
		if(c->op==DO_WHILE_BEGIN_IR){
			if(c->jmpTo==MARK1){
				c->jmpTo=-1;
				break;
			}
		}
	}
	gencode(IF_IR, var0, NULL, NULL, NULL, i);
}

/**
* Prepares the code at current position for function calls and calls then the gencode(...)
* @param operation The operation of this statement (should be Call)
* @param var0 The pointer to the structure of the parameter list
* @param func The pointer to the structure of the function
* @param jmpTo The jump address in the IR code
* @return The pointer to the structure of the function call
*/
struct varentry *gencode_funccall(enum code_operations operation, struct varentry *var0, struct funcentry *func, int jmpTo){
	varentry_t *v;
	v = ir_temp_var();
	gencode(operation, var0, v, NULL, func, jmpTo);
	return v;
}




/*************************************       Backpatching         ************************************/



/**
* Sets the GOTO operation which have the marker (MARK1) to the now known jump address (for if statements)
* @param shift For skipping code (0 - without Else statement, 1- with Else statement)
*/
void backpatch_if(int shift){
	struct code_struct  *c;
	for(int i=code_count-1;i>=0;i--){
		c = &code[i];
		if(c->op==GOTO_IR){
			if(c->jmpTo==MARK1){
				if(shift!=2){
					c->jmpTo = code_count + shift;
					break;
				}
				else{
					c->jmpTo = code_count;
					c->jmpLabel = -3;
					break;
				}
			}
		}
	}
}


/**
* Sets the operation which have the marker (MARK1) to the now known jump address (for return statements)
*/
void backpatch_return(){
	struct code_struct  *c;
	for(int i=0;i<code_count;i++){
		c = &code[i];
		if(c->op==RETURN_IR){
			if(c->jmpTo==MARK1){
				c->jmpTo = code_count - 1;
			}
		}
	}
}

/**
* Sets the operation which have the marker (MARK1) to the now known jump address (for while statements)
*/
void backpatch_while(){
	struct code_struct  *c;
	for(int i=code_count-1;i>=0;i--){
		c = &code[i];
		if(c->op==GOTO_IR){
			if(c->jmpTo==MARK1){
				c->jmpTo = code_count+1;
				//break;
			}
		}
		else if(c->op==WHILE_BEGIN_IR){
			if(c->jmpTo==MARK1){
				gencode(GOTO_IR, NULL, NULL, NULL, NULL, i);
				c->jmpTo=-1;
				break;
			}
		}
	}
}




/************************************       Helper Methods         ***********************************/



/**
* Creates a temporary variable structure for the IR Code (.t0,.t1,[...])
* @return The temporary variable structure
*/
varentry_t *ir_temp_var(){
	temp_reg_count++;
	char buffer [5];
	sprintf (buffer, ".t%d", temp_reg_count);
	varentry_t *v;
	v = temp_var(buffer);
	v->arrdim = temp_reg_count;
	return v;
}

/**
* For function call to find goto address
* @param func The pointer to the structure of the function, which shall be called
* @return The Jump Address to function
*/
int opcode_find_FuncDef(funcentry_t *func){
	struct code_struct  *c;
	for(int i=0;i<code_count;i++){
		c = &code[i];
		if(c->func==func){
			return i;
		}
	}
	return 0;
}

/**
* Sets Jump Labels in the code with the given jmpLabel and code position
* @param cpos The position in the code of the statement/expression
* @param jmpLabel The jump label the statement/expression will get
* @return 0- if code already had a jump Label or position is not valid
* @return 1- if code got the jump label
*/
int set_jmpLabel(int cpos, int jmpLabel){
	if(code[cpos].jmpLabel<0)	{
		if((cpos>0) && (cpos<code_count)){
			code[cpos].jmpLabel = jmpLabel;
			return 1;
		}
	}
	return 0;
}

/**
* Sets the operation of the code at a specified position to NOP
* @param pos The position in the code of the statement/expression
*/
void set_code_to_NOP(int pos){
	code[pos].op = NOP_IR;
}

/**
* Sets the temporary register counter to back to zero, done after every statement
*/
void reset_temp_count(){
	temp_reg_count = 0;
}




/********************************       Generation of IR File         ********************************/



/**
* Initialises the IR file
* @param file The pointer to the file, where the Code shall be stored
*/

void init_ir_code(FILE *file){
	ir_file = file;
}

/**
* Inserts the given char sequence into the IR file
* @param str The string, which shall be inserted
*/
void add_str(const char *str){
	fputs (str,ir_file);
}

/**
* Prints the whole symbol table and IR code to the *.ir file
* The ir output is also generated here
*/
void generate_ir_code(){
	struct code_struct  *c;
	struct varentry *pars=NULL;
	int parcount=0;
	char tab = '\0';
	sprintf (s, "----------   Symbol Table  ----------\n");
	add_str(s);
	print_vars_ir();
	print_funcs_ir();
	sprintf (s, "--------- Intermediate Code ---------\n");
	add_str(s);

	for(int i=0;i<code_count;i++){
		c = &code[i];
		if(c->op==FUNC_DEF_END_IR || c->op==PARAM_IR || c->op==WHILE_BEGIN_IR ||
									c->op==DO_WHILE_BEGIN_IR || c->op==NOP_IR)
			tab = '\0';
		if(c->jmpLabel > -1){
			sprintf (s, ".l%d:\n", c->jmpLabel);
			add_str(s);
		}
		sprintf (s,"%c", tab);
		add_str(s);
		switch(c->op){
		case ASSIGN_IR:
			sprintf (s,"%s = %s",c->var0->varname,c->var1->varname);
			add_str(s);
			break;
		case ADD_IR:
			sprintf (s, "%s = %s + %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case SUB_IR:
			sprintf (s, "%s = %s - %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case MUL_IR:
			sprintf (s, "%s = %s * %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case MINUS_IR:
			sprintf (s, "%s = -%s", c->var0->varname,c->var1->varname);
			add_str(s);
			break;
		case SHIFT_LEFT_IR:
			sprintf (s, "%s = %s << %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case SHIFT_RIGHT_IR:
			sprintf (s, "%s = %s >> %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
			break;
		case LOGICAL_AND_IR:
			sprintf (s, "%s = %s && %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case LOGICAL_OR_IR:
			sprintf (s, "%s = %s || %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case LOGICAL_NOT_IR:
			sprintf (s, "%s = !%s", c->var0->varname,c->var1->varname);
			add_str(s);
			break;
		case NE_IR:
			sprintf (s, "%s = %s != %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case EQ_IR:
			sprintf (s, "%s = %s == %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case GT_IR:
			sprintf (s, "%s = %s > %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case GTEQ_IR:
			sprintf (s, "%s = %s >= %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case LS_IR:
			sprintf (s, "%s = %s < %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case LSEQ_IR:
			sprintf (s, "%s = %s <= %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case IF_IR:
			jmpLabel_count++;
			if(!set_jmpLabel(c->jmpTo, jmpLabel_count)){
				jmpLabel_count--;
			}
			c->jmpTo = jmpLabel_count;
			sprintf (s, "IF %s GOTO .l%d", c->var0->varname,c->jmpTo);
			add_str(s);
			break;
		case GOTO_IR:
			jmpLabel_count++;								//backpatch enhancement
			if(!set_jmpLabel(c->jmpTo, jmpLabel_count)){
				struct code_struct  *c2;
				int count2=-1;
				int temp=-1;
				for(int j=0;j<i;j++){
					c2 = &code[j];
					if(c2->op==WHILE_BEGIN_IR && c2->jmpLabel!=-1){
						count2=c2->jmpLabel;
						temp=j;
					}
				}
				if(temp!=-1)
					code[temp].jmpLabel=-1;
				if(count2==-1){
					if(c->jmpLabel==-3){
						temp=-1;
						for(int j=0;j<i;j++){
							c2 = &code[j];
							if(c2->op==IF_IR){
								count2=code[j+1].jmpTo+1;
								temp=j+1;
								break;
							}
						}
						if(count2==-1){
							jmpLabel_count--;
							c->jmpTo = jmpLabel_count;
						}
						else{
							code[temp].jmpTo=-1;
							c->jmpTo=count2;
						}
						c->jmpLabel=-1;
					}
					else{
					jmpLabel_count--;
					c->jmpTo = jmpLabel_count;
					}
				}
				else
					c->jmpTo=count2;
			}
			else
				c->jmpTo = jmpLabel_count;
			sprintf (s, "GOTO .l%d", c->jmpTo);
			add_str(s);
			break;
		case WHILE_BEGIN_IR:
			jmpLabel_count++;
			/*if(!set_jmpLabel(i, jmpLabel_count)){
				jmpLabel_count = jmpLabel_count - 1;
			}*/
			c->jmpLabel = jmpLabel_count;
			sprintf (s, ".l%d:\n", c->jmpLabel);
			add_str(s);
			break;
		case DO_WHILE_BEGIN_IR:
			jmpLabel_count++;
			/*if(!set_jmpLabel(i, jmpLabel_count)){
				//jmpLabel_count = jmpLabel_count - 1;
			}*/
			c->jmpLabel = jmpLabel_count;
			sprintf (s, ".l%d:\n", c->jmpLabel);
			add_str(s);
			break;
		case RETURN_IR:
			/*jmpLabel_count = jmpLabel_count + 1;
			if(!set_jmpLabel(c->jmpTo, jmpLabel_count)){
				jmpLabel_count = jmpLabel_count - 1;
			}
			c->jmpTo = jmpLabel_count;
			sprintf (s, "RETURN %s GOTO .l%d", c->var0->varname,c->jmpTo);*/
			if (c->var0!=NULL)
				sprintf(s,"RETURN %s", c->var0->varname);
			else
				sprintf(s,"RETURN");
			add_str(s);
			break;
		case PARAM_IR:
			parcount++;
		    HASH_ADD_KEYPTR(hh, pars, c->var0->varname, strlen(c->var0->varname), c->var0);
			tab = '\t';
			break;
		case CALL_IR:
			sprintf (s, "%s = CALL .f_%s(",c->var1->varname,c->func->funcname);
			add_str(s);
			for(int i=0;i<parcount;i++){
				if(i==parcount-1)
					sprintf (s, "%s", pars->varname);
				else
					sprintf (s, "%s, ", pars->varname);
				add_str(s);
				pars=(struct varentry *) pars->hh.next;
			}
			//sprintf (s, ")GOTO .l%d",c->jmpTo);
			sprintf (s, ") GOTO %s",c->func->funcname);
			add_str(s);
			parcount=0;
			varentry_t *p, *tmp;
			HASH_ITER(hh, pars, p, tmp) {
				HASH_DEL(pars,p);
				free(p);
			}
			break;
		case MEM_LD_IR:
			sprintf (s, "%s = %s[%s]", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case MEM_ST_IR:
			sprintf (s, "%s[%s] = %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case ADDR_IR:
			sprintf (s, "%s = ADDR(%s)", c->var0->varname,c->var1->varname);
			add_str(s);
			break;
		case FUNC_DEF_IR:
			if(c->func!=NULL){
				sprintf (s, "%s:", c->func->funcname);
				add_str(s);
			}
			tab = '\t';
			break;
		case FUNC_DEF_END_IR:
			//Nothing (just CRLF)
			break;
		case NOP_IR:
			tab = '\t';
			break;
		}
		if(c->op==WHILE_BEGIN_IR || c->op==DO_WHILE_BEGIN_IR)
			tab = '\t';
		if(c->op!=PARAM_IR && c->op!=NOP_IR && c->op!=WHILE_BEGIN_IR && c->op!=DO_WHILE_BEGIN_IR){
			sprintf (s, "\n");
			add_str(s);
		}
	}
//	sprintf (s, ".l%d:",jmpLabel_count+1);
//	add_str(s);
}
