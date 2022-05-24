#include "betris.hpp"

using namespace std;

// Pre: vEntrada, vSalida y n tienen informacion sobre las piezas colocadas y las respectivas columnas donde se han colocado
// Post: Escribe en pantalla los datos sobre la solucion al problema de colocacion de piezas planteado
void datosFinales(const int vEntrada[], const int vSalida[], const int n) {
    cout << "Entrada (numero de piezas): ";
    int index = 0;
    while(vEntrada[index] != -1) {
        cout << vEntrada[index] << " ";
        index++;
    } 
    cout << endl << "Numero de piezas colocadas: " << n << endl << "Salida (numeros de columnas): ";
    for (int i = 0; i < n; i ++) {
        cout << vSalida[i] << " ";
    }
}


// El argumento argc (argument counter) de la funcion main toma como valor el numero
// de cadenas (o secuencias de caracteres) dados por la linea de ordenes y separadas por
// espacios (por defecto), incluyendo tambien la cadena relativa al nombre del programa.

// El segundo argumento, argv (argument vector), es una referencia a un vector de cadenas de caracteres. 
// En cada posicion de este vector se almacena cada una de las cadenas
// dadas por la linea de ordenes.
int main(int argc, char* argv[]) {

    borrarPantalla();

    int vSalida[MAXENTRADA];
    int vEntrada[MAXENTRADA];
    tpTablero tablero;
    int retardo, objetivo;
    
    escribirParametros(vEntrada, tablero.ncols, tablero.nfils, retardo, objetivo, argc, argv);

    inicializarTablero(tablero);

    // Algoritmo de backtracking para encontrar la solucion al problema
    int n = buscaSolucion(tablero, vEntrada, vSalida, objetivo, 0, retardo);

    if (n == -1) {  // Mostrar el tablero vacio si no encuentra solucion
        inicializarTablero(tablero);
        mostrarTablero(tablero, vEntrada);
    }

    datosFinales(vEntrada, vSalida, n);

    return 0;
}