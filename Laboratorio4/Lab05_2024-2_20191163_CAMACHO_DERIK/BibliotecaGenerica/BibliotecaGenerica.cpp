//
// Created by Derik on 04/05/2026.
//

#include "BibliotecaGenerica.h"

#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;


void crealista(void *&lista,bool (*ptr_lee)(ifstream &,void *&),const char *nombArch) {

    ifstream archivoNumeros1;
    aperturaLectura(archivoNumeros1,nombArch);
    construir(lista);
    void *dato_dupla;
    while (ptr_lee(archivoNumeros1,dato_dupla)) {
        //Insercion de dupla
        insertaInicio(lista,dato_dupla);
    }

}

void insertaInicio(void *&lista, void *dupla) {
    void **aux = (void **)lista;
    void **nuevo_bloque= new void *[2]{};
    nuevo_bloque[DATO]=dupla;
    nuevo_bloque[SIGUIENTE]=nullptr;
    if (eslistavacia(lista)) {
        aux[INICIO] =nuevo_bloque;
        aux[FIN]=nuevo_bloque;
    }else {
        void **ultimo = (void **)aux[FIN];
        ultimo[SIGUIENTE] = nuevo_bloque;
        aux[FIN]=nuevo_bloque;
        // nuevo_bloque[SIGUIENTE]=aux[INICIO];
        // aux[INICIO]=nuevo_bloque;
    }

    // int *nummero_nodos = (int *)aux[NUMERO];

    (*(int*)aux[NUMERO])++;
}

void construir(void *&lista) {

    void **vv_lista = new void *[3];

    vv_lista[INICIO] = nullptr;
    vv_lista[FIN] = nullptr;

    int *numero_nodos=new int;
    *numero_nodos=0;

    vv_lista[NUMERO] = numero_nodos;

    lista=vv_lista;

}

bool eslistavacia(void *lista) {

    void **vv_lista = (void **)lista;

    if (vv_lista[INICIO]==nullptr)return true;

    return false;
}

void cargalista(void *&lista,void *(*ptr_comprueba)(void *,void *),bool (*ptr_lee)(ifstream &,void *&,void*&),const char *nombArch) {

    ifstream archivoNumeros2;
    aperturaLectura(archivoNumeros2,nombArch);
    void *datoDupla1, *datoDupla2_arreglo;
    while (ptr_lee(archivoNumeros2,datoDupla1,datoDupla2_arreglo)) {

        void *dupla = ptr_comprueba(lista,datoDupla1);
        if (dupla!=nullptr) {
            insertaArreglo(dupla,datoDupla2_arreglo);
        }
    }
}

void insertaArreglo(void *dupla,void *datoDupla2_arreglo) {

    void **aux_dupla = (void **)dupla;
    void **arreglo_dupla = (void **)aux_dupla[1];

    for (int i=0; i<20; i++) {
        if (arreglo_dupla[i]==nullptr) {
            arreglo_dupla[i]=datoDupla2_arreglo;
            break;
        }
    }
}

void muestralista(void *lista,void (*imprime)(ofstream &,void *),const char *nombArch) {
    ofstream archivoNumeros;
    aperturaEscritura(archivoNumeros,nombArch);

    void **vv_lista = (void **)lista;
    void **recorrido = (void **)vv_lista[INICIO];

    while (recorrido) {
        imprime(archivoNumeros,recorrido[DATO]);
        recorrido=(void **)recorrido[SIGUIENTE];
    }

}

char *leerCadena(ifstream &archivo, char delimitador) {

    char buffer[500], *ptr_cadena=nullptr;

    archivo.getline(buffer,500,delimitador);
    if (archivo.eof())return nullptr;
    ptr_cadena = new char[strlen(buffer)+1];
    strcpy(ptr_cadena,buffer);

    return ptr_cadena;

}

void aperturaLectura(ifstream &archivo, const char *nombArch) {

    char buffer[100];
    strcpy(buffer,"ArchivoDatos/");
    strcat(buffer,nombArch);

    archivo.open(buffer,ios::in);

    if (not archivo.is_open()) {
        cout<<"No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }

}

void aperturaEscritura(ofstream &archivo, const char *nombArch) {
    char buffer[100];
    strcpy(buffer,"ArchivoReportes/");
    strcat(buffer,nombArch);

    archivo.open(buffer,ios::out);
    if (not archivo.is_open()) {
        cout<<"No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}