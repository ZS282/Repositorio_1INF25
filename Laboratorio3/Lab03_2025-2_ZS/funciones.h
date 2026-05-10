//
// Created by DerikZS on 14/04/2026.
//

#ifndef LAB03_2025_2_ZS_FUNCIONES_H
#define LAB03_2025_2_ZS_FUNCIONES_H

#include <iostream>
using namespace std;

void cargastreamers(void *&streamers);
void *leeRegistroStreamer(ifstream &arch);
char *leerCadena(ifstream &arch,int n,char delimitador);
#endif //LAB03_2025_2_ZS_FUNCIONES_H