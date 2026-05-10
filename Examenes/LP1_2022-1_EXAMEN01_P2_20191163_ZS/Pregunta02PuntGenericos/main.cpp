
#include <iostream>
#include "Funciones/funciones.h"
using namespace std;

int main() {
    void *productos,*pedidos;
    void *clientes;

    cargaProductos(productos);
    cargaPedidos(pedidos);
    procesarClientes(productos,pedidos,clientes);
    imprimeReporte(clientes);
    return 0;
}