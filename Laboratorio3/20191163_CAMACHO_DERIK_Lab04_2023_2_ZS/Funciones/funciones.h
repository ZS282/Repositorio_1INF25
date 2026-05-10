//
// Created by DerikZS on 21/04/2026.
//

#ifndef INC_20191163_CAMACHO_DERIK_2023_1_ZS_FUNCIONES_H
#define INC_20191163_CAMACHO_DERIK_2023_1_ZS_FUNCIONES_H

#include <iostream>
using namespace std;

void cargaclientes(void *&clientes);
bool leerClientes(ifstream &archClientes, void *&ptr_datoRegCliente);

void cargareserva(void *&reserva);
bool leerLibros(ifstream &archReservas,void *&ptr_datoRegLibro);

void cargareservar(void *clientes,void *reserva);
bool cargarPedidos(ifstream &archPedidos,char *&codigo_libro,void *clientes,void *&pedido_cliente);
void *buscarNombre(int dni,void *clientes);
void *buscarLibro(void *reserva,char *codigo_libro);
void agregarPedidosDni_Libros(void *&pedido_cliente,void *libro);
void incrementarRegistrosPedidos(void **&dato_registroPedidos,int numEspacios,int incremento);
int contarRegistros(void *dato_registroPedidos) ;

void reportefinal(void *reserva);

char *leerCadenaExacta(ifstream &arch, char delimitador);
void aperturaArchivoLeer(ifstream &archivo,const char *nombArch);
void aperturaArchivoEscribir(ofstream &archRep,const char *nombArch);

#endif //INC_20191163_CAMACHO_DERIK_2023_1_ZS_FUNCIONES_H