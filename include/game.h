/*
 * Realiza principais atividades do jogo
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Velha.h"

#define LIVRE 'L'
#define X 'X'
#define O 'O'
#define FPS 30
#define W 80
#define H 80
#define DIM 82
#define MIN 4
#define MAX 9

// Inicializa o Jogo e configura GUI 
void start(int N, int J);

// Inicializa GUI
void iniciaVelha(Velha *velha, SDL_Surface *tela, int N);

// Registra Jogadas
int jogada(Velha *velha, int *mouse, int *turno, int N, int J);

// Verifica sttatus da celula
void statusCelula(Velha *velha, int *mouse, SDL_Surface *tela, int N);

// Verifica se ha ganhadores
char checaVitoria(Velha *v, int N);
