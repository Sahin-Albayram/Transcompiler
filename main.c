#include <stdio.h>
#include "token.h"
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    char variables[128][MAX] = {};  // char array that holds variable names
    double variable_value[128] = {}; // double array for variable values
    int variables_def[128]={0};

    char *p_var = &variables[0][0];     // variable pointer
    double *p_val = &variable_value[0]; // value pointer




    int len;                            //variable for len of input
    int bool_equal;                     // =1 if input contains "="

    FILE *fw;
    FILE *fp;
    size_t * line = NULL;
    size_t len_line = 0;
    ssize_t read;

    char wfilename[] = "/Users/mestan/CLionProjects/CmpE230/hw2/file.ll";
    char filename[] = "/Users/mestan/CLionProjects/CmpE230/hw2/bo.adv";    //argv[1]
    int llivm_count = 1;
    int* p_llivm = &llivm_count;
    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    int line_count = 1;
    fw = fopen(wfilename, "w");
    if (fw == NULL)
        exit(EXIT_FAILURE);
    fprintf(fw,"; ModuleID = 'advcalc2ir'\n declare i32 @printf(i8*, ...)\n"
               "@print.str = constant [4 x i8] c\"%cd\\0A\\00\"\n"
               "\n"
               "define i32 @main() {\n",37);
    while ((read = getline(&line, &len_line, fp)) != -1) {// This while loop continues while there is another line

        struct token tokens[128] = {};
        struct token* p_t = &tokens;

        struct element elements[MAX] = {};
        struct element* p_el = &elements;



        char * c = line;

        int loop = strlen(line);
        for(int i=0;i<loop;i++){     // This loop for inline tokenizing.
            if((int)(*c) == 10) continue;
            int token_status = tokenize(c,p_t);
            if(token_status == 0){
                printf("Error on line %d!\n ",line_count);

                return 0;
            }
            *p_t++;    // Increase token pointer
            *c++;       // Go next char
        }
        int check = elementCreator(&tokens,&elements,&variables[0][0],&variable_value[0]);
        if (check == -1){
            printf("Error on line %d!\n ",line_count);
            return 0;
        }
        struct element ass_var;//elementize tokens
        ass_var.type =0;
        ass_var.value = 0;
        struct element* p_ass_var = &ass_var;
        struct Queue* postfix_queue =  shunk_yard(&elements,p_ass_var);

        int result_idx = llivm(fw,postfix_queue,&variables[0][0],&variable_value[0],&variables_def,p_llivm);
        if(p_ass_var->type !=0 || p_ass_var->value !=0){
            fprintf(fw,"store i32 %c%d , i32* %c%s \n",37,result_idx,37,variables[p_ass_var->opr]);
        }
        else{
            fprintf(fw,"call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %c%d ) \n",37,result_idx);
            llivm_count = llivm_count +1;
        }








        line_count++;
    }
    fprintf(fw,"ret i32 0\n"
               "}");
    fclose(fp);
    fclose(fw);



    return 0;
}
