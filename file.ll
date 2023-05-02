; ModuleID = 'advcalc2ir'
 declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%a  = alloca i32 
%1 = add i32 8 ,0 
store i32 %1 , i32* %a 
%b  = alloca i32 
%2 = add i32 8 ,0 
%3 = load i32,i32* %a 
%4 = add i32 6 ,0 
%5 = sub i32 %3, %4 
%6 = mul i32 %2, %5 
store i32 %6 , i32* %b 
%c  = alloca i32 
%7 = load i32,i32* %b 
%8 = add i32 6 ,0 
%9 = add i32 %7, %8 
store i32 %9 , i32* %c 
%10 = load i32,i32* %a 
%11 = add i32 2 ,0 
%12 = shl i32 %10, %11 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %12 ) 
%14 = load i32,i32* %b 
%15 = load i32,i32* %a 
%16 = add i32 1 ,0 
%17 = add i32 17 ,0 
%18 = add i32 %16, %17 
%19 = sub i32 %15, %18 
%20 = xor i32 %14, %19 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %20 ) 
%y  = alloca i32 
%22 = add i32 2 ,0 
%23 = load i32,i32* %b 
%24 = mul i32 %22, %23 
%25 = load i32,i32* %c 
%26 = sub i32 %24, %25 
store i32 %26 , i32* %y 
%27 = load i32,i32* %y 
%28 = add i32 2 ,0 
%29 = ashr i32 %27, %28 
%30 = load i32,i32* %c 
%31 = xor i32 %30, -1 
%32 = xor i32 %29, %31 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %32 ) 
ret i32 0
}