#include <stdio.h>
#include <stdlib.h>

void readBros(int**, int**, int, int);
void printBro(int*, int);
void initializeMatrix(int***, int, int);
void printMatrix(int**, int*, int*, int, int);
void runLCS(int**, int*, int*, int, int);
int max(int, int);
void freeMatrix(int**, int);

int main(int argc, char const *argv[]) {
	int cases, dimension, l1, l2;
	int *bro1, *bro2;
	int **matrix;

	scanf("%d\n", &cases);
	for( ; cases > 0; cases-- ) {
		scanf("%d %d %d\n", &dimension, &l1, &l2);
		readBros(&bro1, &bro2, l1, l2);
		initializeMatrix(&matrix, l1, l2);

		runLCS(matrix, bro1, bro2, l1, l2);
		
		// printf("Matrix after algorithm\n");
		// printMatrix(matrix, bro1, bro2, l1, l2);

		printf("%d\n", matrix[l1][l2]);

		free(bro1);
		free(bro2);
		freeMatrix(matrix, l1);
	}
	return 0;
}

/*****
* void readBros
******
* Almacena los arreglos de enteros desde la entrada estándar
******
* Input:
* int** bro1: puntero al arreglo correspondiente al primer hermano
* int** bro2: puntero al arreglo correspondiente al segundo hermano
* int l1: largo del primer arreglo
* int l2: largo del segundo arreglo
*****/
void readBros(int** bro1, int** bro2, int l1, int l2) {
	int i;
	*bro1 = (int *)malloc(sizeof(int)*l1);
	for( i = 0; i < l1; i++ )
		scanf("%d", &(*bro1)[i]);

	*bro2 = (int *)malloc(sizeof(int)*l2);
	for( i = 0; i < l2; i++ )
		scanf("%d", &(*bro2)[i]);
}

/*****
* void printBro
******
* Imprime hacia la salida estándar el contenido de un arreglo de 
* enteros, separados por tabulaciones
******
* Input:
* int* bro: arreglo a imprimir
* int l: largo del arreglo
*****/
void printBro(int* bro, int l) {
	int i;
	for( i = 0; i < l; i++ )
		printf("%d\t", bro[i]);
	printf("\n");
}

/*****
* void initializeMatrix
******
* Inicializa la matriz a usar para correr el algoritmo que calcule
* la subsecuencia más larga.
* Realiza los mallocs correspondientes y también inicializa cada elemento
* en 0.
******
* Input:
* int*** matrix: puntero a la matriz
* int l1: tamaño del arreglo del primer hermano
* int l2: tamaño del arreglo del segundo hermano
*****/
void initializeMatrix(int*** matrix, int l1, int l2) {
	int i, j;

	*matrix = (int **)malloc(sizeof(int*)*(l1+1));
	for( i = 0; i < l1+1; i++ )
		(*matrix)[i] = (int *)malloc(sizeof(int)*(l2+1));

	for(i = 0; i < l1+1; i++)
		for(j = 0; j < l2+1; j++)
			(*matrix)[i][j] = 0;
}

/*****
* void printMatrix
******
* Imprime hacia la salida estándar el contenido de la matriz usada al
* correr el algoritmo para obtener la subsecuencia más larga.
* Usada a modo de referencia.
******
* Input:
* int** matrix: matriz usada en el algoritmo para obtener la subsecuencia.
* int* bro1: arreglo de enteros que contienen los pasos dados por el primer hermano
* int* bro2: arreglo de enteros que contienen los pasos dados por el segundo hermano
* int l1: tamaño del arreglo del primer hermano
* int l2: tamaño del arreglo del segundo hermano
*****/
void printMatrix(int** matrix, int* bro1, int* bro2, int l1, int l2) {
	int i, j;
	printf("\t\t");
	printBro(bro2, l2);
	for(i = 0; i < l1+1; i++) {
		i > 0 ? printf("%d\t", bro1[i-1]) : printf("\t");
		for(j = 0; j < l2+1; j++)
			printf("%d\t", matrix[i][j]);
		printf("\n");
	}
}

/*****
* void runLCS
******
* Corre el algoritmo para obtener la subsecuencia más larga
******
* Input:
* int** matrix: matriz usada en el algoritmo.
* int* bro1: arreglo de enteros que contienen los pasos dados por el primer hermano
* int* bro2: arreglo de enteros que contienen los pasos dados por el segundo hermano
* int l1: tamaño del arreglo del primer hermano
* int l2: tamaño del arreglo del segundo hermano
*****/
void runLCS(int** matrix, int* bro1, int* bro2, int l1, int l2) {
	int i, j;
	for(i = 1; i < l1+1; i++)
		for(j = 1; j < l2+1; j++)
			if( bro1[i-1] == bro2[j-1] )
				matrix[i][j] = 1 + matrix[i-1][j-1];
			else
				matrix[i][j] = max(matrix[i-1][j], matrix[i][j-1]);
}

/*****
* int max
******
* Entrega el maximo entre 2 enteros
******
* Input:
* int i: primer entero
* int j: segundo entero
******
* Returns:
* int, maximo valor entre los enteros entregados como argumento
*****/
int max(int i, int j) {
	return i > j ? i : j;
}

/*****
* void freeMatrix
******
* Libera el espacio utilizado por la matriz.
******
* Input:
* int** matrix: matriz usada en el algoritmo.
* int l1: tamaño del arreglo del primer hermano, que a su vez indica la 
	cantidad de filas en la matriz
*****/
void freeMatrix(int** matrix, int l1) {
	int i;
	for( i = 0; i < l1+1; i++)
		free(matrix[i]);
	free(matrix);
}