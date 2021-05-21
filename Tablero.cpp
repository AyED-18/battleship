#include <iostream>
#include "Tablero.hpp"

Tablero::Tablero() {
  for(int i = 0; i < N_CASILLEROS_X; i++) {
    for(int j = 0; j < N_CASILLEROS_Y; j++) {
      casilleros[i][j] = new Casillero(i, j);
    }
  }
}


char disparoRealizado(Tablero* tablero, Disparo* disparo) {
  std::cout << "AI: disparo a (" << disparo->coordenadaX << "," << disparo->coordenadaY << "), impacto?" << std::endl;
  std::cout << "Humano: " << std::flush;

  char respuestaHumano;
  bool x = false;
  // evita que el usuario ingrese otra letra que no sea a,v,h.
  do {
    std::cin >> respuestaHumano;
    std::cout << std::endl;
    respuestaHumano = tolower(respuestaHumano);
    if(respuestaHumano == 'a' or respuestaHumano == 'v' or respuestaHumano == 'h') {
      x = true;
    } else {
      std::cout << "Por favor ingrese un caracter valido (a: agua, v: averiado, h: hundido)" << std::endl;
    }
  } while(!x);
  // cambia el estado del casillero y retorna el valor ingresado por el usuario
  switch(respuestaHumano) {
    case 'a':
      tablero->obtenerCasillero(disparo->coordenadaX, disparo->coordenadaY)->estado = EstadoDeCasillero::AGUA;
      return 'a';
    case 'v':
      tablero->obtenerCasillero(disparo->coordenadaX, disparo->coordenadaY)->estado = EstadoDeCasillero::AVERIADO;
      return 'v';
    default:
      tablero->obtenerCasillero(disparo->coordenadaX, disparo->coordenadaY)->estado = EstadoDeCasillero::HUNDIDO;
      return 'h';
  }
}


Barco* Tablero::barcoHundido(BateriaDeDisparos* bateriaDeDisparos){
  // contador
  int cont = 0;
  // nuevo barco, atributos se pueden cambiardespues
  Barco* barco = new Barco(TipoDeBarco::SUBMARINO, 1);
  // recorrer la pila de disparos
  int tamanoOriginalDeBat = bateriaDeDisparos->tamano();
  for(int i=0; i < tamanoOriginalDeBat; i++) {
    // seleccionar los que dieron en el blanco
    Disparo* disparo = bateriaDeDisparos->posicionesADisparar.desapilar();
    if(disparo->blancoAlcanzado) {
      // cambiar estado a hundido
      obtenerCasillero(disparo->coordenadaX, disparo->coordenadaY)->estado = EstadoDeCasillero::HUNDIDO;
      // guardar coordenadas en el barco
      Casillero* casillero = new Casillero(disparo->coordenadaX, disparo->coordenadaY);
      barco->posicionamiento[cont] = casillero;
      // aumentar el contador
      cont++;
      // recorrer los de alrededor y cambiar a agua los no averiados o hundidos
      for(int k=-1; k < 2; k++) {
        for(int l=-1; l < 2; l++) {
          if(((disparo->coordenadaX + k) > -1) && ((disparo->coordenadaX + k) < N_CASILLEROS_X) &&
             ((disparo->coordenadaY + l) > -1) && ((disparo->coordenadaY + l) < N_CASILLEROS_Y) &&
             (obtenerCasillero(disparo->coordenadaX + k, disparo->coordenadaY + l)->estado == (EstadoDeCasillero::SIN_EXPLORAR))) {
            obtenerCasillero(disparo->coordenadaX + k,disparo->coordenadaY + l)->estado = EstadoDeCasillero::AGUA;
          }
        }
      }
    }
  }

  barco->longitud = cont;

  // asignar tipo de barco
  switch(barco->longitud) {
    // si la longitud es 1, queda TipoDeBarco::SUBMARINO, que fue el que se definio en principio
    case 2:
      barco->tipo = BARCOS_SEGUN_LONGITUD[2];
      break;
    case 3:
      barco->tipo = BARCOS_SEGUN_LONGITUD[3];
      break;
    case 4:
      barco->tipo = BARCOS_SEGUN_LONGITUD[4];
      break;
  }

  return barco;
}


bool Tablero::casilleroExplorado(int coordenadaX, int coordenadaY) const {
  return (obtenerCasillero(coordenadaX, coordenadaY)->estado != EstadoDeCasillero::SIN_EXPLORAR);
}

Casillero* Tablero::obtenerCasillero(int coordenadaX, int coordenadaY) const {
  return casilleros[coordenadaX][coordenadaY];
}