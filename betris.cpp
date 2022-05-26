#include "betris.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


using namespace std;

void inicializarTablero(tpTablero &tablero) {
    for(int i = 0; i < tablero.nfils; i++) {
        for(int j = 0; j < tablero.ncols; j++) {
            tablero.matriz[i][j] = -1;              // Se inicializan todas las casillas a -1
        }
    }
}

void borrarPantalla() {
    cout << "\033[2J";
}


void subirCursor(const unsigned lineas) {
    cout << "\033[" << lineas << "A";
}


void mostrarCasilla(const int codigoDeColor) {
    cout << "\033[" << codigoDeColor << "m" << " " << "\033[0m"; 
}

void mostrarTablero(const tpTablero &tablero, const int vEntrada[MAXENTRADA]) {
    subirCursor(tablero.nfils);
    for(int i = 0; i < tablero.nfils; i++) { 
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
}

void escribirParametros(int vEntrada[], int &x, int &y, int &retardo, int &objetivo,const int argc,char* argv[]) {
    y = stoi(argv[1]);
    x = stoi(argv[2]);
    objetivo = stoi(argv[3]);
    retardo = stoi(argv[4]);
    
    int n = stoi(argv[5]);
    if (n < 0) {
        srand(time(nullptr));

        for (int i = 0; i < n; i++) {
            vEntrada[i] = rand() % PIEZASDEF; 
        }    

        vEntrada[n] = -1;
    } else {
        for (int i = 5; i < argc; i++) {
            vEntrada[i - 5] = stoi(argv[i]);
        }
    }
}

int buscaSolucion(tpTablero &tablero, const int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo) {

    if (vEntrada[n] == -1) {
        return -1;
    }
    
    if (comprobarCondicion(tablero, objetivo)) {
        return n;
    }

    int i = 0; 
    bool esSolucion = false;
    int backTracking = -1; 
    while (i < tablero.ncols && !esSolucion) {                                               // Buscamos solución empezando desde la primera columna

        int posicion[2];
        if (buscarFila(tablero, vEntrada[n], posicion, i)) {                //Si con la columna actual se ha encontrado espacio, cuya posición está guardada en el vector posición:

            insertarPieza(tablero, vEntrada[n], n, posicion, vSalida, true);
            if (retardo >= 0) {
                mostrarTablero(tablero, vEntrada);
                //usleep(retardo * 1000); 
            }
                                     

            int backTracking =  buscaSolucion(tablero, vEntrada, vSalida, objetivo, n + 1, retardo);
        
            if (backTracking == -1) {
                insertarPieza(tablero, vEntrada[n], n, posicion, vSalida, false);
            } else {
                return backTracking;
            }

        }

        i++;

    }

    return backTracking;

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

bool buscarFila(const tpTablero &tp, const int nPieza, int posicion[], const int columna) {

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
        
        int posY = pieza.forma[i][0] + posicion[0];
        int posX = pieza.forma[i][1] + posicion[1];
        
        for (int j = posY; j >= 0; j--) {
            if (tp.matriz[j][posX] != VACIO) {
                return false;
            }
        }

    }

    return true;

}

void insertarPieza(tpTablero &tp, const int nPieza, const int index, const int posicion[], int vSalida[], const bool insertar) {
    
    tpPieza pieza = vPiezas[nPieza];

    for (int i = 0; i < TAMPIEZA; i++) {
        const int yPosicion = posicion[0] + pieza.forma[i][0]; // Se almacenan las posiciones de las piezas
        const int xPosicion = posicion[1] + pieza.forma[i][1];

        if (insertar) {
            tp.matriz[yPosicion][xPosicion] = index; // Se cambia la cuadricula a la del color de dicha pieza
        } else {
            tp.matriz[yPosicion][xPosicion] = -1; // Se cambia la cuadricula a -1
        }
    }

    if (insertar) {
        vSalida[index] = posicion[1];
    } else {
        vSalida[index] = -1;
    }
}
