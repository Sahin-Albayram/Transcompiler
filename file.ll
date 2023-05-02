; ModuleID = 'advcalc2ir'
 declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%x  = alloca i32 
%1 = add i32 3 ,0 
store i32 %1 , i32* %x 
%y  = alloca i32 
%2 = add i32 5 ,0 
store i32 %2 , i32* %y 
%zvalue  = alloca i32 
%3 = add i32 23 ,0 
%4 = load i32,i32* %x 
%5 = add i32 1 ,0 
%6 = load i32,i32* %y 
%7 = add i32 %5, %6 
%8 = mul i32 %4, %7 
%9 = add i32 %3, %8 
store i32 %9 , i32* %zvalue 
%10 = load i32,i32* %zvalue 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %10 ) 
%k  = alloca i32 
%12 = load i32,i32* %x 
%13 = load i32,i32* %y 
%14 = load i32,i32* %zvalue 
%15 = sub i32 %13, %14 
%16 = sub i32 %12, %15 
store i32 %16 , i32* %k 
%17 = load i32,i32* %x 
%18 = add i32 3 ,0 
%19 = load i32,i32* %y 
%20 = add i32 1 ,0 
%21 = add i32 2 ,0 
%22 = add i32 5 ,0 
%23 = add i32 %21, %22 
%24 = mul i32 %20, %23 
%25 = mul i32 %19, %24 
%26 = mul i32 %18, %25 
%27 = add i32 %17, %26 
store i32 %27 , i32* %k 
%28 = load i32,i32* %k 
%29 = add i32 1 ,0 
%30 = add i32 %28, %29 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %30 ) 
ret i32 0
}