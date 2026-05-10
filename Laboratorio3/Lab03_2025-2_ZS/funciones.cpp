//
// Created by DerikZS on 14/04/2026.
//

#include "funciones.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "funciones.h"
using namespace std;


void cargastreamers(void *&streamers) {

    void *buffer[300],**aux_streamers;
    ifstream arch("streamers.csv",ios::in);
    if (not arch.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    int i=0;
    while (true) {

        buffer[i]=leeRegistroStreamer(arch);
        if (arch.eof()) break;
        i++;
    }
    aux_streamers = new void *[i+1];
    for (int i=0; i<=i; i++) {
        aux_streamers[i]=buffer[i];
    }
}

void *leeRegistroStreamer(ifstream &arch) {
    char *cuenta,c,*categoria;
    void **registro;
    int num;
    long long *num_espectadores,numLong;
    cuenta=leerCadena(arch,20,',');
    if (arch.eof()) return nullptr;
    num_espectadores=new long long;
    arch>>numLong>>c>>num>>c>>*num_espectadores>>c;
    categoria=leerCadena(arch,10,'\n');
    registro = new void *[4];
    *num_espectadores=numLong;
    registro[0]=cuenta;
    registro[1]=num_espectadores;
    registro[2]=categoria;
    registro[3]=nullptr;
}

char *leerCadena(ifstream &arch,int n,char delimitador) {

    char buffer[n],*ptr_cad;
    arch.getline(buffer,n,delimitador);
    if (arch.eof()) return nullptr;
    ptr_cad=new char[strlen(buffer)+1];
    strcpy(ptr_cad,buffer);

    return ptr_cad;
}