#include "betris.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
//#include <windows.h>

using namespace std;

void inicializarTablero(tpTablero &tablero) {
    for(int i = 0; i < tablero.nfils; i++) {
        for(int j = 0; j < tablero.ncols; j++) {
            tablero.matriz[i][j] = -1;              // Se inicializan todas las casillas a -1
        }
    }
}

/*
 * Pre:  ---
 * Post: Borra la parte visible del terminal y mueve el cursor a la primera
 *       fila y la primera columna, de forma que la siguiente instrucción de 
 *       escritura en pantalla escriba desde el inicio de la parte visible del
 *       terminal.
 */
void borrarPantalla() {
    cout << "\033[2J";
}

/*
 * Pre:  ---
 * Post: Sube el cursor de escritura del terminal «lineas» líneas, sin borrar
 *       el contenido que ya esté escrito en el terminal.
 */
void subirCursor(const unsigned lineas) {
    cout << "\033[" << lineas << "A";
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
    
    if (comprobarCondicion(tablero, objetivo)) {
        return n + 1;
    }

    //while
    int i = 0;  
    while (i < tablero.ncols) {                                               // Buscamos solución empezando desde la primera columna

        cout << "Pieza numero " << n << " y columna numero " << i << endl;     // #

        int posicion[2];
        if (buscarFila(tablero, vEntrada[n], posicion, i)) {                //Si con la columna actual se ha encontrado espacio, cuya posición está guardada en el vector posición:

            insertarPieza(tablero, vEntrada[n], n, posicion, vSalida, true);
            vSalida[n] == i;
            mostrarTablero(tablero, vEntrada);                             

            cout << "Se ha colocado la pieza " << n << endl;
            
            int backTracking =  buscaSolucion(tablero, vEntrada, vSalida, objetivo, n + 1, retardo);
        
            if (backTracking > 0) {
                return backTracking;
            } else {
                insertarPieza(tablero, vEntrada[n], n, posicion, vSalida, false);
            }

        }

        i++;

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

bool insertarPieza(tpTablero &tp, const int nPieza, const int index, const int posicion[], int vSalida[], const bool insertar) {
    
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
