//
// Created by DerikZS on 08/04/2026.
//

#ifndef LAB01_2024_1_ZS_SOBRECARGA_H
#define LAB01_2024_1_ZS_SOBRECARGA_H


#include <iostream>
#include <fstream>
#include "Estructuras.h"
using namespace std;

bool operator >>(ifstream &,Libro &arrLibros);
bool operator >>(ifstream &archivo, Cliente &cliente);

#endif //LAB01_2024_1_ZS_SOBRECARGA_H