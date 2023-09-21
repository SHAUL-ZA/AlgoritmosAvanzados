// Z function

#include <iostream>
#include <string>
#include <vector>

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
    std::string pattern_test = "ABCABC$XABCABXABCABCX";
    std::vector<int> vector_test = zFunction(pattern_test);

    for (int i = 0; i < pattern_test.length(); i++) {
        std::cout << vector_test[i] << "" ;
    }

    return 0;
}