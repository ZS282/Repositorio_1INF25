//
// Created by DerikZS on 05/05/2026.
//

#ifndef LAB05_2024_2_20191163_CAMACHO_DERIK_LISTACONREGISTROS_H
#define LAB05_2024_2_20191163_CAMACHO_DERIK_LISTACONREGISTROS_H

#include <iostream>
using namespace std;

bool leeregistros(ifstream &archivo, void *&dato_dupla);
bool leeordenes(ifstream &archivo, void *&registro1, void *&registro2);
void *compruebaregistro(void *lista, void *registroA);
void imprimeregistros(ofstream &archivo, void *registro);

#endif //LAB05_2024_2_20191163_CAMACHO_DERIK_LISTACONREGISTROS_H