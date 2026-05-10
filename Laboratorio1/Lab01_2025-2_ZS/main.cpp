
#include <iostream>
#include "MiBiblioteca/Estructuras.h"
#include "MiBiblioteca/Funciones.h"
using namespace std;


int main() {

    struct Alumnos alumnos[100];
    struct Cursos cursos[10];

    leerAlumnos("Alumnos.csv",alumnos);
    leerCursos("Cursos.csv",cursos);

    leerMatricula("Matricula.csv",alumnos,cursos);

    imprimirReporte("reporte.txt",cursos);
    return 0;
}