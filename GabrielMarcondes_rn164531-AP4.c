//Gabriel Oliveira Marcondes rn 164531 - Regina Noturno
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 1024

typedef struct {
    int* num;
    int top;
} Pilha;

void initPilha(Pilha* pilha);
int estaVazia(Pilha* pilha);
void empilhar(Pilha* pilha, int num);
int desempilhar(Pilha* pilha);
int calcularRPN(char* expressao);

int main() {
    int resultado;
    char expressao[1025];
    scanf("%s", expressao);

    resultado = calcularRPN(expressao);

    if (resultado == 0) {
        printf("Invalid Expression");
    } else {
        printf("%d", resultado);
    }

    return 0;
}

void initPilha(Pilha* pilha) {
    pilha->top = -1;
    pilha->num = (int*)malloc(MAX_STACK_SIZE * sizeof(int));
}

int estaVazia(Pilha* pilha) {
    return pilha->top == -1;
}

void empilhar(Pilha* pilha, int num) {
    if (pilha->top < MAX_STACK_SIZE - 1) {
        pilha->num[++(pilha->top)] = num;
    } 

    return;
}

int desempilhar(Pilha* pilha) {
    if (!estaVazia(pilha)) {
        return pilha->num[(pilha->top)--];
    } else {
        return 0;
    }
}

int calcularRPN(char* expressao) {
    Pilha pilha;
    initPilha(&pilha);
    int operando2, operando1, resultado;

    for (int i = 0; expressao[i] != '\0'; i++) {
        char token = expressao[i];
        if (token >= '0' && token <= '9') {
            empilhar(&pilha, token - '0');
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            if (!estaVazia(&pilha)) {
                operando2 = desempilhar(&pilha);
                if (!estaVazia(&pilha)) {
                    operando1 = desempilhar(&pilha);
                    switch (token) {
                        case '+':
                            resultado = operando1 + operando2;
                            break;
                        case '-':
                            resultado = operando1 - operando2;
                            break;
                        case '*':
                            resultado = operando1 * operando2;
                            break;
                        case '/':
                            if (operando2 == 0) {
                                free(pilha.num);
                                return 0;
                            }
                            resultado = operando1 / operando2;
                            break;
                    }
                    empilhar(&pilha, resultado);
                } else {
                    free(pilha.num);
                    return 0;
                }
            } else {
                free(pilha.num);
                return 0;
            }
        } else {
            free(pilha.num);
            return 0;
        }
    }
    if (!estaVazia(&pilha)) {
        int resultado = desempilhar(&pilha);
        if (estaVazia(&pilha)) {
            free(pilha.num);
            return resultado;
        } else {
            free(pilha.num);
            return 0;
        }
    } else {
        free(pilha.num);
        return 0;
    }
}