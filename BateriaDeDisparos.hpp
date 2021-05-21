#ifndef BATTLESHIP_BATERIADEDISPAROS_HPP
#define BATTLESHIP_BATERIADEDISPAROS_HPP

class Tablero;

#include "Disparo.hpp"
#include "Pila.hpp"
#include "Tablero.hpp"

class BateriaDeDisparos {
  public:
    // variables de instancia
    Pila<Disparo*> posicionesADisparar;
    // funciones
    BateriaDeDisparos(Disparo* disparo);
    void agregarDisparo(Disparo* disparo);
    Disparo* proximoObjetivo();
    char disparar(Tablero* tablero);
    int tamano();
};

#endif
