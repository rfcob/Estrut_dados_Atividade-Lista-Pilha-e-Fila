#ifndef FILADINAMICA_H
#define FILADINAMICA_H


#include <stdio.h>
#include <malloc.h>
#define ERRO -1
#define true 1
#define false 0
typedef int bool;
typedef int TIPOCHAVE;

#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO, *PONT;

typedef struct {
    PONT noCabeca;
    PONT inicio;
    PONT fim;
} FILA;

// Prototipos das funcoes
void inicializarFila(FILA* f);
int tamanho(FILA* f);
int tamanhoEmBytes(FILA* f);
void destruirFila(FILA* f);
PONT retornarPrimeiro(FILA* f, TIPOCHAVE* ch);
PONT retornarUltimo(FILA* f, TIPOCHAVE* ch);
bool inserirNaFila(FILA* f, REGISTRO reg);
bool excluirDaFila(FILA* f, REGISTRO* reg);

#endif