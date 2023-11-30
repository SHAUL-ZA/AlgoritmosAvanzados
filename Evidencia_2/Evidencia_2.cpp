/*Sylvia Fernanda Colomo Fuente | A01781983*/
/*Shaul Zayat Askenazi | A01783240*/
/*Juan Pablo Moreno | A01374091*/
/*Domingo Mora */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <algorithm>




// Lee el archivo de texto y lo convierte en una matriz de adyacencia
    std::vector<std::vector<int> > read_file(std::string file_name, std::vector<std::string>& Mapa ,int &n) {
    std::ifstream file(file_name);
    std::string line;
    std::vector<std::vector<int> > matrix;

     // Read the first line to get the number of nodes
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> n;
    }

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;  // Skip empty lines
        }

        if (isdigit(line[0]) || line[0] == '-') {
            // This is a line containing matrix data
            std::vector<int> row;
            std::istringstream iss(line); 
            int value;

            while (iss >> value) {
                row.push_back(value);
            }

            matrix.push_back(row);
        } else {
            // This is a line containing city name
            Mapa.push_back(line);
        }
    }

    return matrix;
}
//PARTE 1 KRUSKAL --------------------------------------------------
bool Edges_Bool(const std::vector<int>& a, const std::vector<int>& b) {
    return a[2] < b[2];
}//Edges_Bool
//Compara el peso de las esquinas, regresa true si el peso de a es menor que el de b
//Estas referencias (&) evitan que se realicen copias completas de 
//los vectores a comparar, lo que ahorra memoria y 
//mejora el rendimiento al pasar argumentos a la función.

std::vector<std::vector<int> > esquinas(const std::vector<std::vector<int> >& matrix) {
    std::vector<std::vector<int> > edges; //vector con las esquinas 
    int n = matrix.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (matrix[i][j] != 0) {
                std::vector<int> edge;
                edge.push_back(i);
                edge.push_back(j);
                edge.push_back(matrix[i][j]);
                edges.push_back(edge);

            }
        }
    }

    return edges;
}
int find(int x, std::vector<int>& representante) {
    if (x != representante[x])
        representante[x] = find(representante[x], representante);
    return representante[x];
}//find
//Find se basa en el DSU para poder encontrar si dos nodos están conectados es decir si cuentan con el mismo representante



void unite(int x, int y, std::vector<int>& representante) {
    x = find(x, representante);
    y = find(y, representante);
    if (x == y) return;

    representante[y] = x;
}//unite 
//Unite usa a find para encontrar si dos nodos están conectados
//Kruskal's algorithm
std::vector<std::vector<int> > KA(std::vector<std::vector<int> >& edges, int n) {//se crea la función de kruskal
    std::vector<std::vector<int> > MST;//se crea el vector para el minimun spanning tree
    std::vector<int> representante(n);//se crea el vector representante con tamaño n, siendo n el número de nodos

    for (int i = 0; i < n; ++i)
        representante[i] = i;
    //Se crea y se llena el vector representante con los valores de cada nodo
    std::sort(edges.begin(), edges.end(), Edges_Bool);
    //se hace un sort para ordenar edges de acuerdo a su peso.
    for (std::vector<int>& edge : edges) {
        int u = edge[0], v = edge[1];
        if (find(u, representante) != find(v, representante)) {
            unite(u, v, representante);
            MST.push_back(edge);
        }
    }
    return MST;
}





//PARTE 2 VIAJERO --------------------------------------------------
//Costo posible
int costo_posible(std::vector<std::vector<int> > matrix) {
    int costo = 0;

    // se recorre la matrix para buscar los valores menores de cada fila 
    for (int i = 0; i < matrix.size(); i++) {
        int min = INT_MAX;  //se usa INT_MAX para que el valor minimo sea el maximo posible
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] > 0 && matrix[i][j] < min) {
                min = matrix[i][j];
            }
        }
        costo += min;  // Accumulate the minimum positive value (defaulting to 1)
    }

    return costo;
}


//Viajero

int Viajero(std::vector<std::vector<int> > matrix, std::vector<std::string> Mapa) {
    int pueblo = matrix.size();  // numero de pueblos 

    // Se hace una matrix de bool para contablizar si un pueblo fue visitado, se inicializan con false
    std::vector<bool> visited(pueblo, false);

    //Se decidió que nuestra posición inicial será el pueblo 0
    int source = 0;
    int pos_actual = source;//por lo que pos_actual es 0
    visited[source] = true;//ahora el pueblo acutal ya fue visitado
    int totalCost = 0;//el costo inicial es 0 porque nos encontramos ahí
    int visitados = 1;//el numero de pueblos visitados es 1 porque ya visitamos el pueblo 0

    std::vector<int> camino;//vector que guarda el camino que se tomará (sirve para imprimirlo al final)
    camino.push_back(source);//se añade el pueblo inicial al camino 

//mientras que no se hayan visitado todos los pueblos, ciclo para armar el camino
    while (visitados < pueblo) {
        int pueblo_sig = -1;//se inicializa el pueblo siguiente en -1 ejemplificando que no hay pueblo siguiente
        int costo_min = INT_MAX;//se inicializa el costo minimo en INT_MAX para que el costo minimo sea el maximo posible

        // Se busca el pueblo siguiente con el costo minimo
        for (int i = 0; i < pueblo; i++) {
            //si el pueblo no ha sido visitado y el costo es menor al costo minimo entonces se actualiza el costo minimo y el pueblo siguiente
            if (!visited[i] && matrix[pos_actual][i] < costo_min) {
                costo_min = matrix[pos_actual][i];//toma el costo para llegar a ese pueblo
                pueblo_sig = i;//quiere decir que aun falta por visitar ese pueblo
            }
        }

        if (pueblo_sig != -1) { //como es difernte a -1, es un pueblo visitado nuevo para agregar al camino
            camino.push_back(pueblo_sig);//se agrega al camino
            totalCost += costo_min; //se suma el costo minimo al costo total
            visited[pueblo_sig] = true;//se cambia para no volver a visitar a ese pueblo en las demás iteraciones
            pos_actual = pueblo_sig;//ahora nos encontramos en el pueblo siguiente
            visitados++;//se aumenta el numero de pueblos visitados
        }
    }


    //ya que se acabó de hacer el camino se vuelve a agregar al vector el pueblo inicial para cerrar el ciclo
    camino.push_back(source);
    totalCost += matrix[pos_actual][source]; //costo del último pueblo visitado al source 

    //Imprimir el camino:
    for (int i = 0; i < camino.size(); i++) {
        int k = camino[i];//se guarda el pueblo en la posicion i del camino
        std::cout << Mapa[k];
        if (i != camino.size() - 1) {
            std::cout << "-";
        }
    }
    std::cout << std::endl;
    // Imprime el costo final
    std::cout << "Costo final: ";
    return totalCost;
}
//PARTE 3 EUCLIDEANAS --------------------------------------------------



int main() {

    //Leer el archivo 
    std::string file_name = "Matrix2.txt";
    std::vector<std::vector<int> > matrix;
    std::vector<std::string> Mapa;
    int n;
    matrix = read_file(file_name, Mapa,n);

     //Print the matrix
    std::cout << "Matrix:" << std::endl;
     for (const std::vector<int>& row : matrix) {
         for (int value : row) {
             std::cout << value << ' ';
         }
         std::cout << std::endl;
     }
     //Print number of nodes
        std::cout << "Number of nodes: " << n << std::endl;

    // Print the city names
    //std::cout << "City Names:" << std::endl;
    //for (const std::string& city : Mapa) {
    //    std::cout << city << std::endl;
    //}


    //LLAMA A KRUSKAL -------------------------------------------
    std::vector<std::vector<int> > edges = esquinas(matrix);
     int w=0;
    //printf("Edges:\n");
    //for (const std::vector<int>& edge : edges) {
        //printf("%d - %d : %d\n", edge[0], edge[1], edge[2]);
    //}
    std::cout<<"Caminos a tomar Kruskal: "<<std::endl;
    std::vector<std::vector<int> > MST = KA(edges, n);//se crea el vector MST y se le asigna el valor de la función KA
    for (std::vector<int>& edge : MST) {
        std::cout << Mapa[edge[0] ]<< " - " << Mapa[edge[1]] << " : " << edge[2] << std::endl;
        w+=edge[2];
    }
    std::cout<<"El peso total del MST es: "<<w<<std::endl;
    //LLAMA AL VIAJERO -------------------------------------------
    std::cout<<"El costo posible es: "<< costo_posible(matrix)<< std::endl;
    std::cout << Viajero(matrix, Mapa) << std::endl;

    // LLAMA A LAS ECULIDEANAS -------------------------------------

    return 0;
}
