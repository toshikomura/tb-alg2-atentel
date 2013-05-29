#include<stdio.h>
#include<stdlib.h>
#include<string.h>



typedef struct objeto
{
	int tempo_entrada;
	char tipo[4];
	char user[4];
	char estado[8];
} objeto;

typedef struct no {
  	objeto o;
  	struct no *sucessor;
	struct no *anterior;
} no;

typedef struct lista{
  no *primeiro;
  unsigned int tam;
} lista;

//funcao nao utilizada
objeto objeto_no(no *p);
//

no *primeiro_no(lista *l);
no *sucessor_no(no *p, lista *l);
//funcoes acrescentadas para o programa
no *anterior_no(no *p, lista *l);
void novo_ultimo_no(no *p);
no *procura_ultimo_no(lista *l);
//

//funcoes nao utilizadas
int vazia_lista(lista *l);
unsigned int tamanho_lista(lista *l);
//

lista *constroi_lista(void);

//funcao nao utilizada
void destroi_lista(lista *l);
//

no *insere_lista(objeto o, lista *l);

//funcao nao utilizada
objeto remove_lista(lista *l);
//
