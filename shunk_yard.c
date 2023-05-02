//
// Created by mestan on 1.05.2023.
//

#include "token.h"
#include "structs.h"
#include <string.h>
#include <stdlib.h>

struct Queue* shunk_yard(struct element* p_el,struct element* p_ass_var){
    struct StackNode* root = NULL;
    struct Queue* queue = createQueue(MAX);

    while(p_el->type != 0 || p_el->value != 0){
        int type = p_el->type;
        if(type == EL_NUMBER || type == EL_VARIABLE){
            enqueue(queue,*p_el);
        }
        else if(type== EL_OPERATOR){

            if(isEmpty(root) == 1){
                push(&root,*p_el);
            } else if(peek(root).type==EL_BRACKET_OPEN){
                push(&root,*p_el);
            }
            else{
                struct element peek_el= peek(root);
                if(peek_el.opr > p_el->opr){
                    enqueue(queue,pop(&root));
                    push(&root,*p_el);
                }
                else {push(&root,*p_el);}

            }
        }
        else if(type == EL_BITOPR){
            push(&root,*p_el);
        }
        else if(type== EL_BRACKET_OPEN){
            push(&root,*p_el);
        }
        else if(type== EL_BRACKET_CLOSE){
            while(peek(root).type != EL_BRACKET_OPEN){
                enqueue(queue,pop(&root));
            }
            pop(&root);
        }
        else if(type== EL_EQUALS){
            struct element ass_var = dequeue(queue);
            if(qIsEmpty(queue)!=1){
                return NULL ;
            }
            *p_ass_var = ass_var;
        }
        *p_el++;
    }
    if(isEmpty(root) != 1){
        while(isEmpty(root)!=1){
            enqueue(queue,pop(&root));
        }
    }

    return queue;
}