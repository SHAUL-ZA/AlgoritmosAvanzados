/*
Equipo #6
Shaul Zayat Askenazi - A01783240
S. Fernanda Colomo Fuente - A01781983
Juan Pablo Moreno Robles Arenas - A01374091
Domingo Mora - A01783317

---------------------------collisions-------------------------
*/

#include<iostream>
#include<vector>
#include<string>

unsigned long long chain(std::string s){ //Función que calcula el hash de una cadena, es long long para evitar overflow 
    unsigned int n = s.size(), p = 31, m = 1e9 + 9; //n es el tamaño de la cadena, p es el número primo y m es el módulo
    unsigned long long hash = 0, pow = 1; //hash es el hash de la cadena y pow es la potencia de p

    for(int i = 0; i < n; i++){ //Se recorre la cadena
        hash = (hash + (s[i] - 'a' + 1) * pow) % m; //Se suma el valor de la letra multiplicado por la potencia de p
        pow = (pow * p) % m; //Se actualiza la potencia de p
    }
    return hash;
}

int main(){
    //Cadena de prueba
    std::string s = "ababcabcabababd";
    std::cout << "Hash: " << chain(s) << std::endl;
    return 0;
}
