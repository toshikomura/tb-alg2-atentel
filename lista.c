#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lista.h"


lista *constroi_lista (void)
{
	lista *l;
	l =malloc ( sizeof (lista) );
	//se nao alocou memoria para lista
	if (! l) return NULL; 
	l->tam =0; //tamanho 
	//nao ha nenhum elemento na lista
	l->primeiro =NULL; 
	
	//devolve endereco da lista para o programa principal
	return l; 
}

	

no *primeiro_no (lista *l) { return l->primeiro; }
no *anterior_no (no *p, lista *l) { return p->anterior; }
no *sucessor_no (no *p, lista *l) { return p->sucessor; }
void novo_ultimo_no (no *p) { p->sucessor =NULL; }



no *procura_ultimo_no (lista *l)
{
	//inicio da lista
	no *ultimo =primeiro_no (l); 
	//enquanto nao chegar no final da lista
	while (ultimo->sucessor != NULL) 
	{
		//vai para o proximo no
		ultimo =sucessor_no(ultimo, l); 
	}

	return ultimo;
}
