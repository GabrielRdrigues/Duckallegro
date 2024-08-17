#include "stack.h"



void init_stack(Stack* stack){
    stack->n=0;
}

bool is_empty(Stack* stack){
    return stack->n==0;
}

char top(Stack* stack){
    assert(!is_empty(stack));
    return stack->data[stack->n-1];
}

void push(Stack* stack, char value){
    assert(stack->n < MAXSIZE);
    stack->data[stack->n++] = value;
}

void pop(Stack* stack){
    assert(!is_empty(stack));
    stack->n--;
}

