//Nombres y matriculas:
/*Sylvia Fernanda Colomo Fuente -A01781983*/
/*Shaul Zayat Askenazi - A01783240*/
/*Juan Pablo Moreno Robles Arenas - A01374091*/


#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//funcion para leer el archivo
std::string readTxtFile(std::string filename) {
    std::ifstream file(filename);
    std::string content((std::istreambuf_iterator<char>(file)), //esto es un iterador para el archivo
                        (std::istreambuf_iterator<char>())); //esto es el final del iterador sirve para saber cuando parar de leer
    return content;
}

//Funcion para KMP ----------------------------------------------------
std::vector<int> prefixFunction(std::string pattern)
{
    int pattern_length = pattern.length();
    std::vector<int> prefixVector(pattern_length);
    int i = 1; // Avanzando (y)
    int j = 0; // Yendo y viniendo (x)

    prefixVector[0] = 0;

    while (i < pattern_length)
    {

        if (pattern[i] == pattern[j])
        {
            prefixVector[i] = j + 1;
            j++;
            i++;
        }

        else
        {
            if (j == 0)
            {
                prefixVector[i] = 0;
                i++;
            }
            else
            {
                j = prefixVector[j - 1];
                // Aquí no se aumenta i porque se tiene que volver a comparar
            }
        }
    }
    return prefixVector;
}


//Function to find the pattern in the text using the prefix function
std::vector<int> kmp(std::string text, std::string pattern)
{
    int text_length = text.length();
    int pattern_length = pattern.length();
    std::vector<int> prefixVector = prefixFunction(pattern);
    int i = 0; // Avanzando (y)
    int j = 0; // Yendo y viniendo (x)
    prefixVector[0] = 0;
    bool found = false;

    while(i < text_length)
    {
        if(text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            if(j == 0)
            {
                i++;
            }
            else
            {
                j = prefixVector[j-1];
            }
        }
        if(j == pattern_length)
        {
            std::cout << "TRUE | Pattern found at index " << i - j << std::endl;
            j = prefixVector[j-1];
            found = true;
        }


    }
    if (found == false)
    {
        std::cout << "FALSE | Pattern not found" << std::endl;
    }
    
    //RETURN THE VECTOR WITH THE INDEXES
    return prefixVector;
}
//KMP ------------------------------------------------------------------


//Palindrome -----------------------------------------------------------
//Function to find the longest palindrome in a string
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
//Palindrome -----------------------------------------------------------

//Substring ------------------------------------------------------------

std::string Substr(const std::string& str1, const std::string& str2) {
    std::string subcadena; // Subcadena más larga

    int sub1 = str1.length(); // Longitud de la primera cadena
    int sub2 = str2.length(); // Longitud de la segunda cadena

    // Si alguna de las cadenas está vacía, no hay coincidencia
    if (sub1 == 0 || sub2 == 0) {
        return "";
    }
    
    for (int i = 0; i < sub1; i++) {
        for (int j = 0; j < sub2; j++) {
            int long_actual = 0;
            // Compara los caracteres de las cadenas mientras sean iguales
            while (i + long_actual < sub1 && j + long_actual < sub2 &&
                   str1[i + long_actual] == str2[j + long_actual]) {
                long_actual++;
            }
            // Si la coincidencia es más larga que la anterior, se actualiza
            if (long_actual > subcadena.length()) {
                subcadena = str1.substr(i, long_actual);
            }
        }
    }
    std::cout << subcadena << std::endl;

    return subcadena;
}
//main function
int main()
{   //lectura de archivos
    std::string T1 = readTxtFile("transmission1.txt");//lee el primer archivo
    //std::cout << T1 << std::endl;
    std::string T2 = readTxtFile("transmission2.txt");//lee el segundo archivo
    //std::cout << T2 << std::endl;
    std::string M1 = readTxtFile("mcode1.txt");//lee el primer archivo malicioso
    //std::cout << M1 << std::endl;
    std::string M2 = readTxtFile("mcode2.txt");//lee el segundo archivo malicioso
    //std::cout << M2 << std::endl;
    std::string M3 = readTxtFile("mcode3.txt");//lee el tercer archivo malicioso
    //std::cout << M3 << std::endl;

    //PARTE 1: ---------------------------------------------------------
    //encontrar el patrón con KMP 
    std::cout<<"Checking Transmission 1: " <<std::endl;
    kmp(T1, M1);
    kmp(T1, M2);
    kmp(T1, M3);
    std::cout<<std::endl;
    std::cout<<"Checking Transmission 2: " <<std::endl;
    kmp(T2, M1);
    kmp(T2, M2);
    kmp(T2, M3);
    // ------------------------------------------------------------------

    //Parte 2: ---------------------------------------------------------
    //encontrar el palindromo mas largo
    std::cout<<std::endl;
    std::cout<<"Longest palindrome in Transmission 1: " <<std::endl;
    std::cout << PalindromoMayor(T1) << std::endl;
    std::cout<<std::endl;
    std::cout<<"Longest palindrome in Transmission 2: " <<std::endl;
    std::cout << PalindromoMayor(T2) << std::endl;
    // ------------------------------------------------------------------

    //Parte 3: ---------------------------------------------------------
    //substring más largo dentro de T1 que este en T2
    std::cout<<std::endl;
    std::cout<<"Longest substring in Transmission 1 that is in Transmission 2: " <<std::endl;
    Substr(T1, T2);
    //---------------------------------------------------------------
    return 0;
}
