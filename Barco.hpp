#ifndef BATTLESHIP_BARCO_HPP
#define BATTLESHIP_BARCO_HPP

#include <map>
#include "Casillero.hpp"

enum class TipoDeBarco {DESTRUCTOR,CRUCERO,CANONERA,SUBMARINO};
static std::map<int, TipoDeBarco> BARCOS_SEGUN_LONGITUD = {
    {4, TipoDeBarco::DESTRUCTOR},
    {3, TipoDeBarco::CRUCERO},
    {2, TipoDeBarco::CANONERA},
    {1, TipoDeBarco::SUBMARINO}
};

class Barco {
  public:
    //variables
    TipoDeBarco tipo;
    int longitud;
    Casillero* posicionamiento[4];
    // funciones
    Barco(TipoDeBarco tipo, int longitud) : longitud(longitud), tipo(tipo) {};
};

#endif
