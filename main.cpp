#include <iostream>
#include <fstream>
#include <string.h>
#include "Grafo.h"
using namespace std;

int main(){
    Grafo g;
    g.cargar_archivos();
    int opcion;
    cout << "Indique cual algoritmo desea ejecutar:\n\n1)Coloreo de grafos\n2)FLoyd-Warshall" << endl;
    cout << "-> ";
    cin >> opcion;
    if(opcion == 2){
		g.floyd();
	}
	else{
		g.colorear();
	}
    return 0;
}


