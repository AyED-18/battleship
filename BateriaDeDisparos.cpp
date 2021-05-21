#include "BateriaDeDisparos.hpp"

BateriaDeDisparos::BateriaDeDisparos(Disparo *disparo) {
  posicionesADisparar = Pila<Disparo*>();
  agregarDisparo(disparo);
}

char BateriaDeDisparos::disparar(Tablero* tablero) {
  char rta = disparoRealizado(tablero, posicionesADisparar.getTope());
  if(rta != 'a') {
    proximoObjetivo()->blancoAlcanzado = true;
  }
  return rta;
}

void BateriaDeDisparos::agregarDisparo(Disparo* disparo) {
  posicionesADisparar.apilar(disparo);
}

Disparo* BateriaDeDisparos::proximoObjetivo() {
  return posicionesADisparar.getTope();
}

int BateriaDeDisparos::tamano() {
  return posicionesADisparar.getTamano();
}
