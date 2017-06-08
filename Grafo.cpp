#include "Grafo.h"

Grafo::Grafo(){
    
    
}

Grafo::~Grafo(){
    for (int i = 0; i < cantVertices; i++){
        delete ids[i];
        delete matriz[i];
        delete nombres[i];
    }
    
    delete[] ids;
    delete[] nombres;
    delete[] matriz;
}

int Grafo::pos_de_id(char* id){
    for (int i = 0; i < cantVertices; i++){
        if(!strcmp(ids[i],id)){
            return i;
        }
    }
    return -1;
}

void Grafo::cargar_archivos(){

    ifstream aristas("aristas.csv");   //Se crean las instancias de los dos archivos a leer 
    ifstream verticesLectura("vertices.csv"); 
    ifstream verticesConteo("vertices.csv");
    
    char* str;//Para las lecturas temporales de los archivos 
    
    //Contar la cantidad de vértices
    int n = 0;
    while(1){
        str = new char[max];
        verticesConteo.getline(str,max,'\n');
        if(!strcmp(str,"")){
            cout << n ;
            inicializarAtributos(n);
            break;
        }
        n++;
    }
    
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
        cout << str << endl;
        fila = pos_de_id(str);
        
        //leer segundo id y sacar su posición
        aristas.getline(str, max, ',');
        cout << str << endl;
        columna = pos_de_id(str);
        
        //leer el peso de la arista (leo hasta fin de línea porque es el ultimo dato)
        aristas.getline(str, max, '\n');
        cout << str << endl;
        matriz[fila][columna] = str_to_int(str); //guardo la arista convertida a entero en la matriz de aristas
        
    }
    print_matriz();
    
    
    //for (int i = 0; i < cantVertices; i++){
        //cout << "id: "<<ids[i]<<" -> ";        //para verificar que todos los datos fueron leídos correctamente
        //cout << "nombre: "<<nombres[i]<<endl;
    //}
}

int Grafo::str_to_int(char* str){
    int mult = 1; //multiplicador
    int res = 0; //el resultado de salida 
    int len = strlen(str);
    for (int i = len-1; 0 <= i; i--){
        res += (str[i]-'0')*mult;
        mult*=10; //aumento el multiplicador
    }
    return res;
}

void Grafo::print_matriz(){
    for (int f = 0; f < cantVertices; f++){
        for (int c = 0; c < cantVertices; c++){
            cout << matriz[f][c] << " ";
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
    ids = new char*[cantVertices];
    nombres = new char*[cantVertices];
    matriz = new int*[cantVertices];
    for (int i = 0; i < cantVertices; i++){
        matriz[i] = new int[cantVertices];
    }
}
