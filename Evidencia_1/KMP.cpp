/*
Equipo #6
Shaul Zayat Askenazi - A01783240
S. Fernanda Colomo Fuente - A01781983
Juan Pablo Moreno Robles Arenas - A01374091
Domingo Mora - A01783317

--------------------------KMP--------------------------
*/


#include <iostream>
#include <string>
#include <vector>

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
            std::cout << "Pattern found at index " << i - j << std::endl;
            j = prefixVector[j-1];
        }


    }
    //RETURN THE VECTOR WITH THE INDEXES
    return prefixVector;
}

int main()
{
    std::string text = "XABCABXABCABCX";
    std::string pattern = "ABCABC";

    kmp(text, pattern);

    for(int i = 0; i < prefixFunction(pattern).size(); i++)
    {
        std::cout << prefixFunction(pattern)[i] << " ";
    }
    return 0;
};