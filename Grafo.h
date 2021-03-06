#ifndef GRAFO
#define GRAFO
#include <string.h> //Para el strcmp y strlen
#include <fstream>
#include <iostream>
using namespace std;

/** @brief Maxima cantidad de chars que para el ID y nombre de cada nodo */
#define max 15 

/** @brief */

class Grafo{
    private:
        
    
    public:
        /** @brief El número de vértices que tiene el grafo */
        int cantVertices;
        
        /** @brief Matriz de caminos para el algoritmo de Floyd */
        char*** matrizCaminos;
        
        /** @brief Es la matriz de adyacencia, contiene el peso de cada arista */
        int** matriz;
        
        /** @brief Arreglo que contiene los char* (strings) que identifican a cada nodo (los ID's)*/
        char** ids; 
        
        /** @brief  Arreglo con los nombres (etiquetas de cada nodo) */
        char** nombres;
        
        /** @brief Constructor de la clase Grafo */
        Grafo();
        
        /** @brief Destructor de la clase Grafo
            @details Libera la memoria ocupada por sus atributos: arreglos y matriz de adyacencia 
        */
        ~Grafo();
        
        /** @brief Funciona para conocer la posicion correspondiente al nodo con el identificador señalado
         *  @param id El identificador de un nodo
         *  @return Retorna un entero con la posición del nodo con el id recibido o -1 si no se encontró dicho nodo
        */
        int pos_de_id(char* id);
        
        /** @brief Se encarga de cargar y establecer todos los datos que se leen de los archivos 
         *  @details Llena la matriz de adyacencia con los pesos de las aristas, guarda los ID's 
             y nombres de los nodos
        */
        void cargar_archivos();
        
        /** @brief Convierte un string en su valor en entero 
            @param str Un string que contiene sólo dígito válidos
            @return Retorna el valor entero del string
        */
        int str_to_int(char* str);
        
        /** @brief Imprime la matriz de adyacencia*/
        void print_matriz();
        
        /** @brief Imprime la lista de los ID's de los vértices en el grafo y su nombre asociado*/
        void printVertices();
        
        /** @brief Inicializa los atributos del grafo (matriz, ids, nombres) según la cantidad(válida) de vértices ingresada*/
        void inicializarAtributos(int cantVertices);
        
        /** @brief Colorea el grafo e imprime la matriz de adyacencia */
        void colorear();
        

        /** @brief Saca los mejores caminos para todo par de vertices e imprime los caminos */
        void floyd();
        

        /** @brief Sirve para averiguar si el nodo en **posNodo** tiene algún otro nodo adyacente con el color **color** 
         *  @param posNodo Es la posición en el arreglo del nodo al cual se le van buscar los adyacentes
         *  @param color   Es el número que representa el color contra el cual se va a comparar
         *  @param colores Es el puntero correspondiente al arreglo de los colores de cada nodo. Es decir colores[i] debe ser
         *                 el color que tiene el nodo con **id** = ids[i]
         *  @return retorna true si el nodo tiene almenos un vecino con el color **color**  o false si ningún vecino 
         *          es de ese color
        */
        bool vecinoTieneColor(int posNodo, int color, int* colores);
        
        /** @brief Imprime la matriz de caminos mínimos entre todo par de nodos */
        void printMatrizCaminos();
        
        /** @brief Se encarga de llenar la matriz de caminos y dejarla lista para empezar floyd */
        void inicializarMatrizCaminos();
        
        void mostrarRutas();
        
};
#endif
