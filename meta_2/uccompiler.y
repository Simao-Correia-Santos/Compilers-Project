%{
  #include <stdio.h>
  extern int yylex(void);
  void yyerror(char *);
  extern char *yytext;
%}

%token BITWISEAND BITWISEOR BITWISEXOR AND ASSIGN MUL COMMA DIV EQ GE GT LBRACE LE LPAR LT MINUS MOD NE NOT OR PLUS RBRACE RPAR SEMI
%token IDENTIFIER DECIMAL NATURAL CHRLIT

%%
FuctionsAndDeclarations: FuctionsAndDeclarations {;}
                        |FuctionDefinition {;}
                        | FuctionDeclaration {;}
                        | Declaration {;}

FuctionDefinition: TypeSpec FuctionDeclarator FuctionBody {;}

FuctionBody: LBRACE DeclarationAndStatements RBRACE {;}

DeclarationAndStatements: Statement DeclarationAndStatements {;}
                         |Declaration DeclarationAndStatements {;}
                         |Statement {;}
                         |Declaration {;}

FuctionDeclaration: TypeSpec FuctionDeclarator SEMI {;}

FuctionDeclarator: IDENTIFIER LPAR ParamaterList RPAR {;}

ParameterList: ParameterDeclaration {;}
              |COMMA ParameterDeclaration {;}

ParameterDeclaration: TypeSpec IDENTIFIER {;}

Declaration: TypeSpec Declarator COMMA Declarator SEMI {;}

TypeSpec: CHAR {;}
         |INT {;}
         |VOID {;}
         |SHORT {;}
         |DOUBLE {;}

Declarator: IDENTIFIER ASSIGN Expr {;}

Statement: Expr SEMI {;}

Statement: LBRACE Statement RBRACE {;}

Statement: IF LPAR Expr RPAR Statement ELSE Statement {;}

Statement: WHILE LPAR Expr RPAR Statement {;}

Statement: RETURN Expr SEMI {;}

Expr: Expr ASSIGN| COMMA Expr {;}

Expr: Expr PLUS|MINUS|MUL|DIV|MOD Expr {;}

Expr: Expr OR|AND|BITWISEAND|BITWISEOR|BITWISEXOR Expr {;}

Expr: Expr EQ|NE|LE|GE|LT|GT Expr {;}

Expr: PLUS|MINUS|NOT Expr {;}

Expr: IDENTIFIER LPAR Expr COMMA Expr RPAR {;}

Expr: IDENTIFIER|NATURAL|CHRLIT|DECIMAL|LPAR Expr RPAR {;}



%%
void yyerror(char *error) {
    printf("%s '%s', line: %d, column: %d\n", error, yytext, line, column);
}