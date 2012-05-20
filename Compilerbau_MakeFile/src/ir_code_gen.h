/**
 * @file 	ir_code_gen.h
 * @date	Created on: 10 Apr 2012
 * @author	Sebastian Boehm, Magnus Bruehl, Philipp Goetze
 * @brief	Structures, enumerations and functions (definition) for intermediate code generation
 *
 */

#ifndef _DHBWCC_IR_CODE_GEN_H
#define _DHBWCC_IR_CODE_GEN_H

#include <stdio.h>
#include "include/uthash.h"

/**	ir_code_gen was created with the help of
 * 		http://foja.dcs.fmph.uniba.sk/kompilatory/docs/compiler.pdf
 * 		And
 * 		Samuel Schneider
**/

//enum for 3-adress code representation, same operators as in scanner.l
enum code_ops
{
	opASSIGN, opADD, opSUB, opMUL, opMINUS, opSHIFT_LEFT, opSHIFT_RIGHT,

	opLOGICAL_AND, opLOGICAL_OR, opLOGICAL_NOT, opNE, opEQ, opGT, opGTEQ, opLS, opLSEQ,

	opIF, opGOTO, opWHILE_BEGIN, opDO_WHILE_BEGIN,

	opRETURN, opPARAM, opCALL, opMEM_LD, opMEM_ST, opADDR, opFUNC_DEF, opFUNC_DEF_END, opNOP
};

static char* enumStrings[] = {
							"ASSIGN", "ADD", "SUB", "MUL", "MINUS", "SHIFT_LEFT", "SHIFT_RIGHT",

							"LOGICAL_AND", "LOGICAL_OR", "LOGICAL_NOT", "NE", "EQ", "GT", "GTEQ", "LS", "LSEQ",

							"IF", "GOTO", "WHILE_BEGIN", "DO_WHILE_BEGIN",

							"RETURN", "PARAM", "CALL", "MEM_LD", "MEM_ST", "ADDR", "FUNC_DEF", "FUNC_DEF_END", "NOP"

};

/**
 * Not all have to be used in every opcode
 */
struct strCode
{
	enum code_ops op;
	struct varentry *var0;
	struct varentry *var1;
	struct varentry *var2;
	struct funcentry *func;
	int jmpLabel;
	int jmpTo;
};

struct varentry *ir_temp_var();
void init_ir_code(FILE *file);
void add_str(const char *str);
void gencode(enum code_ops operation, struct varentry *var0, struct varentry *var1, struct varentry *var2, struct funcentry *func, int jmpTo);
void gencode_ass(struct varentry *var0, struct varentry *var1);
void gencode_op1(enum code_ops operation, struct varentry *var0);
struct varentry *gencode_op1exp(enum code_ops operation, struct varentry *var1);
void genif(struct varentry *var0);
void genif_goto();
void backpatch_if(int shift);
void backpatch_return();
void genwhile(struct varentry *var0);
void genwhile_begin();
void genwhile_gotobegin();
void backpatch_while();
void gendowhile();
void gendowhile_end(struct varentry *var0);
struct varentry *gencode_op2exp(enum code_ops operation, struct varentry *var1, struct varentry *var2);
struct varentry * gencode_load_arr(struct varentry *var1, struct varentry *var2);
void gencode_opfunc(enum code_ops operation, struct varentry *var0, struct funcentry*func);
struct varentry *gencode_funccall(enum code_ops operation, struct varentry *var0, struct funcentry *func, int jmpTo);
void print_all_opcodes();
int opcode_find_FuncDef(struct funcentry *func);
int set_jmpLabel(int cpos, int jmpLabel);
void set_code_to_NOP(int pos);
void reset_temp_count();
void generate_ir_code();


#endif
