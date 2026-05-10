//
// Created by DerikZS on 05/05/2026.
//

#include <fstream>
#include <cstring>
#include <iomanip>
#include "ListaconRegistros.h"

#include <functional>

#include "../BibliotecaGenerica/BibliotecaGenerica.h"

using namespace std;

bool leeregistros(ifstream &archivo, void *&registro) {

    char *codigo_repartidor=nullptr;
    char *nombre_repartidor=nullptr;
    char *unidad=nullptr;

    int num=10;
    //Lectura de datos
    codigo_repartidor=leerCadena(archivo,',');
    if (archivo.eof())return false;
    nombre_repartidor=leerCadena(archivo,',');
    unidad=leerCadena(archivo,'\n');

    void **registro_auxiliar = new void *[2]{};
    void **triple = new void*[3]{};
    void **arreglo_dupla= new void *[20]{};
    triple[0]=codigo_repartidor;
    triple[1]=nombre_repartidor;
    triple[2]=unidad;

    registro_auxiliar[0]=triple;
    registro_auxiliar[1]=arreglo_dupla;

    registro=registro_auxiliar;

    return true;

}

bool leeordenes(ifstream &archivo, void *&registro1, void *&registro2) {

    int dni,cantidad;
    char *plato=nullptr;
    char *codigo=nullptr;

    archivo>>dni;
    if (archivo.eof())return false;
    archivo.ignore();
    archivo>>cantidad;
    archivo.ignore();
    plato=leerCadena(archivo,',');
    codigo=leerCadena(archivo,'\n');

    void **registro2_aux= new void *[3]{};

    registro2_aux[0]=new int(dni);
    registro2_aux[1]=new int(cantidad);
    registro2_aux[2]=plato;

    registro1=codigo;
    registro2=registro2_aux;

    return true;
}

void *compruebaregistro(void *lista, void *registroA) {

    void **aux_lista= (void **)lista;
    void **recorrido=(void **)aux_lista[INICIO];

    char *codigo_verificar=(char *)registroA;

    char *codigo_repartidor =nullptr;

    while (recorrido) {
        void **registro_auxiliar= (void **)recorrido[DATO];
        void **datos_registro = (void **)registro_auxiliar[0];
        codigo_repartidor= (char *)datos_registro[0];
        if (strcmp(codigo_verificar,codigo_repartidor)==0) {
            return recorrido[DATO];
        }

        recorrido=(void**)recorrido[SIGUIENTE];
    }

    return nullptr;
}

void imprimeregistros(ofstream &archivo, void *registro) {

    void **dato= (void **)registro;
    void **registro_aux=(void **)dato[0];
    void **arreglo_ordenes =(void **)dato[1];

    char *codigo=(char *)registro_aux[0];
    char *nombre = (char *)registro_aux[1];

    archivo<<codigo<<setw(10)<<" "<<nombre<<endl;
    archivo<<"Ordenes:"<<endl;
    archivo<<right;
    for (int i=0;arreglo_ordenes[i];i++) {
        void **datos_ordenes= (void **)arreglo_ordenes[i];
        int dni=*(int *)datos_ordenes[0];
        int cantidad=*(int *)datos_ordenes[1];
        char *plato = (char *)datos_ordenes[2];
        archivo<<dni<<setw(10)<<cantidad<<setw(10)<<plato<<endl;
    }
    archivo<<endl<<endl;
}


