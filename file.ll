; ModuleID = 'advcalc2ir'
 declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%x  = alloca i32 
%1 = add i32 1 ,0 
store i32 %1 , i32* %x 
%y  = alloca i32 
%2 = load i32,i32* %x 
%3 = add i32 3 ,0 
%4 = add i32 %2, %3 
store i32 %4 , i32* %y 
%z  = alloca i32 
%5 = load i32,i32* %x 
%6 = load i32,i32* %y 
%7 = load i32,i32* %y 
%8 = load i32,i32* %y 
%9 = mul i32 %7, %8 
%10 = mul i32 %6, %9 
%11 = mul i32 %5, %10 
store i32 %11 , i32* %z 
%12 = load i32,i32* %z 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %12 ) 
%14 = load i32,i32* %x 
%15 = load i32,i32* %x 
%16 = xor i32 %14, %15 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %16 ) 
%18 = load i32,i32* %x 
%19 = load i32,i32* %x 
%20 = xor i32 %18, %19 
%21 = load i32,i32* %z 
%22 = or i32 %20, %21 
%23 = load i32,i32* %y 
%24 = add i32 %22, %23 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %24 ) 
%26 = load i32,i32* %x 
%27 = load i32,i32* %x 
%28 = xor i32 %26, %27 
%29 = load i32,i32* %z 
%30 = or i32 %28, %29 
%31 = load i32,i32* %y 
%32 = add i32 %30, %31 
%33 = add i32 1 ,0 
%34 = ashr i32 %32, %33 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %34 ) 
%36 = load i32,i32* %x 
%37 = load i32,i32* %x 
%38 = xor i32 %36, %37 
%39 = load i32,i32* %z 
%40 = or i32 %38, %39 
%41 = load i32,i32* %y 
%42 = add i32 %40, %41 
%43 = add i32 1 ,0 
%44 = ashr i32 %42, %43 
%45 = add i32 1 ,0 
%46 = shl i32 %44, %45 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %46 ) 
ret i32 0
}