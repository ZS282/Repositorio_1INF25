//
// Created by DerikZS on 27/03/2026.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

#include "Funciones.h"
#include "Estructuras.h"
#include "Sobrecarga.h"

void leerAlumnos(const char *nombArch,struct Alumnos *arrAlumnos) {

    ifstream arch(nombArch,ios::in);
    int i=0;
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo"<<nombArch << endl;
        exit(1);
    }

    while (true) {
        arch>>arrAlumnos[i];
        if (arch.eof()) break;
        i++;
    }
    arrAlumnos[i].codigo=0;
}

void leerCursos(const char *nombArch,struct Cursos *arrCursos) {
    ifstream arch(nombArch,ios::in);
    int i=0;
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo"<<nombArch << endl;
        exit(1);
    }
    while (true) {
        arch>>arrCursos[i];
        if (arch.eof()) break;
        i++;
    }
    arrCursos[i].codigo=nullptr;
}

void leerMatricula(const char *nombArch, Alumnos *alumnos,Cursos *cursos) {

    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo"<<nombArch<<endl;
        exit(1);
    }

    while (true) {
        Cursos aux_cur;
        Alumnos aux_alu;
        aux_cur.codigo=leecadena(arch,10,',');
        if (arch.eof()) break;
        arch>>aux_alu.codigo;
        arch.get();
        int indice_curso= cursos>=aux_cur;
        int indice_alumno= alumnos<=aux_alu;

        cursos[indice_curso]+=alumnos[indice_alumno];
    }

}

void imprimirReporte(const char *nombArch, Cursos *arr_curso) {
    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo"<<nombArch << endl;
        exit(1);
    }

    for (int i=0;arr_curso[i].codigo!=nullptr;i++) {
        arch<<arr_curso[i];
    }
}