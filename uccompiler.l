digit [0-9]
letter [a-zA-Z]
keyword "char"|"else"|"while"|"if"|"int"|"short"|"double"|"return"|"void"
reserved "++"|"--"|"["|"]"|"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"long"|"register"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"_Packed"|"_Bool"|"_Complex"|"_Imaginary"|"inline"|"restrict"
white_spaces " "|"\n"|"\t"|"\r"
error .
scape_sequence '\\([nt\\'\"]|[0-7]?[0-7]?[0-7])'

%{  
    #include <string.h>

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

{reserved}                                         { printf("RESERVED(%s)\n", yytext); }

{keyword}                                          { toUpper(yytext, yyleng); printf("%s\n", yytext); }

"&"                                                { printf("BITWISEAND\n"); }
"|"                                                { printf("BITWISEOR\n"); }
"^"                                                { printf("BITWISEXOR\n"); }
"&&"                                               { printf("AND\n"); }
"="                                                { printf("ASSIGN\n"); }
"*"                                                { printf("MUL\n"); }
","                                                { printf("COMMA\n"); }
"/"                                                { printf("DIV\n"); }
"=="                                               { printf("EQ\n"); }
">="                                               { printf("GE\n"); }
">"                                                { printf("GT\n"); }
"{"                                                { printf("LBRACE\n"); }
"<="                                               { printf("LE\n"); }
"("                                                { printf("LPAR\n");}
"<"                                                { printf("LT\n"); }
"-"                                                { printf("MINUS\n"); }
"%"                                                { printf("MOD\n"); }
"!="                                               { printf("NE\n"); }
"!"                                                { printf("NOT\n"); }
"||"                                               { printf("OR\n"); }
"+"                                                { printf("PLUS\n"); }
"}"                                                { printf("RBRACE\n"); }
")"                                                { printf("RPAR\n"); }
";"                                                { printf("SEMI\n"); }


({letter}|"_")+({letter}|{digit}|"_")*             { printf("IDENTIFIER(%s)\n", yytext); }

{digit}+                                           { printf("NATURAL(%s)\n", yytext); }

(({digit}*"."{digit}+)|({digit}+"."?{digit}*))([eE][+-]?{digit}+)? { printf("DECIMAL(%s)\n", yytext);} 


{scape_sequence}|'[^"\n"'\\]'|'\"'                  { printf("CHRLIT(%s)\n", yytext); }

'                                                { BEGIN CHAR; buffer[0] = '\0'; strcat(buffer, yytext); row_char = row; column_char = column; }
<CHAR>'                                          { BEGIN 0; strcat(buffer, yytext); printf("Line %d, column %d: invalid char constant (%s)\n", row_char, column_char, buffer); }
<CHAR>["\n"<<EOF>>]                              { BEGIN 0; printf("Line %d, column %d: unterminated char constant\n", row_char, column_char); column = 0; row += 1; }
<CHAR>\\['\\\"]                                    { strcat(buffer, yytext); }
<CHAR>.                                            { strcat(buffer, yytext); }

{error}                                            { printf("Line %d, column %d: unrecognized character (%s)\n", row, column, yytext);}



%%
extern int yylex();
int main() {
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}
