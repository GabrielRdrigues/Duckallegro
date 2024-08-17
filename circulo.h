#pragma once
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct{
    float x, y, raio;
    int r, g, b;
    }circulo;


    bool circulos_colidem(circulo C1, circulo C2);
