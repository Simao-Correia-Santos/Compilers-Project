%{
  #include <stdio.h>
  #include "ast.h"
  extern int yylex(void);
  void yyerror(char *);
  struct node *program;
%}

%token BITWISEAND BITWISEOR BITWISEXOR AND ASSIGN MUL COMMA DIV EQ GE GT LBRACE LE LPAR LT MINUS MOD NE NOT OR PLUS RBRACE RPAR SEMI CHR ELSE WHILE IF INT SHORT DOUBLE RETURN VOID
%token<lexeme> IDENTIFIER DECIMAL NATURAL CHRLIT RESERVED
%type<node> Program FunctionsAndDeclarations FunctionDefinition FunctionBody DeclarationAndStatements FunctionDeclaration FunctionDeclarator ParameterList ParameterDeclaration Declaration AuxDeclaration TypeSpec Declarator Statement AuxStatement Expr Expr_comma Statement_error

%union{
     char* lexeme;
     struct node* node;
}

%right ELSE
%left COMMA
%right ASSIGN
%left OR
%left AND
%left BITWISEOR
%left BITWISEXOR
%left BITWISEAND
%left EQ NE
%left LT GT GE LE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%left LPAR RPAR



%%
Program: FunctionsAndDeclarations {$$ = program = newnode(Program, NULL); addchild($$, $1);}

FunctionsAndDeclarations: FunctionsAndDeclarations FunctionDefinition {$$ = $1; addchild($$, $2);}
                        |FunctionsAndDeclarations FunctionDeclaration {$$ = $1; addchild($$, $2);}
                        |FunctionsAndDeclarations Declaration {$$ = $1; addchild($$, $2);}
                        |FunctionDefinition {$$ = $1;}
                        |FunctionDeclaration {$$ = $1;}
                        |Declaration {$$ = $1;}
                        ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody {$$ = newnode(FuncDefinition, NULL); addchild($$, $1); addchild($$, $2); addchild($$, $3);}

FunctionBody: LBRACE DeclarationAndStatements RBRACE {$$ = newnode(FuncBody, NULL); addchild($$, $2);}
            |LBRACE RBRACE {$$ = newnode(FuncBody, NULL);}
            ;

DeclarationAndStatements: DeclarationAndStatements Statement {$$ = $1; addchild($$, $2);}
                         |DeclarationAndStatements Declaration {$$ = $1; addchild($$, $2);}
                         |Statement {$$ = $1;}
                         |Declaration {$$ = $1;}
                         ;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI {$$ = newnode(FuncDeclaration, NULL); addchild($$, $1); addchild($$, $2);}

FunctionDeclarator: IDENTIFIER LPAR ParameterList RPAR {$$ = newnode(Identifier, $1); addBrother($$, $3);}

ParameterList: ParameterDeclaration {$$ = newnode(ParamList, NULL); addchild($$, $1);}
              |ParameterList COMMA ParameterDeclaration {$$ = $1; addchild($$, $3);}
              ;

ParameterDeclaration: TypeSpec IDENTIFIER {$$ = newnode(ParamDeclaration, NULL); addchild($$, $1); addchild($$, newnode(Identifier, $2));}
                     |TypeSpec {$$ = newnode(ParamDeclaration, NULL); addchild($$, $1);}
                     ;

Declaration: TypeSpec Declarator AuxDeclaration SEMI {$$ = newnode(Declaration, NULL); addchild($$, $1); addchild($$, $2); addchild($$, $3);}
            |error SEMI {;}

AuxDeclaration: AuxDeclaration COMMA Declarator {$$ = $1; addBrother($$, $3);}
               |{}; 
               ;

TypeSpec: CHR {$$ = newnode(Char, NULL);}
         |INT {$$ = newnode(Int, NULL);}
         |VOID {$$ = newnode(Void, NULL);}
         |SHORT {$$ = newnode(Short, NULL);}
         |DOUBLE {$$ = newnode(Double, NULL);}
         ;

Declarator: IDENTIFIER ASSIGN Expr_comma {$$ = newnode(Identifier, $1); addBrother($$, $3);}
           |IDENTIFIER {$$ = newnode(Identifier, $1);}
           ;

Statement_error: error SEMI {$$ = newnode(Null, NULL);}
                |Statement {$$ = $1;}
                ;

AuxStatement: AuxStatement Statement_error {$$ = newnode(StatList, NULL); addchild($$, $2);}
             | Statement_error{$$ = $1;}
             ;

Statement: LBRACE AuxStatement RBRACE {$$ = $2;} 
          |SEMI {;}
          |LBRACE error RBRACE {;}
          |LBRACE RBRACE {;}
          |Expr_comma SEMI {$$ = $1;}
          |IF LPAR Expr_comma RPAR Statement_error ELSE Statement_error {$$ = newnode(If, NULL); addchild($$, $3); addchild($$, $5); addchild($$, $7);}
          |IF LPAR Expr_comma RPAR Statement_error %prec ELSE {$$ = newnode(If, NULL); addchild($$, $3); addchild($$, $5); addchild($$, newnode(Null, NULL));}
          |WHILE LPAR Expr_comma RPAR Statement_error {$$ = newnode(While, NULL); addchild($$, $3); addchild($$, $5);}
          |RETURN Expr_comma SEMI {$$ = newnode(Return, NULL); addchild($$, $2);}
          |RETURN SEMI {$$ = newnode(Return, NULL); addchild($$, newnode(Null, NULL));}
          ;

Expr_comma: Expr_comma COMMA Expr {$$ = newnode(Comma, NULL); addchild($$, $1); addchild($$, $3);}
           |Expr {$$ = $1;}
           ;

Expr:    IDENTIFIER LPAR error RPAR {;}
        |LPAR error RPAR {;}
        |Expr ASSIGN Expr {$$ = newnode(Store, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr PLUS Expr {$$ = newnode(Add, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr MINUS Expr {$$ = newnode(Sub, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr MUL Expr {$$ = newnode(Mul, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr DIV Expr {$$ = newnode(Div, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr MOD Expr {$$ = newnode(Mod, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr OR Expr {$$ = newnode(Or, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr AND Expr {$$ = newnode(And, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr BITWISEAND Expr {$$ = newnode(BitWiseAnd, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr BITWISEOR Expr {$$ = newnode(BitWiseOr, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr BITWISEXOR Expr {$$ = newnode(BitWiseXor, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr EQ Expr {$$ = newnode(Eq, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr NE Expr {$$ = newnode(Ne, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr LE Expr {$$ = newnode(Le, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr GE Expr {$$ = newnode(Ge, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr LT Expr {$$ = newnode(Lt, NULL); addchild($$, $1); addchild($$, $3);}
        |Expr GT Expr {$$ = newnode(Gt, NULL); addchild($$, $1); addchild($$, $3);}
        |PLUS Expr %prec NOT {$$ = newnode(Plus, NULL); addchild($$, $2);} 
        |MINUS Expr %prec NOT {$$ = newnode(Minus, NULL); addchild($$, $2);}
        |NOT Expr {$$ = newnode(Not, NULL); addchild($$, $2);}
        |IDENTIFIER LPAR RPAR {$$ = newnode(Call, NULL); addchild($$, newnode(Identifier, $1));}
        |IDENTIFIER LPAR Expr_comma RPAR {$$ = newnode(Call, NULL); addchild($$, newnode(Identifier, $1)); addchild($$, $3);}
        |IDENTIFIER {$$ = newnode(Identifier, $1);}
        |NATURAL {$$ = newnode(Natural, $1);}
        |CHRLIT {$$ = newnode(Chrlit, $1);}
        |DECIMAL {$$ = newnode(Decimal, $1);}
        |LPAR Expr_comma RPAR {$$ = $2;}
        ;