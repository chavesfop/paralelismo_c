#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define QTDARRAY 100
#define TAMARRAY 10000

pthread_t threads[QTDARRAY];
int ordenar[QTDARRAY][TAMARRAY];

//prototipo de funcoes
void exibeMatriz();
void *ordenaMatriz(void *arg);

int main (int argc, char **argv) {

	//inicializa matriz com numeros aleatorios
	for (int i = 0; i < QTDARRAY; i++){
		for (int j = 0; j < TAMARRAY; j++){
			ordenar[i][j] = rand() % 90 + 10;
		}
	}

	exibeMatriz(ordenar);

	//inicia threads de ordenação
	for (int i = 0; i < QTDARRAY; i++){
		int *arg = malloc(sizeof(*arg));
		*arg = i;
		pthread_create(&(threads[i]), NULL, quickSort, arg);
	}

	//realiza join das threads
	for (int i = 0; i < QTDARRAY; i++){
		pthread_join(threads[i], NULL);
	}
	exibeMatriz(ordenar);
}

void exibeMatriz(){
	for (int i = 0; i < QTDARRAY; i++){
		for (int j = 0; j < TAMARRAY; j++){
			printf("[%d,%d] = %d |", i, j, ordenar[i][j]);
		}
		printf("\n");
	}
}

void *quickSort(void *iarg){
	int i = *((int *) iarg);
	int pivo, aux, i, j, meio;
   
	i = inicio;
	j = fim;
   
   meio = (int) ((i + j) / 2);
   pivo = vetor[meio];
   
   do{
      while (vetor[i] < pivo) i = i + 1;
      while (vetor[j] > pivo) j = j - 1;
      
      if(i <= j){
         aux = vetor[i];
         vetor[i] = vetor[j];
         vetor[j] = aux;
         i = i + 1;
         j = j - 1;
      }
   }while(j > i);
   
   if(inicio < j) Quick(vetor, inicio, j);
   if(i < fim) Quick(vetor, i, fim);  
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
