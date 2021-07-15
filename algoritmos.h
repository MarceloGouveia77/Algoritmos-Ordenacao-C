#include <stdlib.h>
#ifndef ALGORITMOS_H
#define ALGORITMOS_H

struct senha{
	char *palavra;
	int tamanho;
	int frequencia;
};
typedef struct senha Senha;

void quick_struct(Senha **senhas, int count);
void qs_struct(Senha **senhas, int left, int right);
void selectionSort(Senha **senhas, int tam);
void bubbleSort(Senha **senhas, int tam);
void insertionSort(Senha **senhas, int n);
void shellSort(Senha **senha, int tam);
void mergeSort(Senha **senhas, int comeco, int fim);
void heapSort(Senha **senhas, int n);

#endif
