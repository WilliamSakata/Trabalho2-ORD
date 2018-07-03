#include <stdio.h>
#include <stdlib.h>

#define maxkey 4
#define minkey maxkey/2
#define nokey '@'
#define erro -10
#define true 1
#define false 0
#define promocao = 10
#define sem_promo = 5

typedef struct {
    short keycout;
    char key[maxkey];
    short child[maxkey+1];
} pagina;


int main(){
    FILE *chaves, *arvore;
    int found_rrn, found_pos;

    chaves = fopen("chaves.txt", "r");
    arvore = fopen("arvore.txt", "w+");
}

int busca(int rrn, int key, int found_rrn, int found_pos, FILE *chaves){
    pagina *pag;
    int pos=0, found = false ;


    if(rrn = NULL)
        return 0;

    else{
        fseek(chaves, (rrn* sizeof(pagina)+4), SEEK_SET);
        fread(pag, sizeof(pagina), 1, chaves);

        while(found == false && pag->key <= 4){
            if(pag->key[pos]==key)
                found = true;
            pos++;
        }

        if(found){
            found_rrn = rrn;
            found_pos = pos;
            return true;
        } else{
            return busca(pag->child[pos], key, found_rrn, found_pos, chaves);
        }
    }
}

int insere(int rrn_atual, int key, int filho_d_pro, int chave_pro, FILE *chaves){ //da pra retornar o ponteiro pro arquivo?
    pagina *pag;
    int pos=0;

    if(rrn_atual == NULL){
        chave_pro = key;
        filho_d_pro = NULL;
        return promocao;
    } else{
        fseek(chaves, rrn_atual+4, SEEK_SET);
        fread(pag, sizeof(pagina), 1, chaves);

        while(key != pag->key && pag->key <= 4){
            pos++;
        }

        if(pos < 4){
            printf("\nError!!! Chave Duplicada!!");
            return erro;
        }

        return insere(pag->child[pos], key, ) //como que retorna o rrn_pro e o chv_pro
    }


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