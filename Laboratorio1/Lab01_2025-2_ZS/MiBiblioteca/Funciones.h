//
// Created by DerikZS on 27/03/2026.
//

#ifndef LAB01_2025_2_FUNCIONES_H
#define LAB01_2025_2_FUNCIONES_H

#include "Estructuras.h"

void leerAlumnos(const char *nombArch,struct Alumnos *arrAlumnos);
void leerCursos(const char *nombArch,struct Cursos *arrCursos);
void leerMatricula(const char *nombArch, Alumnos *alumnos,Cursos *cursos);
void imprimirReporte(const char *nombArch,struct Cursos *arr_curso);
#endif //LAB01_2025_2_FUNCIONES_H