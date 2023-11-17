digit [0-9]
letter [a-zA-Z]
reserved "++"|"--"|"["|"]"|"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"long"|"register"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"_Packed"|"_Bool"|"_Complex"|"_Imaginary"|"inline"|"restrict"
white_spaces " "|"\n"|"\t"|"\r"|"\n\r"
error .
scape_sequence '\\([nt\\'\"]|[0-7]?[0-7]?[0-7])'

%option noyywrap

%{  
    #include <string.h>
    #include "y.tab.h"
    #include "ast.h"
    #define PASS_TOKEN() yylval.lexeme = strdup(yytext);

    int yyparse(void);
    int tokens = 0;
    int pass_tokens = 0;
    int row = 1;
    int column = 0;
    int syntax_errors = 0;
    int row_com, column_com, row_char, column_char;
    char buffer[1024];
    extern struct node *program;

    #define YY_USER_ACTION { column += yyleng; }
%}

%X CHAR COMMENT_1 COMMENT_2

%%
"/*"                                               { BEGIN COMMENT_1; row_com = row; column_com = column;}
<COMMENT_1>.                                       { ; }
<COMMENT_1>"\n"                                    { column = 0; row += 1; }
<COMMENT_1>"*/"                                    { BEGIN 0; }
<COMMENT_1><<EOF>>                                 { printf("Line %d, column %d: unterminated comment\n", row_com, column_com-1); BEGIN 0;}

"//"                                               { BEGIN COMMENT_2; }
<COMMENT_2>.                                       { ; }
<COMMENT_2>"\n"                                    { column = 0; row += 1; BEGIN 0; }

{white_spaces}                                     { if (*yytext == '\n') {column = 0; row += 1;}; }

{reserved}                                         { if(tokens) printf("RESERVED(%s)\n", yytext); PASS_TOKEN(); if(pass_tokens) return RESERVED;}

"char"                                             { if(tokens) printf("CHAR\n"); if(pass_tokens) return CHR; }
"else"                                             { if(tokens) printf("ELSE\n"); if(pass_tokens) return ELSE; }
"while"                                            { if(tokens) printf("WHILE\n"); if(pass_tokens) return WHILE; }
"if"                                               { if(tokens) printf("IF\n"); if(pass_tokens) return IF; }
"int"                                              { if(tokens) printf("INT\n"); if(pass_tokens) return INT; }
"short"                                            { if(tokens) printf("SHORT\n"); if(pass_tokens) return SHORT; }
"double"                                           { if(tokens) printf("DOUBLE\n"); if(pass_tokens) return DOUBLE; }
"return"                                           { if(tokens) printf("RETURN\n"); if(pass_tokens) return RETURN; }
"void"                                             { if(tokens) printf("VOID\n"); if(pass_tokens) return VOID; }

"&"                                                { if(tokens) printf("BITWISEAND\n"); if(pass_tokens) return BITWISEAND; }
"|"                                                { if(tokens) printf("BITWISEOR\n"); if(pass_tokens) return BITWISEOR; }
"^"                                                { if(tokens) printf("BITWISEXOR\n"); if(pass_tokens) return BITWISEXOR; }
"&&"                                               { if(tokens) printf("AND\n"); if(pass_tokens) return AND; }
"="                                                { if(tokens) printf("ASSIGN\n"); if(pass_tokens) return ASSIGN; }
"*"                                                { if(tokens) printf("MUL\n"); if(pass_tokens) return MUL; }
","                                                { if(tokens) printf("COMMA\n"); if(pass_tokens) return COMMA; }
"/"                                                { if(tokens) printf("DIV\n"); if(pass_tokens) return DIV; }
"=="                                               { if(tokens) printf("EQ\n"); if(pass_tokens) return EQ; }
">="                                               { if(tokens) printf("GE\n"); if(pass_tokens) return GE; }
">"                                                { if(tokens) printf("GT\n"); if(pass_tokens) return GT; }
"{"                                                { if(tokens) printf("LBRACE\n"); if(pass_tokens) return LBRACE; }
"<="                                               { if(tokens) printf("LE\n"); if(pass_tokens) return LE; }
"("                                                { if(tokens) printf("LPAR\n"); if(pass_tokens) return LPAR; }
"<"                                                { if(tokens) printf("LT\n"); if(pass_tokens) return LT;}
"-"                                                { if(tokens) printf("MINUS\n"); if(pass_tokens) return MINUS; }
"%"                                                { if(tokens) printf("MOD\n"); if(pass_tokens) return MOD; }
"!="                                               { if(tokens) printf("NE\n"); if(pass_tokens) return NE; }
"!"                                                { if(tokens) printf("NOT\n"); if(pass_tokens) return NOT; }
"||"                                               { if(tokens) printf("OR\n"); if(pass_tokens) return OR; }
"+"                                                { if(tokens) printf("PLUS\n"); if(pass_tokens) return PLUS; }
"}"                                                { if(tokens) printf("RBRACE\n"); if(pass_tokens) return RBRACE; }
")"                                                { if(tokens) printf("RPAR\n"); if(pass_tokens) return RPAR; }
";"                                                { if(tokens) printf("SEMI\n"); if(pass_tokens) return SEMI; }


({letter}|"_")+({letter}|{digit}|"_")*             { if(tokens) printf("IDENTIFIER(%s)\n", yytext); PASS_TOKEN(); if(pass_tokens) return IDENTIFIER; }

{digit}+                                           { if(tokens) printf("NATURAL(%s)\n", yytext); PASS_TOKEN(); if(pass_tokens) return NATURAL; }

(({digit}*"."{digit}+)|({digit}+"."?{digit}*))([eE][+-]?{digit}+)? { if(tokens) printf("DECIMAL(%s)\n", yytext); PASS_TOKEN(); if(pass_tokens) return DECIMAL; } 


{scape_sequence}|'[^"\n"'\\]'|'\"'                 { if(tokens) printf("CHRLIT(%s)\n", yytext); PASS_TOKEN(); if(pass_tokens) return CHRLIT; }

'                                                  { BEGIN CHAR; buffer[0] = '\0'; strcat(buffer, yytext); row_char = row; column_char = column; }
<CHAR>'                                            { BEGIN 0; strcat(buffer, yytext); printf("Line %d, column %d: invalid char constant (%s)\n", row_char, column_char, buffer); }
<CHAR><<EOF>>                                      { printf("Line %d, column %d: unterminated char constant\n", row_char, column_char); BEGIN 0; }
<CHAR>"\n"                                         { printf("Line %d, column %d: unterminated char constant\n", row_char, column_char); column = 0; row += 1; BEGIN 0; }
<CHAR>\\['\\\"]                                    { strcat(buffer, yytext); }
<CHAR>.                                            { strcat(buffer, yytext); }

<<EOF>>                                            {column += 1; return 0;}

{error}                                            { printf("Line %d, column %d: unrecognized character (%s)\n", row, column, yytext);}



%%
extern int yylex();

void yyerror(char *error) {
    syntax_errors += 1;
    printf("Line %d, column %d: %s: %s\n", row, column-yyleng+1, error, yytext);
}

int main(int argc, char const *argv[]) {
    if (argc > 1 && strcmp(argv[1], "-l") == 0){
        tokens = 1;
        yylex();
    }
    if (argc > 1 && strcmp(argv[1], "-t") == 0){
        pass_tokens = 1;
        yyparse();
        if (syntax_errors == 0){
            show_ast_tree(program, 0); 
        }
    }
    if (argc == 1){
        pass_tokens = 1;
        yyparse();
    }
    deallocate_memory(program);    
    return 0;
}