#ifndef BATTLESHIP_UBICABLE_HPP
#define BATTLESHIP_UBICABLE_HPP

// Ubicable es una clase abstracta, ya que no se generan instancias de ella, sino que sirve como superclase de otras.
// Un objeto ubicable, en este caso es un objeto que contiene en si una cierta ubicacion coordenada.
class Ubicable {
  public:
    // variables
    int coordenadaX;
    int coordenadaY;
    // funciones
    Ubicable(int coordenadaX, int coordenadaY) : coordenadaX(coordenadaX), coordenadaY(coordenadaY) {};
};

#endif
