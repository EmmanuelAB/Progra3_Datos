#include <iostream>
#include <fstream>
#include <string.h>
#include "Grafo.h"
using namespace std;

int main(){
    Grafo g;
    g.cargar_archivos();
    g.floyd();
    return 0;
}


