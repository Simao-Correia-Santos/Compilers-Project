digit [0-9]
letter [a-zA-Z]
reserved "++"|"--"|"["|"]"|"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"long"|"register"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"_Packed"|"_Bool"|"_Complex"|"_Imaginary"|"inline"|"restrict"
white_spaces " "|"\n"|"\t"|"\r"|"\r\n"
error .
scape_sequence '\\([nt\\'\"]|[0-7]?[0-7]?[0-7])'

%option noyywrap

%{  
    #include <string.h>
    #include "y.tab.h"
    #include "ast.h"
    #include "semantics.h"
    #include "codegen.h"
    #define PASS_TOKEN() yylval.lexeme = strdup(yytext);

    int yyparse(void);
    int tokens = 0;
    int pass_tokens = 0;
    int row = 1;
    int column = 1;
    int syntax_errors = 0;
    int semantic_errors = 0;
    int row_com, column_com, row_char, column_char;
    char buffer[1024];
    extern struct node *program;
    int syn_line = 1, syn_column = 1;

    #define YY_USER_ACTION {syn_line = yylloc.first_line = row; syn_column = yylloc.first_column = column;}
%}

%X CHAR COMMENT_1 COMMENT_2

%%
"/*"                                               { BEGIN COMMENT_1; row_com = row; column_com = column; column += yyleng;}
<COMMENT_1>.                                       { column += yyleng; }
<COMMENT_1>"\n"                                    { column = 1; row += 1;}
<COMMENT_1>"*/"                                    { column += yyleng; BEGIN 0; }
<COMMENT_1><<EOF>>                                 { printf("Line %d, column %d: unterminated comment\n", row_com, column_com); column += yyleng; BEGIN 0;}

"//"                                               { column += yyleng; BEGIN COMMENT_2; }
<COMMENT_2>.                                       { column += yyleng; }
<COMMENT_2>"\n"                                    { column = 1; row += 1; BEGIN 0; }

{white_spaces}                                     { if (*yytext == '\n') {column = 1; row += 1;} else column += yyleng;}

{reserved}                                         {column += yyleng; if(tokens) printf("RESERVED(%s)\n", yytext); PASS_TOKEN(); if(pass_tokens) return RESERVED; }

"char"                                             {column += yyleng; if(tokens) printf("CHAR\n"); if(pass_tokens) return CHR; }
"else"                                             {column += yyleng; if(tokens) printf("ELSE\n"); if(pass_tokens) return ELSE; }
"while"                                            {column += yyleng; if(tokens) printf("WHILE\n"); if(pass_tokens) return WHILE; }
"if"                                               {column += yyleng; if(tokens) printf("IF\n"); if(pass_tokens) return IF; }
"int"                                              {column += yyleng; if(tokens) printf("INT\n"); if(pass_tokens) return INT; }
"short"                                            {column += yyleng; if(tokens) printf("SHORT\n"); if(pass_tokens) return SHORT; }
"double"                                           {column += yyleng; if(tokens) printf("DOUBLE\n"); if(pass_tokens) return DOUBLE; }
"return"                                           {column += yyleng; if(tokens) printf("RETURN\n"); if(pass_tokens) return RETURN; }
"void"                                             {column += yyleng; if(tokens) printf("VOID\n"); if(pass_tokens) return VOID; }

"&"                                                {column += yyleng; if(tokens) printf("BITWISEAND\n"); if(pass_tokens) return BITWISEAND; }
"|"                                                {column += yyleng; if(tokens) printf("BITWISEOR\n"); if(pass_tokens) return BITWISEOR; }
"^"                                                {column += yyleng; if(tokens) printf("BITWISEXOR\n"); if(pass_tokens) return BITWISEXOR; }
"&&"                                               {column += yyleng; if(tokens) printf("AND\n"); if(pass_tokens) return AND; }
"="                                                {column += yyleng; if(tokens) printf("ASSIGN\n"); if(pass_tokens) return ASSIGN; }
"*"                                                {column += yyleng; if(tokens) printf("MUL\n"); if(pass_tokens) return MUL; }
","                                                {column += yyleng; if(tokens) printf("COMMA\n"); if(pass_tokens) return COMMA; }
"/"                                                {column += yyleng; if(tokens) printf("DIV\n"); if(pass_tokens) return DIV; }
"=="                                               {column += yyleng; if(tokens) printf("EQ\n"); if(pass_tokens) return EQ; }
">="                                               {column += yyleng; if(tokens) printf("GE\n"); if(pass_tokens) return GE; }
">"                                                {column += yyleng; if(tokens) printf("GT\n"); if(pass_tokens) return GT; }
"{"                                                {column += yyleng; if(tokens) printf("LBRACE\n"); if(pass_tokens) return LBRACE; }
"<="                                               {column += yyleng; if(tokens) printf("LE\n"); if(pass_tokens) return LE; }
"("                                                {column += yyleng; if(tokens) printf("LPAR\n"); if(pass_tokens) return LPAR; }
"<"                                                {column += yyleng; if(tokens) printf("LT\n"); if(pass_tokens) return LT;}
"-"                                                {column += yyleng; if(tokens) printf("MINUS\n"); if(pass_tokens) return MINUS; }
"%"                                                {column += yyleng; if(tokens) printf("MOD\n"); if(pass_tokens) return MOD; }
"!="                                               {column += yyleng; if(tokens) printf("NE\n"); if(pass_tokens) return NE; }
"!"                                                {column += yyleng; if(tokens) printf("NOT\n"); if(pass_tokens) return NOT; }
"||"                                               {column += yyleng; if(tokens) printf("OR\n"); if(pass_tokens) return OR; }
"+"                                                {column += yyleng; if(tokens) printf("PLUS\n"); if(pass_tokens) return PLUS; }
"}"                                                {column += yyleng; if(tokens) printf("RBRACE\n"); if(pass_tokens) return RBRACE; }
")"                                                {column += yyleng; if(tokens) printf("RPAR\n"); if(pass_tokens) return RPAR; }
";"                                                {column += yyleng; if(tokens) printf("SEMI\n"); if(pass_tokens) return SEMI; }


({letter}|"_")+({letter}|{digit}|"_")*             {column += yyleng; if(tokens) printf("IDENTIFIER(%s)\n", yytext); PASS_TOKEN(); if(pass_tokens) return IDENTIFIER; }

{digit}+                                           {column += yyleng; if(tokens) printf("NATURAL(%s)\n", yytext); PASS_TOKEN(); if(pass_tokens) return NATURAL; }

(({digit}*"."{digit}+)|({digit}+"."?{digit}*))([eE][+-]?{digit}+)? {column += yyleng; if(tokens) printf("DECIMAL(%s)\n", yytext); PASS_TOKEN(); if(pass_tokens) return DECIMAL; } 


{scape_sequence}|'[^"\n"'\\]'|'\"'                 {column += yyleng; if(tokens) printf("CHRLIT(%s)\n", yytext); PASS_TOKEN(); if(pass_tokens) return CHRLIT; }

'                                                  { BEGIN CHAR; buffer[0] = '\0'; strcat(buffer, yytext); row_char = row; column_char = column; column += yyleng;}
<CHAR>'                                            { BEGIN 0; strcat(buffer, yytext); printf("Line %d, column %d: invalid char constant (%s)\n", row_char, column_char, buffer); column += yyleng;}
<CHAR><<EOF>>                                      { printf("Line %d, column %d: unterminated char constant\n", row_char, column_char); column += yyleng; BEGIN 0; }
<CHAR>"\n"                                         { printf("Line %d, column %d: unterminated char constant\n", row_char, column_char); column = 1; row += 1; BEGIN 0; }
<CHAR>\\['\\\"]                                    { strcat(buffer, yytext); column += yyleng;}
<CHAR>.                                            { strcat(buffer, yytext); column += yyleng;}

<<EOF>>                                            {if (column > 1) syn_column += 1; return 0;}

{error}                                            { printf("Line %d, column %d: unrecognized character (%s)\n", row, column, yytext); column += yyleng;}



%%
extern int yylex();

void yyerror(char *error) {
    syntax_errors += 1;
    printf("Line %d, column %d: %s: %s\n", syn_line, syn_column, error, yytext);
}

int main(int argc, char const *argv[]) {
    if (argc > 1 && strcmp(argv[1], "-l") == 0){
        tokens = 1;
        yylex();
    }
    else if (argc > 1 && strcmp(argv[1], "-t") == 0){
        pass_tokens = 1;
        yyparse();
        if (syntax_errors == 0){
            show_ast_tree(program, 0); 
        }
    }
    else if (argc > 1 && strcmp(argv[1], "-s") == 0){
        pass_tokens = 1;
        yyparse();
        if (syntax_errors == 0){
            check_program(program);
            show_symbol_table();
            show_ast_tree(program, 0);
        }
    }
    else {
        pass_tokens = 1;
        yyparse();
        if (syntax_errors == 0){
            check_program(program);
            if (semantic_errors == 0){
                codegen_program(program);
            }
        }
    }
    deallocate_memory(program);    
    return 0;
}
