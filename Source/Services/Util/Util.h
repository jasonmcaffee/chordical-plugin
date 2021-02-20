#pragma once
#include <JuceHeader.h>
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

    static juce::String convertDynamicObjectToJsonString(DynamicObject* json){
        juce::var jsonVar(json);
        juce::String jsonString = juce::JSON::toString(jsonVar, true);
        return jsonString;
    }

    static String urlDecode(std::basic_string<char, std::char_traits<char>, std::allocator<char>> SRC) {
        std::string ret;
        char ch;
        int i, ii;
        for (i=0; i<SRC.length(); i++) {
            if (int(SRC[i])==37) {
                sscanf(SRC.substr(i+1,2).c_str(), "%x", &ii);
                ch=static_cast<char>(ii);
                ret+=ch;
                i=i+2;
            } else {
                ret+=SRC[i];
            }
        }
        return (ret);
    }
};