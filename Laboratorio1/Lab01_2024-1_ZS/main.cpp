

#include <iostream>
#include <fstream>
#include "MiLibreria/Estructuras.h"
#include "MiLibreria/sobrecarga.h"
using namespace std;

int main() {

    Libro arrLibros[300];
    Cliente arrClientes[300];

    LibroSolicitado libroPedido;


    ifstream arch("Libros.txt",ios::in);
    if (not arch.is_open()) {
        cout << "Error opening file " << "Libros.csv" << endl;
        exit(1);
    }
    int i = 0;
    while (true) {
        if (arch>>arrLibros[i]) {
            i++;
        } else break;
    }

    ifstream archCli("Cientes.csv",ios::in);
    if (not archCli.is_open()) {
        cout << "Error opening file " << "Clientes.csv" << endl;
        exit(1);
    }
    int j=0;
    while (true) {
        if (archCli>>arrClientes[j]) {
            cout<<j<<arrClientes[j].dni<<" "<<arrClientes[j].nombre<<endl;
            j++;

        }else break;
    }
    
    // libroPedido>>

    return 0;
}