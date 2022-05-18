#include "betris.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <windows.h>

using namespace std;

void inicializarTablero(tpTablero &tablero) {
    for(int i = 0; i < tablero.nfils; i++) {
        for(int j = 0; j < tablero.ncols; j++) {
            tablero.matriz[i][j] = -1;              // Se inicializan todas las casillas a -1
        }
    }
}

void mostrarCasilla(const int codigoDeColor) {
    cout << "\033[" << codigoDeColor << "m" << " " << "\033[0m"; 
}

void mostrarTablero(const tpTablero &tablero, const int vEntrada[MAXENTRADA]) {
    for (int i = 0; i < tablero.ncols; i++) {
        cout << "-";
    }
    cout << endl;
    for(int i = 0; i < tablero.nfils; i++) {                     // Se invierte el tablero para empezar desde abajo
        for(int j = 0; j  < tablero.ncols; j++) {
            int indexCasilla = tablero.matriz[i][j];
            if (indexCasilla != -1) {
                mostrarCasilla(piezaAColor[vEntrada[indexCasilla]]);
            } else {
                mostrarCasilla(0);
            }
        }
        cout << endl;
    }
    for (int i = 0; i < tablero.ncols; i++) {
        cout << "-";
    }
    cout << endl;
}

void escribirParametros(int vEntrada[], int &x, int &y, int &retardo, int &objetivo) {

    cout << "Escribe los parametros de entrada (dimension x, dimension y, objetivo, retardo, piezas): " << endl;
    cin >> x >> y >> objetivo >> retardo >> vEntrada[0];

    int n = 1;

    if (vEntrada[0] < 0) {
        // Funcion aleatoria de entrada con -vEntrada[0] numeros
    } else {
        while(vEntrada[n] != -1) {
            n++;
            cin >> vEntrada[n];
        }
    }

}

int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo) {
    
    if (vEntrada[n] == -1) {
        cout << "No se ha podido encontrar una solución al problema" << endl;   // #
        return -1;
    }
    
    for (int i = 0; i < tablero.ncols; i++) {                               // Buscamos solución empezando desde la primera columna

        cout << "Pieza numero " << n << " y columna numero " << i << endl;     // #

        int posicion[2];
        if (buscarFila(tablero, vEntrada[n], posicion, i)) {                //Si con la columna actual se ha encontrado espacio, cuya posición está guardada en el vector posición:
            
            tpTablero aux = tablero;                                        // Solucion temporal, no es muy eficiente en memoria
            int vSalAux[MAXENTRADA];
            for(int j = 0; j < n; j++) {
                vSalAux[j] = vSalida[j];
            }
            vSalAux[n] = i;

            insertarPieza(aux, vEntrada[n], n, posicion);
            mostrarTablero(aux, vEntrada);                             

            cout << "Se ha colocado la pieza " << n << endl;

            if (comprobarCondicion(aux, objetivo)) {
                for(int j = 0; j < n; j++) {
                    vSalida[j] = vSalAux[j];
                }
                cout << "Se ha encontrado solucion al problema en la columna " << n << endl; // #
                return n + 1;   // n empieza en 0, por lo tanto para convertirlo a numero natural hay que sumarle 1
            }
            
            return buscaSolucion(aux, vEntrada, vSalAux, objetivo, n + 1, retardo);
        }   
    }
}
 
bool comprobarCondicion(const tpTablero &tp, const int objetivo) {
    
    int nFilasRellenas = 0;

    for(int i = 0; i < tp.nfils; i++) {
        bool filaLlena = true;
        for(int j = 0; j < tp.ncols; j++) {
            if (tp.matriz[i][j] == -1) {
                filaLlena =  false;
            }
        }
        if (filaLlena) {
            nFilasRellenas++;
        }
    }

    return nFilasRellenas >= objetivo;

}

bool buscarFila(const tpTablero &tp, const int nPieza, int posicion[], int columna) {

    const int objetivoY = tp.nfils - tamPiezas[nPieza][0] + 1;

    tpPieza pieza = vPiezas[nPieza];

    for (int i = tp.nfils-1; i >= 0; i--) { 
        
        posicion[0] = i;
        posicion[1] = columna;

        if (comprobarPosicion(tp, pieza, posicion)) {
            return true;
        }
    }
    
    return false; // Si no se ha encontrado espacio se devuelve falso

}

bool comprobarPosicion(const tpTablero &tp, const tpPieza &pieza, const int posicion[]) {

    for (int i = 0; i < TAMPIEZA; i++) {
        if (tp.matriz[pieza.forma[i][0] + posicion[0]][pieza.forma[i][1] + posicion[1]] != VACIO) {
            return false;
        }
    }

    return true;

}

bool insertarPieza(tpTablero &tp, const int nPieza, const int index, const int posicion[]) {
    
    tpPieza pieza = vPiezas[nPieza];

    for (int i = 0; i < TAMPIEZA; i++) {
        const int yPosicion = posicion[0] + pieza.forma[i][0]; // Se almacenan las posiciones de las piezas
        const int xPosicion = posicion[1] + pieza.forma[i][1];

        tp.matriz[yPosicion][xPosicion] = index; // Se cambia la cuadricula a la del color de dicha pieza
    }
}
