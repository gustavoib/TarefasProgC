#include "Fila.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node No;

struct node {
  Aluno *aluno;
  struct node *proximo;
};

struct fila {
  No *primeiro;
};

/* Aloca espaço em memória e retorna uma fila */
Fila *fila_cria() {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  fila->primeiro = NULL;
  return fila;
}

/* Libera a memória de uma fila previamente criada e atribui NULL ao ponteiro
 * fila. Retorna 1 caso seja possível fazer a liberação e 0 caso a fila
 * informada seja NULL. */
int fila_libera(Fila **fila) {
  if (fila != NULL) {
    if ((*fila)->primeiro != NULL) {
      No *aux = (*fila)->primeiro;
      do {
        alu_libera(&aux->aluno);
        aux = aux->proximo;
      } while (aux != NULL);
    }
    free(*fila);
    *fila = NULL;
    return 1;
  }
  return 0;
}

/* Insere um aluno na fila. Retorna 1 se foi possível adicionar, 0 caso já
 * exista um aluno com a mesma matricula (nesse caso, o aluno não pode ser
 * adicionado) e -1 caso a fila ou aluno sejam NULL
 */
int fila_insere(Fila *fila, Aluno *aluno) {
  if (aluno == NULL || fila == NULL) {
    return-1;
  }
  
  No * adcNo = (No*)malloc(sizeof(No));
  adcNo->aluno = aluno;
  adcNo->proximo = NULL;
  No* aux = fila -> primeiro;
  No* ant = aux;
 
  if(aux == NULL) { 
    No** aux2 =  &(fila->primeiro);
    *aux2 = adcNo; 
    return 1;
  }
  
  int mat;
  char nome[50];
  char curso[30];
  
  int matcmp;
  char nomecmp[50];
  char cursocmp[30];
  
  alu_acessa(aluno, &mat, nome, curso);
  while(aux != NULL) { 
    alu_acessa(aux->aluno, &matcmp, nomecmp, cursocmp);
    if (matcmp == mat) {
      return 0;
    }
    ant = aux; //guarda o valor auxiliar
    aux = aux->proximo; //atualiza o proximo
  } 
  No ** aux2 = &(ant->proximo);
  *aux2 = adcNo;
  return 1;
}

/* Remove um aluno na fila. Retorna o aluno ou NULL caso a fila esteja vazia ou
 * seja NULL */
Aluno *fila_retira(Fila *fila) {
  if (fila->primeiro == NULL || fila == NULL) {
    return NULL;
  }
  Aluno* aux = fila->primeiro->aluno;
  No** aux2 = (&(fila->primeiro));
  *aux2 = fila->primeiro->proximo;
  return aux;
}

/* Recupera o primeiro aluno da fila. Retorna o aluno ou NULL caso a fila esteja
 * vazia ou seja NULL */
Aluno *fila_primeiro(Fila *fila) {
  if (fila->primeiro == NULL || fila == NULL) {
    return NULL;
  }
  return fila->primeiro->aluno;
}

/* Busca aluno pelo número de matricula. Retorna o aluno se este estiver na
 * lista e NULL caso contrário, isto é, (i) fila vazia; (ii) não exista aluno
 * com a matricula fornecida; ou (iii) a fila seja NULL */
Aluno *fila_busca(Fila *fila, int matricula) {
  if (fila->primeiro == NULL || fila == NULL) { //i e ii
    return NULL;
  }
  int mat;
  char nome[50];
  char curso[30];
  No* aux = fila->primeiro;
  
  while (aux != NULL) {
    alu_acessa(aux->aluno, &mat, nome, curso);
    if (mat == matricula) {
      return aux->aluno;
    }
    aux = aux->proximo;
  }
  return NULL;
}

/* Verifica se a fila está vazia. Retorna 1 se a fila estiver vazia, 0 caso não
 * esteja vazia e -1 se a fila for NULL
 */
int fila_vazia(Fila *fila) {
  if (fila->primeiro == NULL){
    return 1; //ok
  } else {
    return 0;
  }
  return -1;
}

/* Computa a quantidade de alunos alunos na fila. Retorna a quantidade de alunos
 * ou -1, caso a fila for NULL.
 */
int fila_quantidade(Fila *fila) {
    if (fila == NULL) {
    return -1; //incompleta
  }
}