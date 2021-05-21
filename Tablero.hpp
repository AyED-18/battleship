#ifndef BATTLESHIP_TABLERO_HPP
#define BATTLESHIP_TABLERO_HPP

// constantes
#define BARCOS_A_HUNDIR 10
#define N_CASILLEROS_X 10
#define N_CASILLEROS_Y 10
#define N_BARCOS 10

class BateriaDeDisparos;

#include "Barco.hpp"
#include "Disparo.hpp"
#include "Casillero.hpp"
#include "Pila.hpp"
#include "BateriaDeDisparos.hpp"

class Tablero {
  private:
    //variables
    Casillero* casilleros[N_CASILLEROS_X][N_CASILLEROS_Y];
  public:
    //funciones
    Tablero();
    Barco* barcoHundido(BateriaDeDisparos* bateriaDeDisparos);
    bool casilleroExplorado(int coordenadaX, int coordenadaY) const;
    Casillero* obtenerCasillero(int coordenadaX, int coordenadaY) const;
};

// necesario para resolver problema de dependencia ciclica
char disparoRealizado(Tablero* tablero, Disparo* disparo);

#endif
