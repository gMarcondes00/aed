//Gabriel Oliveira Marcondes de Souza RN164531
//Ponteiro para Vetores e Structs

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int idCarro;
    char nomeCarro[20];
} Corredor;

void checarId(Corredor *corredor, int idCheck, int tamanho);
void corridaUsavel(char *corridaOrdem, int *corrida, int Nordem);
void ultrapassagem(int *corrida, int idUltra, int tamanho);
void ordenar(int *corrida, Corredor *corredor,Corredor *corredorReal, int tamanho);

int main() {
    int N, ultra = 0, i, Nordem, *corrida;
    char  *corridaOrdem;
    Corredor *corredor, *corredorReal;
    scanf("%d", &N);
    Nordem = N + (N - 1) + 1;

    corredor = (Corredor *)malloc(N * sizeof(Corredor));
    corredorReal = (Corredor *)malloc(N * sizeof(Corredor));
    corrida = (int *)malloc(N * sizeof(int));
    corridaOrdem = (char *)malloc(Nordem * sizeof(char));
    
    for(i = 0; i < N; i++) {
        scanf("%d %s", &corredor[i].idCarro, corredor[i].nomeCarro);
        
        checarId(corredor, corredor[i].idCarro, N); 
    }

    getchar();
    fgets(corridaOrdem, Nordem, stdin);

    corridaUsavel(corridaOrdem, corrida, Nordem);

    while(ultra != -1){
        scanf("%d", &ultra);
        ultrapassagem(corrida, ultra, N); 
    }
 
    ordenar(corrida, corredor, corredorReal,N);

    for(i = 0; i < 3; i++) {
        printf("%d %s\n", corredorReal[i].idCarro, corredorReal[i].nomeCarro);
    }

    free(corredor);
    free(corredorReal);
    free(corrida);
    free(corridaOrdem);
    return 0;
}

void checarId(Corredor *corredor, int idCheck, int tamanho) {
    int i, j, count = 0, N = tamanho;
    for(i = 0; i < tamanho; i++) {
        if(corredor[i].idCarro == idCheck) {
            count++;
            if(count > 1) {
               j = i;
               scanf("%d", &corredor[j].idCarro);
               checarId(corredor, corredor[j].idCarro, N);
            }
        }
    }
}

void corridaUsavel(char *corridaOrdem, int *corrida, int Nordem) {
    int i, j = 0;
    for(i = 0; i < Nordem; i++) {
        if(corridaOrdem[i] != ' ' && corridaOrdem[i] != '\0') {
            corrida[j] = corridaOrdem[i] - '0';
            j++;
        }
    }
} 

void ultrapassagem(int *corrida, int idUltra, int tamanho) {
    int i, aux;
    for(i = 0; i < tamanho; i++){
        if(idUltra == corrida[i] && i > 0){
            aux = corrida[i];
            corrida[i] = corrida[i - 1];
            corrida[i - 1] = aux; 
        }
    }
}

void ordenar(int *corrida, Corredor *corredor, Corredor *corredorReal, int tamanho) {
    int i, j = 0;

    for(i = 0; i < tamanho; i++) {
      corredorReal[i].idCarro = corrida[i];
      if(corredorReal[i].idCarro == corredor[j].idCarro){
           strcpy(corredorReal[i].nomeCarro, corredor[j].nomeCarro);
      }
    }
}