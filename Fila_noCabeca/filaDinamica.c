#include "filaDinamica.h"

//____________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________

//FUNÇÔES MODIFICADAS PARA GARANTIR O FUNCIONAMENTO DO MAIN

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

//____________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________
//FUNÇÕES QUE DEVEM SER MODIFICADAS PELO ENUNCIADO DO EXERCICIO

//____________________________________________________________________________________________________________________________________________________
/* Inserção no fim da fila */

//Na inserção quem deve ser modificado é o apontamento do ultimo elemento. Assim, recebe-se o valor (reg), copiado para o novo. Esse deverá ter o proximo
//elemento nulo. O ultimo nó da fila deve agora aponta para o novo (linha 83) nó e o fim deve ser atualizado (linha 84)



bool inserirNaFila(FILA* f,REGISTRO reg) {

  PONT novo = (PONT) malloc(sizeof(ELEMENTO));

  novo->reg = reg;
  novo->prox = NULL;

  f->fim->prox = novo;  //linha 83
  f->fim = novo; //linha 84

  return true;
} 



//____________________________________________________________________________________________________________________________________________________
/*Exclusão da fila*/

//Na exclusão o elemento que deverá ser retirado é o primeiro que deu entrada. Assim, deverá ser atualizado o inicio, ou seja, o cabeça deve apontar para o novo inicio
// A linha 106 mostra como proceder. O ponteiro excluir inicialmente aponta para o primeiro valor válido, depois em 106 o primeiro valor recabera o próximo ao exluido, 
//ou seja, apontará para o valor seguinte.D Depois é becessário atualizar o fim se a fila estiver vazia


bool excluirDaFila(FILA* f, REGISTRO* reg) {
    if (f->inicio->prox == NULL) { 
        return false;
    }

    PONT excluir = f->inicio->prox; 
    *reg = excluir->reg;           

    f->inicio->prox = excluir->prox; //linha 106

    if (f->inicio->prox == NULL) {
        f->fim = f->inicio;
    }

    free(excluir); 

    return true;
} 





//____________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________
//____________________________________________________________________________________________________________________________________
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