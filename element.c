//
// Created by mestan on 23.04.2023.
//

#include "token.h"
#include "structs.h"
#include <string.h>
#include <stdlib.h>

int ruleChecker(int type,int lastType,int blank);
int bitwiseCheck(char name[]);

double elementCreator(struct token *p_t, struct element *p_el, char *p_var, double *p_val) {
    int blank = 0, bracketCount = 0, type = 0, value = 0, equalChecker = 0;
    int lastType = -1;
    char tempVar[MAX] = {}, tempNum[MAX] = {};
    char *P_var = p_var;
    double *P_val = p_val;
    char *dt;
    while (p_t->type != 0 || p_t->value != 0) {
        type = p_t->type;
        if(type== T_BLANK){
            blank = 1;
            *p_t++;
            continue;
        }
        if (type == T_EQUALS) {
            equalChecker++;
            if (equalChecker == 2) {
                return -1;
            }
        }
        if(type == T_COMA){
            p_el->type = EL_COMA;
            *p_el++;
        }
        if (type == T_BRACKET_OPEN) bracketCount++;
        if (type == T_BRACKET_CLOSE) bracketCount--;
        if (bracketCount < 0) return -1;


        value = p_t->value;
        if (ruleChecker(type, lastType, blank) == 0) return -1;

        if (lastType != T_NUMBER && type == T_NUMBER) {   // _ Num
            strcpy(tempNum, "");
            strncat(tempNum, &p_t->value, 1);
        }
        if (lastType == T_NUMBER && type == T_NUMBER) { //Num Num
            strncat(tempNum, &p_t->value, 1);
        }
        if (lastType == T_NUMBER && type != T_NUMBER) { //Num _
            p_el->type = EL_NUMBER;
            p_el->value = strtod(tempNum, &dt);
            *p_el++;
        }
        if (lastType != T_LETTER && type == T_LETTER) {   // _ Letter
            strcpy(tempVar, "");
            strncat(tempVar, &p_t->value, 1);
        }
        if (lastType == T_LETTER && type == T_LETTER) { //Letter Letter
            strncat(tempVar, &p_t->value, 1);
        }
        if (lastType == T_LETTER && type != T_LETTER && type != T_BRACKET_OPEN) { //Letter _
            p_el->type = EL_VARIABLE;
            p_var = P_var;
            p_val = P_val;
            for (int i = 0; i < MAX; i++) {
                if (*p_var == '\0') {
                    if (equalChecker == 1) {
                        strcpy(p_var, tempVar);
                        p_el->opr = i;
                        p_el->value = '\0';
                        break;
                    } else {
                        return -1;
                    }
                }
                if (strcmp(p_var, tempVar)==0) {
                    p_el->value = *p_val;
                    p_el->opr = i;
                    break;
                }
                p_var = p_var + MAX;
                *p_val++;
            }
            *p_el++;
        }

        if (lastType == T_LETTER && type == T_BRACKET_OPEN && blank == 0) { //Letter( - Potential bitwise opperation
            int bit_opp = bitwiseCheck(tempVar);
            if (bit_opp == -666) {
                return -1;
            }
            p_el->type = EL_BITOPR;
            p_el->bit_opr = bit_opp;
            *p_el++;
        }
        if (type == T_BRACKET_OPEN) { // += (
            p_el->type = EL_BRACKET_OPEN;
            *p_el++;
        }
        if (type == T_OPERATOR) {
            p_el->type = EL_OPERATOR;
            if (p_t->value == 43) {
                p_el->opr = EL_OP_PLUS;
            } else if (p_t->value == 42) {
                p_el->opr = EL_OP_MUL;
            } else if (p_t->value == 45) {
                p_el->opr = EL_OP_SUB;
            } else if (p_t->value == 38) {
                p_el->opr = EL_OP_AND;
            } else if (p_t->value == 124) {
                p_el->opr = EL_OP_OR;
            } else if (p_t->value == 47){
                p_el->opr = EL_OP_DIV;
            }
            *p_el++;
        }
        if (type == T_EQUALS) {
            p_el->type = EL_EQUALS;
            *p_el++;
        }

        if (type == T_BRACKET_CLOSE) {
            p_el->type = EL_BRACKET_CLOSE;
            *p_el++;
        }
        *p_t++;
        lastType = type;
        blank = 0;


    }
    if (type == T_EQUALS) return -1;
    if (type == T_NUMBER) {
        p_el->type = EL_NUMBER;
        p_el->value = strtod(tempNum, &dt);
        *p_el++;
    }
    if (type == T_LETTER) {
        p_el->type = EL_VARIABLE;

        p_var = P_var;
        p_val = P_val;
        for (int i = 0; i < MAX; i++) {
            if (*p_var == '\0') {
                return -1;
            }
        if (strcmp(p_var, tempVar)==0) {
            p_el->value = *p_val;
            p_el->opr = i;
            break;
        }
        p_var += MAX;
        *p_val++;
        }
        *p_el++;
    }
    if (bracketCount != 0) return -1;
    return 0;
}
// T_BLANK 0
// T_NUMBER 1
// T_LETTER 2
//T_BRACKET_OPEN 3
//T_EQUALS 4
//T_OPERATOR 5
//T_BRACKET_CLOSE 6
// T_COMA 7
int ruleChecker(int type, int lastType, int blank) {
    int ruleArray[] = {111, 221, 550, 551, 360, 361, 210, 211, 120, 121,
                       450, 451, 541, 540, 650, 651, 530, 531, 310, 311, 321,
                       740,741,470,471,750,751,570,571,491,490,391,390,
                       690,691,290,291,590,591,670,671,370,371};

    int status = 100 * type + 10 * lastType + blank;
    for (int i = 0; i < (sizeof(ruleArray) / sizeof(ruleArray[0])); i++) {
        if (status == ruleArray[i]) return 0;
    }

    return 1;
}

int bitwiseCheck(char name[]){                     // bitwise operation type decidier

    if (strcmp(name, "xor") == 0) {
        return EL_BIT_OPXOR;
    } else if (strcmp(name, "ls") == 0) {
        return EL_BIT_OPLS;
    } else if (strcmp(name, "rs") == 0) {
        return EL_BIT_OPRS;
    } else if (strcmp(name, "lr") == 0) {
        return EL_BIT_OPLR;
    } else if (strcmp(name, "rr") == 0) {
        return EL_BIT_OPRR;
    } else if (strcmp(name, "not") == 0) {
        return EL_BIT_OPNOT;
    }
    return -666;

}
