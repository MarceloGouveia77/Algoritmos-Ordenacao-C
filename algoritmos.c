#include <stdio.h>
#include <string.h>
#include "algoritmos.h"

#define MAXSENHAS 4592
// *********************  ALGORITMO QUICKSORT  ************************
void quick_struct(Senha **senhas, int count)
{
  qs_struct(senhas,0,count-1);
}

void qs_struct(Senha **senhas, int left, int right)
{
  register int i, j;
  char *x;
  Senha *temp;

  i = left; j = right;
  x = senhas[(left+right)/2]->palavra;

  do {
    while((strcmp(senhas[i]->palavra,x) < 0) && (i < right)) i++;
    while((strcmp(senhas[j]->palavra,x) > 0) && (j > left)) j--;
    if(i <= j) {
      temp = senhas[i];
      senhas[i] = senhas[j];
      senhas[j] = temp;
      i++; j--;
    }
  } while(i <= j);

  if(left < j) qs_struct(senhas, left, j);
  if(i < right) qs_struct(senhas, i, right);
}

// *************************** ALGORITMO SELECTION SORT *************************
int indiceMenor(Senha **senhas, int tam, int ini){
    int min = ini, j;
    for(j=ini+1; j<tam; j++){
        if(strcmp(senhas[min]->palavra, senhas[j]->palavra) == -1)
            min = j;
    }
    return min;
};

void selectionSort(Senha **senhas, int tam){
    Senha *aux;
    int i, min;
    for(i=0; i<tam; i++){
        min = indiceMenor(senhas, tam, i); //Acha posicao do menor elemento a partir de i
        aux = senhas[i];
        senhas[i] = senhas[min];
        senhas[min] = aux;
    }
}
// *************************** BUBBLE SORT ******************************
void trocarElementos(Senha **senha1, Senha **senha2){
    Senha *aux;
    aux = senha1;
    senha1 = senha2;
    senha2 = aux;
}
void bubbleSort(Senha **senhas, int tam){
    int i,j;
    for(i=tam-1; i>0; i--){
        for(j=0; j < i; j++) //Faz trocas at´e posi¸c~ao i
            if(strcmp(senhas[j]->palavra, senhas[j+1]->palavra) == -1)
                trocarElementos(senhas[j], senhas[j+1]);
        }
    }
// *************************** INSERTION SORT *****************************
void insertionSort(Senha **senhas, int n){
    Senha *key;
    int i, j;
    for (i = 1; i < n; i++) {
        key = senhas[i];
        j = i - 1;

        while (j >= 0 && strcmp(senhas[j]->palavra, key->palavra) == 1) {
            senhas[j + 1] = senhas[j];
            j = j - 1;
        }
        senhas[j + 1] = key;
    }
}
// *************************** SHELL SORT ******************************
void shellSort(Senha **senha, int tam) {
    Senha *valor;
    int i, j;

    int h = 1;
    while(h < tam) {
        h = 3*h+1;
    }
    while (h > 0) {
        for(i = h; i < tam; i++) {
            valor = senha[i];
            j = i;

            while (j > h-1 && strcmp(valor->palavra, senha[j - h]->palavra) == -1) {
                senha[j] = senha[j - h];
                j = j - h;
            }
            senha[j] = valor;
        }
        h = h/3;
    }
}
// ***************************** MERGE SORT *****************************
void merge(Senha **senhas, int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio+1, comAux = 0;
    Senha** senhaAux;
    int tam = fim-comeco+1;
    printf("tam = %d", tam);
    senhaAux = (Senha**)malloc(tam * sizeof(Senha*));

    while(com1 <= meio && com2 <= fim){

        if(strcmp(senhas[com1]->palavra, senhas[com2]->palavra) == 1) {
            senhaAux[comAux] = senhas[com1];
            com1++;
        } else {
            senhaAux[comAux] = senhas[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){  //Caso ainda haja elementos na primeira metade
        senhaAux[comAux] = senhas[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   //Caso ainda haja elementos na segunda metade
        senhaAux[comAux] = senhas[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){    //Move os elementos de volta para o vetor original
        senhas[comAux] = senhaAux[comAux-comeco];
    }

    for (int n = 0; n <tam; n++)
		free(senhaAux[n]);

	free(senhaAux);
}

void mergeSort(Senha **senhas, int comeco, int fim){
    if (comeco < fim) {

        int meio = (fim+comeco)/2;

        mergeSort(senhas, comeco, meio);
        mergeSort(senhas, meio+1, fim);
        merge(senhas, comeco, meio, fim);
    }
}
// ********************************* HEAP SORT ***********************************
void peneira(Senha **senhas, int raiz, int fundo) {
	Senha *tmp;
	int pronto, filhoMax;

	pronto = 0;
	while ((raiz*2 <= fundo) && (!pronto)) {
		if (raiz*2 == fundo) {
			filhoMax = raiz * 2;
		}

		else if (strcmp(senhas[raiz * 2]->palavra, senhas[raiz * 2 + 1]->palavra) == 1) {
			filhoMax = raiz * 2;
		}
		else {
			filhoMax = raiz * 2 + 1;
		}

	if (strcmp(senhas[raiz]->palavra, senhas[filhoMax]->palavra) == -1) {
		tmp = senhas[raiz];
		senhas[raiz] = senhas[filhoMax];
		senhas[filhoMax] = tmp;
		raiz = filhoMax;
    }
	else {
      pronto = 1;
	}
  }
}

void heapsort(Senha **senhas, int n) {
    Senha *tmp;
	int i;

	for (i = (n / 2); i >= 0; i--) {
		peneira(senhas, i, n - 1);
	}

	for (i = n-1; i >= 1; i--) {
		tmp = senhas[0];
		senhas[0] = senhas[i];
		senhas[i] = tmp;
		peneira(senhas, 0, i-1);
	}
}
