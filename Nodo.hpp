#ifndef BATTLESHIP_NODO_HPP
#define BATTLESHIP_NODO_HPP

template <typename T> class Nodo {
  public:
    // variables de instancia
    T dato;
    Nodo* next;
    // funciones
    Nodo(T dato) : dato(dato), next(nullptr) {};
    Nodo(T dato, Nodo* next) : dato(dato), next(next) {};
};

#endif
