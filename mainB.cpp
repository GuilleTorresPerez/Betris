#include "betris.hpp"

using namespace std;

void datosFinales(const int vEntrada[], const int vSalida[], const int n) {
    cout << "Entrada (numero de piezas): ";
    int index = 0;
    while(vEntrada[index] != -1) {
        cout << vEntrada[index] << " ";
        index++;
    } 
    cout << endl << "Numero de piezas colocadas: " << n << endl << "Salida (numeros de columnas): " << endl;
    for (int i = 0; i < n; i ++) {
        cout << vSalida[i] << " ";
    }
}

int main() {

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