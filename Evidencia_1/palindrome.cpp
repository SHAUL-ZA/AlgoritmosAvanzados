/*Shaul Zayat Askenazi - A01783240*/

#include <iostream>
#include <string>
#include <vector>

// Función que agrega delimitadores "$" a la cadena original para manejar palíndromos de longitud par e impar.
std::string ProcesarStr(const std::string& k) {
    std::string modStr = "$"; //Se inicializa con un delimitador 
    for (char c : k) {
        modStr += c;
        modStr += "$";
    }
    return modStr;
}

// Función que encuentra los valores de longitud de palíndromos en la cadena utilizando el algoritmo de Manacher.
std::vector<int> EncontrarLongitudes(const std::string& modStr) {
    int n = modStr.length(); // Longitud de la cadena modificada
    std::vector<int> L(n);
    int C = 0; // Centro del palíndromo actual
    int R = 0; // Borde derecho del palíndromo actual

    for (int i = 0; i < n; i++) { 
        int mirr = 2 * C - i; // Espejo de i alrededor de C con el fin de evitar comparaciones innecesarias

        if (i < R) { //Si i es menor que el borde derecho del palíndromo
            L[i] = std::min(R - i, L[mirr]); //Encuentra el mínimo entre el borde derecho del palíndromo y el espejo de i
        }

        // Extender el palíndromo alrededor del centro
        while (modStr[i + 1 + L[i]] == modStr[i - 1 - L[i]] && i + 1 + L[i] < n && i - 1 - L[i] >= 0) {
            L[i]++;
        } /* Mientras que el caracter de la derecha es igual al de la izquierda y el palíndromo
         no se extienda más allá de los bordes de la cadena */


        // Si el palíndromo actual se extiende más allá del borde derecho del otro, actualiza el centro y el borde derecho
        if (i + L[i] > R) {
            C = i;
            R = i + L[i];
        }
    }

    return L; 
}

// Función que encuentra el palíndromo más largo en la cadena original a partir de los valores de longitud.
std::string PalindromoMayor(const std::string& k) {
    std::string modStr = ProcesarStr(k); //Obtieene la cadena con los delimitadores
    std::vector<int> L = EncontrarLongitudes(modStr); //Obtiene el vector con las longitudes de los palindromos

    // Encontrar la longitud y la posición del palíndromo más largo
    int maxLength = 0;
    int maxPosition = 0;

    for (int i = 0; i < modStr.length(); i++) {
        if (L[i] > maxLength) {
            maxLength = L[i]; 
            maxPosition = i; 
        }
    }

    // Calcular la posición inicial en la cadena original
    int start = (maxPosition - maxLength) / 2; //Se divide entre 2 porque se agregaron delimitadores

    // Extraer el palíndromo más largo de la cadena original
    std::string palindromo = k.substr(start, maxLength); //Desde la posición inicial hasta la longitud del palíndromo

    return palindromo;
}


int main() {
    //Espacio en consola
    std::cout << std::endl; 

    //Cadena de prueba
    std::string input = "ABBCEJFRCRABBBAFRFG";

    //Develve la cadena con los delimitadores
    std::string result = ProcesarStr(input);
    std::cout <<"Cadena: "<< result << std::endl;

    //Devuelve el vector con las longitudes de los palindromos
    std::vector<int> L = EncontrarLongitudes(result);
    std::cout << "Longitudes: ";
    for (int i = 0; i < L.size(); i++) {
        std::cout << L[i] << " ";
    }
    std::cout << std::endl; 

    //Devuelve el palindromo mas largo
    std::string palindromo = PalindromoMayor(input);
    std::cout << "Palindromo mas largo: " << palindromo << std::endl;

    return 0; 
}
