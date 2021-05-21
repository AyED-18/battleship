#ifndef BATTLESHIP_MAIN_HPP
#define BATTLESHIP_MAIN_HPP

// source files (headers)
#include "BateriaDeDisparos.hpp"
#include "Tablero.hpp"
#include "Cola.hpp"

// prototipado de funciones en main
Cola<BateriaDeDisparos*>* generarBateriasDeDisparos();
void hacerImpresionIntroductoria();
void hacerImpresionParcial(const bool disparos[N_CASILLEROS_X][N_CASILLEROS_Y], const Tablero& tablero);
void hacerImpresionFinal(const bool disparos[N_CASILLEROS_X][N_CASILLEROS_Y], Barco* barcosHundidos[N_BARCOS]);
int obtenerDisparosRealizados(const bool disparos[N_CASILLEROS_X][N_CASILLEROS_Y]);
void realizarDisparosEnfocados(Disparo* disparo, Tablero& tablero, BateriaDeDisparos* bateriaDeDisparos,
                               bool disparos[N_CASILLEROS_X][N_CASILLEROS_Y], Barco* barcosHundidos[N_BARCOS],
                               int& cantidadBarcosHundidos);
#endif
