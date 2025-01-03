#include "listaLigadaD.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarLista(LISTA* l) {
  l->inicio = NULL;
}

void exibirLista(LISTA* l) {
  PONT end = l->inicio;
  printf("Lista: \" ");
  while (end != NULL) {
    printf("%d ", end->reg.chave);
    end = end->prox;
  }
  printf("\"\n");
}

int tamanho(LISTA* l) {
  PONT end = l->inicio;
  int tam = 0;
  while (end != NULL) {
    tam++;
    end = end->prox;
  }
  return tam;
}

int tamanhoEmBytes(LISTA* l) {
  return (tamanho(l) * sizeof(ELEMENTO)) + sizeof(LISTA);
}

PONT buscaSequencial(LISTA* l, TIPOCHAVE ch) {
  PONT pos = l->inicio;
  while (pos != NULL) {
    if (pos->reg.chave == ch) return pos;
    pos = pos->prox;
  }
  return NULL;
}

PONT buscaSeqOrd(LISTA* l, TIPOCHAVE ch) {
  PONT pos = l->inicio;
  while (pos != NULL && pos->reg.chave < ch) pos = pos->prox;
  if (pos != NULL && pos->reg.chave == ch) return pos;
  return NULL;
}

PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant) {
  *ant = NULL;
  PONT atual = l->inicio;
  while (atual != NULL && atual->reg.chave < ch) {
    *ant = atual;
    atual = atual->prox;
  }
  if (atual != NULL && atual->reg.chave == ch) return atual;
  return NULL;
}


// Exclusão modificada ______________________________________________________________________________________________________


bool excluirElemLista(LISTA* l, TIPOCHAVE ch){
  
  PONT ant, i;
  
  i = buscaSeqExc(l,ch,&ant);
  
  if (i == NULL){
     return false;
  }
  if (ant == NULL){
     l->inicio = i->prox;
  }else {
    ant->prox = i->prox;
  }
  if (i->prox){
     i->prox->ant = ant;
  }
  
  free(i);
  
  return true;

} 


//_____________________________________________________________________________________________________________________________

void reinicializarLista(LISTA* l) {
  PONT end = l->inicio;
  while (end != NULL) {
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  l->inicio = NULL;
}


// Função inserir modifica, incluindo a atualização do pronteiro anterior_______________________________________________

bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {

  TIPOCHAVE ch = reg.chave;
  PONT ant, i;

  i = buscaSeqExc(l, ch, &ant);
  
  if (i != NULL) {
    return false;
  }

  i = (PONT)malloc(sizeof(ELEMENTO));
  i->reg = reg; //copiando o valor de entrada
  i->ant = NULL; // iniciando o ant e o prox.
  i->prox = NULL;

  if (ant == NULL) {  //Se o anterior é nulo, temos o primeiro elemento logo, inserimos o valor e o ant recebe nulo
    
    i->prox = l->inicio;
    PONT auxiliar;

    if(l->inicio != NULL){
        auxiliar = l->inicio;
        auxiliar -> ant = i; //  o inicio agora apontará novo é apontado pelo velho
    } 
    l->inicio=i; // aponta para o novo inicio da lista
  } else {
   
    i->prox = ant->prox;
    PONT proximoAnterior;

    if (ant->prox != NULL) {
        proximoAnterior = ant->prox;       // Armazena o próximo de "ant"
        proximoAnterior->ant = i;         // Atualiza o ponteiro "ant" do próximo elemento
    }

    ant->prox = i;  // Atualiza o ponteiro "prox" do "ant" para o novo elemento
    i->ant = ant;   // Define o "ant" do novo elemento como "ant"

  }

  return true;

}

//________________________________________________________________________________________________________________________

PONT retornarPrimeiro(LISTA* l, TIPOCHAVE *ch) {
  if (l->inicio != NULL) *ch = l->inicio->reg.chave;
  return l->inicio;
}

PONT retornarUltimo(LISTA* l, TIPOCHAVE *ch) {
  PONT ultimo = l->inicio;
  if (l->inicio == NULL) return NULL;
  while (ultimo->prox != NULL) ultimo = ultimo->prox;
  *ch = ultimo->reg.chave;
  return ultimo;
}