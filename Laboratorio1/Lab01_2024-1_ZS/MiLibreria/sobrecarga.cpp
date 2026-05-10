//
// Created by DerikZS on 08/04/2026.
//

#include <iostream>
#include <fstream>
#include "sobrecarga.h"
#include "Estructuras.h"

#include <limits>
using namespace std;

bool operator >>(ifstream &archivo,Libro &libro) {

    char c;
    archivo.getline(libro.codigo,8,',');
    if (archivo.eof()) return false;
    archivo.getline(libro.tiltulo,80,',');
    archivo.getline(libro.autor,60,',');
    archivo>>libro.stock>>c>>libro.precio;
    archivo.get(c);

    return true;
}

bool operator >>(ifstream &archivo, Cliente &cliente) {
    char c;
    archivo>>cliente.dni>>c;
    if (archivo.eof()) return false;
    archivo.getline(cliente.nombre,60,'\n');

    return true;
}

bool operator >>() {

}