#pragma once
#include <cstdlib>
#include <string>
using namespace std;
class Util{
public:
    static int generateRandomNumber(int min, int max){
        if(min == max) { return min; }
        int randomNumber = rand() % (max - min) + min;
        return randomNumber;
    }

    static string generateId(string base = "id_"){
        int randomNumber = generateRandomNumber(0, 99999999999999);
        string id = base + to_string(randomNumber);
        return id;
    }
};