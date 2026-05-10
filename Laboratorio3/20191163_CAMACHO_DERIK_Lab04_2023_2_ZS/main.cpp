

#include <iostream>
#include "Funciones/funciones.h"
using namespace std;

int main() {

    void *clientes, *reserva;

    cargaclientes(clientes);
    cargareserva(reserva);
    cargareservar(clientes,reserva);
    reportefinal(reserva);

    return 0;
}