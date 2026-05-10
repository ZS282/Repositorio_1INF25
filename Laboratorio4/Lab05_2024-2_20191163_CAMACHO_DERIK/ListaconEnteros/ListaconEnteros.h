//
// Created by DerikZS on 05/05/2026.
//

#ifndef LAB05_2024_2_20191163_CAMACHO_DERIK_LISTACONENTEROS_H
#define LAB05_2024_2_20191163_CAMACHO_DERIK_LISTACONENTEROS_H

using namespace std;
bool leenumeros(ifstream &archivo, void *&dato);
bool leeregnumeros(ifstream &archivo, void *&dato1, void *&dato2);
void *compruebanumero(void *lista, void *valorA);
void imprimenumeros(ofstream &archRep, void *lista);
#endif //LAB05_2024_2_20191163_CAMACHO_DERIK_LISTACONENTEROS_H