/**
 * @file 	ir_code_gen.c
 * @date	Created on: 10 Apr 2012
 * @author	Sebastian Boehm, Magnus Bruehl, Philipp Goetze
 * @brief	Functions for intermediate code generation
 *
 */
//TODO: Parser: Function Call Check
//TODO: IR_CODE: Dokumentation
#include "ir_code_gen.h"
#include "symtab.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Constants (Marks/Identifier)
 */
#define MARK1 -2
#define MARK2 1337

/*
 * Structure to store the Code
 */
struct strCode  *code=NULL;
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

/**
* Creates a temporary variable structure for the IR Code (.t0,.t1,[...])
* @return The temporary variable structure
*/
varentry_t *ir_temp_var(){
	temp_reg_count += 1;
	char buffer [5];
	sprintf (buffer, ".t%d", temp_reg_count);
	varentry_t *v;
	v = temp_var(buffer);
	v->arrdim = temp_reg_count;
	return v;
}

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
* Generates the code at current position and stores it into the code variable
* @param operation The operation of this "code snippet", necessary
* @param var0 The pointer to the structure of a first variable (if variable is necessary)[NULLable]
* @param var1 The pointer to the structure of a second variable (if variable is necessary)[NULLable]
* @param var2 The pointer to the structure of a third variable (if variable is necessary)[NULLable]
* @param func The pointer to the structure of the function (if a function is used in this code) [NULLable]
* @param jmpTo For Marking, otherwise = -1 (processed in backpatching)
*/
void gencode(enum code_ops operation, varentry_t *var0, varentry_t *var1, varentry_t *var2, funcentry_t *func, int jmpTo){
	code_count += 1;
	struct strCode *codebuffer = (struct strCode*) realloc (code, code_count * sizeof(struct strCode));
	assert(codebuffer!=NULL);
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
void gencodeass(varentry_t *var0, varentry_t *var1){
	if(var0->tempArrPos>-1)
		gencode(opMEM_ST, (struct varentry *) var0->hh.next,var0->tempArrPos2 , var1 , NULL, -1);
	else
		gencode(opASSIGN, var0, var1, NULL, NULL, -1);
	temp_reg_count = 0;
}

/**
* Prepares the code at current position for Returns and Parameter storing and calls then the gencode(...)
* @param operation The operation of this expression
* @param var0 The pointer to the structure of the affected variable
*/
void gencodeop1(enum code_ops operation, varentry_t *var0){
	if(operation==opRETURN)
		gencode(operation, var0, NULL, NULL, NULL, MARK1);
	else
		gencode(operation, var0, NULL, NULL, NULL, -1);
}

/**
* Prepares the code at current position for expressions with one operand and calls then the gencode(...)
* @param operation The operation of this expression
* @param var1 The pointer to the structure of the affected variable
* @return The pointer to the structure of the variable, which got the altered value of var1
*/
varentry_t *gencodeopexp1(enum code_ops operation, varentry_t *var1){
	varentry_t *v;
	if((struct varentry *) var1->hh.next!=MARK2)
		v = ir_temp_var();
	else
		v=var1;
	gencode(operation, v, var1, NULL, NULL, -1);
	return v;
}

/**
* Prepares the code at current position for expressions with two operands and calls then the gencode(...)
* @param operation The operation of this expression
* @param var0 The pointer to the structure of the first affected variable
* @param var1 The pointer to the structure of the second affected variable
*/
//void gencodeop2(enum code_ops operation, varentry_t *var0, varentry_t *var1){
//	gencode(operation, var0, var1, NULL, NULL, -1);
//}

/**
* Prepares the code at current position for If statements and calls then the gencode(...)
* @param var0 The pointer to the structure of the affected variable (contains if-expression)
*/
void genif(varentry_t *var0){
	gencode(opIF, var0, NULL, NULL, NULL, code_count+2);
}

/**
* Prepares the code at current position for GOTO statements after IF and calls then the gencode(...)
* The GOTO Label will be defined via backpatching, there for the marker(MARK1)
*/
void genifgoto(){
	gencode(opGOTO, NULL, NULL, NULL, NULL, MARK1);
}

/**
* Sets the GOTO operation which have the marker (MARK1) to the now known jump address (for if statements)
* @param shift For skipping code (0 - without Else statement, 1- with Else statement)
*/
void backpatchif(int shift){
	struct strCode  *c;
	for(int i=code_count-1;i>=0;i--){
		c = &code[i];
		if(c->op==opGOTO){
			if(c->jmpTo==MARK1){
				c->jmpTo = code_count + shift;
				break;
			}
		}
	}
}

/**
* Sets the operation which have the marker (MARK1) to the now known jump address (for return statements)
*/
void backpatchreturn(){
	struct strCode  *c;
	for(int i=0;i<code_count;i++){
		c = &code[i];
		if(c->op==opRETURN){
			if(c->jmpTo==MARK1){
				c->jmpTo = code_count - 1;
			}
		}
	}
}

/**
* Prepares the code at current position for While statements and calls then the gencode(...)
* @param var0 The pointer to the structure of the affected variable (contains if-expression)
*/
void genwhile(varentry_t *var0){
	gencode(opIF, var0, NULL, NULL, NULL, code_count+2);
}

/**
* Prepares the code at current position for While Begin and calls then the gencode(...)
*/
void genwhilebegin(){
	gencode(opWHILE_BEGIN, NULL, NULL, NULL, NULL, MARK1);
}

/**
* Prepares the code at current position for While Begin and calls then the gencode(...)
* The GOTO Label will be defined via backpatching, there for the marker(MARK1)
*/
void genwhilegotobegin(){
	gencode(opGOTO, NULL, NULL, NULL, NULL, MARK1);
}

/**
* Sets the operation which have the marker (MARK1) to the now known jump address (for while statements)
*/
void backpatchwhile(){
	struct strCode  *c;
	for(int i=code_count-1;i>=0;i--){
		c = &code[i];
		if(c->op==opGOTO){
			if(c->jmpTo==MARK1){
				c->jmpTo = code_count+1;
				break;
			}
		}
	}
	for(int i=code_count-1;i>=0;i--){
		c = &code[i];
		if(c->op==opWHILE_BEGIN){
			if(c->jmpTo==MARK1){
				gencode(opGOTO, NULL, NULL, NULL, NULL, i);
				c->jmpTo=-1;
				break;
			}
		}
	}
}

/**
* Prepares the code at current position for Do While Begin and calls then the gencode(...)
*/
void gendowhile(){
	gencode(opDO_WHILE_BEGIN, NULL, NULL, NULL, NULL, MARK1);
}

/**
* Checks the code for Do While Begin and set back the jump adresses
* @param var0 The pointer to the structure of the affected variable (for the if-expression at the end of do_while)
*/
void gendowhileend(varentry_t *var0){
	struct strCode  *c;
	int i;
	for(i=code_count-1;i>=0;i--){
		c = &code[i];
		if(c->op==opDO_WHILE_BEGIN){
			if(c->jmpTo==MARK1){
				c->jmpTo=-1;
				break;
			}
		}
	}
	gencode(opIF, var0, NULL, NULL, NULL, i);
}

/**
* Prepares the code at current position for expressions with two operands and calls then the gencode(...)
* @param operation The operation of this expression
* @param var1 The pointer to the structure of the first operand
* @param var2 The pointer to the structure of the second operand
* @return The pointer to the structure of the variable, which got the altered value of var1 and var2
*/
varentry_t *gencodeopexp2(enum code_ops operation, varentry_t *var1, varentry_t *var2){
	varentry_t *v;
	if(((struct varentry *) var1->hh.next==MARK2) && ((struct varentry *) var2->hh.next==MARK2)){
		v = var1;
		temp_reg_count -= 1;
		//printf("temp_reg_count:%d %d.\n", temp_reg_count, (struct varentry *) var1->hh.next);
	}
	else
		v = ir_temp_var();
	gencode(operation, v, var1, var2, NULL, -1);
	return v;
}

/**
* Prepares the code at current position for Arrays and calls then the gencode(...)
* @param var1 The pointer to the structure of the first variable (the Array ID)
* @param var2 The pointer to the structure of the second variable (the array index)
* @return The pointer to the structure of the variable, which gets the altered value of var1 and var2
*/
varentry_t * gencodeloadarr(varentry_t *var1, varentry_t *var2){
	varentry_t *v;
	v = ir_temp_var();
	var1->tempArrPos =	var2->val;
	v->hh.next = var1;
	gencode(opMEM_LD, v, var1, var2, NULL, -1);
	v->tempCodePos = code_count -1 ;
	return v;
}

/**
* Prepares the code at current position for function definitions and calls then the gencode(...)
* @param operation The operation of this statement (should be FuncDef)
* @param var0 The pointer to the structure of the parameter list
* @param func The pointer to the structure of the function
*/
void gencodeopfunc(enum code_ops operation, varentry_t *var0, funcentry_t*func){
	gencode(operation, var0, NULL, NULL, func, -1);
}

/**
* Prepares the code at current position for function calls and calls then the gencode(...)
* @param operation The operation of this statement (should be Call)
* @param var0 The pointer to the structure of the parameter list
* @param func The pointer to the structure of the function
* @param jmpTo The jump address in the IR code
* @return The pointer to the structure of the function call
*/
struct varentry *gencodeopfunccall(enum code_ops operation, struct varentry *var0, struct funcentry *func, int jmpTo){
	varentry_t *v;
	v = ir_temp_var();
	gencode(operation, var0, v, NULL, func, jmpTo);
	return v;
}

/**
* Prints the (for some maybe cryptic) IR code to the console, just for debugging
*/
void debugPrintAllopcodes(){
	struct strCode  *c;
	varentry_t *int_;
	funcentry_t *func_;
	int count=0;
	char tab = '\0';
	for(int i=0;i<code_count;i++){
		c = &code[i];
		if(c->op==opFUNC_DEF_END)
			tab = '\0';
		printf("%cOP #%d: %s", tab, count, enumStrings[c->op]);
		if(c->var0!=NULL){
			int_=c->var0;
			printf(", %s", int_->varname);
		}
		if(c->var1!=NULL){
			int_=c->var1;
			printf(", %s", int_->varname);
		}
		if(c->var2!=NULL){
			int_=c->var2;
			printf(", %s", int_->varname);
		}
		if(c->func!=NULL){
			func_=c->func;
			printf(", FUNC: %s", func_->funcname);
		}
		if(c->jmpTo!=-1) {
			printf(", JMP_TO: %d", c->jmpTo);
		}
		printf("\n");
		count++;
		if(c->op==opFUNC_DEF)
			tab = '\t';
	}
}

/**
* For function call to find goto address
* @param func The pointer to the structure of the function, which shall be called
* @return The Jump Address to function
*/
int opcodeFindFunctionDef(funcentry_t *func){
	struct strCode  *c;
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
int setJmpLabel(int cpos, int jmpLabel){
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
void setCodeToNOP(int pos){
	code[pos].op = opNOP;
}

/**
* Sets the temporary register counter to back to zero, done after every statement
*/
void resetTempCount(){
	temp_reg_count = 0;
}

/**
* Prints the whole symbol table and IR code to the *.ir file
* The ir output is also generated here
*/
void generate_ir_code(){
	struct strCode  *c;
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
		if(c->op==opFUNC_DEF_END || c->op==opPARAM || c->op==opWHILE_BEGIN ||
									c->op==opDO_WHILE_BEGIN || c->op==opNOP)
			tab = '\0';
		if(c->jmpLabel > -1){
			sprintf (s, ".l%d:\n", c->jmpLabel);
			add_str(s);
		}
		sprintf (s,"%c", tab);
		add_str(s);
		switch(c->op){
		case opASSIGN:
			sprintf (s,"%s = %s",c->var0->varname,c->var1->varname);
			add_str(s);
			break;
		case opADD:
			sprintf (s, "%s = %s + %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opSUB:
			sprintf (s, "%s = %s - %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opMUL:
			sprintf (s, "%s = %s * %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opMINUS:
			sprintf (s, "%s = -%s", c->var0->varname,c->var1->varname);
			add_str(s);
			break;
		case opSHIFT_LEFT:
			//Not implemented in parser
			break;
		case  opSHIFT_RIGHT:
			//Not implemented in parser
			break;
		case opLOGICAL_AND:
			sprintf (s, "%s = %s && %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opLOGICAL_OR:
			sprintf (s, "%s = %s || %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opLOGICAL_NOT:
			sprintf (s, "%s = !%s", c->var0->varname,c->var1->varname);
			add_str(s);
			break;
		case opNE:
			sprintf (s, "%s = %s != %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opEQ:
			sprintf (s, "%s = %s == %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opGT:
			sprintf (s, "%s = %s > %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opGTEQ:
			sprintf (s, "%s = %s >= %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opLS:
			sprintf (s, "%s = %s < %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opLSEQ:
			sprintf (s, "%s = %s <= %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opIF:
			jmpLabel_count = jmpLabel_count + 1;
			if(!setJmpLabel(c->jmpTo, jmpLabel_count)){
				jmpLabel_count = jmpLabel_count - 1;
			}
			c->jmpTo = jmpLabel_count;
			sprintf (s, "IF %s GOTO .l%d", c->var0->varname,c->jmpTo);
			add_str(s);
			break;
		case opGOTO:
			jmpLabel_count = jmpLabel_count + 1;
			if(!setJmpLabel(c->jmpTo, jmpLabel_count)){
				jmpLabel_count = jmpLabel_count - 1;
			}
			c->jmpTo = jmpLabel_count;
			sprintf (s, "GOTO .l%d", c->jmpTo);
			add_str(s);
			break;
		case opWHILE_BEGIN:
			//Nothing
			break;
		case opDO_WHILE_BEGIN:
			//Nothing
			break;
		case opRETURN:
			jmpLabel_count = jmpLabel_count + 1;
			if(!setJmpLabel(c->jmpTo, jmpLabel_count)){
				jmpLabel_count = jmpLabel_count - 1;
			}
			c->jmpTo = jmpLabel_count;
			sprintf (s, "RETURN %s GOTO .l%d", c->var0->varname,c->jmpTo);
			add_str(s);
			break;
		case opPARAM:
			parcount++;
		    HASH_ADD_KEYPTR(hh, pars, c->var0->varname, strlen(c->var0->varname), c->var0);
			tab = '\t';
			break;
		case opCALL:
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
		case opMEM_LD:
			sprintf (s, "%s = %s[%s]", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opMEM_ST:
			sprintf (s, "%s[%s] = %s", c->var0->varname,c->var1->varname,c->var2->varname);
			add_str(s);
			break;
		case opADDR:
			sprintf (s, "%s = ADDR(%s)", c->var0->varname,c->var1->varname);
			add_str(s);
			break;
		case opFUNC_DEF:
			if(c->func!=NULL){
				sprintf (s, "%s:", c->func->funcname);
				add_str(s);
			}
			tab = '\t';
			break;
		case opFUNC_DEF_END:
			//Nothing (just CRLF)
			break;
		case opNOP:
			//Nothing
			tab = '\t';
			break;
		}
		if(c->op==opWHILE_BEGIN || c->op==opDO_WHILE_BEGIN)
			tab = '\t';
		if(c->op!=opPARAM && c->op!=opNOP && c->op!=opWHILE_BEGIN && c->op!=opDO_WHILE_BEGIN){
			sprintf (s, "\n");
			add_str(s);
		}
	}
//	sprintf (s, ".l%d:",jmpLabel_count+1);
//	add_str(s);
}
