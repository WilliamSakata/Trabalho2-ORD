#include <stdio.h>
#include <stdlib.h>

#define maxchave 4
#define minchave maxkey/2
#define nokey '@'
#define erro -10
#define true 1
#define false 0
#define promocao = 10
#define sem_promo = 5

typedef struct {
    short keycout;
    char key[maxchave];
    short child[maxchave+1];
} pagina;

typedef struct {
    short keycount;
    char key[maxchave+1];
    short child[maxchave+2];
} pagaux;


int main(){
    FILE *chaves, *arvore;
    int found_rrn, found_pos, promo, raiz, rrn_pro;

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
    pagina *novapag;
    int pos=0, retorno, fit, i=0 ,j, rrn_pro = filho_d_pro, chv_pro = chave_pro;

    if(rrn_atual == NULL){
        chave_pro = key;
        filho_d_pro = NULL;
        retorno = promocao;
    } else{
        fseek(chaves, rrn_atual+4, SEEK_SET);
        fread(pag, sizeof(pagina), 1, chaves);

        while(key != pag->key && pag->key <= 4){
            pos++;
        }

        if(pos < 4){
            printf("\nError!!! Chave Duplicada!!");
            retorno = erro;
        }

        retorno = insere(pag->child[pos], key, rrn_pro, chv_pro, chaves); //como que retorna o rrn_pro e o chv_pro
    }
    if(retorno == erro || retorno == sem_promo){
        return retorno;
    } else{
        if(pag->keycout < maxchave){

            while(pag->key[i] < chv_pro){
                i++;
            }

            for(j=3;j>i;j--){
                pag->key[j]=pag->key[j-1];
            }

            pag->key[i] = chv_pro;

            for(j=4; j>i+1; j--){
                pag->child[j] = pag->child[j-1];
            }
            pag->child[i+1] = rrn_pro;

            fseek(chaves, rrn_atual, SEEK_SET+4);

            fwrite(pag, sizeof(pag), 1, chaves);

            return sem_promo;
        } else{
            divide(chv_pro, rrn_pro, pag, chave_pro, filho_d_pro, novapag, chaves); //perguntar sobre a novapag, onde cria

            fseek(chaves, rrn_atual, SEEK_SET+4);
            fwrite(pag, sizeof(pag), 1, chaves);

            fseek(chaves, filho_d_pro, SEEK_SET+4);
            fwrite(novapag, sizeof(novapag), 1, chaves);
        }
    }
}

void divide(int chave_i, int rrn_i, pagina *pag, int chave_pro, int filho_d_pro, pagina *novapag, FILE *chaves){
    pagaux *pagaux1;
    pagina *novapag1;
    int i=0, j=0, rrn_nova;

    pagaux1 = pag;

    while(pagaux1->key[i] < chave_i){
        i++;
    }
    for(j=4;j>i;j--){
        pagaux1->key[j] = pagaux1->key[j-1];
    }

    pagaux1->key[i] = chave_i;

    for(j=5; j>i+1; j--){
        pagaux1->child[j] = pagaux1->child[j-1];
    }
    pagaux1->child[i+1] = rrn_i;

    chave_pro = pagaux1->key[2];

    fseek(chaves, 0, SEEK_END);


    filho_d_pro = ((ftell(chaves)/ sizeof(pagina)) - 4);

    for(j=0; j<i;j++){
        pag->key[j] = pagaux1->key[j];
    }

    for(j=i;j<=5;j++){
        novapag1->key[j] = pagaux1->key[j];
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