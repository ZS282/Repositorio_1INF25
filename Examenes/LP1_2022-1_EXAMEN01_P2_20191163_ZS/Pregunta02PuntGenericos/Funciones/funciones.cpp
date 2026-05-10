//
// Created by DerikZS on 22/04/2026.
//

#include "funciones.h"

#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "funciones.h"
#define INC 5
using namespace std;

void cargaProductos(void *&productos) {

    ifstream archivoProductos;
    aperturaArchivoLeer(archivoProductos,"productos2.csv");

    void **bufferProductos = new void *[100];
    int numDatos=0;

    while (leerProductos(archivoProductos,bufferProductos[numDatos]))numDatos++;

    void **vv_productos=new void *[numDatos+1]{};
    for (int i=0;i<numDatos;i++) {
        vv_productos[i]=bufferProductos[i];
    }
    vv_productos[numDatos]=nullptr;
    delete [] bufferProductos;

    productos=vv_productos;
}

bool leerProductos(ifstream &archivoProductos,void *&ptr_datosRegProducto) {

    int codigo_producto,cantidad;
    char *descripcion_producto;
    double precio;

    archivoProductos>>codigo_producto;
    if (archivoProductos.eof())return false;
    archivoProductos.ignore();
    descripcion_producto=leerCadenaExacta(archivoProductos,',');
    archivoProductos>>precio;
    archivoProductos.ignore();
    archivoProductos>>cantidad;

    void **vv_auxProductos=new void *[4];

    vv_auxProductos[0]=new int(codigo_producto);
    vv_auxProductos[1]=descripcion_producto;
    vv_auxProductos[2]=new double(precio);
    vv_auxProductos[3]=new int(cantidad);

    ptr_datosRegProducto=vv_auxProductos;
    return true;
}

void cargaPedidos(void *&pedidos) {

    ifstream archivoPedidos;
    aperturaArchivoLeer(archivoPedidos,"pedidos2.csv");

    void **bufferPedidos=new void *[200];
    int numDatos=0;
    while (leerPedidos(archivoPedidos,bufferPedidos[numDatos]))numDatos++;

    void **vv_pedidos=new void *[numDatos+1]{};
    for (int i=0;i<numDatos;i++) {
        vv_pedidos[i]=bufferPedidos[i];
    }
    vv_pedidos[numDatos]=nullptr;
    delete [] bufferPedidos;

    pedidos=vv_pedidos;
}

bool leerPedidos(ifstream &archivoPedidos,void *&ptr_datosRegPedido){

    int codigo_producto,cantidad_solicitada,dni_cliente,dia,mes,anio;
    char *descripcion_producto,c;
    // 422763,GALLETAS SUAVICREMAS FRESA 158GR,2,17913944,23/09/2019
    // 675770,JARABE DE MAMEY 1.25KG,5,17913944,20/10/2019
    // 696000,MEDIA CREMA NESTLE 1LT,1,17913944,28/12/2019
    archivoPedidos>>codigo_producto;
    if (archivoPedidos.eof())return false;
    archivoPedidos.ignore();
    descripcion_producto=leerCadenaExacta(archivoPedidos,',');
    archivoPedidos>>cantidad_solicitada>>c>>dni_cliente>>c;
    archivoPedidos>>dia>>c>>mes>>c>>anio;
    int fecha=anio*10000+mes*100+dia;
    char estado='N';

    void **vv_auxPedidos=new void *[6];
    vv_auxPedidos[0]=new int(codigo_producto);
    vv_auxPedidos[1]=descripcion_producto;
    vv_auxPedidos[2]=new int(cantidad_solicitada);
    vv_auxPedidos[3]=new int(dni_cliente);
    vv_auxPedidos[4]=new int(fecha);
    vv_auxPedidos[5]=new char(estado);

    ptr_datosRegPedido=vv_auxPedidos;

    return true;
}

void procesarClientes(void *productos,void *pedidos,void *&clientes) {

    ifstream archClientes;
    aperturaArchivoLeer(archClientes,"clientes2.csv");

    void **bufferClientes=new void *[30]{};
    int numClientes=0,dni,numPedidos[30]{},capacidad[30]{};
    while (leerClientes(archClientes,dni,bufferClientes[numClientes],pedidos,productos)) {
        verificarPedidoClientes(dni,bufferClientes[numClientes],pedidos,productos,numPedidos[numClientes],
            capacidad[numClientes]);
        numClientes++;
    }

    void **vv_Clientes=new void *[numClientes+1]{};
    for (int i=0;i<numClientes;i++) {
        vv_Clientes[i]=bufferClientes[i];
    }
    vv_Clientes[numClientes]=nullptr;
    delete [] bufferClientes;
    clientes=vv_Clientes;
}

void verificarPedidoClientes(int dni,void *&ptr_datoRegCliente,void *pedidos,void *productos,int &numDatos,int &capacidad) {

    int cod_producto,stock,dni_encontrado;
    void *registro_PedidoCliente=nullptr,*registro_producto;
    void **vv_Pedidos=(void**)pedidos;
    for (int i=0;vv_Pedidos[i];i++) {
        void **regAux_Pedido=(void **)vv_Pedidos[i];
        dni_encontrado=*(int*)regAux_Pedido[3];
        if (dni==dni_encontrado) {
            registro_PedidoCliente=regAux_Pedido;
            cod_producto=*(int *)regAux_Pedido[0];
            registro_producto=buscarProducto(cod_producto,productos);
            void **vv_Productos=(void**)registro_producto;
            stock = *(int*)vv_Productos[3];
            if (stock>0) {
                agregarPedidos(ptr_datoRegCliente,registro_PedidoCliente,numDatos,capacidad);
                *(char *)regAux_Pedido[5]='A';
                *(int *)vv_Productos[3]-=*(int *)regAux_Pedido[2];
            }
        }
    }
}

void agregarPedidos(void *&ptr_datoRegCliente,void *registro_PedidoCliente,int &numDatos,int &capacidad) {

    void **vv_regCliente=(void **)ptr_datoRegCliente;
    void **vv_arrPedidosCliente=(void **)vv_regCliente[2];// ** = *

    if (numDatos==capacidad) {
        incrementarCapacidad(vv_arrPedidosCliente,numDatos,capacidad);
    }
    // void **vv_datoPedido=(void **)vv_arrPedidosCliente[numDatos];// ** = * (INNECESARIO)
    //Asignacion de datos
    void **vv_regPedidoCliente=(void **)registro_PedidoCliente;//convertimos los datos
    void **vv_datoPedido=new void *[4];
    int fecha = *(int*)vv_regPedidoCliente[4];
    int codigo_prod=*(int*)vv_regPedidoCliente[0];
    char *descripcion_prod=(char *)vv_regPedidoCliente[1];
    int cantidad_atendida = *(int*)vv_regPedidoCliente[2];

    vv_datoPedido[0]=new int(fecha);
    vv_datoPedido[1]=new int(codigo_prod);
    vv_datoPedido[2]=descripcion_prod;
    vv_datoPedido[3]=new int(cantidad_atendida);

    //Conectamos los datos (direccion de memoria)
    vv_arrPedidosCliente[numDatos]=vv_datoPedido;
    vv_arrPedidosCliente[numDatos+1]=nullptr;
    numDatos++;
    vv_regCliente[2]=vv_arrPedidosCliente;
}

void incrementarCapacidad(void **&vv_arrPedidosCliente,int numDatos,int &capacidad) {
    capacidad+=INC;
    void **vv_auxArrPedidosCliente=nullptr;

    if (vv_arrPedidosCliente==nullptr) {
        vv_arrPedidosCliente=new void *[capacidad+1]{};
    }else {
        vv_auxArrPedidosCliente=new void *[capacidad+1]{};
        for (int i=0;i<numDatos;i++) {
            vv_auxArrPedidosCliente[i]=vv_arrPedidosCliente[i];
        }
        delete [] vv_arrPedidosCliente;
        vv_arrPedidosCliente=vv_auxArrPedidosCliente;
    }
}

void *buscarProducto(int cod_producto,void *productos) {

    int codProd_encontrado;
    void **vv_Productos=(void **)productos;
    void *resultado=nullptr;
    for (int i=0;vv_Productos[i];i++) {
        void **regAux_Producto=(void **)vv_Productos[i];
        codProd_encontrado=*(int *)regAux_Producto[0];
        if (codProd_encontrado==cod_producto) {
            resultado=vv_Productos[i];
            break;
        }
    }
    return resultado;
}

bool leerClientes(ifstream &archClientes,int &dni,void *&ptr_datoRegCliente,void *pedidos,void *productos) {

    char *nombre_cliente;

    archClientes>>dni;
    if (archClientes.eof())return false;
    archClientes.ignore();
    nombre_cliente=leerCadenaExacta(archClientes,'\n');


    void **vv_datoRegCliente=new void *[3];
    vv_datoRegCliente[0]=new int(dni);
    vv_datoRegCliente[1]=nombre_cliente;
    vv_datoRegCliente[2]=nullptr;

    ptr_datoRegCliente=vv_datoRegCliente;

    return true;
}

void imprimeReporte(void *clintes) {

    ofstream archReporte;
    aperturaArchivoEscribir(archReporte,"reporte.txt");

    void **vv_clientes=(void**)clintes;

    for (int i=0;vv_clientes[i];i++) {
        void **registro_cliente=(void **)vv_clientes[i];
        archReporte<<"DNI:"<<setw(40)<<" "<<setw(10)<<"NOMBRE:"<<endl;
        archReporte<<*(int*)registro_cliente[0]<<setw(39)<<" "<<(char *)registro_cliente[1]<<endl;
        void **registro_PedidosClientes=(void **)registro_cliente[2];
        archReporte<<"--------------------------------------------------------------------------------------"<<endl;
        archReporte<<"Pedidos atendidos"<<endl;
        archReporte<<"--------------------------------------------------------------------------------------"<<endl;
        archReporte<<"Fecha"<<setw(13)<<"Codigo"<<setw(21)<<"Descripcion"<<setw(65)<<"Cantidad"<<endl;
        archReporte<<"--------------------------------------------------------------------------------------"<<endl;
        if (registro_PedidosClientes!=nullptr) {
            for (int j=0;registro_PedidosClientes[j];j++) {
                void **datos_pedidos=(void **)registro_PedidosClientes[j];
                archReporte<<right<<*(int *)datos_pedidos[0]<<setw(10)<<*(int *)datos_pedidos[1]
                            <<setw(10)<<" "<<left<<setw(60)<<(char *)datos_pedidos[2]
                            <<right<<setw(15)<<*(int*)datos_pedidos[3]<<endl;
            }
        }
        archReporte<<"======================================================================================"<<endl;
    }
}

char *leerCadenaExacta(ifstream &archivo, char delimitador) {

    char buffer[500],*ptr_cadena;
    archivo.getline(buffer,500,delimitador);
    if (archivo.eof()) return nullptr;
    ptr_cadena = new char[strlen(buffer)+1];
    strcpy(ptr_cadena,buffer);

    return ptr_cadena;
}

void aperturaArchivoLeer(ifstream &archivo, const char *nombArch) {
    archivo.open(nombArch,ios::in);
    if (not archivo.is_open()) {
        cout<<"No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}

void aperturaArchivoEscribir(ofstream &archivo, const char *nombArch) {
    archivo.open(nombArch,ios::out);
    if (not archivo.is_open()) {
        cout<<"No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
}