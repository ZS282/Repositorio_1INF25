//
// Created by DerikZS on 02/05/2026.
//

#ifndef EJERCICIO01_ALUMNO_H
#define EJERCICIO01_ALUMNO_H
#include <iostream>
#include <ostream>

#include <iostream>
using namespace std;

//Una clase puede agrupar muchos objetos
class Alumno {
    //Modificadores public, private, protected
private:
    int dni;
    int codigo;
    char *nombre;
    char *facultad;
    int ciclo;
public:
    Alumno();//Constructor por defecto
    Alumno(int dni,int codigo);//Constructor propiamente dicho (opcional)
    Alumno(const Alumno &);//Constructor de copia

    Alumno& operator=(const Alumno &);//Sobrecarga de operador binario

    int getDni() const;//getter
    void setDni(int dni);//setter

    int getCodigo() const;//getter
    void setCodigo(int codigo);//setter

    char *getNombre() const;
    void setNombre(char *nombre);

    char *getFacultad() const;
    void setFacultad(char *facultad);

    int getCiclo() const;
    void setCiclo(int ciclo);

    ~Alumno();//Destructor

    void imprimir() ;
};


#endif //EJERCICIO01_ALUMNO_H