#include "betris.hpp"

using namespace std;

int main() {


    int vEntrada[MAXENTRADA];
    int vSalida[MAXENTRADA];
    int x, y;
    int retardo, objetivo;

    tpTablero tablero;

    tablero.ncols = x;
    tablero.nfils = y;

    escribirParametros(vEntrada, x, y, retardo, objetivo);

    buscaSolucion(tablero, vEntrada, vSalida, objetivo, 0, retardo);

    return 0;
}