#include "Grafo.h"

Grafo::Grafo(){
    
    
}

Grafo::~Grafo(){
    for (int i = 0; i < cantVertices; i++){
        delete ids[i];
        delete matriz[i];
        delete nombres[i];
        delete matrizCaminos[i];
    }
    
    delete[] ids;
    delete[] nombres;
    delete[] matriz;
}

int Grafo::pos_de_id(char* id){
    for (int i = 0; i < cantVertices; i++){
        if(!strcmp(ids[i],id)){ //Si son iguales retorna 0 al negarlo es 1, es decir, "if(son iguales)"
            return i;
        }
    }
    return -1;
}

void Grafo::cargar_archivos(){

    ifstream aristas("aristas.csv");   //Se crean las instancias de los dos archivos a leer 
    ifstream verticesLectura("vertices.csv"); //Una instancia para contar la cantidad de vértices
    ifstream verticesConteo("vertices.csv"); //y la otra para leerlos
    
    char* str;//Para las lecturas temporales de los archivos 
    
    //Contar la cantidad de vértices
    int n = 0;
    str = new char[max];
    while(1){
        verticesConteo.getline(str,max,'\n');
        if(!strcmp(str,"")){ //si ya no se leyó nada (fin de archivo)
            inicializarAtributos(n);
            break;
        }
        n++;
    }
    delete str; // Sólo se usó para contar
    //Leer ID's y nombre de los nodos del archivo de vertices
    int i=0;
    while(1){
        //Leer el id del vertice hasta coma
        str = new char[max];
        verticesLectura.getline(str, max, ','); //para el primer dato (id) leo hasta la coma
        if(!strcmp(str,""))//Ya leyó hasta fin de archivo
            break;
        ids[i] = str;
        
        //Leer el nombre del vértice hasta fin de línea
        str = new char[max];
        verticesLectura.getline(str, max, '\n'); //para el segundo (nombre) hasta el cambio de línea
        nombres[i++] = str;
    }
    
    //Leer los pesos de las aristas entre los nodos del archivo de aristas
    int fila, columna;
    while(1){
        //str = new char[15];
        //leer el primer id y sacar su posición
        aristas.getline(str, max, ',');
        if(!strcmp(str,""))//Ya leyó hasta fin de archivo
            break;
        fila = pos_de_id(str);
        
        //leer segundo id y sacar su posición
        aristas.getline(str, max, ',');
        columna = pos_de_id(str);
        
        //leer el peso de la arista (leo hasta fin de línea porque es el ultimo dato)
        aristas.getline(str, max, '\n');
        //El grafo no es dirigido -> toda arista es bidireccional
        matriz[fila][columna] = str_to_int(str); //guardo la arista convertida a entero en la matriz de aristas
        //matriz[columna][fila] = str_to_int(str); //guardo la arista convertida a entero en la matriz de aristas        
    }
    //print_matriz();

}

int Grafo::str_to_int(char* str){
    int mult = 1; //multiplicador
    int res = 0; //el resultado de salida 
    int len = strlen(str);
    for (int i = len-1; 0 <= i; i--){
        res += (str[i]-'0')*mult; //paso el char a entero, lo multiplico por mul y lo sumo al acumulado
        mult*=10; //aumento el multiplicador
    }
    return res;
}

void Grafo::print_matriz(){
    printf("-- |");
    for (int i = 0; i < cantVertices; i++){
        printf("%.2d|", i);
    }
    cout << endl;
    for (int f = 0; f < cantVertices; f++){
        printf("%.2d |",f);
        for (int c = 0; c < cantVertices; c++){
            printf("%.2d ",matriz[f][c]);
        }
        cout << endl;
    }
    printVertices();
}

void Grafo::printVertices(){
    cout << "--Pos-- --ID--   --Nombre--"<<endl;
    for (int i = 0; i < cantVertices; i++){
        cout <<"  "<<i << "       "<< ids[i] << "      "<<nombres[i]<<endl;
    }
}

void Grafo::inicializarAtributos(int cantVertices){
    this->cantVertices=cantVertices;
    ids = new char*[cantVertices];
    nombres = new char*[cantVertices];
    
    matrizCaminos = new char**[cantVertices];
    for(int i = 0; i < cantVertices; i++){
		matrizCaminos[i]= new char*[cantVertices];
	}
	
    matriz = new int*[cantVertices];
    for (int i = 0; i < cantVertices; i++){
        matriz[i] = new int[cantVertices];
    }
}

bool Grafo::vecinoTieneColor(int posNodo, int color, int* colores){
    if(posNodo<0 || cantVertices <= posNodo){
        cout << "Se ingresó una posición de nodo inválida" << endl;
        return -1;
    }
    for (int i = 0; i < cantVertices; i++){   
        if(matriz[posNodo][i]){ //Hay adyacencia
            if(colores[i]==color)//i es las pos del nodo con el que hay adyacencia
                return true;
        }
              
    }   
    return false;
}

void Grafo::colorear(){
    int matriz[cantVertices][cantVertices] = {0};
    int colores[cantVertices] = {0}; //contiene el color de cada vértice, es decir colores[i] es el color del nodo en ids[i]
    int colorActual = 1;
    for (int nodo = 0; nodo < cantVertices; nodo++){
        bool colorUsado=false;
        for (int c = 1; c <= colorActual; c++){ //itero con los colores ya usado a ver si alguno sirve
            if(!vecinoTieneColor(nodo,c,colores)){
                colores[nodo]=c; //Hay que usar color nuevo
                colorUsado=true;
                break;
            }
        }
        if(!colorUsado)//No se pudo reutilizar color
            colores[nodo]=++colorActual; //Hay que usar color nuevo
        
    }
    //imprimir los colores que le quedaron a cada vértice
    cout << "\nLista de colores" << endl;
    cout << "-----------------" << endl; 
    for (int i = 0; i < cantVertices-1; i++){
        cout << "Vértice " << nombres[i] << " con id " << ids[i] << " tiene color "<< colores[i] << endl;
    }
    cout << "Vértice " << nombres[cantVertices-1] << " con id " << ids[cantVertices-1] << " tiene color "<< colores[cantVertices-1] << endl;
	
	
}

void Grafo::floyd(){
	
	inicializarMatrizCaminos();
	
	int i, j, k;
	
    for(k = 0; k < cantVertices; k++){
        for (i = 0; i < cantVertices; i++){
            for (j = 0; j < cantVertices; j++){
                if((matriz[i][k] * matriz[k][j] != 0) && (i != j)){ //valida que no haya elemento absorvente y que no se está
                                                                    //en la diagonal
                    if((matriz[i][k] + matriz[k][j] < matriz[i][j]) || (matriz[i][j] == 0)){//valida si se pueda mejorar la 
                                                                                            //casilla                        
                        matriz[i][j] = matriz[i][k] + matriz[k][j];
                        matrizCaminos[i][j] = ids[k];
                    }
                }
            }
        }
    }
    //Imprime el resultado de la matriz de costos 
    cout << "Resultado: Costos" << endl;
    for (i = 0; i < cantVertices; i++){
        cout << "\nCostos desde vértice:" << ids[i] << "\n";
        cout << "---------------------" << endl;
        for (j = 0; j < cantVertices; j++){
			cout << "Vértice:" << ids[j] << " costo:";
            cout << matriz[i][j] << "    ";
        }
        cout << endl;
    }
    
    mostrarRutas();
}

void Grafo::inicializarMatrizCaminos(){ //inicializa las columnas iguales 
	for (int i = 0; i < cantVertices; i++){
		for(int j = 0; j < cantVertices; j++){
			matrizCaminos[i][j] = ids[j];
		}
	}
}

void Grafo::printMatrizCaminos(){
	cout << "\n\nMatriz Caminos" << endl;
	cout << "---------------\n" << endl;
	cout << "  ";
	for(int x = 0; x < cantVertices; x++){
		cout << ids[x] << " ";
	}
	for(int i = 0; i < cantVertices; i++){
		cout << endl;
		cout << ids[i] << "|";
		for(int j = 0; j < cantVertices; j++){
			cout << matrizCaminos[i][j] << " ";
		}
	}
	cout << "\n\n";
}	

void Grafo::mostrarRutas(){
	
	printMatrizCaminos();
	cout << endl;
	
	cout << "Rutas con los mejores caminos" << endl;
	
	for(int i = 0; i < cantVertices; i++){
		cout << "-----------------------------" << endl;
		for (int j = 0; j < cantVertices; j++){
			cout << "Arista " << ids[i] << " hacia " << "Arista " << ids[j] << " pasa por ";
			int tmp = i;
			while(matrizCaminos[i][j] != ids[j]){
				cout << matrizCaminos[i][j];
				cout << "-";
				i = pos_de_id(matrizCaminos[i][j]);
			}
			cout << matrizCaminos[i][j] << endl;
			i = tmp;
		}
	}
}


