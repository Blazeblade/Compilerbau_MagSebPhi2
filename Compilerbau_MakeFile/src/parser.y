/* 
 * parser.y - Parser utility for the DHBW compiler
 */
 
 
 
%{
#include "include/uthash.h";
#include "symtab.h";
#include "ir_code_gen.h";
#include <assert.h>
#include <stdlib.h>


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
 // struct symentry	*sym;
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
%type <var> 	identifier_declaration
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
			$$->varname=$3->varname;
			if($3->arrdim>=0){
					$$->vartype=1;
					add_var($$->varname, $$->vartype,$3->arrdim,NULL);
				}
				else {
					$$->vartype=0;
					add_var($$->varname, $$->vartype,NOT_DEFINED,NULL);
				}
			//printf("DEBUG --- Variable was added to Symboltable: %s\n",$$->varname);
		}
     | type identifier_declaration 
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			if($1==voidtype) {
				fprintf(stderr,"Variables can not be of type void (%s). Line: %d Column: %d \n",$2->varname, @1.first_line,@1.first_column);
			} 
			else {
				$$->varname=$2->varname;
				if($2->arrdim>=0){
					$$->vartype=1;
					add_var($$->varname, $$->vartype,$2->arrdim,NULL);
				}
				else {
					$$->vartype=0;
					add_var($$->varname, $$->vartype,NOT_DEFINED,NULL);
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
			if(find_var($1)){
				$$=find_var($1);
				if($$->scope==get_func_scope())
					fprintf(stderr,"This Symbol was already defined (%s), Line: %d Column: %d \n",$$->varname, @1.first_line,@1.first_column);
				else{
					$$->varname=$1;
					$$->vartype=1;
					$$->arrdim= $3;
				}
			}	
			else{
				$$->varname=$1;
				$$->vartype=1;
				$$->arrdim= $3;
			}
		}   
     | ID 
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			if(find_var($1)){
				$$=find_var($1);
				if($$->scope==get_func_scope())
					fprintf(stderr,"This Symbol was already defined (%s), Line: %d Column: %d \n",$$->varname, @1.first_line,@1.first_column);
				else{
					$$->varname=$1;
					$$->arrdim=NOT_DEFINED;
				}
			}	
			else{
				$$->varname=$1;
				$$->arrdim=NOT_DEFINED;

			}
		}   
     ;

function_definition
     : type ID PARA_OPEN PARA_CLOSE
			{
			if(find_func($2)){
				if(is_func_proto($2)){
					if($1!=find_func($2)->returntype){	
						fprintf(stderr,"Types mismatch from function %s's declaration. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
					}
					set_func_to_decl($2);
					set_func_scope(find_func($2));
				}
				else{	
					fprintf(stderr,"A function definition with the same name (%s) already exists. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
				}
			}
			else{										
				$<func>$=malloc(sizeof(*$<func>$));
				assert($<func>$!=NULL);
				$<func>$->funcname=$2;
				$<func>$->returntype=(int)$1;
				$<func>$->dim=0;
				add_func($<func>$->funcname, $<func>$->returntype,$<func>$->dim,NULL);
				set_func_scope(find_func($2));
				}
			gencodeopfunc(opFUNC_DEF, NULL, find_func($2));
		}
		 BRACE_OPEN stmt_list BRACE_CLOSE {gencodeopfunc(opFUNC_DEF_END, NULL, find_func($2));set_func_scope(NULL);backpatchreturn();}
		
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE
     	{	
     		if(find_func($2)){
				if(is_func_proto($2)){
					if(!check_funccallpar(find_func($2), $4)){
						fprintf(stderr,"Function-Parameter definition does not match the declaration of function %s. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
					}
					if($1!=find_func($2)->returntype){
						fprintf(stderr,"Type mismatch from function %s's declaration. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
					}
					if(strcmp ($4->funcname,"temp1")==0){
						delete_func (find_func("temp1"));
						set_func_to_decl ($2);
						set_func_scope(find_func($2));
						gencodeopfunc(opFUNC_DEF, $4, find_func($2));
					}
					else{
						printf("INTERNAL ERROR: Function has not the expected TEMP_NAME!\n");
					}
				}
				else{
					fprintf(stderr,"A function definition with the same name (%s) already exists. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
				}
			}
			else{
				if(strcmp ($4->funcname,"temp1") == 0){
					$<func>$=find_func("temp1");
					$<func>$->dim=count_pars($<func>$->funcname);
					$<func>$->funcname=$2;
					$<func>$->returntype=(int)$1;
					add_func($<func>$->funcname, $<func>$->returntype,$<func>$->dim,$<func>$->var);
					delete_func($<func>$);
					gencodeopfunc(opFUNC_DEF, $4, find_func($2));
				}
				else{
					printf("INTERNAL ERROR: Function has not the expected TEMP_NAME!\n");
				}
			}			
		}
		 BRACE_OPEN stmt_list BRACE_CLOSE{gencodeopfunc(opFUNC_DEF_END, NULL, find_func($2));set_func_scope(NULL);backpatchreturn();}
     ;

function_declaration 
     : type ID PARA_OPEN PARA_CLOSE
		{
			if(find_func($2)){
				fprintf(stderr,"A function definition with the same name (%s) already exists. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
				set_func_to_proto (find_func($2));
				set_scope_for_pars (find_func($2));
			}
			else{
				$$=malloc(sizeof(*$$));
				assert($$!=NULL);
				$$->funcname=$2;
				$$->returntype=(int)$1;
				$$->dim=0;
				add_func($$->funcname, $$->returntype,$$->dim,NULL);
				set_func_to_proto($$);
				set_scope_for_pars ($$);
			}
			set_func_scope(NULL);
		}								
														
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE 
     	{
			if(find_func($2)) {
				fprintf(stderr,"A function definition with the same name (%s) already exists. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
				delete_func ("temp1");
				set_func_to_proto(find_func($2));
				set_scope_for_pars (find_func($2));
			}
			else{
				$$=find_func("temp1");
				$$->dim=count_pars($$->funcname);
				$$->funcname=$2;
				$$->returntype=(int)$1;
				add_func($$->funcname, $$->returntype,$$->dim,$$->var);
				delete_func($$);				//Deletes the temp function	
				set_func_to_proto(find_func($2));
				set_scope_for_pars (find_func($2));															
			}
			set_func_scope(NULL);
		}
     ;

function_parameter_list
     : function_parameter
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			if(!find_func("temp1"))	{
				add_func("temp1", 0,0,NULL);
				$$=find_func("temp1");
				add_funcpar("temp1",$1->varname, $1->vartype, $1->arrdim);
				$1->scope=$$;
			} 
			else{	
				$$=find_func("temp1");
				add_funcpar("temp1",$1->varname, $1->vartype, $1->arrdim);
				$1->scope=$$;
			}
		}
     | function_parameter_list COMMA function_parameter
		{
			$$=malloc(sizeof(*$$));
			assert($$!=NULL);
			if(!find_func("temp1")){
				add_func("temp1", 0,0,NULL);
				$$=find_func("temp1");
				add_funcpar("temp1",$3->varname, $3->vartype, $3->arrdim);
			} 
			else{
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
			$$->varname = $2->varname; 
			if($1==voidtype) { 
				fprintf(stderr,"Function parameters can not be of type void. Line: %d Column: %d \n", @1.first_line,@1.first_column); 
			} 
			else {
				if($2->arrdim>=0){
					$$->vartype=1;
					$$->arrdim=$2->arrdim;
				}
				else {
					$$->vartype=0;
					$$->arrdim=NOT_DEFINED;
				}
			}
		}
     ;
									
stmt_list
     : /* empty: epsilon */
     | stmt_list stmt
     ;

stmt
     : stmt_block
     | variable_declaration SEMICOLON	{resetTempCount();}
     | expression SEMICOLON				{resetTempCount();}
     | stmt_conditional					{resetTempCount();}
     | stmt_loop						{resetTempCount();}
     | RETURN expression SEMICOLON		{
										if($2->scope!=NULL){
											if($2->scope->returntype==2){ 
												fprintf(stderr,"Function was declared as VOID. It can not return a value. Either use \"RETURN;\" or use type int for the func. Line: %d Column: %d \n",	@1.first_line,@1.first_column);
											}
										}
										gencodeop1(opRETURN, $2);
										{resetTempCount();}
										}
     | RETURN SEMICOLON					{gencodeop1(opRETURN, NULL);{resetTempCount();}}
     | SEMICOLON 						{resetTempCount();}
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
									
expression	
     : expression ASSIGN expression				{$$ = $3;
												gencodeass($1, $3);
												if($1->tempCodePos>-1) {
													setCodeToNOP($1->tempCodePos);
												}}	
     | expression LOGICAL_OR expression			{$$ = gencodeopexp2(opLOGICAL_OR, $1, $3);}
     | expression LOGICAL_AND expression		{$$ = gencodeopexp2(opLOGICAL_AND, $1, $3);}
     | LOGICAL_NOT expression					{$$ = gencodeopexp1(opLOGICAL_NOT, $2);}
     | expression EQ expression					{$$ = gencodeopexp2(opEQ, $1, $3);}
     | expression NE expression					{$$ = gencodeopexp2(opNE, $1, $3);}
     | expression LS expression 				{$$ = gencodeopexp2(opLS, $1, $3);}
     | expression LSEQ expression 				{
												struct varentry *t0;struct varentry *t1;
												t0 = gencodeopexp2(opLS, $1, $3);
												t1 = gencodeopexp2(opEQ, $1, $3);
												$$ = gencodeopexp2(opLOGICAL_OR, t0, t1);
												}
     | expression GTEQ expression 				{	
												struct varentry *t0;struct varentry *t1;
												t0 = gencodeopexp2(opGT, $1, $3);
												t1 = gencodeopexp2(opEQ, $1, $3);
												$$ = gencodeopexp2(opLOGICAL_OR, t0, t1);
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
     | function_call							{$$ = $1}
     | primary									{$$ = $1}
     ;


primary
     : NUM {								//random id for primary-NUMs
			char *s;
			s=malloc(20);
			do{
				int i=rand()%100;
			sprintf(s,"int_prim%d",i);
			}while(find_var(s));
			add_var(s,0, NOT_DEFINED, $1);
			$$ = find_var(s);
			free(s);
			}
     | ID {	
			if(find_var($1)) {
				$$ = find_var($1);
			} 
			else if(find_funcpar2($1)) {
				$$=find_funcpar2($1);
			}
			else {
				fprintf(stderr,"ERROR! The variable %s was not declared. Line: %d Column: %d \n", $1, @1.first_line,@1.first_column);
				add_var ($1, 0,NOT_DEFINED,0);
				$$= find_var($1);
			}
	  }

function_call
      : ID PARA_OPEN PARA_CLOSE
		{
			funcentry_t *f;
			//printf("DEBUG --- Function call regocnised[%s()].\n",$1);
			if(find_func($1)){
				f = find_func($1);
			}
			else{
				fprintf(stderr,"ERROR! Function was not declared before the call! Line: %d Column: %d \n", @1.first_line,@1.first_column);
				add_func("undeclared1",0,0,NULL);
				f=find_func("undeclared1");
			}
			varentry_t *v;
			char *s;
			s=malloc(20);
			do{
			int i=rand()%100;
			sprintf(s,"int_call%d",i);
			}while(find_var(s));
			add_var(s,0,-1,0);
			v=find_var(s);
			free(s);
			$$ = gencodeopfunccall(opCALL, v, f, opcodeFindFunctionDef(f));
		}
      | ID PARA_OPEN function_call_parameters PARA_CLOSE
      	{
			funcentry_t *f;
			//printf("DEBUG --- Parameterise Function call regocnised[%s()].\n",$1);
			if(find_func($1)){
				f = find_func($1);
				if(check_funccallpar(f, $3)){
					//printf("Functional Call Param Check OK!\n");
				}
				else{
					fprintf(stderr,"ERROR: Functional Call Param Check FAILED![%s(%s)] Line: %d Column: %d \n",f->funcname,$3->var->varname, @1.first_line,@1.first_column);
				}
			}
			else{
				fprintf(stderr,"ERROR! Function was not declared before the call!Line: %d Column: %d \n", @1.first_line,@1.first_column);
				add_func("undeclared1",0,0,NULL);
				f=find_func("undeclared1");
				
			}
			varentry_t *v;
			char *s;
			s=malloc(20);
			do{
				int i=rand()%100;
			sprintf(s,"int_call%d",i);
			}while(find_var(s));
			add_var(s,0,-1,$3->count);
			v=find_var(s);
			free(s);
			$$ = gencodeopfunccall(opCALL, v, f, opcodeFindFunctionDef(f));
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
			$$ = create_pars_list($1);
			gencodeop1(opPARAM, $1);
		}
     ;

%%

void yyerror (const char *msg)
{
  fprintf(stderr,"ERROR: %s, Line: %d Column: %d \n",msg, yylloc.first_line,yylloc.first_column);
}
