#pragma once

#define MAXSIZE 6

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef struct{
    char data[MAXSIZE];
    int n;
}Stack;


/* Inicia a pilha */
void init_stack(Stack* stack);

/* Verifica se está vazia*/
bool is_empty(Stack* stack);

/* Retorna o topo da pilha*/
char top(Stack* stack);

/* Empilha */
void push(Stack* stack, char value);

/* Desempilha */
void pop(Stack* stack);
