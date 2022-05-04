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
    
    vSalida[n] = -1;                                    // La primera pieza aún no tiene una columna designada

    for (int i = 0; i < tablero.ncols; i++) {
        vSalida[n]++;                                   //Empezamos en la columna 0 para la primera pieza

        tpTablero aux = tablero;
        const int posicion[2] = {0, 0};                 // Array auxiliar para que no de fallos el programa (hay que cambiarlo)

        bool esValido = insertarPieza(aux, vPiezas[vEntrada[i]], posicion);      //Falta poner exactamente en que fila poner la pieza (Depende de si hay piezas debajo o de la propia altura de la pieza)

        // TODO: ACTUALIZAR VENTRADA Y VSALIDA CON LOS NUEVOS DATOS

        mostrarTablero(aux, vEntrada);              //Mostramos la pieza puesta en este caso

        // Se produce retardo

        if (esValido) {
            if (n < objetivo)  {
                return buscaSolucion(tablero, vEntrada, vSalida, objetivo, n + 1, retardo);
            } else {
                return n;
            }
        }

        
    }


    


}

bool insertarPieza(tpTablero &tp, const tpPieza &pieza, const int posicion[]) {
    
    bool solapado = false; // Comprobar si se ha solapado alguna pieza

    for (int i = 0; i < TAMPIEZA; i++) {
        const int xPosicion = posicion[0] + pieza.forma[i][0]; // Se almacenan las posiciones de las piezas
        const int yPosicion = posicion[1] + pieza.forma[i][1];

        solapado = tp.matriz[xPosicion][yPosicion] == -1 ? solapado : true; // Si hay alguna pieza en dicha posicion hay solapacion

        tp.matriz[xPosicion][yPosicion] = pieza.color; // Se cambia la cuadricula a la del color de dicha pieza
    }
    
    return !solapado;
}

int main() {
    tpTablero tablero;
    int vEntrada[MAXENTRADA];

    mostrarTablero(tablero, vEntrada);
    
    return 0;
}

/*
if (esValido(tablero, vSalida[n])) {
            if (n < objetivo)  {
                return buscaSolucion(tablero, vEntrada, vSalida, objetivo, n + 1, retardo);
            } else {
                return n;
            }
        }
        */

/*
// Comprobar si el objetivo se ha cumplido
    // ---------------------------------------
    bool filasCompletadas = 0;

    for (int i = 0; i < tablero.nfils; i++) {
        
        bool filaCompletada = true;
        
        for (int j = 0; j < tablero.ncols; j++) {
            if (tablero.matriz[i][j] == -1) {
                filaCompletada = false;
            }
        }

        if (filaCompletada) {
            filasCompletadas++;
        }
    }
    return filasCompletadas >= objetivo ? n : -1;
    // ---------------------------------------
*/