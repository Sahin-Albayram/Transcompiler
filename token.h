//
// Created by mestan on 21.04.2023.
//

#include "structs.h"

#ifndef HW2_TOKEN_H
#define HW2_TOKEN_H



#define MAX 256
#define T_BLANK 0
#define T_NUMBER 1
#define T_LETTER 2
#define T_BRACKET_OPEN 3
#define T_EQUALS 4
#define T_OPERATOR 5
#define T_BRACKET_CLOSE 6
#define T_COMA 7

#define EL_COMA 100
#define EL_VARIABLE 101
#define EL_NUMBER 102
#define EL_OPERATOR 103
#define EL_BITOPR 104
#define EL_EQUALS 105
#define EL_BRACKET_OPEN 106
#define EL_BRACKET_CLOSE 107
#define EL_OP_LLVM 108
#define EL_LLVM_EMPTY 109
#define EL_OP_PLUS -1
#define EL_OP_SUB 0
#define EL_OP_MUL 1
#define EL_OP_DIV 2
#define EL_OP_AND 3
#define EL_OP_OR 4



#define EL_BIT_OPXOR 22
#define EL_BIT_OPLS 33
#define EL_BIT_OPRS 44
#define EL_BIT_OPLR 55
#define EL_BIT_OPRR 66
#define EL_BIT_OPNOT 77
#define EL_NONE -1

int tokenize(char *string, struct token *t);
double elementCreator(struct token *p_t, struct element *p_el, char *p_var, double *p_val);


struct StackNode* newNode(struct element data);
int isEmpty(struct StackNode* root);
void push(struct StackNode** root, struct element data);
struct element pop(struct StackNode** root);
struct element peek(struct StackNode* root);

struct Queue* createQueue(unsigned capacity);
int isFull(struct Queue* queue);
int qIsEmpty(struct Queue* queue);
void enqueue(struct Queue* queue, struct element item);
struct element dequeue(struct Queue* queue);
struct element front(struct Queue* queue);
struct element rear(struct Queue* queue);



struct Queue* shunk_yard(struct element* p_el,struct element* p_ass_var);
int llivm(FILE* fw,struct Queue* postfix_queue,char* p_var,double* p_val,int * p_var_def,int* p_llivm);







#endif //HW2_TOKEN_H
