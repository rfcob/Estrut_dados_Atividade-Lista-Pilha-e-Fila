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
  PONT end = f->noCabeca->prox;
  int tam = 0;
  while (end != NULL){
    tam++;
    end = end->prox;
  }
  return tam;
} /* tamanho */


//____________________________________________________________________________________________________________________________________






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


/* Exibição da fila sequencial */
void exibirFila(FILA* f){
  PONT end = f->inicio;
  printf("Fila: \" ");
  while (end != NULL){
    printf("%d ", end->reg.chave); // soh lembrando TIPOCHAVE = int
    end = end->prox;
  }
  printf("\"\n");
} /* exibirFila */ 


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





//FUNÇÕES QUE DEVEM SER MODIFICADAS PELO ENUNCIADO DO EXERCICIO_______________________________________________________________________________________

//____________________________________________________________________________________________________________________________________________________
/* Inserção no fim da fila */



bool inserirNaFila(FILA* f,REGISTRO reg) {

  PONT novo = (PONT) malloc(sizeof(ELEMENTO));
  novo->reg = reg;
  novo->prox = NULL;
  
    novo->reg = reg;
    novo->prox = NULL;
    f->fim->prox = novo; 
    f->fim = novo;

  return true;
} 



//____________________________________________________________________________________________________________________________________________________
/*Exclusão da fila*/



bool excluirDaFila(FILA* f, REGISTRO* reg) {
  if (f->inicio==NULL){
    return false;                     
  }

  *reg = f->inicio->reg;
  PONT apagar = f->inicio;
  f->inicio = f->inicio->prox;
  free(apagar);
  
  if (f->inicio == NULL){
    f->fim = NULL;
  }
    
  return true;
} 
