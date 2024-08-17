#include "circulo.h"


    bool circulos_colidem(circulo C1, circulo C2){
        float d = hypot(C1.x - C2.x, C1.y - C2.y);
        return d <= C1.raio + C2.raio;
    }
