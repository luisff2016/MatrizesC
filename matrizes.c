#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"

matriz *alocaMatriz(int linhas,int colunas)
{
        matriz *mat;
        int i,j;
        
        mat=(matriz*)malloc(sizeof(matriz));
        if(mat==NULL)
                     return NULL;
        mat->valores=(float**)malloc(linhas*sizeof(float*));
        if(mat->valores==NULL)
        {
                              free(mat);
                              return NULL;
        }
        for(i=0;i<linhas;i++)
        {
                             mat->valores[i]=(float*)malloc(colunas*sizeof(float));
                             if(mat->valores[i]==NULL)
                             {
                                                      for(j=i-1;j>=0;j--)
                                                                         free(mat->valores[j]);
                                                      free(mat->valores);
                                                      free(mat);
                                                      return NULL;
                                                      
                             }
        }
        return mat;
}

void desalocaMatriz(matriz *m)
{
     int i;
     for(i=0;i<(m->colunas);i++)
     {
                                free(m->valores[i]);
     }
     free(m->valores);
     free(m);
}

void imprimeArquivo(matriz *invK,FILE *fp2)
{
	int i,j;
	fprintf(fp2,"%d\n",invK->linhas);
	fprintf(fp2,"%d\n",invK->colunas);
			
	for(i=0;i<invK->linhas;i++)
	{
		for(j=0;j<invK->colunas;j++)
		{
			fprintf(fp2,"%g ",invK->valores[i][j]);
		}
		fprintf(fp2,"\n");
	}
	desalocaMatriz(invK);
}

matriz *semicof(matriz *m, int lin, int col)
{
    int i,j,k,l;
    matriz *cof;
    
    cof=alocaMatriz(m->linhas-1,m->colunas-1);
    
    if(cof==NULL)
    {
                         return NULL;
    }
    
    cof->linhas = m->linhas -1;
    cof->colunas = m->colunas -1;
    
    for(i=0,k=0;i<m->linhas;i++)
    {
	                              for(j=0,l=0;j<m->colunas;j++)
                                  {
	                                                            if((i != lin) && (j!=col))
		                                                        cof->valores[k][l] = m->valores[i][j];
	                                                            if(j != col)
		                                                        l++;
                                  }
                                  if(i != lin)
	                              k++;
    }
    return cof;
}

float determinante(matriz *m)
{
    int lin,sinal;
    float det;
    matriz* m1;
    
    if((m->linhas)==1)
	              return (m->valores[0][0]);

    sinal =-1;
    det=0;

    for(lin=0;lin<(m->linhas);lin++)
    {
	                               	m1=semicof(m,lin,0);
					sinal = sinal * -1;
	                               	det = det + (m->valores[lin][0] * determinante(m1) * sinal);
	                               	desalocaMatriz(m1);
    }
    return det;
}

matriz *divideEscalar(matriz *m,float k)
{
    matriz *resultado;
    int i,j;
    
    resultado=alocaMatriz(m->linhas,m->colunas);
    
    if(resultado==NULL)
    {
                         return NULL;
    }
    
    resultado->linhas=m->linhas;
    resultado->colunas=m->colunas;
    
    if(k==0)
            return resultado;
    
    for(i=0;i<(resultado->linhas);i++)
    {
	                          for(j=0;j<(resultado->colunas);j++)
                                  {
                                                                      resultado->valores[i][j]=m->valores[i][j]/k;               
                                  }
    }
    return resultado;
}

matriz *multiplicaEscalar(matriz *m,float k)
{
    matriz *resultado;
    int i,j;
    
    resultado=alocaMatriz(m->linhas,m->colunas);
    
    if(resultado==NULL)
    {
                         return NULL;
    }
    
    resultado->linhas=m->linhas;
    resultado->colunas=m->colunas;
    
    if(k==0)
            return resultado;
    
    for(i=0;i<(resultado->linhas);i++)
    {
	                          for(j=0;j<(resultado->colunas);j++)
                                  {
                                                                      resultado->valores[i][j]=m->valores[i][j]*k;               
                                  }
    }
    return resultado;
}

matriz *transpor(matriz *m)
{
    matriz *transposta;
    int i,j;
    
    transposta=alocaMatriz(m->linhas,m->colunas);
    
    if(transposta==NULL)
    {
                         return NULL;
    }
    
    transposta->linhas=m->linhas;
    transposta->colunas=m->colunas;
    
    for(i=0;i<(transposta->linhas);i++)
    {
	                              for(j=0;j<(transposta->colunas);j++)
                                                                      transposta->valores[i][j]=m->valores[j][i];
    }
    return transposta;
}

matriz *cofator(matriz *m)
{
    matriz *cof,*m1;
    int i,j;
    
    cof=alocaMatriz(m->linhas,m->colunas);
    
    if(cof==NULL)
    {
                         return NULL;
    }
    
    cof->linhas=m->linhas;
    cof->colunas=m->colunas;
    
    if((cof->linhas)==1 && (cof->colunas)==1)
                     return m;     
    
    for(i=0;i<(cof->linhas);i++)
    {
	                              	for(j=0;j<(cof->colunas);j++)
                                  	{
                                                                m1=semicof(m,i,j);
								if((i+j)%2==0)
                                                                              cof->valores[i][j]=determinante(m1);
                                                                else
                                                                    cof->valores[i][j]=-determinante(m1);
                                  	}
	desalocaMatriz(m1);
    }
    return cof;
}

matriz *inversao(matriz *m)
{
              matriz *inversa,*m1,*m2;              
		
	      inversa=alocaMatriz(m->linhas,m->colunas);

          inversa->linhas=m->linhas;
          inversa->colunas=m->colunas;
              
          if(((m->colunas)!= (m->linhas)) || (determinante(m)==0))
	      {
                   	m->colunas=0;
			        m->linhas=0;
			        return m;
          }
          m1=cofator(m);
	      m2=transpor(m1);
	      inversa=(divideEscalar(m2,determinante(m)));
	      desalocaMatriz(m1);
	      desalocaMatriz(m2);
		                 
          return inversa;
}

matriz *multiplicaMatriz(matriz* m1, matriz* m2)
{
	matriz *result;
	int i,j,k;

	result = alocaMatriz(m1->linhas, m2->colunas);	

	if(m1->colunas != m2->linhas)
	{	
		result->linhas=0;		
		result->colunas=0;
		return result;
	}
	
	for(i=0;i<m1->linhas;i++)
	{
		for(j=0;j<m2->colunas;j++)
		{
			result->valores[i][j] = 0;

			for(k=0;k<m1->colunas;k++)
				result->valores[i][j] = result->valores[i][j] + m1->valores[i][k]  * m2->valores[k][j];

		}
	}

	result->linhas = m1->linhas;
	result->colunas = m2->colunas;
	return result;
}

int verificaQuadrada(matriz **m,int indice)
{
	if(m[indice]->linhas==m[indice]->colunas && m[indice]->linhas!=0 && m[indice]->colunas!=0)
		return 1;

	return 0;
}

int verificaNula(matriz **m,int indice)
{
	int i,j;
	
	if(indice>numeroMatrizes)
	{
		return 2;
	}

	for(i=0;i<m[indice]->linhas;i++)
		for(j=0;m[indice]->colunas;j++)
		{
			if(m[indice]->valores[i][j]!=0)
				return 1;
		}
	return 0;
}

matriz *adjuntaMatriz(matriz *m)
{
	matriz* adjunta, *result;

	result = cofator(m);
	adjunta = transpor(result);
	desalocaMatriz(result);

	return adjunta;
}


