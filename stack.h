#pragma once

#define MAXSIZE 6

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct{
    int data[MAXSIZE];
    int n;
}Stack;


/* Inicia a pilha */
void init_stack(Stack* stack);

/* Verifica se está vazia*/
bool is_empty(Stack* stack);

/* Retorna o topo da pilha*/
int top(Stack* stack);

/* Empilha */
void push(Stack* stack, int value);

/* Desempilha */
void pop(Stack* stack);
