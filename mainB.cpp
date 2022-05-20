#include "betris.hpp"

using namespace std;

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


//el argumento argc (argument counter) de la funci´on main toma como valor el n´umero
//de cadenas (o secuencias de caracteres) dados por la l´ınea de ´ordenes y separadas por
//espacios (por defecto), incluyendo tambi´en la cadena relativa al nombre del programa

//El segundo argumento, argv (argument vector), es una referencia a un vector de cadenas de caracteres. 
//En cada posici´on de este vector se almacena cada una de las cadenas
//dadas por la l´ınea de ´ordenes
int main(/*int argc, char* argv[]*/) {

    borrarPantalla();

    /*
    int vSalida[MAXENTRADA];
    int vEntrada[MAXENTRADA];
    tpTablero tablero;

    tablero.nfils = int(argv[0]);
    tablero.ncols = int(argv[1]);
    int objetivo = int(argv[2]);
    int retardo = int(argv[3]);
    for (int i = 4; i < argc; i++) {
        vEntrada[i - 4] = int(argv[i]);
    }*/


    int vEntrada[MAXENTRADA] = {0, 0, 4, 2, 3, 2, 1, -1};
    int vSalida[MAXENTRADA];
    int x = 5, y = 6;
    int retardo = 0, objetivo = 4;

    tpTablero tablero;

    tablero.ncols = x;
    tablero.nfils = y;

    inicializarTablero(tablero);

    //escribirParametros(vEntrada, x, y, retardo, objetivo);        // Por ahora los parametros están fijos para testear mas rapido

    int n = buscaSolucion(tablero, vEntrada, vSalida, objetivo, 0, retardo);

    datosFinales(vEntrada, vSalida, n);

    return 0;
}