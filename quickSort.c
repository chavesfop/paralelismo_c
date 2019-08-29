#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define QTDARRAY 500
#define TAMARRAY 500

clock_t tclock[8];
pthread_t threads[QTDARRAY];
int ordenar[QTDARRAY][TAMARRAY];

//prototipo de funcoes
void exibeMatriz();
void exibeTempos();
void *threadCall(void *arg);
void quickSort(int idx, int left, int right);

int main (int argc, char **argv) {
	printf("===================================================================================================\n");
	printf("=======================ORDENACAO DE MATRIZ ALEATORIA COM BUBBLE SORT===============================\n");
	printf("---------------------------------------------------------------------------------------------------\n");
	tclock[0] = clock();
	//inicializa matriz com numeros aleatorios
	for (int i = 0; i < QTDARRAY; i++){
		for (int j = 0; j < TAMARRAY; j++){
			ordenar[i][j] = rand() % 90 + 10;
		}
	}
	tclock[1] = clock();

	tclock[4] = clock();
	//exibeMatriz(ordenar);
	tclock[5] = clock();

	tclock[2] = clock();
	//inicia threads de ordenação
	for (int i = 0; i < QTDARRAY; i++){
		int *arg = malloc(sizeof(*arg));
		*arg = i;
		pthread_create(&(threads[i]), NULL, threadCall, arg);
	}

	//realiza join das threads
	for (int i = 0; i < QTDARRAY; i++){
		pthread_join(threads[i], NULL);
	}
	tclock[3] = clock();

	tclock[6] = clock();;
	//exibeMatriz(ordenar);
	tclock[7] = clock();
	exibeTempos();
	printf("==================================================================================================\n");
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
	printf("==================================================================\n");
}

void quickSort(int idx, int left, int right){
	int a, b, c, d;
	a = left;
	b = right;
	c = ordenar[idx][(int)((a + b) / 2)];
	while (a <= b){
		while(ordenar[idx][a] < c && a < right){
			a++;
		}
		while(ordenar[idx][b] > c && b > left){
			b--;
		}
		if (a <= b){
			d = ordenar[idx][a];
			ordenar[idx][a] = ordenar[idx][b];
			ordenar[idx][b] = d;
			a++;
			b--;
		}
	}
	
	if (b > left){
		quickSort(idx, left, b);
	}
	if (a < right){
		quickSort(idx, a, right);
	}
}

void *threadCall(void *iarg){
	int i = *((int *) iarg);
	quickSort(i, 0, QTDARRAY-1);
	return 0;
}
