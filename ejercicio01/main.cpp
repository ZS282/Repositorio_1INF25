#include <iostream>
#include "Alumno.h"

int main() {
    //No se dice declarar objeto, sino instanciar un objeto
    //Existen 2 formas de instanciar (estatica o dinamica)
    //Se instancia un objeto a
    //Instantiation estatico
    // Alumno a(123,589);
    // Alumno b = a;
    // a.imprimir();//Se llama su metodo imprimir
    //Instanciamiento dinamico
    Alumno * a = new Alumno();
    Alumno b=*a;
    delete a;

    return 0;
}