#ifndef BATTLESHIP_COLA_HPP
#define BATTLESHIP_COLA_HPP

#include "Nodo.hpp"

template <class T> class Cola {
  private:
    // variables de instancia
    Nodo<T>* inicio = nullptr;
    Nodo<T>* fin = nullptr;
  public:
    // funciones
    Cola() {};
    Cola(T dato) {encolar(dato);};
    void encolar(T dato);
    T desencolar();
};



// definiciones de las funciones no-inline de la clase
template<typename T>
void Cola<T>::encolar(T dato) {
  if(inicio) {
    // si no esta vacia
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    fin->next = nuevoNodo;
    fin = nuevoNodo;
  } else {
    // si esta vacia
    fin = inicio = new Nodo<T>(dato);
  }
}


template<typename T>
T Cola<T>::desencolar() {
  // el primer de la fila debe salir
  if(inicio) {
    // copy initialization
    T datoADevolver(inicio->dato);
    Nodo<T>* nodoABorrar = inicio;
    inicio = inicio->next;
    delete nodoABorrar;
    return datoADevolver;
  } else {
    return nullptr;
  }
}

#endif
