#include "Pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_INICIAL 10

struct node {
  Aluno *aluno;
  struct node *proximo;
};

typedef struct node No;

struct pilha {
  No *primeiro;
};

/* Aloca espaço em memória e retorna uma pilha. */
Pilha *pilha_cria() {
  Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
  pilha->primeiro = NULL;
  return pilha;
}

/* Libera a memória de uma pilha previamente criada e atribui NULL ao ponteiro
 * pilha. Retorna 1 caso seja possível fazer a liberação e 0 caso a pilha
 * informada seja NULL. */
int pilha_libera(Pilha **pilha) {
  if (pilha != NULL) {
    if ((*pilha)->primeiro != NULL) {
      No *aux = (*pilha)->primeiro;
      do {
        alu_libera(&aux->aluno);
        aux = aux->proximo;
      } while (aux != NULL);
    }
    free(*pilha);
    *pilha = NULL;
    return 1;
  }
  return 0;
}

/* Insere um aluno na Pilha. Retorna 1 se foi possível adicionar, 0 caso já
 * exista um aluno com a mesma matricula (nesse caso, o aluno não pode ser
 * adicionado) e -1 caso a pilha ou aluno sejam NULL.
 */
int pilha_push(Pilha *pilha, Aluno *aluno) {
  if (aluno == NULL || pilha == NULL) {
    return -1;
  }
  
  No *adcNo = (No*)malloc(sizeof(No));
  adcNo->aluno = aluno;
  adcNo->proximo = NULL;
  No *aux = pilha -> primeiro;
  No *ant = aux;
 
  if(aux == NULL) { 
    No **aux2 =  &(pilha->primeiro);
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
    ant = aux;
    aux = aux->proximo; 
  } 
  No **aux2 = &(ant->proximo);
  *aux2 = adcNo;
  return 1;
}

/* Remove um aluno na pilha. Retorna o aluno ou NULL caso a pilha esteja vazia
 * ou seja NULL. */
Aluno *pilha_pop(Pilha *pilha) {
  //logi pop: o anterior ao topo será o topo e o retorno é o antigo topo.
  if(pilha == NULL || pilha->primeiro == NULL){
    return NULL;
  }
  No *atual = pilha->primeiro; //acessa o primeiro nó
  No *topo = atual; 
  No *armazena = atual;
  
  while(atual != NULL) {
    armazena = topo; //guarda o antigo topo
    topo = atual; //atualiza o topo como sendo o nó atual 
    atual = atual->proximo; //atualiza o atual como sendo o proximo nó
  }
  armazena->proximo = NULL;
  return topo->aluno;
}

/* Recupera o primeiro aluno da pilha. Retorna o aluno ou NULL caso a pilha
 * esteja vazia ou seja NULL. */
Aluno *pilha_top(Pilha *pilha) {
  if (pilha == NULL || pilha->primeiro == NULL) {
    return NULL;
  }
  No *aux = pilha->primeiro;
  while(aux->proximo != NULL) {
    aux = aux->proximo;
  }
  return aux->aluno;
}

/* Busca aluno pelo número de matricula. Retorna o aluno se este estiver na
 * lista e NULL caso contrário, isto é, (i) pilha vazia; (ii) não exista aluno
 * com a matricula fornecida; ou (iii) a pilha seja NULL */
Aluno *pilha_busca(Pilha *pilha, int matricula) {
  if (pilha->primeiro == NULL || pilha == NULL) { 
    return NULL;
  }
  int mat;
  char nome[50];
  char curso[30];
  No *aux = pilha->primeiro;
  
  while (aux != NULL) {
    alu_acessa(aux->aluno, &mat, nome, curso);
    if (mat == matricula) {
      return aux->aluno;
    }
    aux = aux->proximo;
  }
  return NULL;
}

/* Verifica se a pilha está vazia. Retorna 1 se a pilha estiver vazia, 0 caso
 * não esteja vazia e -1 se p Pilha for NULL
 */
int pilha_vazia(Pilha *pilha) {
  if (pilha->primeiro == NULL) {
    return 1;
  } else {
    return 0;
  }
  return -1;
}

/* Computa a quantidade de alunos na pilha. Retorna a quantidade de alunos
 * ou -1, caso a Pilha for NULL.
 */
int pilha_quantidade(Pilha *pilha) {
  if (pilha == NULL) {
    return -1;
  }
  No *aux = pilha->primeiro;
  int qtd = 0;
  while (aux != NULL) {
    qtd++;
  }
  return qtd;
}
