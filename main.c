#include <stdio.h>
#include <stdlib.h>

#define MAXCHAVE 4

#define ERRO -10
#define TRUE 1
#define FALSE 0
#define PROMOCAO 10
#define SEMPROMO 5
#define NIL -1


typedef struct {
    short keycount;
    char key[MAXCHAVE];
    short child[MAXCHAVE+1];
} pagina;

typedef struct {
    short keycount;
    char key[MAXCHAVE+1];
    short child[MAXCHAVE+2];
} pagaux;

int busca(int rrn, int key, int found_rrn, int found_pos, FILE *chaves);
int insere(int rrn_atual, int key, int *filho_d_pro, int *chave_pro, FILE *chaves, FILE *arvore);
void divide(int chave_i, int rrn_i, pagina *pag, int *chave_pro, int *filho_d_pro, pagina *novapag, FILE *chaves);
int search_node(int key, pagina pag, short pos);


int main(){
    FILE *chaves, *arvore;
    int found_rrn, found_pos, promo, raiz, rrn_pro, key, quant_chaves, i;
    int *filho_d_pro, *chave_pro;
    pagina *pag;

    chaves = fopen("chaves.txt", "r");
    arvore = fopen("arvore.txt", "w+");

    raiz = 1;

    fread(quant_chaves, sizeof(int), 1, chaves);

    fread(key, sizeof(char), 1, chaves);

    fwrite(raiz, sizeof(short), 1, arvore);

    insere(raiz, key, *filho_d_pro, *chave_pro, chaves, arvore);

    for(i=0;i<quant_chaves-2; i++){
        if(insere(raiz, key, *filho_d_pro, *chave_pro, chaves, arvore));
    }
}


int search_node(int key, pagina pag, short pos){
    int i;

    for(i=0; i<pag.keycount && key>pag.key[i];i++);

    pos = i;

    if(pos < pag.keycount && key == pag.key[pos])
        return TRUE;
    else
        return FALSE;
}

int busca(int rrn, int key, int found_rrn, int found_pos, FILE *chaves){
    pagina *pag;
    int pos=0, found = FALSE, i ;

    if(rrn == NIL)
        return 0;

    else {
        fseek(chaves, (rrn * sizeof(pagina) + 4), SEEK_SET);
        fread(pag, sizeof(pagina), 1, chaves);

        while (i < pag->keycount && key > pag->key[i]){
            i++;
        }

        pos = i;

        if (pos < pag->keycount && key * pag->key[pos])
            return TRUE;
        else
            return FALSE;
    }
}

int insere(int rrn_atual, int key, int *filho_d_pro, int *chave_pro, FILE *chaves, FILE *arvore){
    pagina pag;
    pagina novapag;

    int pos=0, retorno, fit, i=0 ,j, rrn_pro = *filho_d_pro, chv_pro = *chave_pro, found, found_rrn, found_pos;

    if(rrn_atual == NIL){
        *chave_pro = key;
        *filho_d_pro = NIL;
        retorno = PROMOCAO;

    }
    found = busca(rrn_atual,key, found_rrn, found_pos, chaves);

    if(found){
        printf("\nErro!! Chave Duplicada\n");
        retorno = ERRO;
    }

    retorno = insere(pag.child[pos], key, &rrn_pro, &chv_pro, chaves, arvore);

    if(retorno == ERRO || retorno == SEMPROMO)
        return retorno;
    else
        if(pag.keycount < MAXCHAVE){
            while(pag.key[i] < chv_pro){
                i++;
            }

            for(j=3;j>i;j--){
                pag.key[j]=pag.key[j-1];
            }

            pag.key[i] = chv_pro;

            for(j=4; j>i+1; j--){
                pag.child[j] = pag.child[j-1];
            }
            pag.child[i+1] = rrn_pro;

            fseek(chaves, rrn_atual, SEEK_SET+4);

            fwrite(&pag, sizeof(pag), 1, chaves);

            return SEMPROMO;
        } else{

            divide(chv_pro, rrn_pro, &pag, chave_pro, filho_d_pro, &novapag, chaves);

            fseek(chaves, rrn_atual, SEEK_SET+4);
            fwrite(&pag, sizeof(pag), 1, chaves);

            fseek(chaves, *filho_d_pro, SEEK_SET+4);
            fwrite(&novapag, sizeof(novapag), 1, arvore);
        }
    }



void divide(int chave_i, int rrn_i, pagina *pag, int *chave_pro, int *filho_d_pro, pagina *novapag, FILE *chaves){
    pagaux *pagaux1;
    pagina *novapag1;
    int i=0, j=0, rrn_nova;

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


    *chave_pro = pagaux1->key[2];

    fseek(chaves, 0, SEEK_END);

    *filho_d_pro = ((ftell(chaves)/ sizeof(pagina)) - 4);

    for(j=0; j<i;j++){
        pag->key[j] = pagaux1->key[j];
    }

    for(j=i;j<=5;j++){
        novapag1->key[j] = pagaux1->key[j];
    }

}
