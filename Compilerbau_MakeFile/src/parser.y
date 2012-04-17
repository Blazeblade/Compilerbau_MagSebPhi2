/* 
 * parser.y - Parser utility for the DHBW compiler
 */
 
 
 
%{
#include "include/uthash.h";
#include "symtab.h";
#include "ir_code_gen.h";


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
					add_var($$->varname, $$->vartype,$3->arrdim,0,NULL);
				}
				else {
					$$->vartype=0;
					add_var($$->varname, $$->vartype,-1,0,NULL);
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
					add_var($$->varname, $$->vartype,$2->arrdim,0,NULL);
				}
				else {
					$$->vartype=0;
					add_var($$->varname, $$->vartype,-1,0,NULL);
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
			add_func($$->funcname, $$->returntype,$$->dim,$$->arrdim,$$->var);
			$$=find_func("temp1");
			$$->var=NULL;
			
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
			add_func($$->funcname, $$->returntype,$$->dim,$$->arrdim,$$->var);
			//delete_func("temp1");
			$$=find_func("temp1");
			$$->var=NULL;
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
									
expression								// 0 = "false", nonzero = "true"
     : expression ASSIGN expression				{$$ = $3;addcodeass($1, $3);if($1->tempCodePos>-1) {setCodeToNOP($1->tempCodePos);}}	//WARNING: Ambigious! You dont know if you have to assign to/load from an array or if it is an normal int at this point. check this when generating final code
     | expression LOGICAL_OR expression			{$$ = addcodeopexp2(opLOGICAL_OR, $1, $3);}
     | expression LOGICAL_AND expression		{$$ = addcodeopexp2(opLOGICAL_AND, $1, $3);}
     | LOGICAL_NOT expression					{$$ = addcodeopexp1(opLOGICAL_NOT, $2);}
     | expression EQ expression					{$$ = addcodeopexp2(opEQ, $1, $3);}
     | expression NE expression					{$$ = addcodeopexp2(opNE, $1, $3);}
     | expression LS expression 					{$$ = addcodeopexp2(opLS, $1, $3);}
     | expression LSEQ expression 				{	//$$ = $1 <= $2 -> $$ = $1 < $2 || $1 == $2;
											struct varentry *t0;struct varentry *t1;
											t0 = addcodeopexp2(opLS, $1, $3);
											t1 = addcodeopexp2(opEQ, $1, $3);
											$$ = addcodeopexp2(opLOGICAL_OR, t0, t1);
											//$$ = addcodeopexp2(opLSEQ, $1, $3);
										}
     | expression GTEQ expression 				{	//$$ = $1 >= $2 -> $$ = $1 > $2 || $1 == $2;
											struct varentry *t0;struct varentry *t1;
											t0 = addcodeopexp2(opGT, $1, $3);
											t1 = addcodeopexp2(opEQ, $1, $3);
											$$ = addcodeopexp2(opLOGICAL_OR, t0, t1);
											//$$ = addcodeopexp2(opGTEQ, $1, $3);
										}
     | expression GT expression					{$$ = addcodeopexp2(opGT, $1, $3);}
     | expression PLUS expression				{$$ = addcodeopexp2(opADD, $1, $3);}
     | expression MINUS expression				{$$ = addcodeopexp2(opSUB, $1, $3);}
     | expression MUL expression				{$$ = addcodeopexp2(opMUL, $1, $3);}
     | MINUS expression %prec UNARY_MINUS		{$$ = addcodeopexp1(opMINUS, $2);}
     | ID BRACKET_OPEN primary BRACKET_CLOSE	{$$ = addcodeloadarr(find_var($1), $3);$$->tempArrPos=$3->var;$$->tempArrPos2=$3;} /*In c there is no check whether the array acces in the valid bounds*/
     | PARA_OPEN expression PARA_CLOSE			{$$ = $2}
     | function_call							{$$ = $1;/*$$ = irtempInt();*//*TODO: Check whether v0 or v1 is needed as a temp register. for e.g. i = f() + g() -> i = v0 + v1*/}
     | primary									{$$ = $1}
     ;


primary
     : NUM {add_var("int",0, -1,0, $1);$$ = find_var("int");}
     | ID {	if(find_var($1)) {
			$$ = find_var($1);
		} else {
			//TODO: It seems that global variables are not recognised, check this!
			printf("ERROR! The variable %s was not declared. Line: %d Column: %d \n", $1, @1.first_line, @1.first_column);
			//We assume the variable should have been declared. so we declare it for the user...
			add_var ($1, 0,-1, 0,0);
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
