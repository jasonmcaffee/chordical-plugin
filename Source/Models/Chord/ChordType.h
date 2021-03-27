#pragma once
#include<string>
#include<vector>
using namespace std;

enum class ChordType{
    major,
    minor,
    major7th,
    minor7th,
    minorMajor7th,
    sustained4,
    sustained2,
    _6,
    minor6,
    _9,
    minor9,
    major9,
    minorMajor9,
    _11,
    minor11,
    major11,
    minorMajor11,
    _13,
    minor13,
    major13,
    minorMajor13,
    add9,
    minorAdd9,
    _6add9,
    minor6add9,
    dominant7th,
    dominant7thAdd11,
    major7thAdd11,
    minor7thAdd11,
    minorMajor7thAdd11,
    dominant7thAdd13,
    major7thAdd13,
    minor7thAdd13,
    minorMajor7thAdd13,
    dominant7thFlat5,
    dominant7thSharp5,
    dominant7thFlat9,
    dominant7thSharp9,
    dominant7thSharp5Flat9,
    diminished,
    minor7Flat5,
    minor7Sharp5,
    minor7Flat9,
    _9Sharp11,
    _9Flat13,
    _6Sustained4,
    _7Sustained4,
    major7thSustained4,
    _9Sustained4,
    major9thSustained4,
    root,
    dyad1And5,
    dyad1And3
};

vector<string> chordTypes = {
        "major",
        "minor",
        "major7th",
        "minor7th",
        "minorMajor7th",
        "sustained4",
        "sustained2",
        "_6",
        "minor6",
        "_9",
        "minor9",
        "major9",
        "minorMajor9",
        "_11",
        "minor11",
        "major11",
        "minorMajor11",
        "_13",
        "minor13",
        "major13",
        "minorMajor13",
        "add9",
        "minorAdd9",
        "_6add9",
        "minor6add9",
        "dominant7th",
        "dominant7thAdd11",
        "major7thAdd11",
        "minor7thAdd11",
        "minorMajor7thAdd11",
        "dominant7thAdd13",
        "major7thAdd13",
        "minor7thAdd13",
        "minorMajor7thAdd13",
        "dominant7thFlat5",
        "dominant7thSharp5",
        "dominant7thFlat9",
        "dominant7thSharp9",
        "dominant7thSharp5Flat9",
        "diminished",
        "minor7Flat5",
        "minor7Sharp5",
        "minor7Flat9",
        "_9Sharp11",
        "_9Flat13",
        "_6Sustained4",
        "_7Sustained4",
        "major7thSustained4",
        "_9Sustained4",
        "major9thSustained4",
        "root",
        "dyad1And5",
        "dyad1And3",
};

vector<string> formattedChordTypes = {
        "Major",
        "Minor",
        "Major 7th",
        "Minor 7th",
        "Minor Major 7th",
        "Sustained 4",
        "Sustained 2",
        "6",
        "Minor 6",
        "9",
        "Minor 9",
        "Major 9",
        "Minor Major 9",
        "11",
        "Minor 11",
        "Major 11",
        "Minor Major 11",
        "13",
        "Minor 13",
        "Major 13",
        "Minor Major 13",
        "Add 9",
        "Minor Add 9",
        "6 Add 9",
        "Minor 6 Add 9",
        "Dominant 7th",
        "Dominant 7th Add 11",
        "Major 7th Add 11",
        "Minor 7th Add 11",
        "Minor Major 7th Add 11",
        "Dominant 7th Add 13",
        "Major 7th Add 13",
        "Minor 7th Add 13",
        "Minor Major 7th Add 13",
        "Dominant 7th Flat 5",
        "Dominant 7th Sharp 5",
        "Dominant 7th Flat 9",
        "Dominant 7th Sharp 9",
        "Dominant 7th Sharp 5 Flat 9",
        "Diminished / Minor Flat 5",
        "Minor 7 Flat 5",
        "Minor 7 Sharp 5",
        "Minor 7 Flat 9",
        "9 Sharp 11",
        "9 Flat 13",
        "6 Sustained 4",
        "7 Sustained 4",
        "Major 7th Sustained 4",
        "9 Sustained 4",
        "Major 9th Sustained 4",
        "Root",
        "Dyad 1 & 5",
        "Dyad 1 & 3",
};

/**
function convertToC(chordTypeString){
  return `if(chordTypeString == "${chordTypeString}"){ return ChordType::${chordTypeString}; }`;
}
 * @param chordTypeString
 * @return
 */
inline ChordType stringToChordType(string chordTypeString) {
    if(chordTypeString == "major"){ return ChordType::major; }
    if(chordTypeString == "minor"){ return ChordType::minor; }
    if(chordTypeString == "major7th"){ return ChordType::major7th; }
    if(chordTypeString == "minor7th"){ return ChordType::minor7th; }
    if(chordTypeString == "minorMajor7th"){ return ChordType::minorMajor7th; }
    if(chordTypeString == "sustained4"){ return ChordType::sustained4; }
    if(chordTypeString == "sustained2"){ return ChordType::sustained2; }
    if(chordTypeString == "_6"){ return ChordType::_6; }
    if(chordTypeString == "minor6"){ return ChordType::minor6; }
    if(chordTypeString == "_9"){ return ChordType::_9; }
    if(chordTypeString == "minor9"){ return ChordType::minor9; }
    if(chordTypeString == "major9"){ return ChordType::major9; }
    if(chordTypeString == "minorMajor9"){ return ChordType::minorMajor9; }
    if(chordTypeString == "_11"){ return ChordType::_11; }
    if(chordTypeString == "minor11"){ return ChordType::minor11; }
    if(chordTypeString == "major11"){ return ChordType::major11; }
    if(chordTypeString == "minorMajor11"){ return ChordType::minorMajor11; }
    if(chordTypeString == "_13"){ return ChordType::_13; }
    if(chordTypeString == "minor13"){ return ChordType::minor13; }
    if(chordTypeString == "major13"){ return ChordType::major13; }
    if(chordTypeString == "minorMajor13"){ return ChordType::minorMajor13; }
    if(chordTypeString == "add9"){ return ChordType::add9; }
    if(chordTypeString == "minorAdd9"){ return ChordType::minorAdd9; }
    if(chordTypeString == "_6add9"){ return ChordType::_6add9; }
    if(chordTypeString == "minor6add9"){ return ChordType::minor6add9; }
    if(chordTypeString == "dominant7th"){ return ChordType::dominant7th; }
    if(chordTypeString == "dominant7thAdd11"){ return ChordType::dominant7thAdd11; }
    if(chordTypeString == "major7thAdd11"){ return ChordType::major7thAdd11; }
    if(chordTypeString == "minor7thAdd11"){ return ChordType::minor7thAdd11; }
    if(chordTypeString == "minorMajor7thAdd11"){ return ChordType::minorMajor7thAdd11; }
    if(chordTypeString == "dominant7thAdd13"){ return ChordType::dominant7thAdd13; }
    if(chordTypeString == "major7thAdd13"){ return ChordType::major7thAdd13; }
    if(chordTypeString == "minor7thAdd13"){ return ChordType::minor7thAdd13; }
    if(chordTypeString == "minorMajor7thAdd13"){ return ChordType::minorMajor7thAdd13; }
    if(chordTypeString == "dominant7thFlat5"){ return ChordType::dominant7thFlat5; }
    if(chordTypeString == "dominant7thSharp5"){ return ChordType::dominant7thSharp5; }
    if(chordTypeString == "dominant7thFlat9"){ return ChordType::dominant7thFlat9; }
    if(chordTypeString == "dominant7thSharp9"){ return ChordType::dominant7thSharp9; }
    if(chordTypeString == "dominant7thSharp5Flat9"){ return ChordType::dominant7thSharp5Flat9; }
    if(chordTypeString == "diminished"){ return ChordType::diminished; }
    if(chordTypeString == "minor7Flat5"){ return ChordType::minor7Flat5; }
    if(chordTypeString == "minor7Sharp5"){ return ChordType::minor7Sharp5; }
    if(chordTypeString == "minor7Flat9"){ return ChordType::minor7Flat9; }
    if(chordTypeString == "_9Sharp11"){ return ChordType::_9Sharp11; }
    if(chordTypeString == "_9Flat13"){ return ChordType::_9Flat13; }
    if(chordTypeString == "_6Sustained4"){ return ChordType::_6Sustained4; }
    if(chordTypeString == "_7Sustained4"){ return ChordType::_7Sustained4; }
    if(chordTypeString == "major7thSustained4"){ return ChordType::major7thSustained4; }
    if(chordTypeString == "_9Sustained4"){ return ChordType::_9Sustained4; }
    if(chordTypeString == "major9thSustained4"){ return ChordType::major9thSustained4; }
    if(chordTypeString == "root"){ return ChordType::root; }
    if(chordTypeString == "dyad1And5"){ return ChordType::dyad1And5; }
    if(chordTypeString == "dyad1And3"){ return ChordType::dyad1And3; }
    return ChordType::major;
}

inline string chordTypeToString(ChordType chordType){
    if(chordType == ChordType::major){ return "major"; }
    if(chordType == ChordType::minor){ return "minor"; }
    if(chordType == ChordType::major7th){ return "major7th"; }
    if(chordType == ChordType::minor7th){ return "minor7th"; }
    if(chordType == ChordType::minorMajor7th){ return "minorMajor7th"; }
    if(chordType == ChordType::sustained4){ return "sustained4"; }
    if(chordType == ChordType::sustained2){ return "sustained2"; }
    if(chordType == ChordType::_6){ return "_6"; }
    if(chordType == ChordType::minor6){ return "minor6"; }
    if(chordType == ChordType::_9){ return "_9"; }
    if(chordType == ChordType::minor9){ return "minor9"; }
    if(chordType == ChordType::major9){ return "major9"; }
    if(chordType == ChordType::minorMajor9){ return "minorMajor9"; }
    if(chordType == ChordType::_11){ return "_11"; }
    if(chordType == ChordType::minor11){ return "minor11"; }
    if(chordType == ChordType::major11){ return "major11"; }
    if(chordType == ChordType::minorMajor11){ return "minorMajor11"; }
    if(chordType == ChordType::_13){ return "_13"; }
    if(chordType == ChordType::minor13){ return "minor13"; }
    if(chordType == ChordType::major13){ return "major13"; }
    if(chordType == ChordType::minorMajor13){ return "minorMajor13"; }
    if(chordType == ChordType::add9){ return "add9"; }
    if(chordType == ChordType::minorAdd9){ return "minorAdd9"; }
    if(chordType == ChordType::_6add9){ return "_6add9"; }
    if(chordType == ChordType::minor6add9){ return "minor6add9"; }
    if(chordType == ChordType::dominant7th){ return "dominant7th"; }
    if(chordType == ChordType::dominant7thAdd11){ return "dominant7thAdd11"; }
    if(chordType == ChordType::major7thAdd11){ return "major7thAdd11"; }
    if(chordType == ChordType::minor7thAdd11){ return "minor7thAdd11"; }
    if(chordType == ChordType::minorMajor7thAdd11){ return "minorMajor7thAdd11"; }
    if(chordType == ChordType::dominant7thAdd13){ return "dominant7thAdd13"; }
    if(chordType == ChordType::major7thAdd13){ return "major7thAdd13"; }
    if(chordType == ChordType::minor7thAdd13){ return "minor7thAdd13"; }
    if(chordType == ChordType::minorMajor7thAdd13){ return "minorMajor7thAdd13"; }
    if(chordType == ChordType::dominant7thFlat5){ return "dominant7thFlat5"; }
    if(chordType == ChordType::dominant7thSharp5){ return "dominant7thSharp5"; }
    if(chordType == ChordType::dominant7thFlat9){ return "dominant7thFlat9"; }
    if(chordType == ChordType::dominant7thSharp9){ return "dominant7thSharp9"; }
    if(chordType == ChordType::dominant7thSharp5Flat9){ return "dominant7thSharp5Flat9"; }
    if(chordType == ChordType::diminished){ return "diminished"; }
    if(chordType == ChordType::minor7Flat5){ return "minor7Flat5"; }
    if(chordType == ChordType::minor7Sharp5){ return "minor7Sharp5"; }
    if(chordType == ChordType::minor7Flat9){ return "minor7Flat9"; }
    if(chordType == ChordType::_9Sharp11){ return "_9Sharp11"; }
    if(chordType == ChordType::_9Flat13){ return "_9Flat13"; }
    if(chordType == ChordType::_6Sustained4){ return "_6Sustained4"; }
    if(chordType == ChordType::_7Sustained4){ return "_7Sustained4"; }
    if(chordType == ChordType::major7thSustained4){ return "major7thSustained4"; }
    if(chordType == ChordType::_9Sustained4){ return "_9Sustained4"; }
    if(chordType == ChordType::major9thSustained4){ return "major9thSustained4"; }
    if(chordType == ChordType::root){ return "root"; }
    if(chordType == ChordType::dyad1And5){ return "dyad1And5"; }
    if(chordType == ChordType::dyad1And3){ return "dyad1And3"; }
    return "major";
}

inline string chordTypeToFormattedString(ChordType chordType){
    if(chordType == ChordType::major){ return "Major"; }
    if(chordType == ChordType::minor){ return "Minor"; }
    if(chordType == ChordType::major7th){ return "Major 7th"; }
    if(chordType == ChordType::minor7th){ return "Minor 7th"; }
    if(chordType == ChordType::minorMajor7th){ return "Minor Major 7th"; }
    if(chordType == ChordType::sustained4){ return "Sustained 4"; }
    if(chordType == ChordType::sustained2){ return "Sustained 2"; }
    if(chordType == ChordType::_6){ return "6"; }
    if(chordType == ChordType::minor6){ return "Minor 6"; }
    if(chordType == ChordType::_9){ return "9"; }
    if(chordType == ChordType::minor9){ return "Minor 9"; }
    if(chordType == ChordType::major9){ return "Major 9"; }
    if(chordType == ChordType::minorMajor9){ return "Minor Major 9"; }
    if(chordType == ChordType::_11){ return "11"; }
    if(chordType == ChordType::minor11){ return "Minor 11"; }
    if(chordType == ChordType::major11){ return "Major 11"; }
    if(chordType == ChordType::minorMajor11){ return "Minor Major 11"; }
    if(chordType == ChordType::_13){ return "13"; }
    if(chordType == ChordType::minor13){ return "Minor 13"; }
    if(chordType == ChordType::major13){ return "Major 13"; }
    if(chordType == ChordType::minorMajor13){ return "Minor Major 13"; }
    if(chordType == ChordType::add9){ return "Add 9"; }
    if(chordType == ChordType::minorAdd9){ return "Minor Add 9"; }
    if(chordType == ChordType::_6add9){ return "6 Add 9"; }
    if(chordType == ChordType::minor6add9){ return "Minor 6 Add 9"; }
    if(chordType == ChordType::dominant7th){ return "Dominant 7th"; }
    if(chordType == ChordType::dominant7thAdd11){ return "Dominant 7th Add 11"; }
    if(chordType == ChordType::major7thAdd11){ return "Major 7th Add 11"; }
    if(chordType == ChordType::minor7thAdd11){ return "Minor 7th Add 11"; }
    if(chordType == ChordType::minorMajor7thAdd11){ return "Minor Major 7th Add 11"; }
    if(chordType == ChordType::dominant7thAdd13){ return "Dominant 7th Add 13"; }
    if(chordType == ChordType::major7thAdd13){ return "Major 7th Add 13"; }
    if(chordType == ChordType::minor7thAdd13){ return "Minor 7th Add 13"; }
    if(chordType == ChordType::minorMajor7thAdd13){ return "Minor Major 7th Add 13"; }
    if(chordType == ChordType::dominant7thFlat5){ return "Dominant 7th Flat 5"; }
    if(chordType == ChordType::dominant7thSharp5){ return "Dominant 7th Sharp 5"; }
    if(chordType == ChordType::dominant7thFlat9){ return "Dominant 7th Flat 9"; }
    if(chordType == ChordType::dominant7thSharp9){ return "Dominant 7th Sharp 9"; }
    if(chordType == ChordType::dominant7thSharp5Flat9){ return "Dominant 7th Sharp 5 Flat 9"; }
    if(chordType == ChordType::diminished){ return "Diminished / Minor Flat 5"; }
    if(chordType == ChordType::minor7Flat5){ return "Minor 7 Flat 5"; }
    if(chordType == ChordType::minor7Sharp5){ return "Minor 7 Sharp 5"; }
    if(chordType == ChordType::minor7Flat9){ return "Minor 7 Flat 9"; }
    if(chordType == ChordType::_9Sharp11){ return "9 Sharp 11"; }
    if(chordType == ChordType::_9Flat13){ return "9 Flat 13"; }
    if(chordType == ChordType::_6Sustained4){ return "6 Sustained 4"; }
    if(chordType == ChordType::_7Sustained4){ return "7 Sustained 4"; }
    if(chordType == ChordType::major7thSustained4){ return "Major 7th Sustained 4"; }
    if(chordType == ChordType::_9Sustained4){ return "9 Sustained 4"; }
    if(chordType == ChordType::major9thSustained4){ return "Major 9th Sustained 4"; }
    if(chordType == ChordType::root){ return "Root"; }
    if(chordType == ChordType::dyad1And5){ return "Dyad 1 & 5"; }
    if(chordType == ChordType::dyad1And3){ return "Dyad 1 & 3"; }
    return "Major";
}

inline ChordType formattedStringToChordType(string formattedString){
    if(formattedString == "Major"){ return ChordType::major; }
    if(formattedString == "Minor"){ return ChordType::minor; }
    if(formattedString == "Major 7th"){ return ChordType::major7th; }
    if(formattedString == "Minor 7th"){ return ChordType::minor7th; }
    if(formattedString == "Minor Major 7th"){ return ChordType::minorMajor7th; }
    if(formattedString == "Sustained 4"){ return ChordType::sustained4; }
    if(formattedString == "Sustained 2"){ return ChordType::sustained2; }
    if(formattedString == "6"){ return ChordType::_6; }
    if(formattedString == "Minor 6"){ return ChordType::minor6; }
    if(formattedString == "9"){ return ChordType::_9; }
    if(formattedString == "Minor 9"){ return ChordType::minor9; }
    if(formattedString == "Major 9"){ return ChordType::major9; }
    if(formattedString == "Minor Major 9"){ return ChordType::minorMajor9; }
    if(formattedString == "11"){ return ChordType::_11; }
    if(formattedString == "Minor 11"){ return ChordType::minor11; }
    if(formattedString == "Major 11"){ return ChordType::major11; }
    if(formattedString == "Minor Major 11"){ return ChordType::minorMajor11; }
    if(formattedString == "13"){ return ChordType::_13; }
    if(formattedString == "Minor 13"){ return ChordType::minor13; }
    if(formattedString == "Major 13"){ return ChordType::major13; }
    if(formattedString == "Minor Major 13"){ return ChordType::minorMajor13; }
    if(formattedString == "Add 9"){ return ChordType::add9; }
    if(formattedString == "Minor Add 9"){ return ChordType::minorAdd9; }
    if(formattedString == "6 Add 9"){ return ChordType::_6add9; }
    if(formattedString == "Minor 6 Add 9"){ return ChordType::minor6add9; }
    if(formattedString == "Dominant 7th"){ return ChordType::dominant7th; }
    if(formattedString == "Dominant 7th Add 11"){ return ChordType::dominant7thAdd11; }
    if(formattedString == "Major 7th Add 11"){ return ChordType::major7thAdd11; }
    if(formattedString == "Minor 7th Add 11"){ return ChordType::minor7thAdd11; }
    if(formattedString == "Minor Major 7th Add 11"){ return ChordType::minorMajor7thAdd11; }
    if(formattedString == "Dominant 7th Add 13"){ return ChordType::dominant7thAdd13; }
    if(formattedString == "Major 7th Add 13"){ return ChordType::major7thAdd13; }
    if(formattedString == "Minor 7th Add 13"){ return ChordType::minor7thAdd13; }
    if(formattedString == "Minor Major 7th Add 13"){ return ChordType::minorMajor7thAdd13; }
    if(formattedString == "Dominant 7th Flat 5"){ return ChordType::dominant7thFlat5; }
    if(formattedString == "Dominant 7th Sharp 5"){ return ChordType::dominant7thSharp5; }
    if(formattedString == "Dominant 7th Flat 9"){ return ChordType::dominant7thFlat9; }
    if(formattedString == "Dominant 7th Sharp 9"){ return ChordType::dominant7thSharp9; }
    if(formattedString == "Dominant 7th Sharp 5 Flat 9"){ return ChordType::dominant7thSharp5Flat9; }
    if(formattedString == "Diminished / Minor Flat 5"){ return ChordType::diminished; }
    if(formattedString == "Minor 7 Flat 5"){ return ChordType::minor7Flat5; }
    if(formattedString == "Minor 7 Sharp 5"){ return ChordType::minor7Sharp5; }
    if(formattedString == "Minor 7 Flat 9"){ return ChordType::minor7Flat9; }
    if(formattedString == "9 Sharp 11"){ return ChordType::_9Sharp11; }
    if(formattedString == "9 Flat 13"){ return ChordType::_9Flat13; }
    if(formattedString == "6 Sustained 4"){ return ChordType::_6Sustained4; }
    if(formattedString == "7 Sustained 4"){ return ChordType::_7Sustained4; }
    if(formattedString == "Major 7th Sustained 4"){ return ChordType::major7thSustained4; }
    if(formattedString == "9 Sustained 4"){ return ChordType::_9Sustained4; }
    if(formattedString == "Major 9th Sustained 4"){ return ChordType::major9thSustained4; }
    if(formattedString == "Root"){ return ChordType::root; }
    if(formattedString == "Dyad 1 & 5"){ return ChordType::dyad1And5; }
    if(formattedString == "Dyad 1 & 3"){ return ChordType::dyad1And3; }
    return ChordType::major;
}