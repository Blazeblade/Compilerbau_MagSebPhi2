/**
 * @file 	ir_code_gen.h
 * @date	Created on: 10 Apr 2012
 * @author	Sebastian Boehm, Magnus Bruehl, Philipp Goetze
 * @brief	Structures, enumerations and functions (definition) for intermediate code generation
 *		ir_code_gen was created with the help of
 * 		http://foja.dcs.fmph.uniba.sk/kompilatory/docs/compiler.pdf
 * 		And
 * 		Samuel Schneider
 *
 */

#ifndef _DHBWCC_IR_CODE_GEN_H
#define _DHBWCC_IR_CODE_GEN_H

#include <stdio.h>
#include "include/uthash.h"



/**
 * Enumeration for 3-adress code representation, same operators as in scanner.l
 */
enum code_operations
{
	ASSIGN_IR, ADD_IR, SUB_IR, MUL_IR, MINUS_IR, SHIFT_LEFT_IR, SHIFT_RIGHT_IR,
	LOGICAL_AND_IR, LOGICAL_OR_IR, LOGICAL_NOT_IR, NE_IR, EQ_IR, GT_IR, GTEQ_IR,
	LS_IR, LSEQ_IR, IF_IR, GOTO_IR, WHILE_BEGIN_IR, DO_WHILE_BEGIN_IR, RETURN_IR,
	PARAM_IR, CALL_IR, MEM_LD_IR, MEM_ST_IR, ADDR_IR, FUNC_DEF_IR, FUNC_DEF_END_IR, NOP_IR
};

/**
 * Not all have to be used in every opcode
 */
struct code_struct
{
	enum code_operations op;	//Code Operation
	struct varentry *var0;		//First Operand 	[optional]
	struct varentry *var1;		//Second Operand 	[optional]
	struct varentry *var2;		//Third Operand 	[optional]
	struct funcentry *func;		//Function Entry	[optional]
	int jmpLabel;				//Jump Label		[default=-1]
	int jmpTo;					//Jump Code Line	[default=-1]
};

//Code Generations
	void gencode(enum code_operations operation, struct varentry *var0, struct varentry *var1, struct varentry *var2, struct funcentry *func, int jmpTo);
	void gencode_ass(struct varentry *var0, struct varentry *var1);
	struct varentry *gencode_op1exp(enum code_operations operation, struct varentry *var1);
	struct varentry *gencode_op2exp(enum code_operations operation, struct varentry *var1, struct varentry *var2);
	void gencode_op1(enum code_operations operation, struct varentry *var0);
	struct varentry * gencode_load_arr(struct varentry *var1, struct varentry *var2);
	void gencode_opfunc(enum code_operations operation, struct varentry *var0, struct funcentry*func);
	void genif(struct varentry *var0);
	void genif_goto();
	void genwhile(struct varentry *var0);
	void genwhile_begin();
	void genwhile_gotobegin();
	void gendowhile();
	void gendowhile_end(struct varentry *var0);
	struct varentry *gencode_funccall(enum code_operations operation, struct varentry *var0, struct funcentry *func, int jmpTo);
//Backpatching
	void backpatch_if(int shift);
	void backpatch_return();
	void backpatch_while();
//Helper Methods
	struct varentry *ir_temp_var();
	int opcode_find_FuncDef(struct funcentry *func);
	int set_jmpLabel(int cpos, int jmpLabel);
	void set_code_to_NOP(int pos);
	void reset_temp_count();
//Generation of IR File
	void init_ir_code(FILE *file);
	void add_str(const char *str);
	void generate_ir_code();


#endif
