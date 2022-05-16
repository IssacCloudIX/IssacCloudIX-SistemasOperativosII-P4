//
// ParallelMatrix.h
// Practica4
//
//

#pragma once

#ifndef ParallelMatrix_h
#define ParallelMatrix_h

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//Prototipos de funciones
void inicializar (int *, int, int);
void suma (int *, int *, int *, int, int);
void sumaParalela (int *, int *, int *, int, int);
void mayor (int *, int *, int, int);
void mayorParalela (int *, int *, int, int);

#endif
