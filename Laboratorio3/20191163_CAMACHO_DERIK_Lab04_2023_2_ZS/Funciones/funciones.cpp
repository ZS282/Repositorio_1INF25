//
// Created by DerikZS on 21/04/2026.
//
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "funciones.h"
#define INC 1
using namespace std;

void cargaclientes(void *&clientes) {

    ifstream archClientes;
    aperturaArchivoLeer(archClientes,"Clientes.csv");

    void **buffer=new void*[60];
    int numDat=0;

    while (leerClientes(archClientes,buffer[numDat]))numDat++;

    void **vv_arrRegClientes=new void*[numDat+1]{};
    for (int i = 0; i < numDat; i++) {
        vv_arrRegClientes[i]=buffer[i];
    }

    vv_arrRegClientes[numDat]=nullptr;
    delete[] buffer;

    clientes=vv_arrRegClientes;
}

bool leerClientes(ifstream &archClientes, void *&ptr_datoRegCliente) {

    int dni;
    char *nombre;

    archClientes>>dni;
    if (archClientes.eof())return false;
    archClientes.ignore();
    nombre=leerCadenaExacta(archClientes,'\n');

    void **vv=new void *[2];
    vv[0]=new int(dni);
    vv[1]=nombre;

    ptr_datoRegCliente=vv;

    return true;
}

void cargareserva(void *&reserva) {

    ifstream archReservas;
    aperturaArchivoLeer(archReservas,"Libros.csv");

    void **buffer_libros=new void*[300];
    int numDat=0;

    while (leerLibros(archReservas,buffer_libros[numDat]))numDat++;

    void **vv_arrRegReservas=new void*[numDat+1]{};
    for (int i = 0; i < numDat; i++) {
        vv_arrRegReservas[i]=buffer_libros[i];
    }
    vv_arrRegReservas[numDat]=nullptr;
    delete[] buffer_libros;

    reserva=vv_arrRegReservas;
}

bool leerLibros(ifstream &archReservas,void *&ptr_datoRegLibro) {

    char *codigo_libro,*nombre_libro,*nombre_autor;
    int stock;
    double precio;

    codigo_libro=leerCadenaExacta(archReservas,',');
    if (archReservas.eof())return false;
    nombre_libro=leerCadenaExacta(archReservas,',');
    nombre_autor=leerCadenaExacta(archReservas,',');
    archReservas>>stock;
    archReservas.ignore();
    archReservas>>precio;
    archReservas.ignore();

    void **vv=new void*[5];
    // void **reg_pedidosClientes=new void*[stock]{};
    vv[0]=codigo_libro;
    vv[1]=nombre_libro;
    vv[2]=nombre_autor;
    vv[3]=nullptr;
    vv[4]=new int(stock);

    ptr_datoRegLibro=vv;

    return true;
}

void cargareservar(void *clientes,void *reserva) {

    ifstream archPedidos;
    aperturaArchivoLeer(archPedidos,"Pedidos2.csv");

    void *pedido_cliente;//puntero para guardar la direccion de memoria que apunte a la estructura del libro
    void *libro;//puntero que gaurda la direccion de memoria que apunte al registro de los pedidos
    char *codigo_libro;
    while (cargarPedidos(archPedidos,codigo_libro,clientes,pedido_cliente)) {
        libro=buscarLibro(reserva,codigo_libro);
        agregarPedidosDni_Libros(pedido_cliente,libro);
    }

}

void agregarPedidosDni_Libros(void *&pedido_cliente,void *libro) {

    void **registro_libro=(void **)libro;
    void **dato_registroPedidos=(void **)registro_libro[3];//Acceder al arreglo dinamico de pedidos de clientes

    int numEspacios=contarRegistros(dato_registroPedidos);
    if (numEspacios<=*(int*)registro_libro[4]) {
        incrementarRegistrosPedidos(dato_registroPedidos,numEspacios,INC);//Se crea y modifica el arreglo
        //dinamico de clientes que solicitan esto
        dato_registroPedidos[numEspacios++]=pedido_cliente;
        dato_registroPedidos[numEspacios]=nullptr;
        registro_libro[3]=dato_registroPedidos;
        libro=registro_libro;
    }
}

void incrementarRegistrosPedidos(void **&dato_registroPedidos,int numEspacios,int incremento) {

    int capacidad = numEspacios + incremento;
    void **vv=(void **)dato_registroPedidos;

    if (vv==nullptr) {
        vv=new void*[capacidad+1]{};
    }else {
        void **vv_aux=new void*[capacidad+1]{};//se crea un nuevo registro que se apuntara nuevamente
        for (int i=0;i<numEspacios;i++) {
            vv_aux[i]=vv[i];
        }
        delete [] vv;
        vv=vv_aux;
    }
    dato_registroPedidos=vv;
}

int contarRegistros(void *dato_registroPedidos) {

    void **vv=(void **)dato_registroPedidos;
    int num=0;
    if (vv!=nullptr) {
        for (;vv[num];num++);
    }

    return num;
}

void *buscarLibro(void *reserva,char *codigo_libro) {

    void **vv=(void**)reserva;
    void **resultado = nullptr;

    for (int i=0;vv[i];i++) {
        void **registro_libros=(void**)vv[i];
        char *codigo=(char *)registro_libros[0];
        if (strcmp(codigo,codigo_libro)==0) {
            resultado=registro_libros;
            break;
        }
    }
    return resultado;
}

bool cargarPedidos(ifstream &archPedidos,char *&codigo_libro,void *clientes,void *&pedido_cliente) {

    int dniCli_pedido;

    archPedidos>>dniCli_pedido;
    if (archPedidos.eof())return false;
    archPedidos.ignore();
    codigo_libro=leerCadenaExacta(archPedidos,'\n');

    void **vv = new void *[2];
    //creamos un puntero doble asterisco que apunte a una dupla o un registro (lineas de pedidos)
    vv[0]=new int(dniCli_pedido);
    void **datos_regCliente=(void**)buscarNombre(dniCli_pedido,clientes);
    vv[1]=(char *)datos_regCliente[1];

    pedido_cliente=vv;//puntero void que apuntara a este registro o arreglo dinamico de 2 elemntos (dni y nombre)

    return true;
}

void *buscarNombre(int dni,void *clientes) {
    void **vv=(void**)clientes;
    void **resultado=nullptr;
    for (int i=0;vv[i];i++) {
        void **registro_cliente=(void**)vv[i];
        int dni_cli=*(int*)registro_cliente[0];
        if (dni_cli==dni) {
            resultado=registro_cliente;
            break;
        }
    }
    return resultado;
}

void reportefinal(void *reserva) {

    ofstream archRep;
    aperturaArchivoEscribir(archRep,"reporte.txt");
    void **vv=(void **)reserva;
    archRep<<"Reporte de Libros Reservados"<<endl;
    for (int i=0;vv[i];i++) {
        archRep<<"==============================================="<<endl;
        void **registro_Libro=(void**)vv[i];
        archRep<<"Libro: "<<(char *)registro_Libro[0]<<endl;
        archRep<<"Nombre: del Libro"<<(char *)registro_Libro[1]<<endl;
        archRep<<"Autor: "<<(char *)registro_Libro[2]<<endl;
        archRep<<"DNI           Nombre del solicitante"<<endl;
        archRep<<"================================================"<<endl;
        void **registro_Clientes=(void**)registro_Libro[3];
        if (registro_Clientes!=nullptr) {
            for (int j=0;registro_Clientes[j];j++) {
                void **datos_clientes=(void**)registro_Clientes[j];
                archRep<<*(int*)datos_clientes[0]<<"           "<<(char *)datos_clientes[1]<<endl;
            }
        }else {
            archRep<<"Libro no reservado por clientes"<<endl;
        }
    }
}

char *leerCadenaExacta(ifstream &arch, char delimitador) {

    char buffer[500],*ptr_cadena;
    arch.getline(buffer,500,delimitador);
    if (arch.eof())return nullptr;
    ptr_cadena=new char[strlen(buffer)+1];
    strcpy(ptr_cadena,buffer);
    return ptr_cadena;
}

void aperturaArchivoLeer(ifstream &archivo,const char *nombArch) {
    archivo.open(nombArch,ios::in);
    if (not archivo.is_open()) {
        cout<<"Error al abrir el archivo"<<endl;
        exit(1);
    }
}

void aperturaArchivoEscribir(ofstream &archRep,const char *nombArch) {
    archRep.open(nombArch,ios::out);
    if (not archRep.is_open()) {
        cout<<"Error al abrir el archivo"<<endl;
        exit(1);
    }
}