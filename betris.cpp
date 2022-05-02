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
            switch(tablero.matriz[i][j]) {
                case -1:
                    mostrarCasilla(NEGRO);
                    break;
                case 0:
                    mostrarCasilla(AZUL);
                    break;
                case 1:
                    mostrarCasilla(VERDE);
                    break;
                case 2:
                    mostrarCasilla(ROJO);
                    break;
                case 3:
                    mostrarCasilla(CIAN);
                    break;
                case 4:
                    mostrarCasilla(AMARILLO);
                    break;
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