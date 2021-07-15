#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "algoritmos.h"

#define MAXSENHAS 430000

void LerSenhas(Senha **senhas, char *filepath)
{
	FILE *fp;
	int n = 0, tam, freq;
	char pass[200];

	fp = fopen(filepath, "r");

	while (fscanf(fp, "%d %d %[^\n]", &tam, &freq, pass) == 3)
	{
		senhas[n] = (Senha*)malloc(sizeof(Senha));
		senhas[n]->tamanho = tam;
		senhas[n]->frequencia = freq;
		senhas[n]->palavra = (char*)malloc((tam+1) * sizeof(char));
		pass[tam] = '\0';
		strcpy(senhas[n]->palavra, pass);
		n++;
	}

	fclose(fp);
}

void obter_tempo(int inicio, int fim, char *algoritmo){
    double total = (double)(fim - inicio) * 1000.0 / CLOCKS_PER_SEC;
    printf("**********\n%s foi executado em: %f milissegundos\n**********\n", algoritmo, total);
}

void iniciar_algoritmo(Senha **senhas, int tam, char *algoritmo){
    LerSenhas(senhas, "senhas.txt"); // ler as senhas antes de começar a contar o tempo
    clock_t tempo_inicio = clock();

    if(strcmp("QuickSort", algoritmo) == 0) quick_struct(senhas, tam);
    if(strcmp("selectionSort", algoritmo) == 0) selectionSort(senhas, tam);
    if(strcmp("bubbleSort", algoritmo) == 0) bubbleSort(senhas, tam);
    if(strcmp("insertionSort", algoritmo) == 0) insertionSort(senhas, tam);
    if(strcmp("shellSort", algoritmo) == 0) shellSort(senhas, tam);
    if(strcmp("heapSort", algoritmo) == 0) heapsort(senhas, tam);
    if(strcmp("mergeSort", algoritmo) == 0) mergeSort(senhas, 0, tam);

    clock_t tempo_fim = clock();
    obter_tempo(tempo_inicio, tempo_fim, algoritmo);
}

int main(){
    int n;
	Senha** senhas;
	senhas = (Senha**)malloc(MAXSENHAS * sizeof(Senha*));

    //iniciar_algoritmo(senhas, MAXSENHAS, "QuickSort");
    //iniciar_algoritmo(senhas, MAXSENHAS, "selectionSort");
    //iniciar_algoritmo(senhas, MAXSENHAS, "bubbleSort");
    //iniciar_algoritmo(senhas, MAXSENHAS, "insertionSort");
    //iniciar_algoritmo(senhas, MAXSENHAS, "shellSort");
    //iniciar_algoritmo(senhas, MAXSENHAS, "heapSort");
    iniciar_algoritmo(senhas, MAXSENHAS, "mergeSort");

	for (n = 0; n < MAXSENHAS; n++)
        printf("%s - %d %d\n", senhas[n]->palavra, senhas[n]->tamanho, senhas[n]->frequencia);



	for (n = 0; n < MAXSENHAS ; n++)
		free(senhas[n]);
	free(senhas);

	return 0;
}
