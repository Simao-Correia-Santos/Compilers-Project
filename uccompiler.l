digit [0-9]
letter [a-zA-Z]
keyword "char"|"else"|"while"|"if"|"int"|"short"|"double"|"return"|"void"
reserved "++"|"--"|"["|"]"|"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"enum"|"extern"|"float"|"for"|"goto"|"long"|"register"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"_Packed"
white_spaces " "|"\n"|"\t"
error .

%{
    int row = 1;
    int column = 0;

    void toUpper(char* string, int len){
        for (int i = 0; i < len; i++){
            *(string+i) = *(string+i) - ('a' - 'A');
        }
    }

    #define YY_USER_ACTION { column += yyleng; }
%}

%X CHAR COMMENT_1 COMMENT_2

%%
"/*"                                               { BEGIN COMMENT_1; }
<COMMENT_1>.                                       { column = 0; row += 1; }
<COMMENT_1>"\n"                                    { ; }
<COMMENT_1>"*/"                                    { BEGIN 0; }
<COMMENT_1><<EOF>>                                 { printf("Line %d, column %d: unterminated comment\n", row, column); BEGIN 0;}

"//"                                               { BEGIN COMMENT_2; }
<COMMENT_2>.                                       { ; }
<COMMENT_2>"\n"                                    { column = 0; row += 1; BEGIN 0; }

{white_spaces}                                     { if (*yytext == '\n') {column = 0; row += 1;}; }

{reserved}                                         { printf("%s\n", yytext); }

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

{digit}*("."{digit}+?)?([eE][+-]?{digit}+)?        { printf("DECIMAL(%s)\n", yytext); }

"'"\\([nt\\'\"]|[0-7]?[0-7]?[0-7])"'"              { printf("CHRLIT(%s)\n", yytext); }
"'"[^'"\n"<<EOF>>]*"'"                             { printf("Line %d, column %d: invalid char constant (%s)\n", row, column-yyleng+1, yytext); }
"'"[^'"\n"<<EOF>>]*["\n"<<EOF>>]                   { printf("Line %d, column %d: unterminated char constant\n", row, column-yyleng+1); column = 0; row += 1; }

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
