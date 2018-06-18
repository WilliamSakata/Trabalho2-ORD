#include <stdio.h>
#include <stdlib.h>

#define maxkey 4

struct btpage{
    short keycount;
    char key[maxkey];
    short child[maxkey + 1];
} page;

int main(){
    FILE *chaves, *arvore;
    int found_rrn, found_pos;

    chaves = fopen("chaves.txt", "r");
    arvore = fopen("arvore.txt", "w+");


}

int search(int rrn, int key, int found_rrn, int found_pos){
    if(rrn = NULL)
        return 0;

}










/*
struct No{
    int numero;
    struct No *esquerda;
    struct No *direita;
};
typedef struct No No;

void criarArvore(No **pRaiz);
void insercao(No **Raiz, int numero);

int main() {

}

void criarArvore(No **pRaiz){
    *pRaiz = NULL;
}

void insercao(No **Raiz, int numero){
    if(*Raiz == NULL){
        *Raiz=(No *)malloc(sizeof(No));
        (*Raiz)->direita = NULL;
        (*Raiz)->esquerda= NULL;
        (*Raiz)->numero = numero;
    } else{
        if (numero<((*Raiz)->numero))
            insercao(&((*Raiz)->esquerda), numero);
        else
            insercao(&((*Raiz)->direita), numero);
    }
}
 */