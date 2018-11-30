#include "include/game.h"
#include "include/menu.h"

void clrscr(){system("@cls||clear");} //Limpa tela do console

//Descricao: Menu principal do programa
void menu(){
	printf("\nMenu Inicializado!\n");
	//Ponteiros
	int *dim, *players;							//*Ponteiro para a dimensao do tabuleiro e quantidade de jogares
	dim = (int *) malloc(sizeof(int));		//Aloca o tamanho de memoria para o ponteiro *dim
	players = (int *) malloc(sizeof(int));		//Aloca o tamanho de memoria para o ponteiro *players

	if(*dim<4||*dim>9){*dim = 4;} 				//Inicializa os ponteiros para os menores valores possiveis
	if(*players<1||*players>2){*players = 2;}

	//Variaveis
	char str[] = 								//String de opcoes do jogo
"Jogo da velha\n \
Digite o numero correspondente a opcao\n \
[1] Iniciar jogo\n \
[2] Configuracoes \n \
[0] Sair do jogo\n";
	int op = -1;								//Variavel de controle do menu

	//Execucao
	do{
		clrscr();								//Limpa a tela do console
		puts(str);
		printf(" -> ");						//Escreve na tela as opcoes disponiveis
		scanf("%i", &op);						//Le a opcao desejada
		switch(op){								//Avalia em qual caso a opcao se encaixa
			case 1: start(*dim, *players); break;		//Comando de inicializacao do jogo
			case 2: confg(players, dim); break;	//Abre menu de configuracoes do jogo
			case 0: break;						//Opcao de saida do jogo
			default: puts("Opcao invalida");	//Mensagem padrao para opcao invalida
		}
	}while(op!=0);
}

/*	Descricao: Menu de configurações do programa
	Entrada: Dois ponteiros: numero de jogares (players) e dimensao do tabuleiro(dim) */
void confg(int *players, int *dim){
	char str[256];
	int op = -1;
	int aux = 0;

	do{
		sprintf(str,							//Formata a string do menu de configuracoes para ser apresentada ao usuario
"Jogo da velha - CONFIGURACOES\n \
Digite o numero correspondente a opcao\n \
[1] Dimensao do tabuleiro [atual: %i]\n \
[2] Numero de jogadores [atual: %i]\n \
[0] Voltar ao menu principal\n",
*dim, *players);
		clrscr();								//Limpa a tela do console
		puts(str);								//Escreve na tela as opcoes disponiveis
		printf(" -> ");
		scanf("%i", &op);						//Le a opcao desejada
		switch(op){
			case 1:
				do{
					clrscr();
					printf("Digite a dimensao desejada\nDeve ser um valor igual ou maior que 4 e menor ou igual a 9\nNumero atual [%i]\n -> ", *dim);
					scanf("%i", &aux);
				}while(aux < 4 || aux > 9);
				*dim = aux;
				break;
			case 2:
				do{
					clrscr();
					printf("Digite o numero de jogares\nDeve ser um valor igual ou maior que 1 e menor ou igual a 2\nNumero atual [%i]\n -> ", *players);
					scanf("%i", &aux);
				}while(aux < 1 || aux > 2);
				*players = aux;
				break;
			case 0: break;
			default: puts("opcao invalida");
		}
	}while(op!=0);
}