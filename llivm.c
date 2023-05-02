//
// Created by mestan on 1.05.2023.
//
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "structs.h"

char* getBitCode(struct element el_opr);


int llivm(FILE* fw,struct Queue* postfix_queue,char* p_var,double* p_val,int* p_var_def,int* p_llivm){
    char* P_var = p_var;
    double* P_val = p_val;
    int* P_var_def = p_var_def;

    struct element el1 = {};
    struct element el2 = {};
    struct element el_opr;
    struct element arr[MAX]={};
    struct element* p_arr = &arr[0];

    while(*p_var !='\0'){    // declaration check part

        if(*p_var_def==0){
            fprintf(fw,"%c%s %s",37,p_var," = alloca i32 \n");
            *p_var_def =1;
        }
        p_var = p_var + MAX;
        *p_var_def++;
    }
    while(qIsEmpty(postfix_queue)!=1){
        *p_arr = dequeue(postfix_queue);
        *p_arr++;
    }
    p_arr = &arr[0];
    for(int i=0;i<MAX;i++){    // Iteration over postfix array

        if(arr[i].type == EL_LLVM_EMPTY){ // If current cell is empty go next
            continue;
        }
        if(arr[i].value==0 &arr[i].type==0){ // If cell is value 0 type 0 then end of story
            break;
        }



        if(arr[i].type==EL_VARIABLE){ // If current cell is variable element we will create a new llivm variable that holds value of it
            struct element el;
            el.type = EL_OP_LLVM;
            el.value = arr[i].value;
            el.llivm_idx = *p_llivm;

            char* p_fvar = P_var;
            p_fvar = p_fvar + MAX * arr[i].opr;
            fprintf(fw,"%c%d = load i32,i32* %c%s \n",37,el.llivm_idx,37,p_fvar);  // example: %0 = load i32,i32*, %x
            *p_llivm = *p_llivm +1;
            arr[i] = el;

        } else if(arr[i].type == EL_NUMBER){  // If current cell is Number element we will create a new llivm variable that holds value of it in order to maintain order in next steps
            struct element el;                // All cells should contain llivm variable element.
            el.type = EL_OP_LLVM;
            el.value = arr[i].value;
            el.llivm_idx = *p_llivm;
            fprintf(fw, "%c%d = add i32 %d ,0 \n",37,el.llivm_idx,(int)el.value);  // example: store i32 23, i32* %1
            arr[i] = el;
            *p_llivm = *p_llivm +1;
        }

        if(arr[i].type==EL_OPERATOR || arr[i].type==EL_BITOPR){    // Now things go crazy If current cell is operation then we should do operation
            el_opr = arr[i];

            if(el_opr.bit_opr == EL_BIT_OPLR || el_opr.bit_opr == EL_BIT_OPRR){ // rotate operations need their own implementation therefore they need special part.

            }
            else {
                if(el_opr.bit_opr == EL_BIT_OPNOT){
                    fprintf(fw,"%c%d = xor i32 %c%d, -1 \n",37,*p_llivm,37,el2.llivm_idx);
                    el1.type=0;                                         //Reset el1 and el2 holders to make them ready to hold other operation values.
                    el1.value=0;
                    el2.type = 0;
                    el2.value = 0;
                    arr[el2.arr_idx].type = EL_OP_LLVM;   // Result variable should stay on element1
                    arr[el2.arr_idx].llivm_idx= *p_llivm;
                    arr[i].type = EL_LLVM_EMPTY;
                    i = 0;
                    *p_llivm = *p_llivm +1;
                }
                else {
                    char *bit_code = getBitCode(el_opr);                // Detect which operation will we do
                    fprintf(fw, "%c%d = %s i32 %c%d, %c%d \n", 37, *p_llivm, bit_code, 37, el1.llivm_idx, 37,
                            el2.llivm_idx);  // Operation example: %2 = mul i32, %0, %1
                    el1.type = 0;                                         //Reset el1 and el2 holders to make them ready to hold other operation values.
                    el1.value = 0;
                    el2.type = 0;
                    el2.value = 0;
                    arr[el1.arr_idx].type = EL_OP_LLVM;   // Result variable should stay on element1
                    arr[el1.arr_idx].llivm_idx = *p_llivm;
                    arr[el2.arr_idx].type = EL_LLVM_EMPTY;// Empty used elements on array  example: 23 x 1 y * + +  ==>  23 x L2 _ _ + +
                    arr[i].type = EL_LLVM_EMPTY;
                    i = 0;
                    *p_llivm = *p_llivm + 1;
                }
            }

        }

        if(el1.type == 0 && el1.value == 0){ // If el1 does not hold any value current element will be value that holded by el1
            el1 = arr[i];
            el1.arr_idx = i;

        }else if(el2.type == 0 && el2.value == 0){ // Same for el2
            el2 = arr[i];
            el2.arr_idx = i;
        }
        else {
            el1 = el2;
            el2 = arr[i];
            el2.arr_idx = i;
        }


    }
    if(el1.type != 0 || el1.value != 0){
        return el1.llivm_idx;
    }


    return -1;
}

char* getBitCode(struct element el_opr){
    int type;
    if(el_opr.type == EL_OPERATOR){
        type = el_opr.opr;

    }else {
        type = el_opr.bit_opr;
    }


    if(type == EL_OP_PLUS){
        return "add";
    }
    else if(type == EL_OP_SUB){
        return "sub";
    }
    else if(type == EL_OP_MUL){
        return "mul";
    }
    else if(type == EL_OP_AND){
        return "and";
    }
    else if(type == EL_OP_DIV){
        return "sdiv";
    }
    else if(type == EL_OP_OR){
        return "or";
    }
    else if(type == EL_BIT_OPXOR){
        return "xor";
    }
    else if(type == EL_BIT_OPLS){
        return "shl";
    }
    else if(type == EL_BIT_OPRS){
        return "ashr";

    }else return "FAIL";

}
