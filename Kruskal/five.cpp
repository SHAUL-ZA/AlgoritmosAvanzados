#include <iostream> //uso de cout y cin
#include <vector> //uso de vectores
#include <algorithm> //uso de sort
//sort sirve para ordenar los vectores
#include <fstream> //uso de archivos

bool Edges_Bool(const std::vector<int>& a, const std::vector<int>& b) {
    return a[2] < b[2];
}//Edges_Bool
//Compara el peso de las esquinas, regresa true si el peso de a es menor que el de b
//Estas referencias (&) evitan que se realicen copias completas de 
//los vectores a comparar, lo que ahorra memoria y 
//mejora el rendimiento al pasar argumentos a la función.

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
    //se usa find para ver si los nodos están conectados
    //si no están conectados se usa unite para conectarlos
    //se agrega el edge al MST
    //asi evitamos conectar nodos los cuales ya tenian un camino
    return MST;
}//KA

int main() {
    std::ifstream inputFile("data.txt");//se abre el archivo
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    int n, m;//se crean las variables n y m
    inputFile >> n >> m;//se leen los valores de n y m del archivo

    std::vector<std::vector<int> > edges(m, std::vector<int>(3));//se crea el vector edges con tamaño m, siendo m el número de aristas/edges
    for (int i = 0; i < m; ++i) {
        inputFile >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }
    //se llena el vector edges con los valores de cada edge
     std::vector<std::vector<int> > MST = KA(edges, n);//se crea el vector MST y se le asigna el valor de la función KA
    for (std::vector<int>& edge : MST) {
        std::cout << edge[0] << " - " << edge[1] << " : " << edge[2] << std::endl;
        w+=edge[2];
    }
    std::cout<<"El peso total del MST es: "<<w<<std::endl;
    //se imprime el MST
    inputFile.close();

    return 0;
}//main
