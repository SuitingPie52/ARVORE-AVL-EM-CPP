/////////////////
// Árvore AVL //
///////////////


// diferença de altura entre esquerda e direita não pode ser superior a 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct no {
	
	int numero;
	struct no *esquerda;
	struct no *direita;
	int altura;
	
};

int getAlturaDoNo (struct no *raiz) { // retorna altura do nó, altura = quantos nós estão abaixo do nó (não é a altura propiamente dita)
	
	return ((raiz == NULL) ? 0 : raiz -> altura); // ? = if, : = else
	
}

int getMaximoEntreDoisNumeros(int a, int b) { // funão que retorna o maior entre dois números
	
	return (a > b) ? a : b;
	
}

int getBalanco (struct no* raiz) { // função que captura o balanço da árvore
	
	int retorno = 0;
	
	if (raiz != NULL) {
		
		retorno = (getAlturaDoNo(raiz -> esquerda) - getAlturaDoNo(raiz -> direita)); // balanco > 1 = desbalanceado p esquerda, balanco < -1 = desbalanceado p direita
		
	}
	
	return retorno;

}

struct no *rotacaoEsquerda (struct no *raiz) {
	
	// ROTACAO PROPIAMENTE DITA:
	// raiz - > direita (novaRaiz) vira a raíz e raiz original vira a raiz -> esquerda
	struct no *novaRaiz = raiz -> direita;
	struct no *temp = novaRaiz -> esquerda;
	
	novaRaiz -> esquerda = raiz;
	raiz -> direita = temp;

	raiz -> altura = (getMaximoEntreDoisNumeros(getAlturaDoNo(raiz -> esquerda), getAlturaDoNo(raiz -> direita)) + 1);
	novaRaiz -> altura = (getMaximoEntreDoisNumeros(getAlturaDoNo(novaRaiz -> esquerda), getAlturaDoNo(novaRaiz -> direita)) + 1);
	
	return novaRaiz; 
	
}

struct no *rotacaoDireita (struct no *raiz) {
	
	// ROTACAO PROPIAMENTE DITA:
	// raiz - > esquerda (novaRaiz) vira a raíz e raiz original vira a raiz -> direita
	struct no *novaRaiz = raiz -> esquerda;
	struct no *temp = novaRaiz -> direita;
	
	novaRaiz -> direita = raiz;
	raiz -> esquerda = temp;

	raiz -> altura = (getMaximoEntreDoisNumeros(getAlturaDoNo(raiz -> esquerda), getAlturaDoNo(raiz -> direita)) + 1);
	novaRaiz -> altura = (getMaximoEntreDoisNumeros(getAlturaDoNo(novaRaiz -> esquerda), getAlturaDoNo(novaRaiz -> direita)) + 1);
	
	return novaRaiz; 
	
}

struct no *inserir(struct no *raiz, int numero) {
	
	if (raiz == NULL) {
		
		raiz = (struct no *) malloc(sizeof(struct no));
		raiz -> numero = numero;
		raiz -> esquerda = NULL;
		raiz -> direita = NULL;
		raiz -> altura = 1;

	} else {
		
		if (raiz -> numero > numero) {
			
			raiz -> esquerda = inserir(raiz -> esquerda, numero);
			
		} else {
			
			raiz -> direita = inserir(raiz -> direita, numero);
			
		}
		
	}
	
	raiz -> altura = (1 + getMaximoEntreDoisNumeros(getAlturaDoNo(raiz -> esquerda), getAlturaDoNo(raiz -> direita)));
	
	int balanco = getBalanco(raiz);
	
	if ((balanco > 1) && (numero < raiz -> esquerda -> numero)) {
		
		raiz = rotacaoDireita(raiz);

	}

	if ((balanco < -1) && (numero > raiz -> direita -> numero)) {
		
		raiz = rotacaoEsquerda(raiz);

	}
	
	if ((balanco > 1) && (numero > raiz -> esquerda -> numero)) {
		
		raiz -> esquerda = rotacaoEsquerda(raiz -> esquerda);
		raiz = rotacaoDireita(raiz);

	}
	
	if ((balanco < -1) && (numero < raiz -> direita -> numero)) {
		
		raiz -> direita = rotacaoDireita(raiz -> direita);
		raiz = rotacaoEsquerda(raiz);

	}
	
	return raiz;
	
}

void imprimir(struct no *raiz, char *endentador) {
	
	if (raiz != NULL) {

		printf("%s%d(A %d)\n", endentador, raiz -> numero, raiz -> altura); // altura pra baixo
		
		char *temp = (char *) malloc(1024 * sizeof(char));
		strcpy(temp, endentador);
		strcat(temp, "---");
	
		imprimir(raiz -> esquerda, temp);
		imprimir(raiz -> direita, temp);
	

	}
	
}

int main() {
	
	struct no *raiz = NULL; 
	int i = 0;
	
	for (i = 0; i < 10; i++) {
		
		raiz = inserir(raiz, i);
		
	}
	
	imprimir(raiz, "");
}
