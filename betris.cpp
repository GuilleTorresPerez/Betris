#include "betris.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

void inicializarTablero(tpTablero &tablero) {
    for(int i = 0; i < tablero.nfils; i++) {
        for(int j = 0; j < tablero.ncols; j++) {
            tablero.matriz[i][j] = -1;
        }
    }
}

//Escribe en pantalla el color indicado
void mostrarCasilla(const int codigoDeColor) {
    cout << "\033[" << codigoDeColor << "m" << " " << "\033[0m";
}

void mostrarTablero(const tpTablero & tablero, const int vEntrada[MAXENTRADA]) {
    for(int i = 0; tablero.nfils; i++) {
        for(int j = 0; tablero.ncols; j++) {
            mostrarCasilla(piezaAColor[tablero.matriz[i][j]]);
        }
    }
}

//Se me ocurre dividir el árbol en etapas las cuales sean las piezas hasta llegar a la etapa final que sería la última pieza y que hasta la fila objetivo esté lleno.
//Hasta que no se consiga colocar la pieza no se continua.
//Y las soluciones van a ser las columnas donde se colocan las las figuras. (Vsalida, supongo)

//La pieza solo puede ponerse sobre el suelo o sobre otra pieza y que no sobrepase la fila objetivo así que en verdad solo hay numColumnas posibles soluciones
//Con que no se solape una pieza encima de otra o se salga del tablero todo ok

int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo = 0) {
    
    if (n > objetivo) return -1;
    vSalida[n] = -1;                                    // La primera pieza aún no tiene una columna designada
    for (int i = 0; i < tablero.ncols; i++) {
        vSalida[n]++;                                   //Empezamos en la columna 0 para la primera pieza

        insertarPieza(tablero, vEntrada, vSalida);      //Falta poner exactamente en que fila poner la pieza (Depende de si hay piezas debajo o de la propia altura de la pieza)

        mostrarTablero(tablero, vEntrada);              //Mostramos la pieza puesta en este caso

        if (esValido(tablero, vSalida[n])) {
            if (n < objetivo)  {
                return buscaSolucion(tablero, vEntrada, vSalida, objetivo, n + 1, retardo);
            } else {
                return n;
            }
        }
    }
    
}

int main() {
    tpTablero tablero;
    int vEntrada[MAXENTRADA];

    mostrarTablero(tablero, vEntrada);
    
    return 0;
}