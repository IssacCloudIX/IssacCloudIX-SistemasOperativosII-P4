//
// ParallelMatrix.c
// Practica4
//
//

#include "ParallelMatrix.h"
//Definicion de funciones
void inicializar(int *matriz, int renglones, int columnas)
{
	for (int i = 0; i < renglones; i++)
	{
		for (int j = 0; j < columnas; j++)
			*(matriz + (i * columnas) + j) = rand() % 256; 
	}
}

void suma(int *matriz, int *aux, int *resultado, int renglones, int columnas)
{
	for (int i = 0; i < renglones; i++)
	{
		for (int j = 0; j < columnas; j++)
			*(resultado + (i * columnas) + j) = *(matriz + (i * columnas) + j) + *(aux + (i * columnas) + columnas);
	}
}

void sumaParalela (int *matriz, int *aux, int *resultado, int renglones, int columnas)
{
	int i, j; 
	#pragma omp parallel for private (j)
	for (i = 0; i < renglones; i++)
	{
		for (j = 0; j < columnas; j++)
			*(resultado + (i * columnas) + j) = *(matriz + (i * columnas) + j) + *(aux + (i * columnas) + columnas);
	}
}

void mayor(int *matriz, int *mayor, int renglones, int columnas)
{
	int aux = -1;
	for (int i = 0; i < renglones; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			if (*(matriz + (i * columnas) + j) > aux)
				aux = *(matriz + (i * columnas) + j);
		}
	}
	*(mayor) = aux;
}

void mayorParalela (int *matriz, int *mayor, int renglones, int columnas)
{
	int i, j; 
	int mayores[renglones];
	int aux = -1;
	#pragma omp parallel for private (j)
	for (i = 0; i < renglones; i++)
	{
		for (j = 0; j < columnas; j++)
		{
			if (*(matriz + (i * columnas) + j) > aux)
				aux = *(matriz + (i * columnas) + j);
		}
		mayores[i] = aux;
	}
	aux = -1;
	for (i = 0; i < renglones; i++)
	{
		if (mayores[i] > aux)
			aux = mayores[i];
	}
	*(mayor) = aux;
}

