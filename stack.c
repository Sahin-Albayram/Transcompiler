//
// Created by mestan on 1.05.2023.
//
#include "structs.h"
#include "token.h"


typedef struct StackNode{
    struct element data;
    struct StackNode* next;
};

struct StackNode* newNode(struct element data){
    struct StackNode* stackNode =
            (struct StackNode*)
                    malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(struct StackNode* root)
{
    return !root;
}
void push(struct StackNode** root, struct element data)
{
    struct StackNode* stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

struct element pop(struct StackNode** root)
{
    struct element empty_el;
    empty_el.type = -666;
    if (isEmpty(*root))
        return empty_el;
    struct StackNode* temp = *root;
    *root = (*root)->next;
    struct element popped = temp->data;
    free(temp);

    return popped;
}

struct element peek(struct StackNode* root)
{
    struct element empty_el;
    empty_el.type = -666;
    if (isEmpty(root))
        return empty_el;
    return root->data;
}
