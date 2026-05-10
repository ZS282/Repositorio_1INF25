
#include <iostream>
#include <iomanip>
#include <cstring>

#include "Estructuras.h"
#include "sobrecarga.h"
using namespace std;

void operator! (CadenaDeCaracteres &cadena) {

    cadena.cadena=nullptr;
    cadena.capacidad=0;
    cadena.longitud=0;
}

void operator <= (CadenaDeCaracteres &cadena, const char *cad) {


    if (cadena.cadena!=nullptr) {
        delete[] cadena.cadena;
    }
    cadena.longitud=strlen(cad);
    cadena.capacidad=cadena.longitud+1;
    cadena.cadena=new char[cadena.capacidad];

    strcpy(cadena.cadena,cad);
}

void operator <= (CadenaDeCaracteres &cadena, int num) {

    !cadena;

    cadena.cadena= new char[num];
    cadena.longitud=0;
    cadena.capacidad=num;
    cadena.cadena[0]='\0';
}

void operator <= (CadenaDeCaracteres &cadena1, CadenaDeCaracteres &cadena2) {

    //Copiara de cadena 2 a cadena 1
    if (cadena2.cadena!=nullptr) {//Si no esta vacia, hay elementos para copiar
        if (cadena1.cadena!=nullptr) {//Si no es nula, verificamos si es valido la capacidad
            if (cadena1.capacidad>=cadena2.capacidad) {//Capacidad valida para la copia de cad2 a cad1
                strcpy(cadena1.cadena,cadena2.cadena);
                cadena1.longitud=cadena2.longitud;
                cadena1.capacidad=cadena2.capacidad;
            }else {
                cadena1<=cadena2.cadena;
            }
        }else {//Si cad1 es nulo
            cadena1<=cadena2.capacidad;//Se invoca el op que reserva memoria
            strcpy(cadena1.cadena,cadena2.cadena);
            cadena1.longitud=cadena2.longitud;
        }
    }
}

bool operator += (CadenaDeCaracteres &cadena,char *cad){

    if (cadena.cadena!=nullptr or cadena.cadena[0]!='\0') {
        strcat(cadena.cadena,cad);
        cadena.longitud+=strlen(cad);
        cadena.capacidad+=cadena.longitud;
    }return false;
}