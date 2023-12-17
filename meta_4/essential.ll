declare i32 @putchar(i32)
declare i32 @getchar()


@global_char = global i32 '\000'
@global_char1 = global i32 '\377'
@global_char2 = global i32 '\4'
@global_char3 = global i32 '\44'
@global_char4 = global i32 '\344'
@global_a = global i32 'A'
@global_b = global i32 'B'
@global_c = global i32 'C'
@global_d = global double 4.0

define i32 @main(){
%1 = alloca i32
store i32 'D', i32* %1
%2 = alloca i32
store i32 'E', i32* %2
%3 = alloca i32
store i32 'F', i32* %3
%4 = alloca double
store double 4.0, double* %4
%5 = alloca i32
store i32 %5, 
store i32 %5, 
store i32 %5, i32 %1
store i32 %1, 
%9 = load i32

store i32 %1, i32 %5
store i32 %5, i32 %2
store i32 %2, 
%13 = load i32

store i32 %2, i32 %5
store i32 %5, i32 %3
store i32 %3, 
%17 = load i32

store i32 %3, i32 %5
store i32 %1, i32 %1
store i32 %2, 
store i32 %3, 
}