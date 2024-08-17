#include "circulos.h"



void desenha_circulo(Circulo C) {
  al_draw_filled_circle(C.x, C.y, C.raio, al_map_rgb_f(C.r, C.g, C.b));

}

bool circulos_colidem(Circulo C1, Circulo C2){
    float d = sqrt((C1.x - C2.x)*(C1.x - C2.x) + (C1.y - C2.y) * (C1.y - C2.y));
    return d <= C1.raio + C2.raio;
}

void apaga_circulo(Circulo C){
        al_draw_filled_circle(C.x, C.y, C.raio, al_map_rgb(150, 150, 200));
    }
