#include <iostream>
#include <vector>
#include <climits> //sirve para INT_MAX 
using namespace std;

int V;//numero de vertices

//sirve para encontrar el vertice con la distancia minima
int Vertice_Min(const vector<int>& dist, const vector<bool>& visitado) {
    int v_min = 0; //vertice con la distancia más pequeña
    int min = INT_MAX;// sirve para comparar las distancias
    //INT_MAX es el valor maximo que puede tener un entero lo usamos para comparar las distancias y asi encontrar la minima
    for (int i = 0; i < V; i++) {
        if (!visitado[i] && dist[i] < min) { //si el vertice no ha sido visitado y la distancia es menor a la minima
            min = dist[i];//esa distancia se vuelve la minima
            v_min = i;//el vertice con la distancia minima es el vertice i
        }
    }
    //el for sirve para recorrer el vector de distancias y encontrar la distancia minima
    return v_min;
}

//sirve para imprimir los resultados en pantalla
void resutlados(const vector<int>& dist, const vector<int>& par) {
    for (int i = 0; i < V; i++) {
        int temp = par[i];//temp es igual al padre del vertice i
        cout << i << " <- ";
        while (temp != -1) { //mientras que temp sea diferente de -1 significa que no ha llegado al vertice inicial
            cout << temp << " <- ";
            temp = par[temp];
        }
        //despues de imprimir el camino se imprime la distancia
        cout << endl;
        cout << "Distancia = " << dist[i] << endl;
        cout << endl;
    }
}

void dijkstra(int src, const vector<vector<int> >& cost) {
    vector<int> par(V, -1); //vector de padres, padre siendo el vertice anterior
    vector<int> dist(V, INT_MAX);//vector de distancias, distancia siendo la distancia del vertice inicial al vertice i
    vector<bool> visitado(V, false);//vector de visitados, visitado siendo si el vertice i ya fue visitado o no

    dist[src] = 0;//la distancia del vertice inicial al vertice inicial es 0 siempre 
    //esta linea nos permite tener un vertice inicial diferente de 0 por default

    for (int i = 0; i < V - 1; i++) {
        int V_distMin = Vertice_Min(dist, visitado);//V_distMin es el vertice con la distancia minima
        visitado[V_distMin] = true;//ya que se visito se cambia a true para no volver a visitarlo
        for (int v = 0; v < V; v++) {//se recorre el vector de vertices
            if (!visitado[v] && (dist[V_distMin] + cost[V_distMin][v]) < dist[v] && cost[V_distMin][v] != 9999) {
                //si no ha sido visitado, la distancia del vertice inicial + la distancia del vertice inicial al vertice v es menor a la distancia del vertice inicial al vertice v y que no sea 9999
                //por lo tanto el el pardre del vertice v es el que tiene la distancia minima
                //y la distancia del vertice inicial al vertice v es la distancia del vertice inicial al vertice con la distancia minima + la distancia del vertice con la distancia minima al vertice v
                par[v] = V_distMin;
                dist[v] = dist[V_distMin] + cost[V_distMin][v];
            }
        }
    }

    resutlados(dist, par);//se imprime el resultado
}

int main() {
    cout << "Vertices: ";
    cin >> V;

    vector<vector<int> > cost(V, vector<int>(V)); //matriz de costos

    cout << "Matriz de costos:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) cin >> cost[i][j];
    }
    //llenarla

    int source;
    cout << "\nVertice inicial: ";
    cin >> source;
    cout << endl;

    dijkstra(source, cost);
}
