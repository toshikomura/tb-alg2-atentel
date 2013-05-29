#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lista.h" 



no *grava_objeto_no_no (lista *l, int clock)
{
	no *novo =malloc( sizeof(no));
	//se nao conseguiu devolve nada
	if (! novo) return NULL;
	objeto o;		
	//recebe as strings
	char *tipo, *user; 
	//leitura dos dados para o primeiro elemento da lista
	scanf ("%s", tipo); 
	scanf ("%s", user);
	strcpy (o.tipo, tipo);
	strcpy (o.user, user);
	printf ("%s %s ", o.tipo, o.user);
	//passa o objeto para o no
	novo->o =o; 
	//aumenta o tamanho da lista
	++l->tam; 

	return novo;
}



objeto remove_primeiro_objeto(lista *fila)
{
	no *primeiro =primeiro_no(fila);
	objeto o =primeiro->o;
	
	return o;
}



// FIM DAS FUNCOES DE ALTERACOES NA LISTA
/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/



objeto insere_objeto (lista *fila)
{
	objeto o;
	scanf ("%s %s", o.tipo, o.user);
	strcpy(o.estado, "normal");
	//aumenta a lista
	fila->tam++;
	return o;
}



/*-----------------------------------------------------------------------------------*/
//PARTE DE GRAVACAO, LEITURA E IMPRESSAO DA FILA


lista *insere_dados_na_lista_dupla (lista *fila)
{
	//variável para ler o tempo de entrada da ligação e controle do final do arquvio
	int temp; 
	objeto o;
	no *novo =malloc (sizeof (no)), *anterior;
	if (! novo) return NULL;
	//primeiro nó da fila
	fila->primeiro =novo; 
	//verifica se não é o final do arquivo
	if (scanf ("%d", &temp) ==EOF ) return NULL; 
	 //faz a leitura do arquivo e passa para o objeto
	o =insere_objeto (fila);
	o.tempo_entrada =temp;
	//nó da fila recebe o objeto
	novo->o =o;
	novo->anterior =NULL;
	//o seu nó sucessor
	novo->sucessor =NULL; 
	//nó para salvar o endereço do penultimo nó inserido
	anterior =novo; 
	//enquanto não chegar no final do arquivo
	while (scanf ("%d", &temp) !=EOF ) 
	{
		//aloca memória para o novo nó
		no *novo =malloc (sizeof (no)); 
		//faz a leitura do arquivo e passa para o objeto
		o =insere_objeto (fila); 
		o.tempo_entrada =temp;
		//o novo nó recebe o objeto
		novo->o =o; 
		//arrumando os ponteiros
		//o sucessor do nó anterior recebe o endereço do atual
		anterior->sucessor =novo; 
		//o anterior do novo eh o "anteior"
		novo->anterior =anterior; 
		//atualiza o endereço do anterior 
		anterior =novo; 
		novo->sucessor =NULL; 
	}

	return fila;
}

/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/

void Quem_Chegou (lista *fila, int tempo)
{
	no *elemento =primeiro_no (fila);
	objeto o =elemento->o;
	//enquanto elemento existir 
	while (elemento !=NULL && o.tempo_entrada <= tempo ) 
	{
		if (o.tempo_entrada ==tempo)
			printf("ura %d %s\n", o.tempo_entrada, o.user);
		//passa para o proximo elemento
		elemento =elemento->sucessor; 
		//se acabou cai fora
		if (elemento ==NULL) 
			break;
		//atualiza o objeto
		o =elemento->o;
	}
}




int  Custo_da_Ligacao (no *melhor_no, int tempo)
{
	int tempo_para_saida_da_ligacao, custo_da_ligacao;
	objeto o =melhor_no->o;
	//calculando qual vai ser o custo da ligacao
	if (!strcmp(o.tipo, "INF" )) custo_da_ligacao =2;
	if (!strcmp(o.tipo, "REC" )) custo_da_ligacao =5;
	if (!strcmp(o.tipo, "COM" )) custo_da_ligacao =7;
	tempo_para_saida_da_ligacao =custo_da_ligacao +tempo;
	//devolve o valor do custo de tempo da ligacao
	return custo_da_ligacao;
}



objeto Gravacao_de_dados_urgencia (no *novo)
{
	objeto o =novo->o;
	strcpy (o.estado, "urgencia");
	return o;
}



void Gravacao_de_dados (objeto o, int tempo)
{
	if (!strcmp (o.estado, "normal"))
		printf ("atendido %d %s\n", tempo, o.user);
	else
		printf ("urgencia %d %s\n", tempo, o.user);
}



int Insere_resto_elementos_dupla (lista *fila, lista *fila_urgencia, no *ultimo_urgencia, int tempo_para_urgencia)
{
	//o novo novamente é o primeiro da fila
	no *novo =primeiro_no (fila); 
	 //atualiza o objeto
	objeto o=novo->o, ant_o;
	//enquanto ele estiver esperando mais d 4min
	while (o.tempo_entrada <= tempo_para_urgencia) 
	{
		novo->o =Gravacao_de_dados_urgencia (novo);
		//fila de urgencia aumenta
		fila_urgencia->tam++; 
		//a fila normal diminui
		fila->tam--; 
		//se existir o próximo nó
		if (novo->sucessor !=NULL) 
		{
			//troca o primeiro da fila normal
			fila->primeiro =sucessor_no (novo, fila); 
			//coloca o novo nó na fila de urgencia
			ultimo_urgencia->sucessor =novo;
			//termina de colocar o nó na fila
			novo->anterior =ultimo_urgencia; 
			//por ser o ultimo a entrar não tem próximo
			novo->sucessor =NULL; 
			//atualiza o novo para o priemiro da fila normal
			novo =primeiro_no (fila); 
			//o novo primeiro da fila normal nao tem anterior
			novo->anterior =NULL; 
			ant_o =ultimo_urgencia->o;
			//atualiza o objeto
			o =novo->o;
			//atualiza o ultimo no da fila de urgencia
			ultimo_urgencia =sucessor_no (ultimo_urgencia, fila_urgencia);
		}
		//senão se não existir um próximo nó
		else 
		{
			//o ultimo nó da fila normal foi para a fila de urgencia
			fila->primeiro =NULL; 
			//coloca o novo nó na fila de urgencia
			ultimo_urgencia->sucessor =novo; 
			//termina de colocar o nó na fila
			novo->anterior =ultimo_urgencia; 
			//por ser o ultimo a entrar não tem próximo
			novo->sucessor =NULL; 
			//termina as iterações, pois não tem mais elementos
			break; 
		}
	}
}




int Alguem_para_fila_de_urgencia_dupla(lista *fila, lista *fila_urgencia, int tempo)
{
	//calculo do tempo de urgencia
	int tempo_para_urgencia =tempo-4;
	no *novo =primeiro_no (fila), *primeiro, *ultimo_urgencia;
	objeto o =novo->o;
	//se o tempo é de urgencia
	if (o.tempo_entrada <= tempo_para_urgencia) 
	{
		novo->o =Gravacao_de_dados_urgencia (novo);
		//fila de urgencia aumenta
		fila_urgencia->tam++; 
		//a fila normal diminui
		fila->tam--; 
		//se não tem ninguem ainda na fila de urgencia
		if (fila_urgencia->primeiro == NULL) 
		{
			//colca o primeiro na fila urgencia
			fila_urgencia->primeiro =novo; 
			//se ter mais de um elemento na fila normal
			if (novo->sucessor !=NULL) 
				//troca o primeiro da fila normal
				fila->primeiro =novo->sucessor; 
			primeiro =primeiro_no (fila);
			//por ser o primeiro ele não tem nenhum antes dele
			primeiro->anterior =NULL; 
			//ultimo da fila de urgenica
			ultimo_urgencia =novo; 
		}
		//senao se já tem elementos na fila de urgencia
		else 
		{
			ultimo_urgencia =procura_ultimo_no (fila_urgencia);
			//coloca o novo na fila urgencia
			ultimo_urgencia->sucessor =novo; 
			//termina a junção dos ponteiros
			novo->anterior =ultimo_urgencia; 
			//se ter mais de um elemento na fila normal
			if (novo->sucessor !=NULL) 
			{
				//troca o primeiro na fila normal
				fila->primeiro =novo->sucessor; 
				primeiro =primeiro_no (fila);
				//desligando-se do no que foi para a fila de urgencia
				primeiro->anterior =NULL; 
			}
			//senao nao tem mais ninguem na fila normal
			else 
			{
				fila->primeiro =NULL;
			}
			//atualiza o ultimo no
			ultimo_urgencia =sucessor_no (ultimo_urgencia, fila_urgencia); 
		}
		//ele eh o ultimo da final de urgencia, entao desliga ele completamente da fila normal
		ultimo_urgencia->sucessor =NULL; 
		//se tem alguem na fila normal
		if (fila->primeiro !=NULL) 
		{
			Insere_resto_elementos_dupla (fila, fila_urgencia, ultimo_urgencia, tempo_para_urgencia);
		}
	}
}



void Acerta_Ponteiros_dupla (lista *fila, no *saindo)
{
	no *anterior =anterior_no (saindo, fila), *proximo =sucessor_no (saindo, fila);
	//se o no que esta saindo tem anterior
	if (anterior !=NULL) 
	{
		//se ele tem sucessor
		if (proximo !=NULL) 
		{
			//arruma os ponteiros com saida do no do meio
			anterior->sucessor =proximo;
			proximo->anterior =anterior;
		}
		//senao ele tem anterior mas nao um sucessor
		else 
		{
			//entao o anterior ao que esta saindo nao tem sucessor
			anterior->sucessor =NULL; 
		}
	}
	//senao ele nao tem anterior
	else 
	{
		//se o que esta saindo nao tem anterior mas tem sucessor
		if (proximo !=NULL) 
		{
			fila->primeiro =proximo;
			proximo->anterior =NULL;
		}
		//senao ele nao tem nem anterior nem sucessor (um elemento na fila)
		else 
		{
			//senao agora a fila nao tem mais elementos
			fila->primeiro =NULL; 
		}
	}
}



no *REC_ou_COM_dupla (lista *fila, no *melhor_no)
{
	no *buscador =melhor_no->sucessor, *anterior, *proximo =sucessor_no (melhor_no, fila);
	objeto o =melhor_no->o, buscador_o =proximo->o;
	// enquanto o tempo do atual nó e do proximo forem iguais 

	while (o.tempo_entrada == buscador_o.tempo_entrada)
	{
		// se o próximo INF, devolve o próximo
		if (!strcmp (buscador_o.tipo, "INF"))
		{
			// se existir um nó depois do próximo
			// o nó anterior ao nó que vai sair(buscador), 
			// aponta para o sucessor do nó que vai sair	
			Acerta_Ponteiros_dupla (fila, buscador);
			//autaliza o melhor_no
			melhor_no =buscador; 
			//devolve o no que e INF
			return melhor_no; 
		}
		//se a ligacao for uma RECLAMACAO
		if (!strcmp (o.tipo, "REC"))
		{
			//se existir um no depois do que esta procurando
			if (buscador->sucessor !=NULL) 
			{		
				//passa ele para o proximo no
				buscador =sucessor_no (buscador, fila); 
			}
			//senao nao tem mais nenhum elemento para analisar, entao devolve o no
			else 
			{
				//acertando os ponteiro
				Acerta_Ponteiros_dupla (fila, melhor_no);
				//deolve a melhor ligacao
				return melhor_no;
			}
		}
		//senao em ultimo caso o primeiro da fila eh COM
		else 
		{
			//sendo COM e o sucessor REC, somente troca o melhor_no
			if (!strcmp (buscador_o.tipo, "REC")) 
			{
				// atualiza o melhor_no
				melhor_no =buscador;
				//se existir um no depois do que esta procurando	
				if (buscador->sucessor !=NULL) 
				{
					//passa ele para a proxima ligacao 
					buscador =sucessor_no (buscador, fila); 
					//atualiza o objeto
					buscador_o =buscador->o;
				}
				//senao nao tem mais nenhum elemento para analisar, entao devolve a ligacao
				else 
				{
					//acertando os ponteiro
					Acerta_Ponteiros_dupla	(fila, melhor_no);
					// devolve a ligacao
					return melhor_no;
				}
			} //final se o proximo eh REC
			//senao se nao eh nem INF nem REC, entao o proximo eh compra
			else
			{
				//se existir o proximo noh
				if (buscador->sucessor !=NULL)
				{
					//passa para o proximo noh
					buscador =sucessor_no (buscador, fila);
					//atualiza o objeto
					buscador_o =buscador->o;
				}
				//senao se ele for o ultimo no 
				else
				{
					//acertando os ponteiro
					Acerta_Ponteiros_dupla	(fila, melhor_no);
					// devolve a ligacao
					return melhor_no;
				}
			}
		} 
	} //final do loop soh sai se os tempos forem diferentes
	Acerta_Ponteiros_dupla (fila, melhor_no);
	//so devolve o melhor_no aqui, quando sia por cuas que os tempos sao diferentes
	return melhor_no; 
}



no *Escolhe_Melhor_Ligacao_dupla (lista *fila)
{
	no *melhor_no =primeiro_no (fila), *primeiro;
	objeto o =melhor_no->o;
	// se for INF ou só tem ele na fila já pode devolver
	if ( ( !strcmp( o.tipo, "INF")) || (melhor_no->sucessor ==NULL))
	{
		//acerta os ponteiros
		//se só tem um na fila
		if (melhor_no->sucessor ==NULL) 
		{
			// agora não tem mais ninguem na fila
			fila->primeiro =NULL; 
		}
		//senão ele é INF e existe mais um nó na fila
		else 
		{
			// atualiza o primeiro nó da fila
			fila->primeiro =sucessor_no (melhor_no, fila); 
			primeiro =primeiro_no (fila);
			primeiro->anterior =NULL;
		}

		return melhor_no;
	}
	// procura a melhor ligacao sabendo que tem mais de uma ligacao na fila
	// e que a primeira ligacao da fila nao eh um pedido de INFORMACAO
	melhor_no = REC_ou_COM_dupla (fila, melhor_no);
	// devolve a melhor ligacao
	return melhor_no;
}



no *Atendimento (lista *fila, lista *fila_urgencia, int tempo, int *tempo_de_nao_atendimento)
{
	*tempo_de_nao_atendimento =0;
	//declara um ponteiro para ser o melhor noc
	no *melhor_no; 
	//se tem alguem na fila de urgencia
	if (fila_urgencia->primeiro !=NULL) 
	{
		//retirou uma ligacao da fila de urgencia
		fila_urgencia->tam--;
		//procura a melhor ligacao na fila de urgencia 
		melhor_no =Escolhe_Melhor_Ligacao_dupla (fila_urgencia);	
		//calcula o tempo que nao pode fazer atendimento
		*tempo_de_nao_atendimento =tempo + Custo_da_Ligacao (melhor_no, tempo);
	}
	//senao atende uma ligacao da fila normal 
	else 
	{
		//procura o primeiro no da fila normal
		no *primeiro =primeiro_no (fila);
		//recebe o objeto
		objeto o =primeiro->o; 
		//se o primeiro tempo da fila normal eh menor ou igual ao tempo
		//e nao tem ninguem na fila de urgencia
		if (o.tempo_entrada <= tempo)
		{
			//retirou um da fila normal
			fila->tam--; 
			//procura a melhor ligacao da fila normal
			melhor_no =Escolhe_Melhor_Ligacao_dupla (fila);	
			//calcula o tempo que nao pode fazer atendimento
			*tempo_de_nao_atendimento =tempo + Custo_da_Ligacao (melhor_no, tempo);
		}
		//senao ainda nao pode fazer o atendimento da ligacao por causa do tempo
		else
			return NULL;
	}
	//devolve o melhor_no para o programa principal
	return melhor_no;
}


void imprime_lista (lista *l)
{
	if (l->primeiro !=NULL)
	{
		no *novo =primeiro_no (l);
		objeto o;
		while (novo !=NULL)
		{
			o =novo->o;
			printf("%d %s %s %s\n", o.tempo_entrada, o.tipo, o.user, o.estado);
			novo =sucessor_no (novo, l);
		}
	}
	printf("\n\n");
}



main ()
{
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
	//iniciando a lista que vai ser uma fila
	lista *fila, *fila_urgencia; //sao os ponteiro para as filas
	//reserva espaco na memoria para as filas
	fila =constroi_lista ( ); 
	fila_urgencia =constroi_lista ( ); 
	
/*------------------------------------------------------------------------*/

	//faz a leitura dos dados e passa para a fila
	fila =insere_dados_na_lista_dupla (fila); 
	//Determinando primeiro tempo para fazer o primeiro atendimento
	no *primeiro =primeiro_no(fila), *melhor_no=NULL;
	//atualizando o objeto
	objeto o =primeiro->o, melhor_no_o; 
	//inicio o tempo
	int tempo =1, 
	//primeiro tempo que nao pode atender
	tempo_de_nao_atendimento =o.tempo_entrada;  

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

	//enquanto existir alguem na fila normal ou na fila de urgencia ou o tempo que pode 
	//fazer o atendimento 
	while (fila->primeiro != NULL || fila_urgencia->primeiro != NULL || tempo <= tempo_de_nao_atendimento)
	{
		//se existir alguem em alguma das filas
		if (fila->primeiro != NULL || fila_urgencia->primeiro != NULL )
		{
			// se existir alguem na fila normal
			if (fila->primeiro !=NULL) 
			{
				// procura qual ligacao esta che	gando na fila para ser atendido de acordo como tempo
				Quem_Chegou (fila, tempo);
				// verifica se tem alguem que deve ir para a fila de urgencia
				Alguem_para_fila_de_urgencia_dupla (fila, fila_urgencia, tempo);
			}
			// se o tempo for maior ou igual ao tempo que jah pode fazer o atendimento
			// ou seja pode fazer o atendimento da ligacao
			if (tempo >= tempo_de_nao_atendimento)
			{ 
				// se o melhor_no existir e estiver no tempo que pode fazer o atendimento
				if (melhor_no !=NULL && (tempo_de_nao_atendimento == tempo) )
				{
					//mostra qual ligacao foi atendida
					Gravacao_de_dados (melhor_no_o, tempo); 
					//o melhor_no nao tem mais nenhum valor
					melhor_no =NULL; 
				}
				// procura o melhor_no ou na fila de urgenica, ou na fila normal
				melhor_no =Atendimento (fila, fila_urgencia, tempo, &tempo_de_nao_atendimento);
				if (melhor_no !=NULL)
					//recebe o objeto do melhor_no
					melhor_no_o =melhor_no->o;
			}
		} //final da verificacao se tem alguem em alguma das filas
		else //senao, se esta no ultimo no da fila
		{
			//se existo o melhor_no e o tempo eh o que pode atender
			if (melhor_no !=NULL && tempo_de_nao_atendimento ==tempo)
			{
				//mostra qual ligacao foi atendida
				Gravacao_de_dados (melhor_no_o, tempo); 
 				//libera o no
				free (melhor_no);
			} 
		} //fim da verificacao de atendimento ou nao ;
		//aumenta o tempo
		tempo++; 
	} //fim do loop de atendimentos
	 // isto eh todas as ligacoes jah foram atendidas
	
	free(fila); //lebera o espaco de memoria que era da fila
	free(fila_urgencia); //lebera o espaco de memoria que era da fila de urgencia
}
/* REPRESENTACAO DA FILA

	////////////////////////////////////////////////////////////////////////////////
	//	   tempo_entrada  //            //   tempo_entrada   //            //
	//							//    ////    //   				     //   ///      //
	//		tipo				//	ponteiro   //   tipo            // ponteiro   //
	//		user				//  para o    //   user            //   para o   //
	//		estado			//	proximo	  //   estado          // proximo    //
	//							//  no	     //                   //  no        //
	///////////////////////////////////////////////////////////////////////////////// 
*/
