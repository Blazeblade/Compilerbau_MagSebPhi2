/* 
 * parser.y - Parser utility for the DHBW compiler
 */
 
 
 
%{
#include "include/uthash.h";
#include "symtab.h";
#include "ir_code_gen.h";
#include <assert.h>


#define NOT_DEFINED -1
#define GLOBAL 0
#define LOCAL 1
#define PARAMETER 2


%}

%union {
  int 				num;
  char*				id;
  struct varentry 	*var;
  struct funcentry 	*func;
  struct symentry	*sym;
  struct funccallparlist *plist;
}
 
%debug
%locations
%start program

/*
 * One shift/reduce conflict is expected for the "dangling-else" problem. This
 * conflict however is solved by the default behavior of bison for shift/reduce 
 * conflicts (shift action). The default behavior of bison corresponds to what
 * we want bison to do: SHIFT if the lookahead is 'ELSE' in order to bind the 'ELSE' to
 * the last open if-clause. 
 */
%expect 1

%token DO WHILE
%token IF ELSE
%token <id>INT <id>VOID
%token RETURN
%token COLON COMMA SEMICOLON
%token BRACE_OPEN BRACE_CLOSE

%token <id>ID
%token <num>NUM

%right ASSIGN 
%left  LOGICAL_OR
%left  LOGICAL_AND
%left  EQ NE     
%left  LS LSEQ GTEQ GT 
%left  SHIFT_LEFT SHIFT_RIGHT
%left  PLUS MINUS     
%left  MUL
%right LOGICAL_NOT UNARY_MINUS UNARY_PLUS
%left  BRACKET_OPEN BRACKET_CLOSE PARA_OPEN PARA_CLOSE

%type <plist> 	function_call_parameters
%type <id> 		type
%type <func> 	function_definition
%type <func> 	function_parameter_list
%type <func> 	function_declaration
%type <func> 	function_call
%type <var> 	function_parameter
%type <sym> 	identifier_declaration
%type <var> 	expression
%type <var> 	primary

%type <var>		variable_declaration

%%

program
     : program_element_list{
		printf("\n\n----------DEBUG printing all functions and variables----------:\n");
		printf("<<----------DEBUG Functions---------->>:\n");
		print_funcs();
		printf("<<----------DEBUG Variables---------->>:\n");
		print_vars();
		printf("<<----------DEBUG IR---------->>:\n");
		debugPrintAllopcodes();
		printf("<<----------DEBUG END---------->>:\n\n\n");
		}
     ;

program_element_list
     : program_element_list program_element 
     | program_element 
     ;

program_element
     : variable_declaration SEMICOLON
     | function_declaration SEMICOLON
     | function_definition
     | SEMICOLON
     ;
									
type
     : INT	{$$=integer;}
     | VOID {$$=voidtype;}
     ;

variable_declaration
     : variable_declaration COMMA identifier_declaration
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			$$->varname=$3->name;
			if($3->arrdim>=0){
					$$->vartype=1;
					add_var($$->varname, $$->vartype,$3->arrdim,GLOBAL,NULL);
				}
				else {
					$$->vartype=0;
					add_var($$->varname, $$->vartype,NOT_DEFINED,GLOBAL,NULL);
				}
			//printf("DEBUG --- Variable was added to Symboltable: %s\n",$$->varname);
		}
     | type identifier_declaration 
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			if($1==voidtype) {
				fprintf(stderr,"Variables can not be of type void (%s).\n",$2->name);
			} 
			else {
				$$->varname=$2->name;
				if($2->arrdim>=0){
					$$->vartype=1;
					add_var($$->varname, $$->vartype,$2->arrdim,GLOBAL,NULL);
				}
				else {
					$$->vartype=0;
					add_var($$->varname, $$->vartype,NOT_DEFINED,GLOBAL,NULL);
				}
				//printf("DEBUG --- Variable was added to Symboltable: %s\n",$$->varname);
				//printf("DEBUG --- Symboltable: ");
				//print_vars();
			}
		}
     ;

identifier_declaration
     : ID BRACKET_OPEN NUM BRACKET_CLOSE
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			if(find_sym($1)){
				$$=find_sym($1);
				fprintf(stderr,"This Symbol was already defined.(%s)\n",$$->name);
			}	
			else{
				$$->name=$1;
				$$->arrdim= $3;
				//printf("DEBUG --- We have recognised a Symbol: %s\n",$1);
			}
		}   
     | ID 
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			if(find_sym($1)){
				$$=find_sym($1);
				fprintf(stderr,"This Symbol was already defined.(%s)\n",$$->name);
			}	
			else{
				$$->name=$1;
				$$->arrdim=NOT_DEFINED;
				//printf("DEBUG --- We have recognised a Symbol: %s\n",$1);
			}
		}   
     ;

function_definition		//TODO: stmt_list
     : type ID PARA_OPEN PARA_CLOSE BRACE_OPEN
			{
			$<func>$=malloc(sizeof(*$<func>$));
			assert($<func>$!=NULL);
			$<func>$->funcname=$2;
			$<func>$->returntype=(int)$1;
			$<func>$->dim=0;
			$<func>$->arrdim=NOT_DEFINED;
			add_func($<func>$->funcname, $<func>$->returntype,$<func>$->dim,$<func>$->arrdim,NULL);
			gencodeopfunc(opFUNC_DEF, NULL, find_func($2), -1);

		}
		 stmt_list BRACE_CLOSE
		
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE BRACE_OPEN
     	{	
			$<func>$=find_func("temp1");
			$<func>$->dim=count_pars($<func>$->funcname);
			$<func>$->funcname=$2;
			$<func>$->returntype=(int)$1;
			$<func>$->arrdim=NOT_DEFINED;
			add_func($<func>$->funcname, $<func>$->returntype,$<func>$->dim,$<func>$->arrdim,$<func>$->var);
			delete_func($<func>$);
			//$$=find_func("temp1");
			//$$->var=NULL;
			gencodeopfunc(opFUNC_DEF, NULL, find_func($2), -1);
			
		}
		 stmt_list BRACE_CLOSE
     ;

function_declaration 
     : type ID PARA_OPEN PARA_CLOSE
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			$$->funcname=$2;
			$$->returntype=(int)$1;
			$$->dim=0;
			$$->arrdim=NOT_DEFINED;
			add_func($$->funcname, $$->returntype,$$->dim,$$->arrdim,NULL);
			//printf("DEBUG --- Function was added to Symboltable: %s\n",$$->funcname);
			//printf("DEBUG --- Symboltable: ");
			//print_funcs();
		}
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE 
		{
			$$=find_func("temp1");
			$$->dim=count_pars($$->funcname);
			$$->funcname=$2;
			$$->returntype=(int)$1;
			$$->arrdim=NOT_DEFINED;
			add_func($$->funcname, $$->returntype,$$->dim,$$->arrdim,$$->var);
			delete_func($$);				//Deletes the temp function
			//$$=find_func("temp1");
			//$$->var=NULL;
			//printf("DEBUG --- Function was added to Symboltable: %s\n",$$->funcname);
			//printf("DEBUG --- Symboltable: ");
			//print_funcs();			
		}
     ;

function_parameter_list
     : function_parameter	
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			if(!find_func("temp1"))
			{
				add_func("temp1", 0,0,NOT_DEFINED,NULL);
				$$=find_func("temp1");
				add_funcpar("temp1",$1->varname, $1->vartype, $1->arrdim);
				//add_var($1->varname, $1->vartype, $1->arrdim,1,0);
			} 
			else 
			{	
				$$=find_func("temp1");
				add_funcpar("temp1",$1->varname, $1->vartype, $1->arrdim);
				//add_var($1->varname, $1->vartype, $1->arrdim,1,0);
				
			}
		}
     | function_parameter_list COMMA function_parameter
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			if(!find_func("temp1"))
			{
				add_func("temp1", 0,0,NOT_DEFINED,NULL);
				$$=find_func("temp1");
				add_funcpar("temp1",$3->varname, $3->vartype, $3->arrdim);
				//add_var($3->varname, $3->vartype, $3->arrdim,1,0);
			} 
			else 
			{
				$$=find_func("temp1");
				add_funcpar("temp1",$3->varname, $3->vartype, $3->arrdim);
				//add_var($3->varname, $3->vartype, $3->arrdim,1,0);
			}
		}
     ;
	
function_parameter
     : type identifier_declaration	
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			$$->varname = $2->name; 
			if($1==voidtype) { 
				fprintf(stderr,"Function parameters can not be of type void.\n"); 
			} 
			else {
				if($2->arrdim>=0){
						$$->vartype=1;
						$$->arrdim=$2->arrdim;
						//add_funcpar(funcname, $$->name, $$->type, $2->arrdim);
					}
				else {
						$$->vartype=0;
						$$->arrdim=NOT_DEFINED;
						//add_var($$->varname, $$->vartype,-1);
					}
				}
			//printf("DEBUG --- Symboltable: ");
			//print_all(); 
		}
     ;
									
stmt_list
     : /* empty: epsilon */
     | stmt_list stmt
     ;

stmt
     : stmt_block
     | variable_declaration SEMICOLON	{resetTempCount();}
     | expression SEMICOLON			{resetTempCount();}
     | stmt_conditional				{resetTempCount();}
     | stmt_loop						{resetTempCount();}
     | RETURN expression SEMICOLON		{
									if($2->scope!=NULL)
									{
										if($2->vartype==2)
										{
											printf("ERROR: Function was declarad as VOID. It can not return a value. Either use \"RETURN;\" or use type int for the func.\n");
										}
									}
									gencodeop1(opRETURN, $2);
									{resetTempCount();}
								}
     | RETURN SEMICOLON				{gencodeop1(opRETURN, NULL);{resetTempCount();}}
     | SEMICOLON {resetTempCount();}
     ;


stmt_block
     : BRACE_OPEN stmt_list BRACE_CLOSE
     ;
	
stmt_conditional
     : IF PARA_OPEN expression {genif($3);genifgoto();} PARA_CLOSE stmt_conditional_r //stmt
     //| IF PARA_OPEN expression {genif($3);genifgoto();} PARA_CLOSE stmt ELSE stmt	//{genif($3);genifgoto();}
     ;
     
stmt_conditional_r
     : stmt {backpatchif(0);}
     | stmt ELSE {backpatchif(1);genifgoto();} stmt {backpatchif(0);}
     ;
									
stmt_loop
     : WHILE {genwhilebegin();} PARA_OPEN expression PARA_CLOSE {genwhile($4);genwhilegotobegin();} stmt {backpatchwhile();}
     | DO {gendowhile();} stmt WHILE PARA_OPEN expression PARA_CLOSE SEMICOLON {gendowhileend($6);}
     ;
									
expression								// 0 = "false", nonzero = "true"
     : expression ASSIGN expression				{$$ = $3;gencodeass($1, $3);if($1->tempCodePos>-1) {setCodeToNOP($1->tempCodePos);}}	//WARNING: Ambigious! You dont know if you have to assign to/load from an array or if it is an normal int at this point. check this when generating final code
     | expression LOGICAL_OR expression			{$$ = gencodeopexp2(opLOGICAL_OR, $1, $3);}
     | expression LOGICAL_AND expression		{$$ = gencodeopexp2(opLOGICAL_AND, $1, $3);}
     | LOGICAL_NOT expression					{$$ = gencodeopexp1(opLOGICAL_NOT, $2);}
     | expression EQ expression					{$$ = gencodeopexp2(opEQ, $1, $3);}
     | expression NE expression					{$$ = gencodeopexp2(opNE, $1, $3);}
     | expression LS expression 					{$$ = gencodeopexp2(opLS, $1, $3);}
     | expression LSEQ expression 				{	//$$ = $1 <= $2 -> $$ = $1 < $2 || $1 == $2;
											struct varentry *t0;struct varentry *t1;
											t0 = gencodeopexp2(opLS, $1, $3);
											t1 = gencodeopexp2(opEQ, $1, $3);
											$$ = gencodeopexp2(opLOGICAL_OR, t0, t1);
											//$$ = gencodeopexp2(opLSEQ, $1, $3);
										}
     | expression GTEQ expression 				{	//$$ = $1 >= $2 -> $$ = $1 > $2 || $1 == $2;
											struct varentry *t0;struct varentry *t1;
											t0 = gencodeopexp2(opGT, $1, $3);
											t1 = gencodeopexp2(opEQ, $1, $3);
											$$ = gencodeopexp2(opLOGICAL_OR, t0, t1);
											//$$ = gencodeopexp2(opGTEQ, $1, $3);
										}
     | expression GT expression					{$$ = gencodeopexp2(opGT, $1, $3);}
     | expression PLUS expression				{$$ = gencodeopexp2(opADD, $1, $3);}
     | expression MINUS expression				{$$ = gencodeopexp2(opSUB, $1, $3);}
     | expression MUL expression				{$$ = gencodeopexp2(opMUL, $1, $3);}
     | MINUS expression %prec UNARY_MINUS		{$$ = gencodeopexp1(opMINUS, $2);}
     | ID BRACKET_OPEN primary BRACKET_CLOSE	{
		if(!find_var($1))
			$$ = gencodeloadarr(find_funcpar2($1), $3);
		else
			$$ = gencodeloadarr(find_var($1), $3);
		$$->tempArrPos=$3->val;
		$$->tempArrPos2=$3;
		}
     | PARA_OPEN expression PARA_CLOSE			{$$ = $2}
     | function_call							{$$ = $1;/*$$ = irtempInt();*//*TODO: Check whether v0 or v1 is needed as a temp register. for e.g. i = f() + g() -> i = v0 + v1*/}
     | primary									{$$ = $1}
     ;


primary
     : NUM {add_var("int",0, NOT_DEFINED,GLOBAL, $1);$$ = find_var("int");}
     | ID {	
			if(find_var($1)) {
			$$ = find_var($1);
		} else {
			//TODO: It seems that global variables are not recognised, check this!
			fprintf(stderr,"ERROR! The variable %s was not declared. Line: %d Column: %d \n", $1, yylloc.first_line,yylloc.first_column);
			//We assume the variable should have been declared. so we declare it for the user...
			add_var ($1, 0,NOT_DEFINED, GLOBAL,0);
			$$= find_var($1);
			//yyerror("syntax error");
		}
	  }

function_call
      : ID PARA_OPEN PARA_CLOSE
		{
			funcentry_t *f;
			printf("DEBUG --- Function call regocnised[%s()].\n",$1);
			if(find_func($1)){
				f = find_func($1);
			}
			else{
				fprintf(stderr,"ERROR! Function was not declared before the call!\n");
			}
			//$$ = gencodeopfunccall(opCALL, putInt ("int", 0, 0), sFunc, opcodeFindFunctionDef(sFunc));

		}
      | ID PARA_OPEN function_call_parameters PARA_CLOSE
      	{
			funcentry_t *f;
			printf("DEBUG --- Parameterise Function call regocnised[%s()].\n",$1);
			if(find_func($1)){
				f = find_func($1);
				if(check_funccallpar(f, $3)){
					printf("Functional Call Param Check OK!\n");
				}
				else{
					fprintf(stderr,"ERROR: Functional Call Param Check FAILED![%s(%s)]\n",f->funcname,$3->var);
				}
			}
			else{
				fprintf(stderr,"ERROR! Function was not declared before the call!\n");
			}
			//$$ = gencodeopfunccall(opCALL, putInt ("int", 0, $3->count), f, opcodeFindFunctionDef(f));
		}
      ;

function_call_parameters
     : function_call_parameters COMMA expression	
		{
			$$->count += 1;
			gencodeop1(opPARAM, $3);
		}
     | expression
		{
			$$ = createParamList($1);
			gencodeop1(opPARAM, $1);
		}
     ;

%%

void yyerror (const char *msg)
{
  printf("ERROR: %s\n", msg);
}
