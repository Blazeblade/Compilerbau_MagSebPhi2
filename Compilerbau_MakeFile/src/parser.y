/**
 * @file 	parser.y
 * @author	Sebastian Boehm, Magnus Bruehl, Philipp Goetze
 * @brief	Parser utility for the DHBW compiler
 *
 */
 
%{
#include "include/uthash.h";
#include "symtab.h";
#include "ir_code_gen.h";
#include "diag.h";
//#include <assert.h>
#include <stdlib.h>


#define NOT_DEFINED 	-1
#define INT_ 			0
#define INT_ARR_		1
#define VOID_			2
#define NO_PARAMS		NULL
int 		prim_count=0;	//count for primaries (numbers)
int 		call_count=0;	//count for call variables
%}

%union {
  int 						num;
  char*						id;
  struct varentry 			*var;
  struct funcentry 			*func;
  struct funccallparlist 	*plist;
}

 
%debug
%locations
%start program

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

%type <id> 		type

%type <plist> 	function_call_parameters

%type <func> 	function_definition
%type <func> 	function_declaration
%type <func> 	function_parameter_list

%type <var>		variable_declaration
%type <var> 	identifier_declaration
%type <var> 	function_call
%type <var> 	function_parameter
%type <var> 	expression
%type <var> 	primary


%%

program
     : program_element_list{
		/*printf("\n\n----------DEBUG printing all functions and variables----------:\n");
		printf("<<----------DEBUG Functions---------->>:\n");
		print_funcs();
		printf("<<----------DEBUG Variables---------->>:\n");
		print_vars();
		printf("<<----------DEBUG END---------->>:\n\n\n");*/
		//find_protos();
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
     | SEMICOLON 	{fprintf(stderr,"WARNING: Single Semicolon can be deleted. Line: %d Column: %d \n", @1.first_line,@1.first_column);}
     ;
									
type
     : INT	{$$=integer;}
     | VOID {$$=voidtype;}
     ;

variable_declaration
     : variable_declaration COMMA identifier_declaration
		{
			$$=malloc(sizeof(*$$));
			if ($$ == NULL) {
				FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "variable_declaration -> malloc");
				return;
			}
			//assert($$!=NULL);
			$$->varname=$3->varname;
			if($3->arrdim>=0){
					$$->vartype=INT_ARR_;
					add_var($$->varname, $$->vartype,$3->arrdim,NULL);
				}
				else {
					$$->vartype=INT_;
					add_var($$->varname, $$->vartype,NOT_DEFINED,NULL);
				}
		}
     | type identifier_declaration 
		{
			$$=malloc(sizeof(*$$));
			if ($$ == NULL) {
				FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "variable_declaration -> malloc");
				return;
			}
			//assert($$!=NULL);
			if($1==voidtype) {
				fprintf(stderr,"ERROR: Variables can not be of type void (%s). Line: %d Column: %d \n",$2->varname, @1.first_line,@1.first_column);
			} 	
			//Add variable although it is void for the rest of the analysis?
			else {
				$$->varname=$2->varname;
				if($2->arrdim>=0){
					$$->vartype=INT_ARR_;
					add_var($$->varname, $$->vartype,$2->arrdim,NULL);
				}
				else{
					$$->vartype=INT_;
					add_var($$->varname, $$->vartype,NOT_DEFINED,NULL);
				}
			}
		}
     ;

identifier_declaration
     : ID BRACKET_OPEN NUM BRACKET_CLOSE
		{
			$$=malloc(sizeof(*$$));
			if ($$ == NULL) {
				FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "identifier_declaration -> malloc");
				return;
			}
			//assert($$!=NULL);
			if(find_var($1)){
				$$=find_var($1);
				if($$->scope==get_func_scope())
					fprintf(stderr,"ERROR: This Symbol was already defined (%s), Line: %d Column: %d \n",$$->varname, @1.first_line,@1.first_column);
				else{
					$$->varname=$1;
					$$->vartype=INT_ARR_;
					$$->arrdim= $3;
				}
			}	
			else{
				$$->varname=$1;
				$$->vartype=INT_ARR_;
				$$->arrdim= $3;
			}
		}   
     | ID 
		{
			$$=malloc(sizeof(*$$));
			if ($$ == NULL) {
				FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "identifier_declaration -> malloc");
				return;
			}
			//assert($$!=NULL);
			if(find_var($1)){
				$$=find_var($1);
				if($$->scope==get_func_scope())
					fprintf(stderr,"ERROR: This Symbol was already defined (%s), Line: %d Column: %d \n",$$->varname, @1.first_line,@1.first_column);
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
			if(find_var($2)){
				varentry_t *v;
				v=find_var($2);
				if(v->scope==get_func_scope())
					fprintf(stderr,"ERROR: This Symbol was already defined as variable(%s), Line: %d Column: %d \n",v->varname, @1.first_line,@1.first_column);
			}
			else if(find_func($2)){
					if(is_func_proto(find_func($2))){
						int temp=1;
						funcentry_t *f=find_func($2);
						if($1!=f->returntype)
							temp=0;
						if(f->dim != 0)
							temp=0;
						if(f->var != NULL)
							temp=0;
						if(temp==0){
							fprintf(stderr,"ERROR: A function declaration with the same name (%s) already exists with other parameters. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
						}
						if($1!=find_func($2)->returntype){	
							fprintf(stderr,"ERROR: Types mismatch from function %s's declaration. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
						}
						set_func_to_decl($2);
						set_func_scope(find_func($2));
					}
					else{	
						fprintf(stderr,"ERROR: A function definition with the same name (%s) already exists. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
					}
				}
				else{										
					$<func>$=malloc(sizeof(*$<func>$));
					if ($<func>$ == NULL) {
						FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "function_definition -> malloc");
						return;
					}
					//assert($<func>$!=NULL);
					$<func>$->funcname=$2;
					$<func>$->returntype=(int)$1;
					$<func>$->dim=0;
					add_func($<func>$->funcname, $<func>$->returntype,$<func>$->dim,NO_PARAMS);
					set_func_scope(find_func($2));
				}
			gencode_opfunc(FUNC_DEF_IR, NULL, find_func($2));
		}
		
		 BRACE_OPEN stmt_list BRACE_CLOSE {gencode_opfunc(FUNC_DEF_END_IR, NULL, find_func($2));set_func_scope(NULL);backpatch_return();}
		
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE
     	{	
     		if(find_var($2)){
				varentry_t *v;
				v=find_var($2);
				if(v->scope==get_func_scope())
					fprintf(stderr,"ERROR: This Symbol was already defined as variable(%s), Line: %d Column: %d \n",v->varname, @1.first_line,@1.first_column);
			}
			else if(find_func($2)){
				if(is_func_proto(find_func($2))){
					int temp=1;
					funcentry_t *f=find_func($2);
					if($1!=f->returntype)
						temp=0;
					if(f->dim != $4->dim)
						temp=0;
					varentry_t *par0 = f->var;
					varentry_t *par1 = $4->var;
					for(int i=0;i<f->dim;i++){
						if(par0->arrdim != par1->arrdim)
							temp=0;
						if(par0->vartype != par1->vartype)
						temp=0;
						if(par0->hh.next!=NULL)
							par0 = par0->hh.next;
						else
							break;
						if(par1->hh.next!=NULL)
							par1 = par1->hh.next;
						else
							break;
					}
					if(temp==0){
						fprintf(stderr,"ERROR: Function-Parameter definition does not match the declaration of function %s. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
					}
					if($1!=find_func($2)->returntype){
						fprintf(stderr,"ERROR: Type mismatch from function %s's declaration. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
					}
					if(strcmp ($4->funcname,"temp1")==0){
						delete_func (find_func("temp1"));
						set_func_to_decl ($2);
						set_func_scope(find_func($2));
						gencode_opfunc(FUNC_DEF_IR, $4, find_func($2));
					}
					else{
						printf("INTERNAL ERROR: Function has not the expected TEMP_NAME!\n");
					}
				}
				else{
					fprintf(stderr,"ERROR: A function definition with the same name (%s) already exists. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
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
					gencode_opfunc(FUNC_DEF_IR, $4, find_func($2));
				}
				else{
					printf("INTERNAL ERROR: Function has not the expected TEMP_NAME!\n");
				}
			}			
		}
		 BRACE_OPEN stmt_list BRACE_CLOSE{gencode_opfunc(FUNC_DEF_END_IR, NULL, find_func($2));set_func_scope(NULL);backpatch_return();}
     ;

function_declaration 
     : type ID PARA_OPEN PARA_CLOSE
		{
			if(find_var($2)){
				varentry_t *v;
				v=find_var($2);
				if(v->scope==get_func_scope())
					fprintf(stderr,"ERROR: This Symbol was already defined as variable(%s), Line: %d Column: %d \n",v->varname, @1.first_line,@1.first_column);
			}
			else if(find_func($2)){
				int temp=1;
				funcentry_t *f=find_func($2);
				if($1!=f->returntype)
					temp=0;
				if(f->dim != 0)
					temp=0;
				if(f->var != NULL)
					temp=0;
				if(temp==0){
					fprintf(stderr,"ERROR: A function declaration with the same name (%s) already exists with other parameters. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
				}
			}
			else{
				$$=malloc(sizeof(*$$));
				if ($$ == NULL) {
					FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "function_declaration -> malloc");
					return;
				}
				//assert($$!=NULL);
				$$->funcname=$2;
				$$->returntype=(int)$1;
				$$->dim=0;
				add_func($$->funcname, $$->returntype,$$->dim,NO_PARAMS);
			}
			set_func_to_proto (find_func($2));
			set_scope_for_pars (find_func($2));
			set_func_scope(NULL);
		}								
														
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE 
     	{
     		if(find_var($2)){
				varentry_t *v;
				v=find_var($2);
				if(v->scope==get_func_scope())
					fprintf(stderr,"ERROR: This Symbol was already defined as variable(%s), Line: %d Column: %d \n",v->varname, @1.first_line,@1.first_column);
			}
			else if(find_func($2)) {
				int temp=1;
				funcentry_t *f=find_func($2);
				if($1!=f->returntype)
					temp=0;
				if(f->dim != $4->dim)
					temp=0;
				varentry_t *par0 = f->var;
				varentry_t *par1 = $4->var;
				for(int i=0;i<f->dim;i++){
					if(par0->arrdim != par1->arrdim)
						temp=0;
					if(par0->vartype != par1->vartype)
						temp=0;
					if(par0->hh.next!=NULL)
						par0 = par0->hh.next;
					else
						break;
					if(par1->hh.next!=NULL)
						par1 = par1->hh.next;
					else
						break;
				}
				if(temp==0){
					fprintf(stderr,"ERROR: A function declaration with the same name (%s) already exists with other parameters or type. Line: %d Column: %d \n",$2, @1.first_line,@1.first_column);
				}
				delete_func(find_func("temp1"));
			}
			else{
				$$=find_func("temp1");
				$$->dim=count_pars($$->funcname);
				$$->funcname=$2;
				$$->returntype=(int)$1;
				add_func($$->funcname, $$->returntype,$$->dim,$$->var);
				delete_func($$);				//Deletes the temp function															
			}
			set_func_to_proto(find_func($2));
			set_scope_for_pars (find_func($2));
			set_func_scope(NULL);
		}
     ;

function_parameter_list
     : function_parameter
		{
			$$=malloc(sizeof(*$$));
			if ($$ == NULL) {
				FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "function_parameter_list -> malloc");
				return;
			}
			//assert($$!=NULL);
			if(!find_func("temp1"))	{
				add_func("temp1", 0,0,NO_PARAMS);
				add_funcpar("temp1",$1->varname, $1->vartype, $1->arrdim);
				$$=find_func("temp1");
				$$->dim++;
				$1->scope=$$;
			} 
			else{	
				add_funcpar("temp1",$1->varname, $1->vartype, $1->arrdim);
				$$=find_func("temp1");
				$$->dim++;
				$1->scope=$$;
			}
		}
     | function_parameter_list COMMA function_parameter
		{
			$$=malloc(sizeof(*$$));
			if ($$ == NULL) {
				FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "function_parameter_list -> malloc");
				return;
			}
			//assert($$!=NULL);
			if(!find_func("temp1")){
				add_func("temp1", 0,0,NO_PARAMS);
				$$=find_func("temp1");
				add_funcpar("temp1",$3->varname, $3->vartype, $3->arrdim);
				$$->dim++;
			} 
			else{
				$$=find_func("temp1");
				add_funcpar("temp1",$3->varname, $3->vartype, $3->arrdim);
				$$->dim++;
				//add_var($3->varname, $3->vartype, $3->arrdim,1,0);
			}
		}
     ;
	
function_parameter
     : type identifier_declaration
		{
			$$=malloc(sizeof(*$$));
			if ($$ == NULL) {
				FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "function_parameter -> malloc");
				return;
			}
			//assert($$!=NULL);
			$$->varname = $2->varname; 
			if($1==voidtype) { 
				fprintf(stderr,"ERROR: Function parameters can not be of type void. Line: %d Column: %d \n", @1.first_line,@1.first_column); 
			} 
			else {
				if($2->arrdim>=0){
					$$->vartype=INT_ARR_;
					$$->arrdim=$2->arrdim;
				}
				else {
					$$->vartype=INT_;
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
     | variable_declaration SEMICOLON	{reset_temp_count();}
     | expression SEMICOLON				{reset_temp_count();}
     | stmt_conditional					{reset_temp_count();}
     | stmt_loop						{reset_temp_count();}
     | RETURN expression SEMICOLON		{
										if($2->scope!=NULL){
											if($2->scope->returntype==VOID_){ 
												fprintf(stderr,"ERROR: Function was declared as VOID. It can not return a value. Either use \"return;\" or use type int for the func. Line: %d Column: %d \n",	@1.first_line,@1.first_column);
											}
										}
										gencode_op1(RETURN_IR, $2);
										{reset_temp_count();}
										}
     | RETURN SEMICOLON					{
										funcentry_t *f=get_func_scope();
										if(f->returntype==INT_)
											fprintf(stderr,"ERROR: Function was declared as Integer. It must return an expression. Line: %d Column: %d \n",	@1.first_line,@1.first_column);
										gencode_op1(RETURN_IR, NULL);
										{reset_temp_count();}
										}
     | SEMICOLON 						{reset_temp_count();
										fprintf(stderr,"WARNING: Single Semicolon can be deleted. Line: %d Column: %d \n", @1.first_line,@1.first_column);
										}
     ;


stmt_block
     : BRACE_OPEN stmt_list BRACE_CLOSE
     ;
	
stmt_conditional
     : IF PARA_OPEN expression {genif($3);genif_goto();} PARA_CLOSE stmt_conditional_r //stmt
     //| IF PARA_OPEN expression {genif($3);genif_goto();} PARA_CLOSE stmt ELSE stmt	//{genif($3);genif_goto();}
     ;
     
stmt_conditional_r
     : stmt {backpatch_if(0);}
     | stmt ELSE {backpatch_if(1);genif_goto();} stmt {backpatch_if(0);}
     ;
									
stmt_loop
     : WHILE {genwhile_begin();} PARA_OPEN expression PARA_CLOSE {genwhile($4);genwhile_gotobegin();} stmt {backpatch_while();}
     | DO {gendowhile();} stmt WHILE PARA_OPEN expression PARA_CLOSE SEMICOLON {gendowhile_end($6);}
     ;
									
expression	
	 : expression ASSIGN expression				{	$$ = $3;
													gencode_ass($1, $3);
													if($1->var_cpos>-1) {
														set_code_to_NOP($1->var_cpos);
													}
												}	
     | expression LOGICAL_OR expression			{$$ = gencode_op2exp(LOGICAL_OR_IR, $1, $3);}
     | expression LOGICAL_AND expression		{$$ = gencode_op2exp(LOGICAL_AND_IR, $1, $3);}
     | LOGICAL_NOT expression					{$$ = gencode_op1exp(LOGICAL_NOT_IR, $2);}
     | expression EQ expression					{$$ = gencode_op2exp(EQ_IR, $1, $3);}
     | expression NE expression					{$$ = gencode_op2exp(NE_IR, $1, $3);}
     | expression LS expression 				{$$ = gencode_op2exp(LS_IR, $1, $3);}
     | expression LSEQ expression 				{$$ = gencode_op2exp(LSEQ_IR, $1, $3);
												//Alternative:
												/*struct varentry *t0;struct varentry *t1;
												t0 = gencode_op2exp(LS_IR, $1, $3);
												t1 = gencode_op2exp(EQ_IR, $1, $3);
												$$ = gencode_op2exp(LOGICAL_OR_IR, t0, t1);*/
												}
     | expression GTEQ expression 				{$$ = gencode_op2exp(GTEQ_IR, $1, $3);	
												//Alternative:
												/*struct varentry *t0;struct varentry *t1;
												t0 = gencode_op2exp(GT_IR, $1, $3);
												t1 = gencode_op2exp(EQ_IR, $1, $3);
												$$ = gencode_op2exp(LOGICAL_OR_IR, t0, t1);*/
												}
     | expression GT expression					{$$ = gencode_op2exp(GT_IR, $1, $3);}
     | expression PLUS expression				{$$ = gencode_op2exp(ADD_IR, $1, $3);}
     | expression MINUS expression				{$$ = gencode_op2exp(SUB_IR, $1, $3);}
     | expression MUL expression				{$$ = gencode_op2exp(MUL_IR, $1, $3);}
	 | expression  SHIFT_LEFT expression		{$$ = gencode_op2exp(SHIFT_LEFT_IR,$1,$3);}
	 | expression  SHIFT_RIGHT expression		{$$ = gencode_op2exp(SHIFT_RIGHT_IR,$1,$3);}
     | MINUS expression %prec UNARY_MINUS		{$$ = gencode_op1exp(MINUS_IR, $2);}
     | ID BRACKET_OPEN primary BRACKET_CLOSE	{
												if(!find_var($1))
													$$ = gencode_load_arr(find_funcpar2($1), $3);
												else
													$$ = gencode_load_arr(find_var($1), $3);
												$$->var_arr_loc=$3->val;
												$$->var_arr_loc_struct=$3;
												}
     | PARA_OPEN expression PARA_CLOSE			{$$ = $2}
     | function_call							{$$ = $1; 	$$->isfunccall=1;}
     | primary									{$$ = $1}
     ;


primary
     : NUM {								
			char *s;
			s=malloc(20);
			if (s == NULL) {
				FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "s -> malloc");
				return;
			}
			//int i=rand()%1000;	//random id for primary-NUMs
			int i= prim_count++;
			sprintf(s,"int_prim%d",i);
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
				fprintf(stderr,"ERROR: The variable %s was not declared. Line: %d Column: %d \n", $1, @1.first_line,@1.first_column);
				add_var ($1, 0,NOT_DEFINED,0);
				$$= find_var($1);
			}
	  }

function_call
      : ID PARA_OPEN PARA_CLOSE
		{
			funcentry_t *f;
			if(find_func($1)){
				f = find_func($1);
				if(f->dim>0)
					fprintf(stderr,"ERROR: Functional Call Paramater Check FAILED! Function %s() needs %d parameter(s). Line: %d Column: %d \n",f->funcname, f->dim, @1.first_line,@1.first_column);
			}
			else{
				fprintf(stderr,"ERROR: Function was not declared before the call! Line: %d Column: %d \n", @1.first_line,@1.first_column);
				add_func("undeclared1",0,0,NO_PARAMS);
				f=find_func("undeclared1");
			}
			varentry_t *v;
			char *s;
			s=malloc(20);
			if (s == NULL) {
				FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "s -> malloc");
				return;
			}
			//int i=rand()%1000;
			int i= 	call_count++;
			sprintf(s,"int_call%d",i);
			add_var(s,0,-1,0);
			v=find_var(s);
			free(s);
			$$ = gencode_funccall(CALL_IR, v, f, opcode_find_FuncDef(f));
			$$->vartype=f->returntype;
		}
      | ID PARA_OPEN function_call_parameters PARA_CLOSE
      	{
			funcentry_t *f;
			if(find_func($1)){
				f = find_func($1);
				if(!check_funccallpar(f, $3))
					fprintf(stderr,"ERROR: Functional Call Paramater Check FAILED![%s(%s)] Line: %d Column: %d \n",f->funcname,$3->var->varname, @1.first_line,@1.first_column);
			}
			else{
				fprintf(stderr,"ERROR: Function was not declared before the call!Line: %d Column: %d \n", @1.first_line,@1.first_column);
				add_func("undeclared1",0,0,NO_PARAMS);
				f=find_func("undeclared1");
				
			}
			varentry_t *v;
			char *s;
			s=malloc(20);
			if (s == NULL) {
				FATAL_OS_ERROR(OUT_OF_MEMORY, 0, "s -> malloc");
				return;
			}
			//do{
			//	int i=rand()%1000;
			int i=call_count++;
			sprintf(s,"int_call%d",i);
			//}while(find_var(s));
			add_var(s,0,-1,$3->count);
			v=find_var(s);
			free(s);
			$$ = gencode_funccall(CALL_IR, v, f, opcode_find_FuncDef(f));
			$$->vartype==f->returntype;
		}
      ;

function_call_parameters
     : function_call_parameters COMMA expression	
		{
			$$->count += 1;
			if($3->vartype==VOID_)
				fprintf(stderr,"ERROR: Parameters can not be of type void (%s). Line: %d Column: %d \n",$3->varname, @1.first_line,@1.first_column);
			gencode_op1(PARAM_IR, $3);
		}
     | expression
		{
			$$ = create_pars_list($1);
			if($1->vartype==VOID_)
				fprintf(stderr,"ERROR: Parameters can not be of type void (%s). Line: %d Column: %d \n",$1->varname, @1.first_line,@1.first_column);
			gencode_op1(PARAM_IR, $1);
		}
     ;

%%

void yyerror (const char *msg)
{
  fprintf(stderr,"ERROR: %s, Line: %d Column: %d \n",msg, yylloc.first_line,yylloc.first_column);
}
