#include <iostream>
#include <fstream>
#include "ListaconEnteros.h"

#include "../BibliotecaGenerica/BibliotecaGenerica.h"
using namespace std;

bool leenumeros(ifstream &archivo, void *&dato_dupla) {

    int datoEntero;

    archivo>>datoEntero;
    if (archivo.eof())return false;

    void **arreglo_void = new void*[20]{};
    void **dupla_aux = new void *[2]{};

    dupla_aux[0]=new int(datoEntero);
    dupla_aux[1]=arreglo_void;

    dato_dupla=dupla_aux;


    return true;
}

bool leeregnumeros(ifstream &archivo, void *&dupla0, void *&dupla1) {

    int dato1,dato2;

    archivo>>dato1;
    if (archivo.eof())return false;
    archivo>>dato2;

    dupla0=new int(dato1);
    dupla1=new int(dato2);

    return true;
}

// void compruebanumero(void *lista, void *valorA,void *valorB) {
//
//     void **aux_lista = (void **)lista;
//     void **ptr_recorrido = (void**)aux_lista[INICIO];
//     int *numero1=(int *)valorA;
//     int *numero2=(int *)valorB;
//
//     while (ptr_recorrido) {
//         void **dupla=(void **)ptr_recorrido[DATO];
//         int *numero=(int *)dupla[0];
//
//         if (*numero==*numero1) {
//
//         }
//     }
// }

void *compruebanumero(void *lista, void *valorA) {
    void **aux_lista = (void **)lista;
    void **ptr_recorrido = (void **)aux_lista[INICIO];
    int *numero1=(int *)valorA;

    while (ptr_recorrido) {
        void **dupla=(void **)ptr_recorrido[DATO];
        int *numero=(int *)dupla[0];
        if (*numero==*numero1) {
            return ptr_recorrido[DATO];
        }
        ptr_recorrido=(void**)ptr_recorrido[SIGUIENTE];
    }
    return nullptr;
}

void imprimenumeros(ofstream &archRep, void *dato) {

    void **dupla = (void **)dato;
    int numero = *(int *)dupla[0];

    void **arreglo = (void **)dupla[1];

    archRep<<numero<<endl;
    for (int i=0;arreglo[i]!=nullptr;i++) {
        int numeros2=*(int *)arreglo[i];
        archRep<<numeros2<<" ";
    }
    archRep<<endl<<endl;
}