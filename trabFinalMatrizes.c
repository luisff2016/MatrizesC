#include "matrizes.h"
#include <stdio.h>
#include <stdlib.h>

matriz **acrescentaMatriz(matriz **m,matriz *deposito);
matriz* recebeTeclado();
void visualizaMatriz(matriz *m);
matriz **lerArquivo(FILE *fp);
void listaMatrizes(matriz **m);
void imprimeResultado(matriz **m);
matriz **adicionaMatriz(matriz **m);
matriz *multiplicaE(matriz **m);
matriz *divideE(matriz **m);
matriz *multiplicaM(matriz **m);
int det(matriz **m);
matriz *transpondo(matriz **m);
matriz **salvarMatriz(matriz **m,matriz *deposito);
void menu(matriz **m,matriz *deposito);

matriz **acrescentaMatriz(matriz **m,matriz *deposito)
{
	matriz **result;
	int i;

	numeroMatrizes++;
	
	result=(matriz**)malloc(numeroMatrizes*sizeof(matriz*));
	
	for(i=0;i<numeroMatrizes;i++)
		result[i]=m[i];
	
	result[numeroMatrizes-1]=deposito;

	free(m);	
	
	return result;
}

matriz *recebeTeclado()
{
	int i,j,lin,col;
	matriz *m;

	printf("Numero de linhas: ");	
	scanf("%d",&lin);
	printf("Numero de colunas: ");
	scanf("%d",&col);

	m=alocaMatriz(lin,col);

	m->linhas=lin;
	m->colunas=col;
	
	for(i=0;i<m->linhas;i++)
	{
		for(j=0;j<m->colunas;j++)
			scanf("%f",&m->valores[i][j]);
	}
	return m;
}	

void visualizaMatriz(matriz *m)
{
	int i,j;
	
	printf("%d\n",m->linhas);
	printf("%d",m->colunas);

		for(i=0;i<m->linhas;i++)
		{
			printf("\n");
			for(j=0;j<m->colunas;j++)
				printf("%g ",m->valores[i][j]);
		}
		printf("\n");
}

matriz **lerArquivo(FILE *fp)
{
    	int i,j,k;
	int lin,col;
	char teste;
	matriz **m;
	
	if(fp!=NULL && !feof(fp))
	{	
		if(numeroMatrizes==0)
			return NULL;
		
        m=(matriz**)malloc(numeroMatrizes*sizeof(matriz*));
        if(m==NULL)
            return NULL;                
		for(k=0;k<numeroMatrizes;k++)
		{		
			teste=fscanf(fp,"%d",&lin);
			teste=fscanf(fp,"%d",&col);
			if(teste==EOF)
				return NULL;		
	
			m[k]=alocaMatriz(lin,col);
		
			m[k]->linhas=lin;
			m[k]->colunas=col;

			for(i=0;i<m[k]->linhas;i++)
			{
				for(j=0;j<m[k]->colunas;j++)
				{
					fscanf(fp,"%f",&m[k]->valores[i][j]);
				}
			}
			lin=0;
			col=0;
		}
		return(m);
	}
	return NULL;
}

void listaMatrizes(matriz **m)
{
	int k;
	
	for(k=0;k<numeroMatrizes;k++)
	{
		printf("Matriz %d\n",k);
		printf("%d\n",m[k]->linhas);
		printf("%d\n",m[k]->colunas);
	}
}

void imprimeResultado(matriz **m)
{
	int i,j,k;
	FILE *fp;
	fp=fopen("matrizes.txt","w+");

	fprintf(fp,"%d\n",numeroMatrizes);

	for(i=0;i<numeroMatrizes;i++)
	{
		fprintf(fp,"%d\n",m[i]->linhas);
		fprintf(fp,"%d",m[i]->colunas);

		for(j=0;j<m[i]->linhas;j++){
			fprintf(fp,"\n");
			for(k=0;k<m[i]->colunas;k++)
				fprintf(fp,"%g ",m[i]->valores[j][k]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}

matriz **adicionaMatriz(matriz **m)
{
	matriz *aux;

	aux=recebeTeclado();

	m=acrescentaMatriz(m,aux);

	return m;
}	


matriz *multiplicaE(matriz **m)
{
	float multiplicador=0.0;
	int indice=0;
	matriz *aux;	
	
	printf("Qual o indice da matriz: ");
	scanf("%d",&indice);
	
	if(indice>numeroMatrizes-1)
		return NULL;
	
	printf("\nMultiplicador: ");
	scanf("%f",&multiplicador);
	aux=multiplicaEscalar(m[indice],multiplicador);

	visualizaMatriz(aux);
	return aux;
}

matriz *divideE(matriz **m)
{
	float divisor;
	int indice=0;
	matriz *aux;	
	
	printf("Qual o indice da matriz: ");
	scanf("%d",&indice);
	
	if(indice>numeroMatrizes-1)
		return NULL;

	printf("\nDivisor: ");
	scanf("%f",&divisor);
	if(divisor==0)
		return NULL;

	aux=divideEscalar(m[indice],divisor);

	visualizaMatriz(aux);
	return aux;
}

matriz *multiplicaM(matriz **m)
{
	int indice1=0,indice2=0;
	matriz *result;
	
	printf("Qual o indice da primeira matriz:");
	scanf("%d",&indice1);

	printf("Qual o indice da segunda matriz:");
	scanf("%d",&indice2);

	if(indice1>numeroMatrizes-1 && indice2>numeroMatrizes-1)
		return NULL;

	if((m[indice1]->colunas!=m[indice2]->linhas))
		return NULL;
	else
	{
		result=multiplicaMatriz(m[indice1],m[indice2]);
		visualizaMatriz(result);
	}
	return result;	
}

int det(matriz **m)
{
	int indice;	
	float det;

	printf("Qual o indice da matriz que sera calculado o determinante: ");
	scanf("%d",&indice);
	if(indice>numeroMatrizes-1)
	{
		printf("Matriz inexistente.\n");
		return 1;
	}
	det=determinante(m[indice]);
	printf("%f\n",det);
	return 0;
}

matriz *cof(matriz **m)
{
	matriz* result;
	int indice;

	printf("Qual o indice da matriz que sera calculada a matriz dos cofatores: ");
	scanf("%d",&indice);
	if(indice>numeroMatrizes-1)
		return NULL;
	else
	{
		result=cofator(m[indice]);
		visualizaMatriz(result);
	}
	return result;
}

matriz *transpondo(matriz **m)
{
	int indice;
	matriz *result;	

	printf("Qual o indice da matriz que deseja transpor: ");
	scanf("%d",&indice);
	if(indice>numeroMatrizes-1)
		return NULL;
	
	result=transpor(m[indice]);
	visualizaMatriz(result);
	return result;
}

matriz *adj(matriz **m)
{
	int indice;
	matriz *result;

	printf("Qual o indice da matriz que deseja calcular a adjunta: ");
	scanf("%d",&indice);
	if(indice>numeroMatrizes-1)
		return NULL;
	
	result=adjuntaMatriz(m[indice]);
	visualizaMatriz(result);
	return result;	
}

matriz **salvarMatriz(matriz **m,matriz *deposito)
{
	int escolha;
	printf("Deseja salvar a matriz: 1-SIM 2-NAO: ");
	scanf("%d",&escolha);
	if(escolha==1)
		m=acrescentaMatriz(m,deposito);
	return m;
}

matriz *inv(matriz **m)
{
	int indice;
	matriz *result;

	printf("Qual o indice da matriz que deseja calcular a inversa: ");
	scanf("%d",&indice);
	if(indice>numeroMatrizes-1)
		return NULL;
	
	result=inversao(m[indice]);
	visualizaMatriz(result);
	return result;	
}
/*
descriçao: funcao responsavel pelo menu do programa
parametros: vetor de matrizes e uma matriz auxiliar para os calculos
retorno: void
*/
void menu(matriz **m,matriz *deposito)
{
	int escolha,indice;	
	while(escolha!=15)
	{
		printf("\t╔══════════════════════════════════════════════════════════╗\n");
		printf("\t║1)Lista de Matrizes da memoria                            ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║2)Multiplicar por Escalar                                 ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║3)Dividir por escalar                                     ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║4)Multiplicar duas matrizes                               ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║5)Verificar se a matriz é quadrada                        ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║6)Verificar se a matriz é nula                            ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║7)Calcular o determinante                                 ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║8)Calcular a transposta de uma matriz                     ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║9)Calcular a matriz dos cofatores de uma matriz           ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║10)Calcular a matriz adjunta de uma matriz quadrada       ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║11)Verificar se uma matriz é inversível                   ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║12)Calcular inversa                                       ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║13)Adicionar Matriz                                       ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║14)Imprime no arquivo                                     ║\n");
		printf("\t╠══════════════════════════════════════════════════════════╣\n");
		printf("\t║15)Sair                                                   ║\n");
		printf("\t╚══════════════════════════════════════════════════════════╝\n");
		printf("O que deseja fazer: ");
		scanf("%d",&escolha);
	
		switch(escolha)
		{
			case 1:
				listaMatrizes(m);
				break;
			case 2:
				deposito=multiplicaE(m);
				if(deposito==NULL)
					printf("Erro!!!Matriz inexistente.\n");
				else
					m=salvarMatriz(m,deposito);
				break;
			case 3:
				deposito=divideE(m);
				if(deposito==NULL)
					printf("Erro!!!Matriz inexistente.\n");
				else
					m=salvarMatriz(m,deposito);
				break;
			case 4:
				deposito=multiplicaM(m);
				if(deposito==NULL)
					printf("Nao foi possivel multiplicar.\n");
				else
					m=salvarMatriz(m,deposito);
				break;
			case 5:
				printf("Qual o indice da matriz que deseja verificar: ");
				scanf("%d",&indice);
				if(indice>numeroMatrizes-1)
				{
					printf("Matriz inexistente.\n");
					break;
				}
				if(verificaQuadrada(m,indice)==1)
					printf("É quadrada.\n");
				else
					printf("Não é quadrada.\n");
				break;
			case 6:
				printf("Qual o indice da matriz que deseja verificar: ");
				scanf("%d",&indice);

				if(verificaNula(m,indice)==2)
				{
					printf("Matriz inexistente.\n");
					break;
				}
				if(verificaNula(m,indice)==0)
					printf("Matriz nula.\n");
				else
					printf("Matriz nao nula.\n");
				break;
			case 7:
				det(m);
				break;
			case 8:
				deposito=transpondo(m);
				if(deposito==NULL)
				{
					printf("Matriz inexistente.\n");
					break;
				}
				m=salvarMatriz(m,deposito);
				break;
			case 9:
				deposito=cof(m);
				if(deposito==NULL)
				{
					printf("Matriz inexistente.\n");
					break;
				}
				m=salvarMatriz(m,deposito);
				break;
			case 10:
				deposito=adj(m);
				if(deposito==NULL)
				{
					printf("Matriz inexistente.\n");
					break;
				}
				m=salvarMatriz(m,deposito);
				break;
			case 11:
				printf("Qual o indice da matriz que deseja verificar: ");
				scanf("%d",&indice);
				if(indice>numeroMatrizes-1)
				{
					printf("Matriz inexistente.\n");
					break;
				}
				if(verificaQuadrada(m,indice)==1 && determinante(m[indice])!=0)
					printf("É inversivel.\n");
				else
					printf("Não é iversivel.\n");
				break;
			case 12:
				deposito=inv(m);
				if(deposito==NULL)
				{
					printf("Matriz inexistente.\n");
					break;
				}
				m=salvarMatriz(m,deposito);
				break;
			case 13:
				m=adicionaMatriz(m);
				break;
			case 14:
				imprimeResultado(m);
				break;
			case 15:
				break;
			default:
				printf("Escolha nao consta no menu\n");
				break;	
		}
	}
}

int main()
{
	FILE *fp;	
	matriz **m,*deposito;	
	fp=fopen("matrizes.txt","r");
	fscanf(fp,"%d",&numeroMatrizes);	
	m=lerArquivo(fp);
	fclose(fp);
	if(m==NULL)
	{
		printf("Formado de arquivo nao valido.\n");
		return 0;
	}
	menu(m,deposito);	
	return 0;
}
