#include <stdio.h>
#include <stdlib.h>
//************* ALTERACAO *******************
// Alterei todos os nomes usados nos defines para caixa alta
// Com caixa baixa estava dando problema no true/false
#define MAXCHAVE 4
#define MINCHAVE MAXCHAVE/2
#define NOKEY '@'
#define ERRO -10
#define TRUE 1
#define FALSE 0
//************* ALTERACAO *******************
//#define promocao = 10
//#define sem_promo = 5
#define PROMOCAO 10
#define SEMPROMO 5
// Esse NIL não é a mesma coisa que NULL
#define NIL -1
//*******************************************

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

//************* ALTERACAO *******************
// Inclui os protótipos das funções
int busca(int rrn, int key, int found_rrn, int found_pos, FILE *chaves);
int insere(int rrn_atual, int key, int *filho_d_pro, int *chave_pro, FILE *chaves);
void divide(int chave_i, int rrn_i, pagina *pag, int *chave_pro, int *filho_d_pro, pagina *novapag, FILE *chaves);
//*******************************************


int main(){
    FILE *chaves, *arvore;
    int found_rrn, found_pos, promo, raiz, rrn_pro;

    chaves = fopen("chaves.txt", "r");
    arvore = fopen("arvore.txt", "w+");
}

int busca(int rrn, int key, int found_rrn, int found_pos, FILE *chaves){
    pagina *pag;
    int pos=0, found = FALSE ;

    if(rrn = NIL)
        return 0;
        //*******************************************
    else{
        fseek(chaves, (rrn* sizeof(pagina)+4), SEEK_SET);
        fread(pag, sizeof(pagina), 1, chaves);

        //************* ALTERACAO *******************
        // Resolvi o erro de compilação, mas esse looping não vai funcionar direito
        //while(!found && pag->key <= 4){
        while(!found && pag->keycount <= 4){
            if(pag->key[pos] == key)
                found = TRUE;
            pos++;
        }
        //*******************************************

        if(found){
            found_rrn = rrn;
            found_pos = pos;
            return TRUE;
        } else{
            return busca(pag->child[pos], key, found_rrn, found_pos, chaves);
        }
    }
}

//************* ALTERACAO *******************
// filho_d_pro e chave_pro têm que ser ponteiros, pois eles são parâmetros de retorno
//int insere(int rrn_atual, int key, int filho_d_pro, int chave_pro, FILE *chaves)
int insere(int rrn_atual, int key, int *filho_d_pro, int *chave_pro, FILE *chaves){ //da pra retornar o ponteiro pro arquivo?
    // Se vc declarar pag e novapag como ponteiros, vai ter que usar malloc para alocar espaço para elas
    // O mais fácil seria declarar como var normal e passar o endereço quando precisar ser ponteiro
    pagina *pag;
    pagina *novapag;
    //Arrumei o erro de compilação, mas essa inicialização do rrn_pro e do chv_pro não vai dar certo
    //int pos=0, retorno, fit, i=0 ,j, rrn_pro = filho_d_pro, chv_pro = chave_pro;
    int pos=0, retorno, fit, i=0 ,j, rrn_pro = *filho_d_pro, chv_pro = *chave_pro;

    if(rrn_atual == NIL){
        *chave_pro = key;
        //filho_d_pro = NULL;
        *filho_d_pro = NIL;
        retorno = PROMOCAO;

    } else{
        fseek(chaves, rrn_atual+4, SEEK_SET);
        fread(pag, sizeof(pagina), 1, chaves);

        while(key != pag->key[pos] && pag->keycount <= 4){
            pos++;
        }

        if(pos < 4){
            printf("\nError!!! Chave Duplicada!!");
            retorno = ERRO;
        }

        retorno = insere(pag->child[pos], key, &rrn_pro, &chv_pro, chaves); //como que retorna o rrn_pro e o chv_pro
    }
    if(retorno == ERRO || retorno == SEMPROMO){
        return retorno;
    } else{
        if(pag->keycount < MAXCHAVE){

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

            return SEMPROMO;
        } else{

            divide(chv_pro, rrn_pro, pag, chave_pro, filho_d_pro, novapag, chaves);

            fseek(chaves, rrn_atual, SEEK_SET+4);
            fwrite(pag, sizeof(pag), 1, chaves);

            fseek(chaves, *filho_d_pro, SEEK_SET+4);
            fwrite(novapag, sizeof(novapag), 1, chaves);
        }
    }
}

void divide(int chave_i, int rrn_i, pagina *pag, int *chave_pro, int *filho_d_pro, pagina *novapag, FILE *chaves){
    pagaux *pagaux1;
    pagina *novapag1;
    int i=0, j=0, rrn_nova;

    //pagaux e pagina são tipos diferentes, portanto vc não pode fazer essa atribuicao
    //pagaux1 = pag;
    //para copiar os elementos de pag para pagaux1, tem que passar um por um

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
