#include <iostream>
#include "funciones/funcionesAux.h"
using namespace std;

int main() {

    void *inventario,*menu;

    cargarInventario("inventario.csv",inventario);
    probarCargarInventario("prueba-inventario.txt",inventario);

    cargarMenu("menu.csv",menu);
    pruebaCargarMenu("menu-inicial.txt",menu);
    actualizarMenu("insumos-bebidas.csv",inventario,menu);

    reporteMenu("menu.txt",menu);

    return 0;
}