//Nombres y matriculas:

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
std::string longestPalindrome(std::string text)
{
    int text_length = text.length();
    int max_length = 1;
    int start_index = 0;
    int low, high;
    std::string palindrome = "";

    //One by one consider every character as center point of even and odd length palindromes
    for (int i = 1; i < text_length; i++)
    {
        //Find the longest even length palindrome with center points as i-1 and i.
        low = i - 1;
        high = i;
        while (low >= 0 && high < text_length && text[low] == text[high])
        {
            if (high - low + 1 > max_length)
            {
                start_index = low;
                max_length = high - low + 1;
            }
            low--;
            high++;
        }

        //Find the longest odd length palindrome with center point as i
        low = i - 1;
        high = i + 1;
        while (low >= 0 && high < text_length && text[low] == text[high])
        {
            if (high - low + 1 > max_length)
            {
                start_index = low;
                max_length = high - low + 1;
            }
            low--;
            high++;
        }
    }

    //Return the longest palindrome
    for (int i = start_index; i <= start_index + max_length - 1; i++)
    {
        palindrome += text[i];
    }
    return palindrome;
}
//Palindrome -----------------------------------------------------------

//Substring ------------------------------------------------------------

std::string Substr(const std::string& str1, const std::string& str2) {
    std::string longestCoincidence; // Store the longest coincidence

    for (int i = 0; i < str1.length(); i++) {
        for (int j = 0; j < str2.length(); j++) {
            int k = 0;
            // Compare characters from both strings
            while (i + k < str1.length() && j + k < str2.length() &&
                   str1[i + k] == str2[j + k]) {
                k++;
            }
            // If a longer coincidence is found, update longestCoincidence
            if (k > longestCoincidence.length()) {
                longestCoincidence = str1.substr(i, k);
            }
        }
    }
    std::cout << longestCoincidence << std::endl;

    return longestCoincidence;
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
    std::cout << longestPalindrome(T1) << std::endl;
    std::cout<<std::endl;
    std::cout<<"Longest palindrome in Transmission 2: " <<std::endl;
    std::cout << longestPalindrome(T2) << std::endl;
    // ------------------------------------------------------------------

    //Parte 3: ---------------------------------------------------------
    //substring más largo dentro de T1 que este en T2
    std::cout<<std::endl;
    std::cout<<"Longest substring in Transmission 1 that is in Transmission 2: " <<std::endl;
    Substr(T1, T2);
    //---------------------------------------------------------------
    return 0;
}
