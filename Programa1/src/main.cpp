#include "Lector.h"
#include "Analizador.h"
using namespace std;

//.i
int main()
{
    Lector lector;
    Analizador analizador;

    analizador.contarLineas(lector);
    analizador.imprimir();
    
    return 0;
}