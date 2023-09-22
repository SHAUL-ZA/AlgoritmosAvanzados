// Z function
//Sylvia Fernanda Colomo Fuente - A01781983
//Shaul Zayat Askenazi - A01783240
//Juan Pablo Moreno Robles Arenas - A01374091
//Domingo Mora - A01783317
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector <int> zFunction(std::string pattern){
    int patternLength = pattern.length();
    std::vector <int> zVector(patternLength);
    int x = 0;
    int y = 0;
    zVector[0] = 0;
    for (int i = 1; i < patternLength; i++){
        if(i > y){
            x = y = i;
            while(y < patternLength && pattern[y] == pattern[y-x]){
                y++;
            }
            zVector[i] = y - x;
            y--;
        }
        else{
            int k = i - x;
            if(zVector[k] < y - i + 1){
                zVector[i] = zVector[k];
            }
            else{
                x = i;
                while(y < patternLength && pattern[y] == pattern[y-x]){
                    y++;
                }
                zVector[i] = y - x;
                y--;
            }
        }
    }
    return zVector;
}



int main() {
    std::string pattern_test = "ABABD$ABABCABCABABABD";
    //ABCABC$XABCABXABCABCX
    //ABABD$ABABCABCABABABD
    std::vector<int> vector_test = zFunction(pattern_test);

    for (int i = 0; i < pattern_test.length(); i++) {
        std::cout << vector_test[i] << "" ;

    }
   //obtiene el valor del elemento maximo del vector ya que es donde haya el mayor número de coincidencias con el patrón por lo que indica el inicio del patrón
    std::cout << std::endl << "El patron empieza en la posicion: " ;
    std::cout  << std::distance(vector_test.begin(), std::max_element(vector_test.begin(), vector_test.end())) << std::endl;
    return 0;
}