#ifndef CIRCULOS_H
#define CIRCULOS_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>



typedef struct Circulo {
  float x, y, raio;
  float r, g, b;
} Circulo;

void desenha_circulo(Circulo C);
bool circulos_colidem(Circulo C1, Circulo C2);
void apaga_circulo(Circulo C);

#endif
