; ModuleID = 'advcalc2ir'
 declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%1 = add i32 10 ,0 
%2 = add i32 3 ,0 
%RT1 = sub i32 32, %2 
%RT2 = shl i32 %1, %2 
%RT3 = lshr i32 %1, %RT1 
%3 = or i32 %RT2 ,%RT3 
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %2 ) 
ret i32 0
}