#ifndef BATTLESHIP_DISPARO_HPP
#define BATTLESHIP_DISPARO_HPP

// source files (headers)
#include "Ubicable.hpp"

// Un Disparo representa una bomba que en algun momento sera disparada por una bateria de disparos, hacia un cierto
// objetivo coordenado de cierto tablero.
class Disparo : public Ubicable {
  public:
    // variables
    bool blancoAlcanzado = false;
    // funciones
    Disparo(int coordenadaX, int coordenadaY) : Ubicable(coordenadaX, coordenadaY) {};
};

#endif
