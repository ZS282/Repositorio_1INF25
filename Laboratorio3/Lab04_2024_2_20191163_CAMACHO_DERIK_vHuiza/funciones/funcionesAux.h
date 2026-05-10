//
// Created by Derik on 19/04/2026.
//

#ifndef LAB04_2024_2_20191163_CAMACHO_DERIK_VHUIZA_FUNCIONESAUX_H
#define LAB04_2024_2_20191163_CAMACHO_DERIK_VHUIZA_FUNCIONESAUX_H
#include <iostream>
#include <fstream>
using namespace std;

void cargarInventario(const char *nombArch,void *&inventario);
void cargarMenu(const char *nombArch,void *&menu);

void actualizarMenu(const char *nombArch,void *&inventario,void *&menu);
bool cargarInsumoBebida(ifstream &archInsumosBebidas,void *&inventario, void *&insumo,char *&codigo_bebida) ;
void *buscarInsumo(char *codigo_insumo,void *inventario);
void *buscarBebida(char *codigo_bebida,void *menu);
void agregarInsumoBebida(void *&bebida,void *insumo);
void incrementarInsumos(void **&dato_registroInsumos,int numInsumos,int incremento);
int numInsumosBebida(void *registroInsumos);
void verificarInventario(void* menu);
bool existeSuficienteInsumoEnInventario(void* insumos, int cantVentDiarias);

void reporteMenu(const char *nommbArch,void *menu);

bool leerBebidas(ifstream &archMenu,void *&ptr_datoRegBebida);
bool leerInsumos(ifstream &archInventario,void *&ptr_datoRegInsumo);
void probarCargarInventario(const char *nombArch, void *inventario);
void pruebaCargarMenu(const char* nombreArchivo,void* menu);
void apertura_leer_archivos(ifstream &archivo, const char *nombreArch);
void apertura_escribir_archivos(ofstream &archivo, const char *nombreArch);
char *leer_cadena(ifstream &archivo, char delimitador);

#endif //LAB04_2024_2_20191163_CAMACHO_DERIK_VHUIZA_FUNCIONESAUX_H