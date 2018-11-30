/*
 * Tipo_Velha forma células da matriz
 */
 
//#define TIPO_VELHA_H
#include <SDL/SDL.h>

typedef struct {
        SDL_Rect rect;
        Uint32 color;
        char status;
} Velha;
