//
// Created by DerikZS on 15/04/2026.
//

#include <iostream>
#include <fstream>
#include "funciones.h"

#include <cstring>
using namespace std;

void lecturaDeProuctos(const char *nombArch,char ***&productos,int *&stock,double *&precios) {


    //1. Declarar buffers (Metodo exacto)
    char **bufferProductos[200];
    int bufferStock[200];
    int bufferPrecios[200];

    //2. Lectura de archivo
    ifstream archProductos(nombArch,ios::in);
    if (not archProductos.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    //BIT-434,Campana Extractora modelo Glass,375.09,10
    //SSE-115,Refrigeradora  CoolStyle 311N Steel,3243.58,23
    int i=0;
    while (true) {
        bufferProductos[i]=leerProductos(archProductos);
        if (bufferProductos[i]==NULL) break;
        i++;
    }
}

char **leerProductos(ifstream &arch) {
    char **dupla,*codProd;

    codProd=leerCadenaExacta(arch,8,',');
    if (arch.eof())return nullptr;

}

void pruebaDeLecturaDeProductos(const char *nombArch,char ***productos,int *stock,double *precios) {

}

char *leerCadenaExacta(istream &arch,int max,char delimitador) {
    char buffer[max], *ptr_cad;
    arch.getline(buffer,max,delimitador);
    if (arch.eof()) return nullptr;
    ptr_cad=new char[strlen(buffer)+1];
    strcpy(ptr_cad,buffer);
    return ptr_cad;
}