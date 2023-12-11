%{
  #include <stdio.h>
  #include "ast.h"
  extern int yylex(void);
  void yyerror(char *);
  struct node *program;
  struct node *aux;
  int statement_list_check = 0;
%}

%token BITWISEAND BITWISEOR BITWISEXOR AND ASSIGN MUL COMMA DIV EQ GE GT LBRACE LE LPAR LT MINUS MOD NE NOT OR PLUS RBRACE RPAR SEMI CHR ELSE WHILE IF INT SHORT DOUBLE RETURN VOID
%token<lexeme> IDENTIFIER DECIMAL NATURAL CHRLIT RESERVED
%type<node> Program FunctionsAndDeclarations FunctionDefinition FunctionBody DeclarationAndStatements FunctionDeclaration FunctionDeclarator ParameterList ParameterDeclaration Declaration AuxDeclaration TypeSpec Declarator Statement AuxStatement Expr Expr_comma Statement_error Expr_call

%union{
     char* lexeme;
     struct node* node;
}

%locations
%{
#define LOCATE(node, line, column) { node->token_line = line; node->token_column = column; }
%}

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

FunctionsAndDeclarations: FunctionsAndDeclarations FunctionDefinition {$$ = $1; addBrother($$, $2);}
                        |FunctionsAndDeclarations FunctionDeclaration {$$ = $1; addBrother($$, $2);}
                        |FunctionsAndDeclarations Declaration {$$ = $1; addBrother($$, $2);}
                        |FunctionDefinition {$$ = $1;}
                        |FunctionDeclaration {$$ = $1;}
                        |Declaration {$$ = $1;}
                        ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody {$$ = newnode(FuncDefinition, NULL); addchild($$, $1); addchild($$, $2); addchild($$, $3);}

FunctionBody: LBRACE DeclarationAndStatements RBRACE {$$ = newnode(FuncBody, NULL); addchild($$, $2);}
            |LBRACE RBRACE {$$ = newnode(FuncBody, NULL);}
            ;

DeclarationAndStatements: DeclarationAndStatements Statement {if($1 == NULL) $$ = $2; else {$$ = $1; addBrother($$, $2);}}
                         |DeclarationAndStatements Declaration {$$ = $1; addBrother($$, $2);}
                         |Statement {$$ = $1;}
                         |Declaration {$$ = $1;}
                         ;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI {$$ = newnode(FuncDeclaration, NULL); addchild($$, $1); addchild($$, $2);}

FunctionDeclarator: IDENTIFIER LPAR ParameterList RPAR {$$ = newnode(Identifier, $1); addBrother($$, $3); LOCATE($$, @1.first_line, @1.first_column);}

ParameterList: ParameterDeclaration {$$ = newnode(ParamList, NULL); addchild($$, $1);}
              |ParameterList COMMA ParameterDeclaration {$$ = $1; if ($1->category == 4) addchild($$, $3); else addBrother($$, $3);}
              ;

ParameterDeclaration: TypeSpec IDENTIFIER {$$ = newnode(ParamDeclaration, NULL); addchild($$, $1); addchild($$, newnode(Identifier, $2)); LOCATE(getchild($$, 1), @2.first_line, @2.first_column);}
                     |TypeSpec {$$ = newnode(ParamDeclaration, NULL); addchild($$, $1);}
                     ;

Declaration: TypeSpec AuxDeclaration SEMI {
                                            $$ = $2;
                                            aux = $$;
                                            while (aux != NULL){
                                              insert_typespec(aux, $1);
                                              aux = aux->brother;
                                            }
                                          }
             |error SEMI {$$ = newnode(Error, NULL);}

AuxDeclaration: AuxDeclaration COMMA Declarator {$$ = $1; addBrother($$, $3);}
               |Declarator {$$ = $1;} 
               ;

TypeSpec: CHR {$$ = newnode(Char, NULL); LOCATE($$, @1.first_line, @1.first_column);}
         |INT {$$ = newnode(Int, NULL); LOCATE($$ , @1.first_line, @1.first_column);}
         |VOID {$$ = newnode(Void, NULL); LOCATE($$, @1.first_line, @1.first_column);}
         |SHORT {$$ = newnode(Short, NULL); LOCATE($$ , @1.first_line, @1.first_column);}
         |DOUBLE {$$ = newnode(Double, NULL); LOCATE($$ , @1.first_line, @1.first_column);}
         ;

Declarator: IDENTIFIER ASSIGN Expr_comma {$$ = newnode(Declaration, NULL); addchild($$, newnode(Identifier, $1)); addchild($$, $3); LOCATE(getchild($$, 0), @1.first_line, @1.first_column);}
           |IDENTIFIER {$$ = newnode(Declaration, NULL); addchild($$, newnode(Identifier, $1));LOCATE(getchild($$ , 0), @1.first_line, @1.first_column);}
           ;

Statement_error: error SEMI {$$ = newnode(Error, NULL);}
                |Statement {$$ = $1;}
                ;

AuxStatement: AuxStatement Statement_error {if($1 != NULL) {$$ = $1; addBrother($$, $2); statement_list_check = 1;} else $$ = $2;}
             |Statement_error{$$ = $1; statement_list_check = 0;}
             ;

Statement: LBRACE AuxStatement RBRACE {
                                        if (statement_list_check == 1){
                                        $$ = newnode(StatList, NULL);
                                        addchild($$, $2);
                                        }                             
                                        else $$ = $2;
                                      } 
          |SEMI {$$ = NULL;}
          |LBRACE error RBRACE {$$ = newnode(Error, NULL);}
          |LBRACE RBRACE {$$ = NULL;}
          |Expr_comma SEMI {$$ = $1;}
          |IF LPAR Expr_comma RPAR Statement_error ELSE Statement_error {
                                                                         $$ = newnode(If, NULL); 
                                                                         addchild($$, $3); 
                                                                         if($5 != NULL) {addchild($$, $5);} 
                                                                         else {addchild($$, newnode(Null, NULL));}
                                                                         if ($7 != NULL) {addchild($$, $7);}
                                                                         else {addchild($$, newnode(Null, NULL));}
                                                                        }

          |IF LPAR Expr_comma RPAR Statement_error %prec ELSE {
                                                               $$ = newnode(If, NULL); 
                                                               addchild($$, $3); 
                                                               if ($5 != NULL) {addchild($$, $5);}
                                                               else {addchild($$, newnode(Null, NULL));} 
                                                               addchild($$, newnode(Null, NULL));
                                                              }
          |WHILE LPAR Expr_comma RPAR Statement_error {
                                                       $$ = newnode(While, NULL); 
                                                       addchild($$, $3); 
                                                       if($5 != NULL) {addchild($$, $5);}
                                                       else {addchild($$, newnode(Null, NULL));}
                                                      }
          |RETURN Expr_comma SEMI {$$ = newnode(Return, NULL); addchild($$, $2);}
          |RETURN SEMI {$$ = newnode(Return, NULL); addchild($$, newnode(Null, NULL));}
          ;

Expr_call: Expr_call COMMA Expr {$$ = $1; addBrother($$, $3); LOCATE($3, @1.first_line, @1.first_column);}
          |Expr {$$ = $1; LOCATE($$, @1.first_line, @1.first_column);}
          ;

Expr_comma: Expr_comma COMMA Expr {$$ = newnode(Comma, NULL); LOCATE($$, @2.first_line, @2.first_column);
                                   addchild($$, $1); 
                                   addchild($$, $3);}
           |Expr {$$ = $1;}
           ;

Expr:    IDENTIFIER LPAR error RPAR {$$ = newnode(Error, NULL);}
        |LPAR error RPAR {$$ = newnode(Error, NULL);}
        |Expr ASSIGN Expr {$$ = newnode(Store, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr PLUS Expr {$$ = newnode(Add, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr MINUS Expr {$$ = newnode(Sub, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr MUL Expr {$$ = newnode(Mul, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr DIV Expr {$$ = newnode(Div, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr MOD Expr {$$ = newnode(Mod, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr OR Expr {$$ = newnode(Or, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr AND Expr {$$ = newnode(And, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr BITWISEAND Expr {$$ = newnode(BitWiseAnd, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr BITWISEOR Expr {$$ = newnode(BitWiseOr, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr BITWISEXOR Expr {$$ = newnode(BitWiseXor, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr EQ Expr {$$ = newnode(Eq, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr NE Expr {$$ = newnode(Ne, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr LE Expr {$$ = newnode(Le, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr GE Expr {$$ = newnode(Ge, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr LT Expr {$$ = newnode(Lt, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |Expr GT Expr {$$ = newnode(Gt, NULL); addchild($$, $1); addchild($$, $3);LOCATE($$, @2.first_line, @2.first_column);}
        |PLUS Expr %prec NOT {$$ = newnode(Plus, NULL); addchild($$, $2);LOCATE($$, @1.first_line, @1.first_column);} 
        |MINUS Expr %prec NOT {$$ = newnode(Minus, NULL); addchild($$, $2);LOCATE($$, @1.first_line, @1.first_column);}
        |NOT Expr {$$ = newnode(Not, NULL); addchild($$, $2);LOCATE($$, @1.first_line, @1.first_column);}
        |IDENTIFIER LPAR RPAR {$$ = newnode(Call, NULL); addchild($$, newnode(Identifier, $1)); LOCATE(getchild($$, 0), @1.first_line, @1.first_column);}
        |IDENTIFIER LPAR Expr_call RPAR {$$ = newnode(Call, NULL); addchild($$, newnode(Identifier, $1)); addchild($$, $3); LOCATE(getchild($$, 0), @1.first_line, @1.first_column);}
        |IDENTIFIER {$$ = newnode(Identifier, $1); LOCATE($$, @1.first_line, @1.first_column);}
        |NATURAL {$$ = newnode(Natural, $1);LOCATE($$, @1.first_line, @1.first_column);}
        |CHRLIT {$$ = newnode(Chrlit, $1);LOCATE($$, @1.first_line, @1.first_column);}
        |DECIMAL {$$ = newnode(Decimal, $1);LOCATE($$, @1.first_line, @1.first_column);}
        |LPAR Expr_comma RPAR {$$ = $2;}
        ;