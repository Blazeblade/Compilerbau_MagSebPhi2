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

%type <par> 	function_call_parameters
%type <id> 		type
%type <func> 	function_definition
%type <par> 	function_parameter_list
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
		printf("----------DEBUG printing all functions and variables:\n\n");
		printf("----------DEBUG Functions:\n");
		print_funcs();
		printf("----------DEBUG Variables:\n");
		print_vars();
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
			$$->vartype=$1->vartype;
			add_var($$->varname, $$->vartype);
			printf("DEBUG --- Variable was added to Symboltable: %s\n",$$->varname);
		}
     | type identifier_declaration 
		{
			$$=malloc(sizeof($$));
			if($1==voidtype) {
				fprintf(stderr,"Variables can not be of type void (%s).\n",$2->name);
			} 
			else {
				$$->varname=$2->name;
				$$->vartype=$2->type;
				add_var($$->varname, $$->vartype);
				printf("DEBUG --- Variable was added to Symboltable: %s\n",$$->varname);
				printf("DEBUG --- ");
				print_vars();
			}
		}
     ;

identifier_declaration
     : ID BRACKET_OPEN NUM BRACKET_CLOSE	//TODO: Arrays 
     | ID 
		{
			$$=malloc(sizeof($$));
			if(find_sym($1)){
				$$=find_sym($1);
				fprintf(stderr,"This Symbol was already defined.\n");
			}	
			else{
				$$->name=$1;
				printf("DEBUG --- We have recognised a Symbol: %s\n",$1);
			}
		}   
     ;

function_definition
     : type ID PARA_OPEN PARA_CLOSE BRACE_OPEN stmt_list BRACE_CLOSE
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE BRACE_OPEN stmt_list BRACE_CLOSE
     ;

function_declaration 
     : type ID PARA_OPEN PARA_CLOSE
     | type ID PARA_OPEN function_parameter_list PARA_CLOSE 
		{
			add_funcpar($2,$4->name, $4->type); //TODO: Don't know how to do this with Parameters
		}
     ;

function_parameter_list
     : function_parameter
     | function_parameter_list COMMA function_parameter
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
				$$->type=(int)$1;
			} 
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
      | ID PARA_OPEN function_call_parameters PARA_CLOSE
      ;

function_call_parameters
     : function_call_parameters COMMA expression
     | expression
     ;

%%

void yyerror (const char *msg)
{
  printf("ERROR: %s\n", msg);
}
