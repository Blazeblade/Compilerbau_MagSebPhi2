/*
 * ir_code_gen.c
 *
 *  Created on: 10.04.2012
 *      Author: s.s.
 */

#include "ir_code_gen.h"
#include "symtab.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct strCode  *code=NULL;

int code_count = 0;
int temp_reg_count = -1;

varentry_t *irtempInt()
{
	temp_reg_count += 1;
	char buffer [5];
	sprintf (buffer, ".t%d", temp_reg_count);

	varentry_t *ptr;
	ptr = tempInt(buffer);
	ptr->arrdim = temp_reg_count;

	return ptr;
}

/* Generates code at current location */
void gencode(enum code_ops operation, varentry_t *int0, varentry_t *int1, varentry_t *int2, funcentry_t *func, int jmpTo)
{
	code_count += 1;
	//malloc because realloc throws a "invalid next size"-error
	struct strCode *codebuffer = malloc(code_count * sizeof(struct strCode));
	//codebuffer = (struct strCode*) realloc (code, code_count * sizeof(struct strCode));
	assert(codebuffer!=NULL);

	code = codebuffer;

	code[code_count-1].op = operation;

	code[code_count-1].int0 = int0;
	code[code_count-1].int1 = int1;
	code[code_count-1].int2 = int2;
	code[code_count-1].func = func;
	code[code_count-1].jmpTo = jmpTo;
	code[code_count-1].jmpLabel = -1;
}

void gencodeass(varentry_t *int0, varentry_t *int1)
{
	if(int0->tempArrPos>-1)
	{
		printf("t_isArray:%d.\n", int1->arrdim);
		//gencode(opMEM_ST, int0->hh.next, find_var("int") , int1 /*=int2*/, NULL, -1);
		gencode(opMEM_ST, int0->hh.next,int0->tempArrPos2 , int1 /*=int2*/, NULL, -1);

	}
	else
	{
		gencode(opASSIGN, int0, int1, NULL, NULL, -1);
		printf("Code offset: %d\n", code_count);
		printf("IR: ASSIGN %s = %s\n", code[code_count-1].int0->varname, code[code_count-1].int1->varname);
	}
	printf("t_count:%d.\n", temp_reg_count);
	temp_reg_count = 0;
}

void gencodeop1(enum code_ops operation, varentry_t *int0)
{
	if(operation==opRETURN)
	{
		gencode(operation, int0, NULL, NULL, NULL, -137);
	}
	else
	{
		gencode(operation, int0, NULL, NULL, NULL, -1);
	}
}

varentry_t *gencodeopexp1(enum code_ops operation, varentry_t *int1)
{
	varentry_t *ptr;
	if(int1->hh.next!=137)
	{
		ptr = irtempInt();
	}
	else
	{
		ptr=int1;
	}


	gencode(operation, ptr, int1, NULL, NULL, -1);
	printf("IR: %d %s = op %s\n", operation, ptr->varname, int1->varname);

	return ptr;
}

void gencodeop2(enum code_ops operation, varentry_t *int0, varentry_t *int1)
{
	gencode(operation, int0, int1, NULL, NULL, -1);
}

void genif(varentry_t *int0)
{
	gencode(opIF, int0, NULL, NULL, NULL, getopcodeCount()+2);
}

void genifgoto()
{
	gencode(opGOTO, NULL, NULL, NULL, NULL, -137);
}

void backpatchif(int shift)
{
	struct strCode  *c;
	for(int i=code_count-1;i>=0;i--)
	{
		c = &code[i];

		if(c->op==opGOTO)
		{
			if(c->jmpTo==-137)
			{
				c->jmpTo = getopcodeCount() + shift;
				break;
			}
		}
	}
}

void backpatchreturn()
{
	struct strCode  *c;

	for(int i=0;i<code_count;i++)
	{
		c = &code[i];

		if(c->op==opRETURN)
		{
			if(c->jmpTo==-137)
			{
				c->jmpTo = getopcodeCount() - 1;
			}
		}
	}
}

void genwhile(varentry_t *int0)
{
	gencode(opIF, int0, NULL, NULL, NULL, getopcodeCount()+2);
}

void genwhilebegin()
{
	gencode(opWHILE_BEGIN, NULL, NULL, NULL, NULL, -137);
}

void genwhilegotobegin()
{
	gencode(opGOTO, NULL, NULL, NULL, NULL, -137);
}

void backpatchwhile()
{
	struct strCode  *c;
	for(int i=code_count-1;i>=0;i--)
	{
		c = &code[i];

		if(c->op==opGOTO)
		{
			if(c->jmpTo==-137)
			{
				c->jmpTo = getopcodeCount()+1;
				break;
			}
		}
	}
	for(int i=code_count-1;i>=0;i--)
	{
		c = &code[i];

		if(c->op==opWHILE_BEGIN)
		{
			if(c->jmpTo==-137)
			{
				gencode(opGOTO, NULL, NULL, NULL, NULL, i);
				c->jmpTo=-1;
				break;
			}
		}
	}
}

void gendowhile()
{
	gencode(opDO_WHILE_BEGIN, NULL, NULL, NULL, NULL, -137);
}

void gendowhileend(varentry_t *int0)
{
	struct strCode  *c;
	int i;
	for(i=code_count-1;i>=0;i--)
	{
		c = &code[i];

		if(c->op==opDO_WHILE_BEGIN)
		{
			if(c->jmpTo==-137)
			{
				c->jmpTo=-1;
				break;
			}
		}
	}
	gencode(opIF, int0, NULL, NULL, NULL, i);
}

varentry_t *gencodeopexp2(enum code_ops operation, varentry_t *int1, varentry_t *int2)
{
	varentry_t *ptr;
	if((int1->hh.next==137) && (int2->hh.next==137))
	{
		ptr = int1;
		temp_reg_count -= 1;
		printf("\n\n\n\n\n\ntemp_reg_count:%d %d.\n", temp_reg_count, int1->hh.next);
	}
	else
	{
		ptr = irtempInt();
	}

	gencode(operation, ptr, int1, int2, NULL, -1);
	printf("IR: %d %s = %s op %s\n", operation, ptr->varname, int1->varname, int2->varname);
	return ptr;
}

varentry_t * gencodeloadarr(varentry_t *int1, varentry_t *int2)
{
	varentry_t *ptr;
	ptr = irtempInt();

	int1->tempArrPos =	int2->val;
	ptr->hh.next = int1;

	gencode(opMEM_LD, ptr, int1, int2, NULL, -1);

	ptr->tempCodePos = code_count -1 ;

	return ptr;
}

void gencodeopfunc(enum code_ops operation, varentry_t *int0, funcentry_t*func, int jmpTo)
{
	gencode(operation, int0, NULL, NULL, func, jmpTo);
}

int gencodeopfunccall(enum code_ops operation, varentry_t *int0, funcentry_t*func, int jmpTo)
{
	varentry_t *ptr;
	ptr = irtempInt();

	gencode(operation, int0, ptr, NULL, func, jmpTo);

	return ptr;
}

void printcode()
{
	int i = 0;
	while (i < code_count) {
		i++;
	}
}

void debugPrintAllopcodes()
{
	struct strCode  *c;
	varentry_t *int_;
	varentry_t *func_;
	int count=0;
	char tab = '\0';

	for(int i=0;i<code_count;i++)
	{
		c = &code[i];

		if(c->op==opFUNC_DEF_END) tab = '\0';

		printf("%cOP #%d: %s", tab, count, enumStrings[c->op]);
		if(c->int0!=NULL) {int_=c->int0;printf(", INT0: %s", int_->varname);}
		if(c->int1!=NULL) {int_=c->int1;printf(", INT1 %s", int_->varname);}
		if(c->int2!=NULL) {int_=c->int2;printf(", INT2: %s", int_->varname);}

		if(c->func!=NULL) {func_=c->func;printf(", FUNC: %s", func_->varname);}

		if(c->jmpTo!=-1) {printf(", JMP_TO: %d", c->jmpTo);}

		printf("\n");
		count++;

		if(c->op==opFUNC_DEF) tab = '\t';
	}
}

struct strCode  *getopcodeArray()
{
	return code;
}

int getopcodeCount()
{
	return code_count;
}

int opcodeFindFunctionDef(funcentry_t*func)
{
	struct strCode  *c;
	for(int i=0;i<code_count;i++)
	{
		c = &code[i];
		if(c->func==func)
		{
			return i;
		}
	}
	return NULL;
}

int setJmpLabel(int cpos, int jmpLabel)
{
	if(code[cpos].jmpLabel<0)
	{
		if((cpos>0) && (cpos<code_count))
		{
			code[cpos].jmpLabel = jmpLabel;
			return 1;
		}
	}
	return 0;
}

void setCodeToNOP(int pos)
{
	code[pos].op = opNOP;
}

void resetTempCount()
{
	temp_reg_count = 0;
}
