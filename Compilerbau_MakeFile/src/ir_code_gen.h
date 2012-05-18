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
void gencodeass(struct varentry *var0, struct varentry *var1);
void gencodeop1(enum code_ops operation, struct varentry *var0);
struct varentry *gencodeopexp1(enum code_ops operation, struct varentry *var1);
//void gencodeop2(enum code_ops operation, struct varentry *var0, struct varentry *var1);
void genif(struct varentry *var0);
void genifgoto();
void backpatchif(int shift);
void backpatchreturn();
void genwhile(struct varentry *var0);
void genwhilebegin();
void genwhilegotobegin();
void backpatchwhile();
void gendowhile();
void gendowhileend(struct varentry *var0);
struct varentry *gencodeopexp2(enum code_ops operation, struct varentry *var1, struct varentry *var2);
struct varentry * gencodeloadarr(struct varentry *var1, struct varentry *var2);
void gencodeopfunc(enum code_ops operation, struct varentry *var0, struct funcentry*func);
struct varentry *gencodeopfunccall(enum code_ops operation, struct varentry *var0, struct funcentry *func, int jmpTo);
void debugPrintAllopcodes();
int opcodeFindFunctionDef(struct funcentry *func);
int setJmpLabel(int cpos, int jmpLabel);
void setCodeToNOP(int pos);
void resetTempCount();
void generate_ir_code();


#endif
