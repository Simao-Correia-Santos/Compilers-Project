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
Program: FunctionsAndDeclarations {;}

FunctionsAndDeclarations: FunctionsAndDeclarations FunctionDefinition {;}
                        |FunctionsAndDeclarations FunctionDeclaration {;}
                        |FunctionsAndDeclarations Declaration {;}
                        |FunctionDefinition {;}
                        |FunctionDeclaration {;}
                        |Declaration {;}
                        ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody {;}

FunctionBody: LBRACE DeclarationAndStatements RBRACE {;}
            |LBRACE RBRACE {;}
            ;

DeclarationAndStatements: Statement DeclarationAndStatements {;}
                         |Declaration DeclarationAndStatements {;}
                         |Statement {;}
                         |Declaration {;}
                         ;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI {;}

FunctionDeclarator: IDENTIFIER LPAR ParameterList RPAR {;}

ParameterList: ParameterDeclaration {;}
              |ParameterList COMMA ParameterDeclaration {;}
              ;

ParameterDeclaration: TypeSpec IDENTIFIER {;}
                     |TypeSpec {;}
                     ;

Declaration: TypeSpec Declarator AuxDeclaration SEMI {;}
            |error SEMI {;}

AuxDeclaration: AuxDeclaration COMMA Declarator {;}
               |{}; 
               ;

TypeSpec: CHR {;}
         |INT {;}
         |VOID {;}
         |SHORT {;}
         |DOUBLE {;}
         ;

Declarator: IDENTIFIER ASSIGN Expr_comma {;}
           |IDENTIFIER {;}
           ;

Statement_error: error SEMI {;}
                |Statement {;}
                ;

AuxStatement: AuxStatement Statement_error {;}
             | Statement_error{};
             ;

Statement:LBRACE AuxStatement RBRACE {;} 
          |SEMI {;}
          |LBRACE error RBRACE {;}
          |LBRACE RBRACE {;}
          |Expr_comma SEMI {;}
          |IF LPAR Expr_comma RPAR Statement_error ELSE Statement_error  {;}
          |IF LPAR Expr_comma RPAR Statement_error %prec ELSE{;}
          |WHILE LPAR Expr_comma RPAR Statement_error {;}
          |RETURN Expr_comma SEMI {;}
          |RETURN SEMI {;}
          ;

Expr_comma: Expr_comma COMMA Expr {;}
           |Expr {;}
           ;

Expr:    IDENTIFIER LPAR error RPAR {;}
        |LPAR error RPAR {;}
        |Expr ASSIGN Expr {;}
        |Expr PLUS Expr {;}
        |Expr MINUS Expr {;}
        |Expr MUL Expr {;}
        |Expr DIV Expr {;}
        |Expr MOD Expr {;}
        |Expr OR Expr {;}
        |Expr AND Expr {;}
        |Expr BITWISEAND Expr {;}
        |Expr BITWISEOR Expr {;}
        |Expr BITWISEXOR Expr {;}
        |Expr EQ Expr {;}
        |Expr NE Expr{;}
        |Expr LE Expr{;}
        |Expr GE Expr{;}
        |Expr LT Expr{;}
        |Expr GT Expr{;}
        |PLUS Expr %prec NOT {;} 
        |MINUS Expr %prec NOT {;}
        |NOT Expr {;}
        |IDENTIFIER LPAR RPAR {;}
        |IDENTIFIER LPAR Expr_comma RPAR {;}
        |IDENTIFIER  {;}
        |NATURAL {;}
        |CHRLIT {;}
        |DECIMAL {;}
        |LPAR Expr_comma RPAR {;}
        ;