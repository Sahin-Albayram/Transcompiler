//
// Created by mestan on 21.04.2023.
//

#ifndef HW2_STRUCTS_H
#define HW2_STRUCTS_H
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct token {
    int type;
    int value;
};

typedef struct element{
    int type;
    int opr;
    int bit_opr;
    double value;
    int llivm_idx;
    int arr_idx;
};






#endif //HW2_STRUCTS_H
