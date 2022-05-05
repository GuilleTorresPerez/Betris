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

/* 

    Algoritmo de Backtracking: 
    - Se coge una pieza de las disponibles en un array de entrada
    - Se comprueba si esa pieza cabe en el tablero, en alguna parte
    - Se elimina la pieza del array de entrada
        - Si la pieza no cabe
            - Si se ha comprobado con todas las piezas, o ninguna de las dichas cabe más, se devuelve false y no se prueba más con esa rama
            - Si no se sigue comprobando el resto de las piezas
        - Si la pieza cabe en alguna parte
            - Se actualiza vSalida con la nueva pieza, así como vEntrada
            - Se comprueba si se ha cumplido el objetivo
                - Si se ha cumplido el objetivo se para de buscar y finaliza el programa
                - Si no se ha cumplido el objetivo se sigue buscando con el algoritmo de backtracking, habiendo eliminado la pieza que se ha colocado

    Hay que retirar las piezas usadas de alguna lista, entonces da igual hacer un for con columnas que con piezas, aunque me parece
    más intuitivo con piezas, esto ya lo haces tu como veas

*/

// TODO: Hay muchas partes de la función que las he dejado inacabadas, si crees que algo está mal es porque seguramente lo está

int buscaSolucion(tpTablero &tablero, int vEntrada[MAXENTRADA], int vSalida[MAXENTRADA], const int objetivo, int n, const int retardo = 0) {
    
    for (int i = 0; i < tablero.ncols; i++) {
        
        vSalida[n] = i;

        tpTablero aux = tablero;

        // TODO: CALCULAR NUEVA POSICION PARA COLOCAR PIEZAS (SI CABEN EN EL TABLERO O SI HAY ALGUNA YA EN EL SUELO, ETC)

        //const int posicion[2] = {0, 0};                 // Array auxiliar para que no de fallos el programa (hay que cambiarlo)


        int height = 0;
        int index = -1;
        while(height != 0) {
            height = aux.matriz[0][vSalida[n]]; // Check for empty bottom space
        }

        const int posicion[2] = {0, vSalida[n]};

        bool esValido = false;      //Falta poner exactamente en que fila poner la pieza (Depende de si hay piezas debajo o de la propia altura de la pieza)

        while(!esValido) {

        }

        //insertarPieza(aux, vPiezas[vEntrada[i]], posicion);
        // TODO: ACTUALIZAR VENTRADA Y VSALIDA CON LOS NUEVOS DATOS

        mostrarTablero(aux, vEntrada);              //Mostramos la pieza puesta en este caso

        // Se produce retardo

        if (esValido) {
            vEntrada[n] = 
            if (n < objetivo)  {
                return buscaSolucion(aux, vEntrada, vSalida, objetivo, n + 1, retardo);
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


// ESTOS ES CODIGO QUE NO CREO QUE LLEGUE A SER NECESARIO PERO NO LO BORRO POR SI ACASO


/*

bool comprobarEspacio(const tpTablero &tp, const int nPieza, int posicion[]) {

    const int objetivoY = tp.nfils - tamPiezas[nPieza][0];
    const int objetivoX = tp.ncols - tamPiezas[nPieza][1];

    tpPieza pieza = vPiezas[nPieza];

    for (int i = 0; i < objetivoX; i++) {
        for (int j = 0; j < objetivoY; j++) {
            
            posicion[0] = i;
            posicion[1] = j;

            if (comprobarPosicion(tp, pieza, posicion)) {
                return true;
            }
        }
    }

    return false; // Si no se ha encontrado espacio se devuelve falso

}

bool comprobarPosicion(const tpTablero &tp, const tpPieza &pieza, const int posicion[]) {

    bool hayEspacio = true;

    for (int i = 0; i < TAMPIEZA; i++) {
        if (tp.matriz[pieza.forma[i][0] + posicion[0]][pieza.forma[i][1] + posicion[1]] != 0) {
            hayEspacio = false;
        }
    }

    return hayEspacio;

}

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