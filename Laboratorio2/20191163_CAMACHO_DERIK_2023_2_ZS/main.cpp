

#include <iostream>
#include "FuncionesAuxiliares/funciones.h"
using namespace std;

int main() {

    char***productos,***codigoPedidos;
    int *stock,*fechaPedidos,***dniCantPedidos;
    double *precios;

    lecturaDeProuctos("Productos.csv",productos,stock,precios);
    pruebaDeLecturaDeProductos("ReporteDeProductos.txt",productos,stock,precios);
    //
    // lecturaDePedidos("Pedidos.csv",fechaPedidos,codigoPedidos,dniCantPedidos);
    // pruebaDeLecturaDePedidos("ReporteDePedidos.txt",fechaPedidos,codigoPedidos,dniCantPedidos);
    //
    // reporteDeEnvioDePedidos("ReporteEntregaDePedidos.txt",productos,stock,precios,
    //     fechaPedidos,codigoPedidos,dniCantPedidos);
    // pruebaDeLecturaDeProductos("ReporteDeProductosFinal.txt",productos,stock,precios);

    return 0;
}