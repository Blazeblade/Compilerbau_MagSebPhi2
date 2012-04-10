/* 
 * parser.y - Parser utility for the DHBW compiler
 */
 
 
 
%{
#include "include/uthash.h";
#include "symtab.h";

%}

%union {
  int 				num;
  char*				id;
  struct funcpar 	*par;
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
%type <par> 	function_parameter
%type <sym> 	identifier_declaration
%type <var> 	expression
%type <var> 	primary

%type <var>		variable_declaration

%%

program
     : program_element_list
     ;

program_element_list
     : program_element_list program_element 
		{
		printf("\n\n----------DEBUG printing all functions and variables----------:\n");
		printf("<<----------DEBUG Functions---------->>:\n");
		print_funcs();
		printf("<<----------DEBUG Variables---------->>:\n");
		print_vars();
		printf("<<----------DEBUG END---------->>:\n");
		}
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
			$$=malloc(sizeof($$));
			$$->varname=$3->name;
			if($3->arrdim>=0){
					$$->vartype=1;
					add_var($$->varname, $$->vartype,$3->arrdim,0);
				}
				else {
					$$->vartype=0;
					add_var($$->varname, $$->vartype,-1,0);
				}
			//printf("DEBUG --- Variable was added to Symboltable: %s\n",$$->varname);
		}
     | type identifier_declaration 
		{
			$$=malloc(sizeof($$));
			if($1==voidtype) {
				fprintf(stderr,"Variables can not be of type void (%s).\n",$2->name);
			} 
			else {
				$$->varname=$2->name;
				if($2->arrdim>=0){
					$$->vartype=1;
					add_var($$->varname, $$->vartype,$2->arrdim,0);
				}
				else {
					$$->vartype=0;
					add_var($$->varname, $$->vartype,-1,0);
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
			$$=malloc(sizeof($$));
			if(find_sym($1)){
				$$=find_sym($1);
				fprintf(stderr,"This Symbol was already defined.\n");
			}	
			else{
				$$->name=$1;
				$$->arrdim= $3;
				//printf("DEBUG --- We have recognised a Symbol: %s\n",$1);
			}
		}   
     | ID 
		{
			$$=malloc(sizeof($$));
			if(find_sym($1)){
				$$=find_sym($1);
				fprintf(stderr,"This Symbol was already defined.\n");
			}	
			else{
				$$->name=$1;
				$$->arrdim=-1;
				//printf("DEBUG --- We have recognised a Symbol: %s\n",$1);
			}
		}   
     ;

function_definition		//TODO: stmt_list
     : type ID PARA_OPEN PARA_CLOSE BRACE_OPEN stmt_list BRACE_CLOSE
		{
			$$=malloc(sizeof($$));
			$$->funcname=$2;
			$$->returntype=(int)$1;
			$$->dim=0;
			$$->arrdim=-1;
			add_func($$->funcname, $$->returntype,$$->dim,$$->arrdim,NULL);
		}
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE BRACE_OPEN stmt_list BRACE_CLOSE
     	{
			$$=find_func("temp1");
			$$->funcname=$2;
			$$->returntype=(int)$1;
			$$->dim=0;							//TODO: count_pars($2);
			$$->arrdim=-1;
			add_func($$->funcname, $$->returntype,$$->dim,$$->arrdim,$$->par);
			$$=find_func("temp1");
			$$->par=NULL;
			
		}
     ;

function_declaration 
     : type ID PARA_OPEN PARA_CLOSE
		{
			$$=malloc(sizeof($$));
			$$->funcname=$2;
			$$->returntype=(int)$1;
			$$->dim=0;
			$$->arrdim=-1;
			add_func($$->funcname, $$->returntype,$$->dim,$$->arrdim,NULL);
			//printf("DEBUG --- Function was added to Symboltable: %s\n",$$->funcname);
			//printf("DEBUG --- Symboltable: ");
			//print_funcs();
		}
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE 
		{
			$$=find_func("temp1");
			$$->funcname=$2;
			$$->returntype=(int)$1;
			$$->dim=0;							//TODO: count_pars($2);
			$$->arrdim=-1;
			add_func($$->funcname, $$->returntype,$$->dim,$$->arrdim,$$->par);
			//delete_func("temp1");
			$$=find_func("temp1");
			$$->par=NULL;
			//printf("DEBUG --- Function was added to Symboltable: %s\n",$$->funcname);
			//printf("DEBUG --- Symboltable: ");
			//print_funcs();			
		}
     ;

function_parameter_list
     : function_parameter	
		{
			$$=malloc(sizeof($$));
			if(!find_func("temp1"))
			{
				add_func("temp1", 0,0,-1,NULL);
				$$=find_func("temp1");
				add_funcpar("temp1",$1->name, $1->type, $1->arrdim);
			} 
			else 
			{	
				$$=find_func("temp1");
				add_funcpar("temp1",$1->name, $1->type, $1->arrdim);
			}
		}
     | function_parameter_list COMMA function_parameter
		{
			$$=malloc(sizeof($$));
			if(!find_func("temp1"))
			{
				add_func("temp1", 0,0,-1,NULL);
				$$=find_func("temp1");
				add_funcpar("temp1",$3->name, $3->type, $3->arrdim);
			} 
			else 
			{
				$$=find_func("temp1");
				add_funcpar("temp1",$3->name, $3->type, $3->arrdim);
			}
		}
     ;
	
function_parameter
     : type identifier_declaration	
		{
			$$=malloc(sizeof($$));
			$$->name = $2->name; 
			if($1==voidtype) { 
				fprintf(stderr,"Function parameters can not be of type void.\n"); 
			} 
			else {
				if($2->arrdim>=0){
						$$->type=1;
						$$->arrdim=$2->arrdim;
						//add_funcpar(funcname, $$->name, $$->type, $2->arrdim);
					}
				else {
						$$->type=0;
						$$->arrdim=-1;
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
     | variable_declaration SEMICOLON
     | expression SEMICOLON
     | stmt_conditional
     | stmt_loop
     | RETURN expression SEMICOLON 
     | RETURN SEMICOLON
     | SEMICOLON /* empty statement */
     ;

stmt_block
     : BRACE_OPEN stmt_list BRACE_CLOSE
     ;
	
stmt_conditional
     : IF PARA_OPEN expression PARA_CLOSE stmt
     | IF PARA_OPEN expression PARA_CLOSE stmt ELSE stmt
     ;
									
stmt_loop
     : WHILE PARA_OPEN expression PARA_CLOSE stmt
     | DO stmt WHILE PARA_OPEN expression PARA_CLOSE SEMICOLON
     ;
									
expression
     : expression ASSIGN expression
     | expression LOGICAL_OR expression
     | expression LOGICAL_AND expression
     | LOGICAL_NOT expression
     | expression EQ expression
     | expression NE expression
     | expression LS expression 
     | expression LSEQ expression 
     | expression GTEQ expression 
     | expression GT expression
     | expression PLUS expression
     | expression MINUS expression
     | expression MUL expression
     | MINUS expression %prec UNARY_MINUS
     | ID BRACKET_OPEN primary BRACKET_CLOSE
     | PARA_OPEN expression PARA_CLOSE
     | function_call
     | primary
     ;

primary
     : NUM
     | ID
     ;

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
					fprintf(stderr,"ERROR: Functional Call Param Check FAILED!\n");
				}
			}
			else{
				fprintf(stderr,"ERROR! Function was not declared before the call!\n");
			}
		}
      ;

function_call_parameters
     : function_call_parameters COMMA expression	
		{
			$$->count += 1;
		}
     | expression
		{
			$$ = createParamList($1);
		}
     ;

%%

void yyerror (const char *msg)
{
  printf("ERROR: %s\n", msg);
}
