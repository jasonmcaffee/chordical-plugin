#pragma once

#include<vector>
#include<string>
using namespace std;

enum ScaleType {
    chromatic,
    majorIonian,
    naturalMinorAeolian,
    majorPentatonic,
    minorPentatonic,
    dorian,
    greekDorianPhrygian,
    lydian,
    mixolydian,
    locrian,
    ascendingMelodicMinor,
    hexatonicBlues,
    heptatonicBlues,
    nonatonicBlues,
    acoustic,
    algerian,
    altered,
    augmented,
    bebopMajor,
    bebopDominant,
    bebopMinor,
    doubleHarmonic,
    enigmatic,
    eulerFokker,
    flamenco,
    gypsy,
    halfDiminished,
    harmonicMajor,
    harmonicMinor,
    hirajoshi,
    hungarianGypsy,
    hungarianMinor,
    in_,
    insen,
    iwato,
    lydianAugmented,
    neapolitanMajor,
    neapolitanMinor,
    persian,
    phrygrianDominant,
    prometheus,
    tritone,
    ukranianDorian,
    yo,
};

vector<string> scaleTypes = {
    "chromatic",
    "majorIonian",
    "naturalMinorAeolian",
    "majorPentatonic",
    "minorPentatonic",
    "dorian",
    "greekDorianPhrygian",
    "lydian",
    "mixolydian",
    "locrian",
    "ascendingMelodicMinor",
    "hexatonicBlues",
    "heptatonicBlues",
    "nonatonicBlues",
    "acoustic",
    "algerian",
    "altered",
    "augmented",
    "bebopMajor",
    "bebopDominant",
    "bebopMinor",
    "doubleHarmonic",
    "enigmatic",
    "eulerFokker",
    "flamenco",
    "gypsy",
    "halfDiminished",
    "harmonicMajor",
    "harmonicMinor",
    "hirajoshi",
    "hungarianGypsy",
    "hungarianMinor",
    "in_",
    "insen",
    "iwato",
    "lydianAugmented",
    "neapolitanMajor",
    "neapolitanMinor",
    "persian",
    "phrygrianDominant",
    "prometheus",
    "tritone",
    "ukranianDorian",
    "yo"
};

inline ScaleType stringToScaleType(string scaleTypeString){
    if(scaleTypeString == "chromatic"){ return ScaleType::chromatic; }
    if(scaleTypeString == "majorIonian"){ return ScaleType::majorIonian; }
    if(scaleTypeString == "naturalMinorAeolian"){ return ScaleType::naturalMinorAeolian; }
    if(scaleTypeString == "majorPentatonic"){ return ScaleType::majorPentatonic; }
    if(scaleTypeString == "minorPentatonic"){ return ScaleType::minorPentatonic; }
    if(scaleTypeString == "dorian"){ return ScaleType::dorian; }
    if(scaleTypeString == "greekDorianPhrygian"){ return ScaleType::greekDorianPhrygian; }
    if(scaleTypeString == "lydian"){ return ScaleType::lydian; }
    if(scaleTypeString == "mixolydian"){ return ScaleType::mixolydian; }
    if(scaleTypeString == "locrian"){ return ScaleType::locrian; }
    if(scaleTypeString == "ascendingMelodicMinor"){ return ScaleType::ascendingMelodicMinor; }
    if(scaleTypeString == "hexatonicBlues"){ return ScaleType::hexatonicBlues; }
    if(scaleTypeString == "heptatonicBlues"){ return ScaleType::heptatonicBlues; }
    if(scaleTypeString == "nonatonicBlues"){ return ScaleType::nonatonicBlues; }
    if(scaleTypeString == "acoustic"){ return ScaleType::acoustic; }
    if(scaleTypeString == "algerian"){ return ScaleType::algerian; }
    if(scaleTypeString == "altered"){ return ScaleType::altered; }
    if(scaleTypeString == "augmented"){ return ScaleType::augmented; }
    if(scaleTypeString == "bebopMajor"){ return ScaleType::bebopMajor; }
    if(scaleTypeString == "bebopDominant"){ return ScaleType::bebopDominant; }
    if(scaleTypeString == "bebopMinor"){ return ScaleType::bebopMinor; }
    if(scaleTypeString == "doubleHarmonic"){ return ScaleType::doubleHarmonic; }
    if(scaleTypeString == "enigmatic"){ return ScaleType::enigmatic; }
    if(scaleTypeString == "eulerFokker"){ return ScaleType::eulerFokker; }
    if(scaleTypeString == "flamenco"){ return ScaleType::flamenco; }
    if(scaleTypeString == "gypsy"){ return ScaleType::gypsy; }
    if(scaleTypeString == "halfDiminished"){ return ScaleType::halfDiminished; }
    if(scaleTypeString == "harmonicMajor"){ return ScaleType::harmonicMajor; }
    if(scaleTypeString == "harmonicMinor"){ return ScaleType::harmonicMinor; }
    if(scaleTypeString == "hirajoshi"){ return ScaleType::hirajoshi; }
    if(scaleTypeString == "hungarianGypsy"){ return ScaleType::hungarianGypsy; }
    if(scaleTypeString == "hungarianMinor"){ return ScaleType::hungarianMinor; }
    if(scaleTypeString == "in_"){ return ScaleType::in_; }
    if(scaleTypeString == "insen"){ return ScaleType::insen; }
    if(scaleTypeString == "iwato"){ return ScaleType::iwato; }
    if(scaleTypeString == "lydianAugmented"){ return ScaleType::lydianAugmented; }
    if(scaleTypeString == "neapolitanMajor"){ return ScaleType::neapolitanMajor; }
    if(scaleTypeString == "neapolitanMinor"){ return ScaleType::neapolitanMinor; }
    if(scaleTypeString == "persian"){ return ScaleType::persian; }
    if(scaleTypeString == "phrygrianDominant"){ return ScaleType::phrygrianDominant; }
    if(scaleTypeString == "prometheus"){ return ScaleType::prometheus; }
    if(scaleTypeString == "tritone"){ return ScaleType::tritone; }
    if(scaleTypeString == "ukranianDorian"){ return ScaleType::ukranianDorian; }
    if(scaleTypeString == "yo"){ return ScaleType::yo; }
    return ScaleType::majorIonian;
}

inline string scaleTypeToString(ScaleType scaleType){
    if(scaleType == ScaleType::chromatic) { return "chromatic"; }
    if(scaleType == ScaleType::majorIonian) { return "majorIonian"; }
    if(scaleType == ScaleType::naturalMinorAeolian) { return "naturalMinorAeolian"; }
    if(scaleType == ScaleType::majorPentatonic) { return "majorPentatonic"; }
    if(scaleType == ScaleType::minorPentatonic) { return "minorPentatonic"; }
    if(scaleType == ScaleType::dorian) { return "dorian"; }
    if(scaleType == ScaleType::greekDorianPhrygian) { return "greekDorianPhrygian"; }
    if(scaleType == ScaleType::lydian) { return "lydian"; }
    if(scaleType == ScaleType::mixolydian) { return "mixolydian"; }
    if(scaleType == ScaleType::locrian) { return "locrian"; }
    if(scaleType == ScaleType::ascendingMelodicMinor) { return "ascendingMelodicMinor"; }
    if(scaleType == ScaleType::hexatonicBlues) { return "hexatonicBlues"; }
    if(scaleType == ScaleType::heptatonicBlues) { return "heptatonicBlues"; }
    if(scaleType == ScaleType::nonatonicBlues) { return "nonatonicBlues"; }
    if(scaleType == ScaleType::acoustic) { return "acoustic"; }
    if(scaleType == ScaleType::algerian) { return "algerian"; }
    if(scaleType == ScaleType::altered) { return "altered"; }
    if(scaleType == ScaleType::augmented) { return "augmented"; }
    if(scaleType == ScaleType::bebopMajor) { return "bebopMajor"; }
    if(scaleType == ScaleType::bebopDominant) { return "bebopDominant"; }
    if(scaleType == ScaleType::bebopMinor) { return "bebopMinor"; }
    if(scaleType == ScaleType::doubleHarmonic) { return "doubleHarmonic"; }
    if(scaleType == ScaleType::enigmatic) { return "enigmatic"; }
    if(scaleType == ScaleType::eulerFokker) { return "eulerFokker"; }
    if(scaleType == ScaleType::flamenco) { return "flamenco"; }
    if(scaleType == ScaleType::gypsy) { return "gypsy"; }
    if(scaleType == ScaleType::halfDiminished) { return "halfDiminished"; }
    if(scaleType == ScaleType::harmonicMajor) { return "harmonicMajor"; }
    if(scaleType == ScaleType::harmonicMinor) { return "harmonicMinor"; }
    if(scaleType == ScaleType::hirajoshi) { return "hirajoshi"; }
    if(scaleType == ScaleType::hungarianGypsy) { return "hungarianGypsy"; }
    if(scaleType == ScaleType::hungarianMinor) { return "hungarianMinor"; }
    if(scaleType == ScaleType::in_) { return "in_"; }
    if(scaleType == ScaleType::insen) { return "insen"; }
    if(scaleType == ScaleType::iwato) { return "iwato"; }
    if(scaleType == ScaleType::lydianAugmented) { return "lydianAugmented"; }
    if(scaleType == ScaleType::neapolitanMajor) { return "neapolitanMajor"; }
    if(scaleType == ScaleType::neapolitanMinor) { return "neapolitanMinor"; }
    if(scaleType == ScaleType::persian) { return "persian"; }
    if(scaleType == ScaleType::phrygrianDominant) { return "phrygrianDominant"; }
    if(scaleType == ScaleType::prometheus) { return "prometheus"; }
    if(scaleType == ScaleType::tritone) { return "tritone"; }
    if(scaleType == ScaleType::ukranianDorian) { return "ukranianDorian"; }
    if(scaleType == ScaleType::yo) { return "yo"; }
    return "majorIonian";
}