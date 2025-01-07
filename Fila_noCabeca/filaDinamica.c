#include "filaDinamica.h"


//____________________________________________________________________________________________________________________________________
/* Inicialização da fila ligada*/

//MOdificação para incluir a inicialização do nó cabeça


void inicializarFila(FILA* f){
  PONT noCabeca = (PONT)malloc(sizeof(ELEMENTO));

  noCabeca->prox= NULL;
  f->inicio = noCabeca;
  f->fim = noCabeca;
} 



//____________________________________________________________________________________________________________________________________

//Modificação para determinar o tamanho sem considerar o nó cabeça na contagem



/* Retornar o tamanho da fila (numero de elementos) */
int tamanho(FILA* f) {
  PONT end = f->inicio->prox;
  int tam = 0;
  while (end != NULL){
    tam++;
    end = end->prox;
  }
  return tam;
} /* tamanho */


//____________________________________________________________________________________________________________________________________

// Não havia teste para caso a lista não tivesse sido inicializada. Foi incluido. Assim, depois de deletar a lista o print da a msg de erro.


/* Exibição da fila sequencial */
void exibirFila(FILA* f){

  if(f->inicio==NULL){
    printf("Lista Não inicializada");
    return;
  }

  PONT end = f->inicio->prox; // O primiero elemento válido não é o nó cabeça e sim inicio.
  
  printf("Fila: \" ");
  
  while (end != NULL){
    printf("%d ", end->reg.chave); 
    end = end->prox;
  }
  
  printf("\"\n");
  printf("\"\n");

} 


//FUNÇÕES QUE DEVEM SER MODIFICADAS PELO ENUNCIADO DO EXERCICIO_______________________________________________________________________________________

//____________________________________________________________________________________________________________________________________________________
/* Inserção no fim da fila */



bool inserirNaFila(FILA* f,REGISTRO reg) {

  PONT novo = (PONT) malloc(sizeof(ELEMENTO));

  novo->reg = reg;
  novo->prox = NULL;

  f->fim->prox = novo; 
  f->fim = novo;

  return true;
} 



//____________________________________________________________________________________________________________________________________________________
/*Exclusão da fila*/



bool excluirDaFila(FILA* f, REGISTRO* reg) {
    if (f->inicio->prox == NULL) { 
        return false;
    }

    PONT excluir = f->inicio->prox; 
    *reg = excluir->reg;           

    f->inicio->prox = excluir->prox; 

    if (f->inicio->prox == NULL) {
        f->fim = f->inicio;
    }

    free(excluir); 

    return true;
} 






//____________________________________________________________________________________________________________________________________
//FUNÇÔES QUE NÃO FORAM MODIFICDAS


/* Retornar o tamanho em bytes da fila.*/
int tamanhoEmBytes(FILA* f) {
  return (tamanho(f)*sizeof(ELEMENTO)) + sizeof(FILA);
} /* tamanhoEmBytes */



/* Destruição da fila*/
void destruirFila(FILA* f) {
  PONT end = f->inicio;
  while (end != NULL){
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  f->inicio = NULL;
  f->fim = NULL;
} /* destruirFila */

/* retornarPrimeiro */
PONT retornarPrimeiro(FILA* f, TIPOCHAVE *ch){
  if (f->inicio != NULL) *ch = f->inicio->reg.chave;
  return f->inicio;
} /* retornarPrimeiro */

/* retornarUltimo  */
PONT retornarUltimo(FILA* f, TIPOCHAVE* ch){
  if (f->inicio == NULL) return NULL;
  *ch = f->fim->reg.chave;
  return f->fim;
} /* retornarUltimo */

/* Busca sequencial */
PONT buscaSeq(FILA* f,TIPOCHAVE ch){
  PONT pos = f->inicio;
  while (pos != NULL){
    if (pos->reg.chave == ch) return pos;
    pos = pos->prox;
  }
  return NULL;
} /* buscaSeq */

/* Busca sequencial com sentinela alocado dinamicamente */
PONT buscaSeqSent1(FILA* f,TIPOCHAVE ch){
  if (!f->inicio) return NULL;
  PONT sentinela = malloc(sizeof(ELEMENTO));
  sentinela->reg.chave = ch;
  f->fim->prox = sentinela;
  PONT pos = f->inicio;
  while (pos->reg.chave != ch) pos = pos->prox;
  free(sentinela);
  f->fim->prox = NULL;
  if (pos!=sentinela) return pos;
  return NULL;
} /* buscaSeqSent1 */

/* Busca sequencial com sentinela como variavel local */
PONT buscaSeqSent2(FILA* f,TIPOCHAVE ch){
  if (!f->inicio) return NULL;
  ELEMENTO sentinela;
  sentinela.reg.chave = ch;
  f->fim->prox = &sentinela;
  PONT pos = f->inicio;
  while (pos->reg.chave != ch) pos = pos->prox;
  f->fim->prox = NULL;
  if (pos!=&sentinela) return pos;
  return NULL;
} /* buscaSeqSent1 */