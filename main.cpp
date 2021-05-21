// std library
#include <iostream>
#include <random>
#include <chrono>
// source code
#include "main.hpp"


int main() {
  hacerImpresionIntroductoria();

  // matriz que solo almacena los disparos hechos por la AI
  bool disparos[N_CASILLEROS_X][N_CASILLEROS_Y] = {0};
  // se prepara el tablero
  Tablero tablero;
  // se preparan los disparos a realizar
  Cola<BateriaDeDisparos*>* bateriasDeDisparos = generarBateriasDeDisparos();
  int cantidadBarcosHundidos = 0;
  Barco* barcosHundidos[N_BARCOS];

  // loop del juego
  while(cantidadBarcosHundidos < BARCOS_A_HUNDIR) {
    BateriaDeDisparos* bateriaDeDisparos;
    bateriaDeDisparos = bateriasDeDisparos->desencolar();
    // chequear si el lugar a disparar ya fue explorado
    Disparo *disparo;
    disparo = bateriaDeDisparos->proximoObjetivo();
    if(!tablero.casilleroExplorado(disparo->coordenadaX, disparo->coordenadaY)) {
      // no fue explorado, se hara aqui el disparo
      disparos[disparo->coordenadaX][disparo->coordenadaY] = 1;
      // BateriaDeDisparos#disparar devuelve 'a', 'v' o 'h'
      char respuestaHumano;
      respuestaHumano = bateriaDeDisparos->disparar(&tablero);
      if(respuestaHumano != 'a') {
        if(respuestaHumano == 'h') {
          // caso hundido: cambiar valor del casillero, llamar a Tablero#barcoHundido()
          barcosHundidos[cantidadBarcosHundidos] = tablero.barcoHundido(bateriaDeDisparos);
          cantidadBarcosHundidos++;
        } else {
          // 'v'
          hacerImpresionParcial(disparos, tablero);
          // disparo enfocadamente alrededor de donde se detecto un barco hasta hundirlo
          realizarDisparosEnfocados(disparo, tablero, bateriaDeDisparos, disparos, barcosHundidos, cantidadBarcosHundidos);
        }
      }
      hacerImpresionParcial(disparos, tablero);
    }
  }

  // juego terminado, imprimo resultados
  hacerImpresionFinal(disparos, barcosHundidos);
}


// Genera y devuelve todos los disparos que puede realizar la AI.
Cola<BateriaDeDisparos*>* generarBateriasDeDisparos() {
  Cola<BateriaDeDisparos*>* bateriasDeDisparos = new Cola<BateriaDeDisparos*>();

  int helper[N_CASILLEROS_X * N_CASILLEROS_Y];
  // en principio *helper* esta lleno de numeros consecutivos de 0..((N_CASILLEROS_X * N_CASILLEROS_Y) - 1)
  for(int i = 0; i < (N_CASILLEROS_X * N_CASILLEROS_Y); ++i) {
    helper[i] = i;
  }
  // se ira seleccionando de a una vez, un valor de *helper* que conformará un #Disparo
  unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 randomEngine(seed1);
  int tirada, provisorio, ultimoIndexEnRango;
  for(int i = 0; i < (N_CASILLEROS_X * N_CASILLEROS_Y); ++i) {
    // obtengo un index aleatorio dentro del rango
    ultimoIndexEnRango = (N_CASILLEROS_X * N_CASILLEROS_Y) - i - 1;
    std::uniform_int_distribution<int> distribution(0, ultimoIndexEnRango);
    tirada = distribution(randomEngine);
    // obtenido ese numero, creo el disparo basado en el
    Disparo* disparo = new Disparo((helper[tirada] / 10), (helper[tirada] % 10));
    BateriaDeDisparos* bateriaDeDisparos = new BateriaDeDisparos(disparo);
    bateriasDeDisparos->encolar(bateriaDeDisparos);
    // limpio *helper*
    provisorio = helper[tirada];
    helper[tirada] = helper[ultimoIndexEnRango];
    helper[ultimoIndexEnRango] = provisorio;
  }

  return bateriasDeDisparos;
}


void realizarDisparosEnfocados(Disparo* disparo, Tablero& tablero, BateriaDeDisparos* bateriaDeDisparos,
                               bool disparos[N_CASILLEROS_X][N_CASILLEROS_Y], Barco* barcosHundidos[N_BARCOS],
                               int& cantidadBarcosHundidos) {

  // caso averiado ('v'): agregar los disparos de alrededor a la pila. Coordenadas originales
  Disparo* nuevoDisparo;
  int i, xOg, yOg;
  char respuestaNuevoDisparo;
  xOg = disparo->coordenadaX;
  yOg = disparo->coordenadaY;

  // loop OESTE, max = 3 porque longitud max de barco es 4
  for(i = 0; i < 3; i++) {
    // si se esta en el borde izquierdo o si el proximo casillero fue explorado, no se sigue
    if(((yOg - 1 - i) < 0) || tablero.casilleroExplorado(xOg, (yOg - 1 - i))) {break;}
    // el potencial casillero a disparar no fue explorado. Se agrega disparo al oeste
    nuevoDisparo = new Disparo(xOg, (yOg - 1 - i));
    bateriaDeDisparos->agregarDisparo(nuevoDisparo);
    // se dispara (actualizo la matriz de *disparos*)
    disparos[nuevoDisparo->coordenadaX][nuevoDisparo->coordenadaY] = 1;
    respuestaNuevoDisparo = bateriaDeDisparos->disparar(&tablero);
    if(respuestaNuevoDisparo != 'v') {
      if(respuestaNuevoDisparo == 'h') {
        // el ultimo disparo hundio el barco ('h')
        barcosHundidos[cantidadBarcosHundidos] = tablero.barcoHundido(bateriaDeDisparos);
        cantidadBarcosHundidos++;
        return;
      }
      hacerImpresionParcial(disparos, tablero);
      // llegado a este punto, se encontro agua, hay que probar en otra direccion, se sale del for
      break;
    }
    hacerImpresionParcial(disparos, tablero);
  }

  // loop ESTE, max = 3 porque longitud max de barco es 4
  for(i = 0; i < 3; i++) {
    // si se esta en el borde derecho o si el proximo casillero fue explorado, no se sigue
    if(((yOg + 1 + i) < 0) || tablero.casilleroExplorado(xOg, (yOg + 1 + i))) {break;}
    // el potencial casillero a disparar no fue explorado. Se agrega disparo al este
    nuevoDisparo = new Disparo(xOg, (yOg + 1 + i));
    bateriaDeDisparos->agregarDisparo(nuevoDisparo);
    // se dispara (actualizo la matriz de *disparos*)
    disparos[nuevoDisparo->coordenadaX][nuevoDisparo->coordenadaY] = 1;
    respuestaNuevoDisparo = bateriaDeDisparos->disparar(&tablero);
    if(respuestaNuevoDisparo != 'v') {
      if(respuestaNuevoDisparo == 'h') {
        // el ultimo disparo hundio el barco ('h')
        barcosHundidos[cantidadBarcosHundidos] = tablero.barcoHundido(bateriaDeDisparos);
        cantidadBarcosHundidos++;
        return;
      }
      hacerImpresionParcial(disparos, tablero);
      // llegado a este punto, se encontro agua, hay que probar en otra direccion, se sale del for
      break;
    }
    hacerImpresionParcial(disparos, tablero);
  }

  // loop SUR, max = 3 porque longitud max de barco es 4
  for(i = 0; i < 3; i++) {
    // si se esta en el borde inferior o si el proximo casillero fue explorado, no se sigue
    if(((xOg - 1 - i) < 0) || tablero.casilleroExplorado((xOg - 1 - i),yOg )) {break;}
    // el potencial casillero a disparar no fue explorado. Se agrega disparo al sur
    nuevoDisparo = new Disparo((xOg - 1 - i), yOg);
    bateriaDeDisparos->agregarDisparo(nuevoDisparo);
    // se dispara (actualizo la matriz de *disparos*)
    disparos[nuevoDisparo->coordenadaX][nuevoDisparo->coordenadaY] = 1;
    respuestaNuevoDisparo = bateriaDeDisparos->disparar(&tablero);
    if(respuestaNuevoDisparo != 'v') {
      if(respuestaNuevoDisparo == 'h') {
        // el ultimo disparo hundio el barco ('h')
        barcosHundidos[cantidadBarcosHundidos] = tablero.barcoHundido(bateriaDeDisparos);
        cantidadBarcosHundidos++;
        return;
      }
      hacerImpresionParcial(disparos, tablero);
      // llegado a este punto, se encontro agua, hay que probar en otra direccion, se sale del for
      break;
    }
    hacerImpresionParcial(disparos, tablero);
  }

  // loop NORTE, max = 3 porque longitud max de barco es 4
  for(i = 0; i < 3; i++) {
    // si se esta en el borde superior o si el proximo casillero fue explorado, no se sigue
    if(((xOg + 1 + i) < 0) || tablero.casilleroExplorado((xOg + 1 + i),yOg )) {break;}
    // el potencial casillero a disparar no fue explorado. Se agrega disparo al norte
    nuevoDisparo = new Disparo((xOg + 1 + i), yOg);
    bateriaDeDisparos->agregarDisparo(nuevoDisparo);
    // se dispara (actualizo la matriz de *disparos*)
    disparos[nuevoDisparo->coordenadaX][nuevoDisparo->coordenadaY] = 1;
    respuestaNuevoDisparo = bateriaDeDisparos->disparar(&tablero);
    if(respuestaNuevoDisparo != 'v') {
      if(respuestaNuevoDisparo == 'h') {
        // el ultimo disparo hundio el barco ('h')
        barcosHundidos[cantidadBarcosHundidos] = tablero.barcoHundido(bateriaDeDisparos);
        cantidadBarcosHundidos++;
        return;
      }
      hacerImpresionParcial(disparos, tablero);
      // llegado a este punto, se encontro agua, hay que probar en otra direccion, se sale del for
      break;
    }
    hacerImpresionParcial(disparos, tablero);
  }
}


// Impresión en pantalla que se hace al arrancar el juego.
void hacerImpresionIntroductoria() {
  std::cout << "Batalla naval" << std::endl;
  std::cout << "=============" << std::endl << std::endl;
}


// Impresión en pantalla que se hace después de cada disparo. Imprime matriz de disparos(la necesita como arg) e info
// del #Tablero.
void hacerImpresionParcial(const bool disparos[N_CASILLEROS_X][N_CASILLEROS_Y], const Tablero& tablero) {
  std::cout << "Disparos     Exploracion" << std::endl;
  std::cout << "--------     -----------" << std::endl << std::endl;

  int j;
  for(int i = 0; i < N_CASILLEROS_X; ++i) {
    for(j = 0; j < N_CASILLEROS_Y; ++j) {
      // primero imprimo la fila correspondiente a los disparos realizados
      std::cout << (disparos[i][j] ? 'o' : 'x');
    }

    // espacio entre medio de las dos matrices
    std::cout << "   ";

    for(j = 0; j < N_CASILLEROS_Y; ++j) {
      // luego imprimo la fila correspondiente a la matriz del tablero (exploracion)
      switch(tablero.obtenerCasillero(i, j)->estado) {
        case EstadoDeCasillero::SIN_EXPLORAR:
          std::cout << '?';
          break;
        case EstadoDeCasillero::AGUA:
          std::cout << 'a';
          break;
        case EstadoDeCasillero::AVERIADO:
          std::cout << 'v';
          break;
        case EstadoDeCasillero::HUNDIDO:
          std::cout << 'h';
          break;
      }
    }

    std::cout << std::endl;
  }
  std::cout << std::endl;
}


// Impresión en pantalla que se hace al finalizar el juego. Imprime matriz de disparos(la necesita como arg) y
// resultado final del tablero explorado completamente.
void hacerImpresionFinal(const bool disparos[N_CASILLEROS_X][N_CASILLEROS_Y], Barco* barcosHundidos[N_BARCOS]) {
  std::cout << "Disparos   Exploracion total" << std::endl;
  std::cout << "--------   -----------------" << std::endl << std::endl;

  // preparar la matriz de exploracion total
  char exploracionTotal[N_CASILLEROS_X][N_CASILLEROS_Y];
  int i, j, coordenadaX, coordenadaY;
  // la lleno con valores 'a'(agua), por defecto
  for(i = 0; i < N_CASILLEROS_X; ++i) {
    for(j = 0; j < N_CASILLEROS_Y; ++j) {
      exploracionTotal[i][j] = 'a';
    }
  }

  // ahora recorro el contenedor de barcos, y modifico la matriz de exploracion total
  for(i = 0; i < N_BARCOS; ++i) {
    for(j = 0; j < barcosHundidos[i]->longitud; ++j) {
      coordenadaX = barcosHundidos[i]->posicionamiento[j]->coordenadaX;
      coordenadaY = barcosHundidos[i]->posicionamiento[j]->coordenadaY;
      switch(barcosHundidos[i]->tipo) {
        case TipoDeBarco::DESTRUCTOR:
          exploracionTotal[coordenadaX][coordenadaY] = 'd';
          break;
        case TipoDeBarco::CRUCERO:
          exploracionTotal[coordenadaX][coordenadaY] = 'r';
          break;
        case TipoDeBarco::CANONERA:
          exploracionTotal[coordenadaX][coordenadaY] = 'c';
          break;
        case TipoDeBarco::SUBMARINO:
          exploracionTotal[coordenadaX][coordenadaY] = 's';
          break;
      }
    }
  }

  // imprimo las matrices
  for(i = 0; i < N_CASILLEROS_X; ++i) {
    for(j = 0; j < N_CASILLEROS_Y; ++j) {
      // primero imprimo la fila correspondiente a los disparos realizados
      std::cout << (disparos[i][j] ? 'o' : 'x');
    }

    // espacio entre medio de las dos matrices
    std::cout << "   ";

    for(j = 0; j < N_CASILLEROS_Y; ++j) {
      // luego imprimo la fila correspondiente a la matriz de exploracion total
      std::cout << exploracionTotal[i][j];
    }

    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Disparos realizados: " << obtenerDisparosRealizados(disparos) << std::endl << std::endl;
  system("pause");
}

// Parsea el array de disparos(lo necesita como arg) y devuelve la cantidad de disparos realizados hasta el momento.
int obtenerDisparosRealizados(const bool disparos[N_CASILLEROS_X][N_CASILLEROS_Y]) {
  int contador = 0;
  for(int i = 0; i < N_CASILLEROS_X; ++i) {
    for(int j = 0; j < N_CASILLEROS_Y; ++j) {
      if(disparos[i][j] == 1) {
        contador++;
      }
    }
  }
  return contador;
}
