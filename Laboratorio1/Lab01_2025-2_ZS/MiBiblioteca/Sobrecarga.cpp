//
// Created by DerikZS on 25/03/2026.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

#include "Estructuras.h"
#include "Sobrecarga.h"

using namespace std;

void operator>> (ifstream &arch, Cursos &curso) {

    char c;
    int numero;
    curso.codigo=leecadena(arch,10,',');
    curso.nombre=leecadena(arch,100,',');
    arch>>curso.creditos>>c>>numero>>c;
    curso.docente=leecadena(arch,100,'\n');
    curso.numpresencial=0;
    curso.numsemipresencial=0;
    curso.numvirtual=0;

}

void operator>> (ifstream &arch, Alumnos &alumno) {
    char c;
    arch>>alumno.codigo>>c;
    alumno.nombre=leecadena(arch,100,',');
    arch>>alumno.tipo;
}

bool operator > (Cursos curso, char *cod_curso) {

    if (strcmp(curso.codigo,cod_curso)==0) {
        return true;
    }
    return false;
}

bool operator > (Alumnos alumno, int cod_alumno) {
    if (alumno.codigo==cod_alumno)
        return true;
    return false;
}

void operator +=(Cursos &curso,Alumnos &alumno) {

    if (alumno.tipo=='P') {
        curso.presencial[curso.numpresencial]=alumno;
        curso.numpresencial++;
    }else if (alumno.tipo=='S') {
        curso.semipresencial[curso.numsemipresencial]=alumno;
        curso.numsemipresencial++;
    }else if (alumno.tipo=='V') {
        curso.vvirtual[curso.numvirtual]=alumno;
        curso.numvirtual++;
    }
}

int operator >= (Cursos *arr_cursos, Cursos curso) {
    for (int i=0;arr_cursos[i].codigo!=nullptr;i++) {
        if (arr_cursos[i]>curso.codigo) {
            return i;
        }
    }
    return -1;
}

int operator <=(Alumnos *arr_alumnos, Alumnos alumno) {

    for (int i=0;arr_alumnos[i].codigo!=0;i++) {
        if (arr_alumnos[i].codigo>alumno.codigo) {
            return i;
        }
    }
    return -1;
}

void operator ++ (Cursos &curso, int a)  {//i++
    int total=curso.numpresencial+curso.numvirtual+curso.numsemipresencial;
    double porcentaje = 1.0*curso.numpresencial/total;

    if (porcentaje>=0.5) {
        curso.tipofinal=new char[50];
        strcpy(curso.tipofinal,"La clase se dictara en aula");
    }else {
        curso.tipofinal=new char[50];
        strcpy(curso.tipofinal,"La clase se dictara 100% virtual");
    }
}

void operator <<(ofstream &nombArch, Cursos &curso) {

    nombArch<<curso.codigo<<setw(20)<<curso.nombre<<endl;
    nombArch<<curso.docente<<setw(20)<<endl;
    nombArch<<"Alumnos presenciales: "<<setw(5)<<curso.numpresencial<<endl;
    nombArch<<"Alumnos semipresenciales: "<<setw(5)<<curso.numsemipresencial<<endl;
    nombArch<<"Alumnos virtuales: "<<setw(5)<<curso.numvirtual<<endl;
    curso++;
    nombArch<<curso.tipofinal<<endl;
}

char * leecadena(ifstream &arch,int max, char caracter_limitador) {
    char buffer[max],*ptr_cadena;
    arch.getline(buffer,max,caracter_limitador);
    if (arch.eof()) return nullptr;
    ptr_cadena=new char[strlen(buffer)+1];

    strcpy(ptr_cadena,buffer);

    return ptr_cadena;
}