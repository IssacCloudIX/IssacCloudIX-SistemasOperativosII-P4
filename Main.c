//
// Main.c
// Practica4
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ParallelMatrix.h"

int main(int argc, char** argv)
{
	
	//Variables a utilizar
	int renglones[6] = {10, 50, 200, 1000, 1200, 1920}; 
	int columnas[6] = {20, 50, 100, 1000, 1200, 1080}; 
	double tiempoSimulacion[4][6][4]; 
	int accion; 
	int max; 
	int *matriz; 
	int *auxiliar;
	int *resultado; 
	int procesadores, hilos; 
	// Mediciones internas del tiempo 
	double inicio, fin; 
	// Medicion total del tiempo
	double principio, final; 
	
	//Instrucciones para realizar la simulacion con 1, 2, 3 y 4 hilos disponibles para 4 nucleos.
	principio = omp_get_wtime();
	for (int i = 0; i < 4; i++)
	{
		
	//Instrucciones para utilizar una cantidad de hilos.	
		omp_set_num_threads(i + 1);
	//Instruccion para imprimir la cantidad de nucleos disponibles en la computadora
	//y la cantidad maxima de hilos que se solicitaron.
		procesadores = omp_get_num_procs();
		hilos = omp_get_max_threads();
		printf("Cantidad de nucleos disponibles: %d.\nMaximo de hilos: %d.\n", procesadores, hilos);
	/*Instrucciones para realizar la simulacion con matrices de
	10 x 20
	50 x 50
	200 x 100
	1000 x 1000
	1200 x 1200
	1920 x 1080.
	*/
		for (int j = 0; j < 6; j++)
	//Funcion para inicializar las matrices.
		{
			accion = 0;
			matriz = (int *) malloc (renglones[j] * columnas[j] * sizeof(int));
			auxiliar = (int *) malloc (renglones[j] * columnas[j] * sizeof(int));
			resultado = (int *) malloc (renglones[j] * columnas[j] * sizeof(int));
			inicializar(matriz, renglones[j], columnas[j]);
			inicializar(auxiliar, renglones[j], columnas[j]);
	//Funcion para sumar las matrices de forma no paralela y toma de tiempo.
			inicio = omp_get_wtime();
			suma(matriz, auxiliar, resultado, renglones[j], columnas[j]);
			fin = omp_get_wtime();
			tiempoSimulacion[i][j][accion] = fin - inicio;
			accion++;
	//Funcion para sumar las matrices de forma paralela y toma de tiempo.
			inicio = omp_get_wtime();
			sumaParalela(matriz, auxiliar, resultado, renglones[j], columnas[j]);
			fin = omp_get_wtime();
			tiempoSimulacion[i][j][accion] = fin - inicio;
			accion++;
	//Funcion para obtener el valor maximo de forma no paralela y toma de tiempo.
			inicio = omp_get_wtime();
			mayor(matriz, &max, renglones[j], columnas[j]);
			fin = omp_get_wtime();
			tiempoSimulacion[i][j][accion] = fin - inicio;
			accion++;
	//Funcion para obtener el valor maximo de forma paralela y toma de tiempo.
			inicio = omp_get_wtime();
			mayorParalela(matriz, &max, renglones[j], columnas[j]);
			fin = omp_get_wtime();
			tiempoSimulacion[i][j][accion] = fin - inicio;
			accion++;
			if (matriz)
				free(matriz);
			if (auxiliar) 
				free(auxiliar);
			if (resultado)
				free(resultado);
		}
		
	}
	final = omp_get_wtime();
	//Impresion de tabla de tiempos de TODA la simulacion.
	printf("\nTiempo de toda la simulación: %lf segundos\n", final - principio);
	for (int i = 0; i < 4; i++)
	{
		puts("");
		switch(i)
		{
			case 0:
				printf("Tiempos con 1 hilo (en segundos):\n-----------------------------------------------\n");
			break;
			case 1:
				printf("Tiempos con 2 hilos (en segundos): \n-----------------------------------------------\n");
			break;
			case 2:
				printf("Tiempos con 3 hilos (en segundos): \n-----------------------------------------------\n");
			break;
			case 3:
				printf("Tiempos con 4 hilos (en segundos):\n-----------------------------------------------\n");
			break;
		}
		printf("\t\t\t");
		printf("%20s", "suma NO paralela: ");
		printf("%20s", "suma paralela: ");
		printf("%20s", "mayor NO paralelo: ");
		printf("%20s", "mayor paralelo: ");
		puts("");
		for (int j = 0; j < 6; j++)
		{
			puts("");
			switch(j)
			{
				case 0:
					printf("%-25s", "Matriz 10 x 20:");
				break;
				case 1:
					printf("%-25s", "Matriz 50 x 50:");
				break;
				case 2:
					printf("%-25s", "Matriz 200 x 100:");
				break;
				case 3:
					printf("%-25s", "Matriz 1000 x 1000:");
				break;
				case 4:
					printf("%-25s", "Matriz 1200 x 1200:");
				break;
				case 5:
					printf("%-25s", "Matriz 1920 x 1080:");
				break;
			}
			printf("\t");
			for(int k = 0; k < 4; ++k)
				printf("%-20lf", tiempoSimulacion[i][j][k]);
			puts("");
		}
		
		
	}
	return EXIT_SUCCESS;
	
}


