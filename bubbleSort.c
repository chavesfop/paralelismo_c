#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define QTDARRAY 500
#define TAMARRAY 500

//variaveis globais
pthread_t threads[QTDARRAY];
int ordenar[QTDARRAY][TAMARRAY];
clock_t tclock[8]; 
//clock[0-1] -> montar a matriz com numeros aleatorios
//clock[2-3] -> ordenação das matrizes
//clock[4-5] -> exibir a matriz inicial
//clock[6-7] -> exibir a matriz final ordenada

//prototipo de funcoes
void exibeMatriz();
void exibeTempos();
void *bubbleSort(void *arg);

int main (int argc, char **argv) {
	printf("===================================================================================================\n");
	printf("=======================ORDENACAO DE MATRIZ ALEATORIA COM BUBBLE SORT===============================\n");
	printf("---------------------------------------------------------------------------------------------------\n");
	//inicializa matriz com numeros aleatorios
	tclock[0] = clock();
	for (int i = 0; i < QTDARRAY; i++){
		for (int j = 0; j < TAMARRAY; j++){
			ordenar[i][j] = rand() % 90 + 10;
		}
	}
	tclock[1] = clock();

	tclock[4] = clock();
	//exibeMatriz(ordenar);
	tclock[5] = clock();	

	//inicia threads de ordenação
	tclock[2] = clock();
	for (int i = 0; i < QTDARRAY; i++){
		int *arg = malloc(sizeof(*arg));
		*arg = i;
		pthread_create(&(threads[i]), NULL, bubbleSort, arg);
	}

	//realiza join das threads
	for (int i = 0; i < QTDARRAY; i++){
		pthread_join(threads[i], NULL);
	}
	tclock[3] = clock();
	
	tclock[6] = clock();
	//exibeMatriz(ordenar);
	tclock[7] = clock();
	exibeTempos();
	printf("===================================================================================================\n\n\n");
}

void exibeTempos(){
	int qtd, tam;
	qtd = QTDARRAY;
	tam = TAMARRAY;
        double tempos[4]; 
	tempos[0] = (tclock[1] - tclock[0]) * 1000.0 / CLOCKS_PER_SEC;
	tempos[1] = (tclock[3] - tclock[2]) * 1000.0 / CLOCKS_PER_SEC;
	tempos[2] = (tclock[5] - tclock[4]) * 1000.0 / CLOCKS_PER_SEC;
	tempos[3] = (tclock[7] - tclock[6]) * 1000.0 / CLOCKS_PER_SEC;
	printf("Quantidade de arrays/thread: %i\n", qtd);
	printf("Tamanho dos arrays: %i\n\n", tam);
	printf("Tempo para montar a matriz aleatoria: %g ms\n", tempos[0]);
	printf("Tempo para ordenar a matriz: %g ms\n", tempos[1]);
	printf("Tempo para exibir matriz inicial: %g ms\n", tempos[2]);
	printf("Tempo para exibir matriz final: %g ms\n", tempos[3]);
}

void exibeMatriz(){
	for (int i = 0; i < QTDARRAY; i++){
		for (int j = 0; j < TAMARRAY; j++){
			printf("[%d,%d] = %d |", i, j, ordenar[i][j]);
		}
		printf("\n");
	}
	printf("================================================\n");
}

void *bubbleSort(void *iarg){
	int i = *((int *) iarg);
	int aux;
	for (int k = 1; k < TAMARRAY; k++){
		for (int j = 0; j < TAMARRAY-1; j++){
			if (ordenar[i][j] > ordenar[i][j+1]) {
				aux = ordenar[i][j];
				ordenar[i][j] = ordenar[i][j+1];
				ordenar[i][j+1] = aux;
			}
		}
	}
	return 0;
}
