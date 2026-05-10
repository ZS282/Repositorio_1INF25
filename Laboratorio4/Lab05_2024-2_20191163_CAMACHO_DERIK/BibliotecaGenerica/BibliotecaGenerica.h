//
// Created by DerikZS on 05/05/2026.
//

#ifndef LAB05_2024_2_20191163_CAMACHO_DERIK_BIBLIOTECAGENERICA_H
#define LAB05_2024_2_20191163_CAMACHO_DERIK_BIBLIOTECAGENERICA_H
#include <iostream>
using namespace std;

enum LISTA {INICIO,FIN, NUMERO};
enum NODO {DATO,SIGUIENTE};

void crealista(void *&lista,bool (*ptr_lee)(ifstream &,void *&),const char *nombArch);
void insertaInicio(void *&lista, void *dupla);
void construir(void *&lista);
bool eslistavacia(void *lista);
void cargalista(void *&lista,void * (*ptr_comprueba)(void *,void *),bool (*ptr_lee)(ifstream &,void *&,void*&),const char *nombArch);
void insertaArreglo(void *dupla,void *datoDupla2_arreglo);
void muestralista(void *lista,void (*imprime)(ofstream &,void *),const char *nombArch);
char *leerCadena(ifstream &archivo, char delimitador);
void aperturaLectura(ifstream &archivo, const char *nombArch);
void aperturaEscritura(ofstream &archivo, const char *nombArch);


#endif //LAB05_2024_2_20191163_CAMACHO_DERIK_BIBLIOTECAGENERICA_H