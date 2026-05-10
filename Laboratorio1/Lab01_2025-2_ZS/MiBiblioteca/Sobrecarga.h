//
// Created by DerikZS on 25/03/2026.
//

#ifndef LAB01_2025_2_SOBRECARGA_H
#define LAB01_2025_2_SOBRECARGA_H

#include <iostream>
#include <fstream>
using namespace std;

char * leecadena(ifstream &arch,int max, char caracter_limitador);
void operator>> (ifstream &arch, Cursos &curso);
void operator>> (ifstream &arch, Alumnos &alumnos);
int operator >= (Cursos *arr_cursos, Cursos curso);
int operator <=(Alumnos *arr_alumnos, Alumnos alumno);
void operator ++ (Cursos &curso, int a);
bool operator > (Cursos curso, char *cod_curso);
bool operator > (Alumnos alumno, int cod_alumno);
void operator +=(Cursos &curso,Alumnos &alumno);
void operator <<(ofstream &nombArch, Cursos &curso);

#endif //LAB01_2025_2_SOBRECARGA_H