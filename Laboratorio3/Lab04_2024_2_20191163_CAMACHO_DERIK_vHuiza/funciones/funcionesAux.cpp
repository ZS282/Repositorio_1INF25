//
// Created by Derik on 19/04/2026.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "funcionesAux.h"
using namespace std;

void cargarInventario(const char *nombArch,void *&inventario) {

    ifstream archInventario;
    apertura_leer_archivos(archInventario,nombArch);
    //void **vv;
    void **buffer_insumos = new void *[200];
    int num=0;
    while (leerInsumos(archInventario,buffer_insumos[num]))num++;

    void **vv_inventario = new void *[num+1];

    for(int i=0;i<num;i++) {
        vv_inventario[i] = buffer_insumos[i];
    }
    vv_inventario[num] = nullptr;
    delete [] buffer_insumos;


    inventario = vv_inventario;
}

void cargarMenu(const char *nombArch,void *&menu) {

    ifstream archMenu;
    apertura_leer_archivos(archMenu,nombArch);

    void **buffer_menu = new void *[200];
    int num=0;
    while (leerBebidas(archMenu,buffer_menu[num]))num++;

    void **vv_menu = new void *[num+1];
    for(int i=0;i<num;i++) {
        vv_menu[i] = buffer_menu[i];
    }
    vv_menu[num] = nullptr;
    delete [] buffer_menu;
    menu = vv_menu;

}

void actualizarMenu(const char *nombArch,void *&inventario,void *&menu) {

    ifstream archInsumosBebidas;
    apertura_leer_archivos(archInsumosBebidas,nombArch);

    void *insumo;//registro de 1 INSUMO
    char *codigo_bebida;

    while (cargarInsumoBebida(archInsumosBebidas,inventario,insumo,codigo_bebida)) {\
        //Se carga el insumo que requiere la bebida, y lo mentenemos apuntado con el void *insumo;
        void *bebida=buscarBebida(codigo_bebida,menu);
        //Se busca la bebida y se guarda la DM en void *bebida;
        agregarInsumoBebida(bebida,insumo);
    }

    verificarInventario(menu);
}

void verificarInventario(void* menu) {

    void **bebidas=(void **)menu;
    for (int i=0;bebidas[i];i++) {
        void **bebida=(void**)bebidas[i];
        void *insumos = (void**)bebida[7];//Acceso al espacio donde se apunta al arreglo de punteros

        int cantVentasDiaria = *(int*)bebida[6];
        if (!existeSuficienteInsumoEnInventario(insumos,cantVentasDiaria)) {
            *(bool*)bebida[4] = false;
        }
    }
}

bool existeSuficienteInsumoEnInventario(void* insumos, int cantVentDiarias) {

    bool suficiente = true;
    void **vv= (void**)insumos;//Acceder al primer nivel *VV de los insumos
    for (int i=0;vv[i];i++) {
        void **insumo=(void**)vv[i];//Acceder a cada dato del arreglo INSUMOS (primer nivel de los insumos)

        void** insumoInventario = (void**)insumo[0];//Cada dato apunta a una estructura,
        //Apuntamos a esta estructura de Inventario
        double *cantidadPorBebida = (double*)insumo[1];//Cantidad en gramos que se va a pedir
        double *cantidadDisponible = (double*)insumoInventario[2];//Cantidad disponible de la estructura de Inventario
        double *cantidadRequerida = (double*)insumoInventario[3];//Cantidad actualizable de la estructura de Inventario
        double nuevaCantidadRequerida = *cantidadRequerida+((*cantidadPorBebida/1000.00)*cantVentDiarias);
        if (*cantidadDisponible < nuevaCantidadRequerida) {
            suficiente = false;
        }
        *cantidadRequerida = nuevaCantidadRequerida;
        insumoInventario[3] = cantidadRequerida;//Se actualiza el campo de *cantidadRequerida
    }
    return suficiente;
}

void agregarInsumoBebida(void *&bebida,void *insumo) {

    void **registro_bebida=(void **)bebida;// Accedemos al void *bebida para
    void **dato_registroInsumos = (void **)registro_bebida[7];
    //Creamos el vinculo entre el insumo y la bebida

    int numInsumos=numInsumosBebida(dato_registroInsumos);
    incrementarInsumos(dato_registroInsumos,numInsumos,1);
    dato_registroInsumos[numInsumos++]=insumo;//Agregamos, en base al contado numInsumos, los insumos
    registro_bebida[7]=dato_registroInsumos;//Linkeamos el ultimo elemento
    //con el void** de los insumos, de los cuales cada insumo contiene su cantidad
    bebida=registro_bebida;
}

void incrementarInsumos(void **&dato_registroInsumos,int numInsumos,int incremento) {

    int capacidad=numInsumos+incremento;
    void **vv=(void **)dato_registroInsumos;

    if (vv==nullptr) {
        vv=new void *[capacidad+1]{};
    }else {
        void **vv_aux=new void *[capacidad+1]{};
        for(int i=0;i<numInsumos;i++) {
            vv_aux[i]=vv[i];
        }
        delete [] vv;
        vv=vv_aux;
    }
    dato_registroInsumos=vv;
}

int numInsumosBebida(void *registroInsumos) {

    int num=0;
    void **v_aux=(void **)registroInsumos;//acceso a los registros de insumos
    if (v_aux!=nullptr) {
        for (;v_aux[num];num++) ;
    }
    return num;
}

bool cargarInsumoBebida(ifstream &archInsumosBebidas,void *&inventario, void *&insumo,char *&codigo_bebida) {
    double cantidad;
    char *unidadMedida, *codigo_insumo,c;
    // B001,I001,10,g
    // B001,I002,8,g
    // B002,I001,12,g
    // B002,I002,6,g
    // B002,I003,200,g
    // B003,I001,10,g
    codigo_bebida = leer_cadena(archInsumosBebidas,',');
    if (archInsumosBebidas.eof())return false;
    codigo_insumo=leer_cadena(archInsumosBebidas,',');
    archInsumosBebidas>>cantidad>>c;
    unidadMedida=leer_cadena(archInsumosBebidas,'\n');

    void **vv = new void*[3];

    vv[0]=buscarInsumo(codigo_insumo,inventario);
    vv[1]=new double(cantidad);
    vv[2]=unidadMedida;

    insumo=vv;

    return true;
}

void *buscarBebida(char *codigo_bebida,void *menu) {

    void **bebidas = (void**)menu;
    void **resultado = nullptr;
    for (int i=0;bebidas[i];i++) {
        void **bebida = (void **)bebidas[i];
        char *codigo = (char *)bebida[0];
        if (strcmp(codigo_bebida,codigo)==0) {
            resultado=bebida;
            break;
        }
    }
    return resultado;
}

void *buscarInsumo(char *codigo_insumo,void *inventario) {
    void **insumos = (void**)inventario;
    void **resultado=nullptr;
    for (int i=0;insumos[i];i++) {
        void **registro_insumo = (void**)insumos[i];
        char *codigo = (char*)registro_insumo[0];
        if (strcmp(codigo_insumo,codigo)==0) {
            resultado=registro_insumo;
            break;
        }
    }
    int a;
    return resultado;
}

void pruebaCargarMenu(const char* nombreArchivo,void* menu) {
    ofstream archRep;
    apertura_escribir_archivos(archRep,nombreArchivo);

    archRep << "============================= Menú del día ======================================" << endl;

    void** bebidas = (void**)menu;
    for (int i = 0; bebidas[i]; i++) {
        void** bebida = (void**)bebidas[i];

        char* nombre = (char*)bebida[1];
        char* descripcion = (char*)bebida[2];
        char *tipo = (char*)bebida[3];
        bool disponible = (bool*)bebida[4];
        double precio = *(double*)bebida[5];

        // const char* nombreTipoBebida = tipoBebida(tipo);
        //
        archRep << tipo << ": " << nombre << endl;
        archRep << descripcion << endl;
        archRep << "Precio: S/ " << fixed << setprecision(2) << precio << endl;
        archRep << "Disponible: " << (disponible ? "Si" : "No") << endl;

        archRep << "---------------------------------------------------------------------------------" << endl;
    }
}

bool leerBebidas(ifstream &archMenu,void *&ptr_datoRegBebida) {

    char *codido_bebida,*nombre_bebida,*descripcion_bebida,*tipo_bebida,c;
    double precio;
    int cant_ventasEstim;

    codido_bebida=leer_cadena(archMenu,',');
    if (archMenu.eof())return false;
    nombre_bebida=leer_cadena(archMenu,',');
    descripcion_bebida=leer_cadena(archMenu,',');
    tipo_bebida=leer_cadena(archMenu,',');
    archMenu>>precio>>c>>cant_ventasEstim;

    void **registro= new void *[8];

    registro[0]=codido_bebida;
    registro[1]=nombre_bebida;
    registro[2]=descripcion_bebida;
    registro[3]=tipo_bebida;
    registro[4]=new bool(true);
    registro[5]=new double(precio);
    registro[6]=new int(cant_ventasEstim);
    registro[7]=nullptr;
    ptr_datoRegBebida=registro;
    return true;
}

void probarCargarInventario(const char *nombArch, void *inventario) {
    ofstream archReporte;
    apertura_escribir_archivos(archReporte, nombArch);

    void **insumos_inventario = (void**)inventario;

    for (int i=0;insumos_inventario[i]!=nullptr;i++) {
        const void** insumo = (const void**)insumos_inventario[i];

        const char* codigo = (const char*)insumo[0];
        const char* nombre = (const char*)insumo[1];
        const double cantidadDisponible = *(const double*)insumo[2];
        const double cantidadRequerida = *(const double*)insumo[3];
        const char* unidadMedida = (const char*)insumo[4];

        archReporte << left << setw(10) << codigo
                    << setw(50) << nombre
                    << right << setw(20) << fixed << setprecision(2) << cantidadDisponible
                    << setw(12) << fixed << setprecision(2) << cantidadRequerida
                    << setw(10) << unidadMedida << endl;
    }
}

// I001,Café Arábica,50,kg
// I002,Café Robusta,30,kg
// I003,Leche Entera,20,kg
bool leerInsumos(ifstream &archInventario,void *&ptr_datoRegInsumo) {

    char *codigo_insumo,*nombre_insumo,*unidad_medida;
    double cantidad_disponible;

    codigo_insumo=leer_cadena(archInventario,',');
    if (archInventario.eof())return false;
    nombre_insumo=leer_cadena(archInventario,',');

    archInventario>>cantidad_disponible;
    archInventario.ignore();
    unidad_medida=leer_cadena(archInventario,'\n');
    double cantidad_requerida=0.0;

    void **registro=new void *[5];

    registro[0]=codigo_insumo;
    registro[1]=nombre_insumo;
    registro[2]=new double(cantidad_disponible);
    registro[3]=new double(cantidad_requerida);
    registro[4]=unidad_medida;

    ptr_datoRegInsumo=registro;

    return true;
}

void reporteMenu(const char *nombArch,void *menu) {
    ofstream archRep;
    apertura_escribir_archivos(archRep,nombArch);
    archRep << "============================= Menú del día ======================================" << endl;

    const void** bebidas = (const void**)menu;
    for (int i = 0; bebidas[i]; i++) {
        const void** bebida = (const void**)bebidas[i];

        const char* nombre = (const char*)bebida[1];
        const char* descripcion = (const char*)bebida[2];
        const char tipo = *(const char*)bebida[3];
        const bool disponible = *(const bool*)bebida[4];
        const double precio = *(const double*)bebida[5];

        // const char* nombreTipoBebida = getNombreTipoBebida(tipo);

        archRep << tipo << ": " << nombre << endl;
        archRep << descripcion << endl;
        archRep << "Precio: S/ " << fixed << setprecision(2) << precio << endl;
        archRep << "Disponible: " << (disponible ? "Si" : "No") << endl;

        archRep << "---------------------------------------------------------------------------------" << endl;
    }
}

void apertura_leer_archivos(ifstream &archivo, const char *nombreArch) {
    char ruta_completa[500];
    strcpy(ruta_completa, "ArchivosDeDatos/");
    strcat(ruta_completa, nombreArch);
    archivo.open(ruta_completa, ios::in);
    if (not archivo.is_open()) {
        cout<<"Error al abrir el archivo "<<nombreArch<<endl;
        exit(1);
    }

}
void apertura_escribir_archivos(ofstream &archivo, const char *nombreArch) {
    char ruta_completa[500];
    strcpy(ruta_completa, "ArchivosDeReporte/");
    strcat(ruta_completa, nombreArch);
    archivo.open(ruta_completa, ios::out);
    if (not archivo.is_open()) {
        cout<<"Error al abrir el archivo "<<nombreArch<<endl;
        exit(1);
    }

}

char *leer_cadena(ifstream &archivo, char delimitador) {
    char *ptr;
    char buffer[500];
    archivo>>ws;
    archivo.getline(buffer, 500, delimitador);
    if (archivo.eof()) return nullptr;
    ptr = new char[strlen(buffer)+1];
    strcpy(ptr, buffer);
    return ptr;
}