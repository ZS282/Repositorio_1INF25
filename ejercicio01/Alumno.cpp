//
// Created by DerikZS on 02/05/2026.
//

#include "Alumno.h" //Pascal case

#include <cstring>
//Metodos y Atributos : camelCase

//
void Alumno::imprimir() {
    cout<<"Se imprime un alumno"<<endl;
    cout<<dni<<endl;
    cout<<codigo<<endl;
}

Alumno::Alumno() {//Inicializacion

    dni=0;
    codigo=-1;
    nombre=nullptr;
    facultad=nullptr;
    ciclo=0;
    //Atributos miembro
}

Alumno::Alumno(int dni, int codigo) : Alumno(){ //Constructor propiamente dicho (opcional)
    this->dni=dni;
    this->codigo=codigo;
}

Alumno::Alumno(const Alumno & origin) {
    *this = origin;
}


int Alumno::getDni() const {//getter
    return dni;
}
void Alumno::setDni(int dni) {
    //setter
    this->dni=dni;
}
int Alumno::getCodigo() const {
    //getter
    return codigo;
}
void Alumno::setCodigo(int codigo) {
    //setter
    this->codigo=codigo;
}

char* Alumno::getNombre() const {
    return nombre;
}
void Alumno::setNombre(char *nombre) {

    delete [] this->nombre;
    this->nombre= new char[strlen(nombre)+1];
    strcpy(this->nombre,nombre);
}

char *Alumno::getFacultad() const {
    return facultad;
}
void Alumno::setFacultad(char *facultad) {
    delete [] this->facultad;
    this->facultad= new char[strlen(facultad)+1];
    strcpy(this->facultad,facultad);
}

int Alumno::getCiclo() const {
    return ciclo;
}
void Alumno::setCiclo(int ciclo) {
    this->ciclo=ciclo;
}

Alumno& Alumno::operator=(const Alumno& origin) {
    if(this!=&origin) {
        this->setDni(origin.getDni());
        this->setCodigo(origin.getCodigo());
        this->setNombre(origin.getNombre());
        this->setFacultad(origin.getFacultad());
        this->setCiclo(origin.getCiclo());
    }
    return *this;
}

Alumno::~Alumno() {
    delete [] nombre;
    delete [] facultad;
}