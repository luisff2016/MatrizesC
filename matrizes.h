/*
define um tipo strutura pra matriz q contem linhas colunas e um ponteiro pra ponteiro
*/
typedef struct{
 	int linhas;
	int colunas;
	float **valores;
}matriz;

//variavel global que indica o numero de matrizes q tem no arquivo
int numeroMatrizes;

/*
descriçao: aloca uma matriz na memoria
parametros: o numero de linhas e colunas da matriz a ser alocada
retorno: a matriz alocada
*/
matriz *alocaMatriz(int linhas,int colunas);

/*
descriçao: desaloca uma matriz da memoria
parametros: matriz a ser desalocada
retorno: void
*/
void desalocaMatriz(matriz *m);

/*
descricao: funcao calcula o derminante de um matriz
parametros: apontador p/ a matriz a qual sera calculada o determinante
retorno: retorna o determinando do tipo float
*/
float determinante(matriz *m);

/*
descricao: funcao responsavel pela divisao de uma matriz por um numero real inteiro
parametros: apontador p/ a matriz que sera dividida e um divisor do tipo float
retorno: retorna a matriz dividida por k
*/
matriz *divideEscalar(matriz *m,float k);

/*
descricao: funcao responsavel pela multiplicaçao de uma matriz por um numero real inteiro
parametros: apontador p/ a matriz que sera multiplicada e um multiplicador do tipo float
retorno: retorna a matriz multiplicada por k
*/
matriz *multiplicaEscalar(matriz *m,float k);

/*
descricao: funcao responsavel pela tranposiçao de uma matriz
parametros: apontador p/ a matriz q sera transposta
retorno: a matriz transposta
*/
matriz *transpor(matriz *m);

/*
descricao: monta a matriz cofator, junto com a funcao semicof
parametros: apontador p/ matriz que sera calculada a matriz cofator
retorno: matriz dos cofatores
*/
matriz *cofator(matriz *m);

/*
descricao:funcao calcula a inversao da matriz
parametros: apontador p/ matriz que sera calculada a inversao
retorno: a inversa da matriz
*/
matriz *inversao(matriz *m);

/*
descricao:funcao que multiplica 2 matrizes
parametros:as matrizes que serao multiplicadas
retorno:matriz resultado da multuplicacao
*/
matriz *multiplicaMatriz(matriz* m1, matriz* m2);

/*
descricao:funcao que verifica se uma matriz é quadrada
parametros:vetor de matrizes e o indice da matriz que sera verificada no vetor de matrizes
retorno:1 para quadrada 0 pra nao quadrada
*/
int verificaQuadrada(matriz **m,int indice);

/*
descricao:funcao que verifica se uma matriz é nula
parametros:vetor de matrizes
retorno:0 para nula
*/
int verificaNula(matriz **m,int indice);

/*
descricao:funcao que calcula a adjunta de uma matriz
parametros:matriz que tera sua adjunta calculada
retorno:matriz adjunta
*/
matriz *adjuntaMatriz(matriz *m);


