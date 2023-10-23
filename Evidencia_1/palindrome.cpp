#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string editarString(const std::string& inputString) {
    std::string modifiedString = "$"; 

    for (size_t i = 0; i < inputString.length(); i++) {
        modifiedString += inputString[i];
        if (i < inputString.length() - 1) {
            modifiedString += '$';
        }
    }

    modifiedString += '$'; 

    return modifiedString;
}


std::vector<int> findPalindrome(const std::string& k) {
    std::vector<int> L(k.length());
    L[0] = 0;
    L[1] = 1;
    int j = 0;

    for (int i = 2; i < k.length(); i++) {
        while (i + 1 + j < k.length() && k[i + 1 + j] == k[i - 1 - j]) {
            j++;
        }
        L[i] = j;
        j = 0;
    }

    return L;
}

std::string Palindrome(const std::string& k, const std::vector<int>& L) {
  
  //funcion que obtiene en string el palindromo más largo usando L
    
     int maxLength = 0;
    int maxPosition = 0;

    for (int i = 0; i < L.size(); i++) {
        if (L[i] > maxLength) {
            maxLength = L[i];
            maxPosition = i;
        }
    }
    if (maxLength>=maxPosition)
    {
        // Calculate the start and end positions of the longest palindrome in the original string
        int start = (maxPosition - maxLength) / 2;
        int end = start + maxLength;
         // Extract the longest palindromic substring from the original string 
        return k.substr(start, maxLength);
    }
    else{
        std::string p="";
        int i=0;
        int j=maxPosition-1;
        while (i<maxLength)//derecha
        {
            p+=k[j];
            i++;
            j--;
        }
         i=0;
         j=maxPosition;
        while(i<maxPosition){//izquierda
            p+=k[j+1];
            i++;
            j--;
        }
        //remove the $ from the string
        p.erase(std::remove(p.begin(), p.end(), '$'), p.end());
        return p;
    }


}




int main() {
    //std::string input = "CACBCAC";
    std::string input = "ABBA";
    //std::string input ="XCBCC";
    //std::string input="XABCABXBBC";
    std::string result = editarString(input);
    std::cout << result << std::endl; 
    //print the result for findPalindrome
    std::vector<int> result2 = findPalindrome(result);
    for (int i = 0; i < result2.size(); i++) {
        std::cout << result2[i] << " ";
    }
    std::cout << std::endl;
    //print the result for editarString
    std::string result3 = Palindrome(result, result2);
    std::cout << result3 << std::endl;

    return 0;
}


