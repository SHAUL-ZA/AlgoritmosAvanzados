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
std::vector<std::vector<int> > read_file(std::string file_name, std::vector<std::string>& Mapa) {
    std::ifstream file(file_name);
    std::string line;
    std::vector<std::vector<int> > matrix;

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

int main() {
   std::string file_name = "Matrix2.txt";
    std::vector<std::vector<int> > matrix;
    std::vector<std::string> Mapa;

    matrix = read_file(file_name, Mapa);

    // Print the matrix
    // for (const std::vector<int>& row : matrix) {
    //     for (int value : row) {
    //         std::cout << value << ' ';
    //     }
    //     std::cout << std::endl;
    // }

    // Print the city names
    //std::cout << "City Names:" << std::endl;
    //for (const std::string& city : Mapa) {
    //    std::cout << city << std::endl;
    //}



    std::cout<<"El costo posible es: "<< costo_posible(matrix)<< std::endl;
    std::cout << Viajero(matrix, Mapa) << std::endl;

    return 0;
}
