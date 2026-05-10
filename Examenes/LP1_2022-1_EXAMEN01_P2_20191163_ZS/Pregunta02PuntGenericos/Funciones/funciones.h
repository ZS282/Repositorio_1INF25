//
// Created by DerikZS on 22/04/2026.
//

#ifndef PREGUNTA02PUNTGENERICOS_FUNCIONES_H
#define PREGUNTA02PUNTGENERICOS_FUNCIONES_H

#include <iostream>
using namespace std;

void cargaProductos(void *&productos);
bool leerProductos(ifstream &archivoProductos,void *&datos_productos);

void cargaPedidos(void *&pedidos);
bool leerPedidos(ifstream &archivoPedidos,void *&ptr_datosRegPedido);


void procesarClientes(void *productos,void *pedidos,void *&clientes);
bool leerClientes(ifstream &archClientes,int &dni,void *&ptr_datoRegCliente,void *pedidos,void *productos);
void verificarPedidoClientes(int dni,void *&ptr_datoRegCliente,void *pedidos,void *productos,int &numDatos,int &capacidad);
void agregarPedidos(void *&ptr_datoRegCliente,void *registro_PedidoCliente,int &numDatos,int &capacidad);
void incrementarCapacidad(void **&vv_arrPedidosCliente,int numDatos,int &capacidad);
void *buscarProducto(int cod_producto,void *productos);

void imprimeReporte(void *clintes);

char *leerCadenaExacta(ifstream &archivo, char delimitador) ;
void aperturaArchivoLeer(ifstream &archivo, const char *nombArch) ;
void aperturaArchivoEscribir(ofstream &archivo, const char *nombArch);

#endif //PREGUNTA02PUNTGENERICOS_FUNCIONES_H