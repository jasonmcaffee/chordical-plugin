#pragma once
#include<string>
#include<vector>
using namespace std;

enum ChordType{
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
    dyad1And3,
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