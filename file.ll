; ModuleID = 'advcalc2ir'
 declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%siu  = alloca i32 
%1 = add i32 11 ,0 
store i32 %1 , i32* %siu 
%siuuu  = alloca i32 
%2 = add i32 7 ,0 
store i32 %2 , i32* %siuuu 
%3 = load i32,i32* %siu 
%4 = load i32,i32* %siuuu 
%5 = sdiv i32 %3, %4 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %5 ) 
%7 = load i32,i32* %siu 
%8 = load i32,i32* %siuuu 
%9 = mul i32 %7, %8 
store i32 %9 , i32* %siu 
%10 = load i32,i32* %siu 
%11 = load i32,i32* %siu 
%12 = sub i32 %10, %11 
%13 = load i32,i32* %siu 
%14 = load i32,i32* %siu 
%15 = load i32,i32* %siu 
%16 = sdiv i32 %14, %15 
%17 = mul i32 %13, %16 
%18 = add i32 %12, %17 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %18 ) 
ret i32 0
}