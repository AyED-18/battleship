#ifndef BATTLESHIP_CASILLERO_HPP
#define BATTLESHIP_CASILLERO_HPP

// source files (headers)
#include "Ubicable.hpp"

enum class EstadoDeCasillero {SIN_EXPLORAR, AGUA, AVERIADO, HUNDIDO};

class Casillero : public Ubicable {
  public:
    // variables
    EstadoDeCasillero estado = EstadoDeCasillero::SIN_EXPLORAR;
    // funciones
    Casillero( int coordenadaX, int coordenadaY) : Ubicable(coordenadaX, coordenadaY) {};
};

#endif
