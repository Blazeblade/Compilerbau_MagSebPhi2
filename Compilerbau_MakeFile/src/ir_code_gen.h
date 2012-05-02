/*
 * ir_code_gen.h
 *
 *  Created on: 10.04.2012
 *      Author: magnus
 */

#ifndef _DHBWCC_IR_CODE_GEN_H
#define _DHBWCC_IR_CODE_GEN_H
/**	ir_code_gen is based on http://foja.dcs.fmph.uniba.sk/kompilatory/docs/compiler.pdf
***
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
	struct varentry *int0;
	struct varentry *int1;
	struct varentry *int2;
	struct funcentry *func;
	int jmpLabel;
	int jmpTo;
};

void gencodeass(struct varentry *int0, struct varentry *int1);
struct varentry *gencodeopexp1(enum code_ops operation, struct varentry *int1);
struct varentry *gencodeopexp2(enum code_ops operation, struct varentry *int1, struct varentry *int2);
struct varentry * gencodeloadarr(struct varentry *int1, struct varentry *int2);
void gencodeopfunc(enum code_ops operation, struct varentry *int0, struct funcentry *func, int jmpTo);
void gencodeop1(enum code_ops operation, struct varentry *int0);
void gencodeop2(enum code_ops operation, struct varentry *int0, struct varentry *int1);
int opcodeFindFunctionDef(struct funcentry *func);
void genif(struct varentry *int0);
void genifgoto();
void backpatchif(int shift);
void genwhile(struct varentry *int0);
void genwhilebegin();
void genwhilegotobegin();
void backpatchwhile();
void gendowhile();
void gendowhileend(struct varentry *int0);
int setJmpLabel(int cpos, int jmpLabel);
void setCodeToNOP(int pos);
int gencodeopfunccall(enum code_ops operation, struct varentry *int0, struct funcentry *func, int jmpTo);
void resetTempCount();
void backpatchreturn();

void printcode();
void debugPrintAllopcodes();

struct strCode *getopcodeArray();
int getopcodeCount();

#endif
