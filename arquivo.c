#include "arquivo.h"

void Init_Highscore(int* highscore){
    FILE* f = fopen("highscore.txt","r");
    if(fscanf(f,"%d",highscore)==0)
        highscore=0;
    fclose(f);
}


void LerHighscore(int pontos){
    FILE* f = fopen("highscore.txt", "r");
    int auxiliar;
    if (fscanf(f, "%d", &auxiliar) == 1){
        if (pontos > auxiliar){
            fclose(f);
            f = fopen("highscore.txt", "w");
            fprintf(f,"%d", pontos);
        }
    }else {
        fclose(f);
        f = fopen("highscore.txt", "w");
        fprintf(f,"%d", pontos);
    }
    fclose(f);

}
