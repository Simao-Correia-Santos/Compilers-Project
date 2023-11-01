digit [0-9]
letter [a-zA-Z]
reserved "++"|"--"|"["|"]"|"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"long"|"register"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"_Packed"|"_Bool"|"_Complex"|"_Imaginary"|"inline"|"restrict"
white_spaces " "|"\n"|"\t"|"\r"|"\n\r"
error .
scape_sequence '\\([nt\\'\"]|[0-7]?[0-7]?[0-7])'

%{  
    #include <string.h>
    #include "y.tab.h"
    int yyparse(void);

    int tokens = 0;
    int row = 1;
    int column = 0;
    int row_com, column_com, row_char, column_char;
    char buffer[1024];

    void toUpper(char* string, int len){
        for (int i = 0; i < len; i++){
            *(string+i) = *(string+i) - ('a' - 'A');
        }
    }

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

{reserved}                                         { if(tokens) printf("RESERVED(%s)\n", yytext); }

"char"                                             { toUpper(yytext, yyleng); printf("%s\n", yytext); return CHAR; }
"else"                                             { toUpper(yytext, yyleng); printf("%s\n", yytext); return ELSE; }
"while"                                            { toUpper(yytext, yyleng); printf("%s\n", yytext); return WHILE; }
"if"                                               { toUpper(yytext, yyleng); printf("%s\n", yytext); return IF; }
"int"                                              { toUpper(yytext, yyleng); printf("%s\n", yytext); return INT; }
"short"                                            { toUpper(yytext, yyleng); printf("%s\n", yytext); return SHORT; }
"double"                                           { toUpper(yytext, yyleng); printf("%s\n", yytext); return DOUBLE; }
"return"                                           { toUpper(yytext, yyleng); printf("%s\n", yytext); return RETURN; }
"void"                                             { toUpper(yytext, yyleng); printf("%s\n", yytext); return VOID; }

"&"                                                { if(tokens) printf("BITWISEAND\n"); return BITWISEAND; }
"|"                                                { if(tokens) printf("BITWISEOR\n"); return BITWISEOR; }
"^"                                                { if(tokens) printf("BITWISEXOR\n"); return BITWISEOR; }
"&&"                                               { if(tokens) printf("AND\n"); return AND; }
"="                                                { if(tokens) printf("ASSIGN\n"); return ASSIGN; }
"*"                                                { if(tokens) printf("MUL\n"); return MUL; }
","                                                { if(tokens) printf("COMMA\n"); return COMMA; }
"/"                                                { if(tokens) printf("DIV\n"); return DIV; }
"=="                                               { if(tokens) printf("EQ\n"); return EQ; }
">="                                               { if(tokens) printf("GE\n"); return GE; }
">"                                                { if(tokens) printf("GT\n"); return GT; }
"{"                                                { if(tokens) printf("LBRACE\n"); return LBRACE; }
"<="                                               { if(tokens) printf("LE\n"); return LE; }
"("                                                { if(tokens) printf("LPAR\n"); return LPAR; }
"<"                                                { if(tokens) printf("LT\n"); return LT;}
"-"                                                { if(tokens) printf("MINUS\n"); return MINUS; }
"%"                                                { if(tokens) printf("MOD\n"); return MOD; }
"!="                                               { if(tokens) printf("NE\n"); return NE; }
"!"                                                { if(tokens) printf("NOT\n"); return NOT; }
"||"                                               { if(tokens) printf("OR\n"); return OR; }
"+"                                                { if(tokens) printf("PLUS\n"); return PLUS; }
"}"                                                { if(tokens) printf("RBRACE\n"); return RBRACE; }
")"                                                { if(tokens) printf("RPAR\n"); return RPAR; }
";"                                                { if(tokens) printf("SEMI\n"); return SEMI; }


({letter}|"_")+({letter}|{digit}|"_")*             { if(tokens) printf("IDENTIFIER(%s)\n", yytext); return IDENTIFIER; }

{digit}+                                           { if(tokens) printf("NATURAL(%s)\n", yytext); return NATURAL; }

(({digit}*"."{digit}+)|({digit}+"."?{digit}*))([eE][+-]?{digit}+)? { if(tokens) printf("DECIMAL(%s)\n", yytext); return DECIMAL; } 


{scape_sequence}|'[^"\n"'\\]'|'\"'                 { if(tokens) printf("CHRLIT(%s)\n", yytext); return CHRLIT; }

'                                                  { BEGIN CHAR; buffer[0] = '\0'; strcat(buffer, yytext); row_char = row; column_char = column; }
<CHAR>'                                            { BEGIN 0; strcat(buffer, yytext); printf("Line %d, column %d: invalid char constant (%s)\n", row_char, column_char, buffer); }
<CHAR><<EOF>>                                      { printf("Line %d, column %d: unterminated char constant\n", row_char, column_char); BEGIN 0; }
<CHAR>"\n"                                         { printf("Line %d, column %d: unterminated char constant\n", row_char, column_char); column = 0; row += 1; BEGIN 0; }
<CHAR>\\['\\\"]                                    { strcat(buffer, yytext); }
<CHAR>.                                            { strcat(buffer, yytext); }

{error}                                            { printf("Line %d, column %d: unrecognized character (%s)\n", row, column, yytext);}



%%
extern int yylex();
int main(int argc, char const *argv[]) {
    if (argc > 1 && strcmp(argv[1], "-l") == 0){
        tokens = 1;
    }
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}
