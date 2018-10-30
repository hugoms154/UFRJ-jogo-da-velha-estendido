#include "libs/game.h"

/* Verifica se ha ganhador */
char checaVitoria(Velha *v, int N){
  char ref;
  int cont;

  // Verifica colunas
  for(int x=0; x<N; x++){
    ref = v[N*x].status;
    cont = 0;
    for(int y=0; y<N; y++){
      int i = (N*x) + y;
      if(v[i].status == ref){
        cont++;
      }
    }
    if((ref == X || ref == O) && cont == N){
      return ref;
    }
  }
  // Verifica linhas
  for(int y=0; y<N; y++){
    ref = v[y].status;
    cont = 0;
    for(int x=0; x<N; x++){
      int i = (N*x) + y;
      if(v[i].status == ref){
        cont++;
      }
    }
    if((ref == X || ref == O) && cont == N){
      return ref;
    }
  }
  return ref;
}
void start(int N, int J){
    printf("\nJogo Inicializado!\n");

    SDL_Init(SDL_INIT_EVERYTHING); // Inicia a Tela
    SDL_Surface *tela,*xis,*bola;  // Elementos do jogo

    tela = SDL_SetVideoMode(DIM*N,DIM*N,32,SDL_SWSURFACE); // Configura Tela
    xis = SDL_LoadBMP("img/xis.bmp"); // Carrega iamgem do Xis
    bola = SDL_LoadBMP("img/bola.bmp"); // Carrega iamgem da Bola

    // Renderiza imagens
    SDL_SetColorKey(xis,SDL_SRCCOLORKEY,SDL_MapRGB(tela->format,0,255,0));
    SDL_SetColorKey(bola,SDL_SRCCOLORKEY, SDL_MapRGB(tela->format,0,255,0));

    int running = 1; // Variavel de Controle
    int turno=0, fimJogo=0; // Variaveis Auxiliares
    const int fps = FPS;  // Taxa de Frames por Segundo
    int mouse[2]; // Vetor para posicao do mouse
    Uint32 start; // Tempo de Inicializacao
    Velha velha[N*N]; // Vertor de celulas, onde celula = velha[i]

    iniciaVelha(velha, tela, N);

   //aqui começa o loop do jogo e do SDL.
    while(running){
        start = SDL_GetTicks();
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT: // Botão de encerrar programa
                {
                        printf("Programa encerrado!\n");
                        running=0;
                        break;
                }
                case SDL_MOUSEMOTION: //capta o movimento do mouse.
                {
                        mouse[0]=event.motion.x;
                        mouse[1]=event.motion.y;
                        statusCelula(velha, mouse, tela, N);
                        break;
                }
                case SDL_MOUSEBUTTONDOWN://capta o clique do mouse.
                {
                    mouse[0]=event.button.x;
                    mouse[1]=event.button.y;
                    jogada(velha, mouse, &turno, N);

                    fimJogo = checaVitoria(velha, N);
                    if(turno >= (2*N)-1)
                    {
                        if(fimJogo == X)
                        {
                            printf("Fim de jogo jogador X ganhou!\n");
                            running = 0;
                        }
                        else if(fimJogo == O)
                        {
                            printf("Fim de jogo jogador O ganhou!\n");
                            running=0;
                        }
                    }
                    else if(turno==(N*N)-1 && fimJogo==LIVRE)
                    {
                        printf("Fim de jogo o jogo empatou!");
                            running=0;
                    }
                    break;
                }
            }
        }
        //logica e redenrização
        for(int i = 0; i<N*N; i++){
            if(velha[i].status == X){
                SDL_BlitSurface(xis,NULL,tela,&velha[i].rect);
            } else if(velha[i].status == O){
                SDL_BlitSurface(bola,NULL,tela, &velha[i].rect);
            }
        }
        SDL_Flip(tela);
        if((1000/fps)>SDL_GetTicks()-start)
            SDL_Delay(1000/fps-(SDL_GetTicks()-start));
    }
    getchar();
    SDL_FreeSurface(xis);
    SDL_FreeSurface(bola);
    SDL_Quit();
}
/* Funcao que monta o tabuleiro */
void iniciaVelha(Velha *velha, SDL_Surface *tela, int N){
    // Pecorre vetor inicialicando celulas
    for(int x=0, cont=0; x<82*N; x+=82){
        for(int y=0; y<82*N; y+=82, cont++){
            velha[cont].rect.x=x;
            velha[cont].rect.y=y;
            velha[cont].rect.w=W;
            velha[cont].rect.h=H;
            velha[cont].status=LIVRE;
            velha[cont].color=SDL_MapRGB(tela->format,0xff,0xff,0xff);
        }
    }
    // Renderiza Celulas
    for(int i=0; i<N*N; i++){
            SDL_FillRect(tela,&velha[i].rect, velha[i].color);
    }
}
// Faz uma Jogada
void jogada(Velha *velha, int *mouse, int *turno, int N){
  // Precisa pecorre lista anotando posições  na matris
    int i, x, y; // Variaveis Auxiliares
    x = mouse[0]/DIM;
    y = mouse[1]/DIM;

    i = (N*x) + y; // Formula para identificar celula clicada

    if(*turno%2 && velha[i].status==LIVRE){
      // Marca celula como O
        printf("Jogada Valida, jogador O!\n");
        velha[i].status=O;
        *turno=*turno+1;
    } else if (velha[i].status==LIVRE){
      // Marca celula como X
        printf("Jogada Valida, jogador X!\n");
        velha[i].status=X;
        *turno=*turno+1;
    } else {
        printf("Jogada invalida, posicao ja registrada! favor escolher outra.\n");
    }
}
/* Altera cor da Celula */
void statusCelula(Velha *velha, int *mouse, SDL_Surface *tela, int N)
{
    Uint32 color; // Componente da cor
    int i, xi, yi; // Variaveis Auxiliares
    xi = mouse[0]/DIM;
    yi = mouse[1]/DIM;

    i = (N*xi) + yi; // Formula para identificar celula clicada

    // Destaca a celula selecionada
    if((mouse[0] || mouse[1]) && velha[i].status==LIVRE){
        color=SDL_MapRGB(tela->format,0x00,0xff,0xff);
        SDL_FillRect(tela,&velha[i].rect,color);
    }
    // Desstaca a selula ja marcada
    else if((mouse[0] || mouse[1]) && velha[i].status!=LIVRE){
        color=SDL_MapRGB(tela->format,0xff,0x00,0x00);
        SDL_FillRect(tela,&velha[i].rect,color);
    }
    // Limpa selulas nao selecionadas
    for(int x=0; x<N*N; x++){
      if(i!=x){
        color=SDL_MapRGB(tela->format,0xff,0xff,0xff);
        SDL_FillRect(tela,&velha[x].rect,color);
      }
    }
}
//int main(void){
//	return 0;
//}
