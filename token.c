//
// Created by mestan on 21.04.2023.
//
#include "token.h"
#include "structs.h"

int tokenize(char *string, struct token *t) {                   // Tokenize step of each char. Main point is comparing char result with
    int e = (int) (*string);
    int status = 0;

    if ((65 <= e && 90 >= e) || (97 <= e && 122 >= e)) {
        t->type = T_LETTER;
        t->value = e;
        status = 1;
    } else if (e == 37) {
        t->type = -1;
        t->value = e;
        status = -1;
    } else if (e == 44) {
        t->type = T_COMA;
        t->value = e;
        status = 1;
    } else if (e == 32) {
        t->type = T_BLANK;
        t->value = e;
        status = 1;
    } else if (e == 42 || e == 43 || e == 45 || e == 47 || e == 38 || e == 124) {
        t->type = T_OPERATOR;
        t->value = e;
        status = 1;
    } else if (e == 40) {
        t->type = T_BRACKET_OPEN;
        t->value = e;
        status = 1;
    } else if (e == 41) {
        t->type = T_BRACKET_CLOSE;
        t->value = e;
        status = 1;
    } else if (e == 61) {
        t->type = T_EQUALS;
        t->value = e;
        status = 1;
    } else if (e >= 48 && e <= 57) {
        t->type = T_NUMBER;
        t->value = e;
        status = 1;
    }

    return status;      // status =0 if unknown symbol

}
