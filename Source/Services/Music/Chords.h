#pragma once
#include "./PredefinedNotes.h"
#include "./Scales.h"
#include "../../Models/Chord/Chord.h"
#include "../../Models/Scale/ScaleDegree.h"
#include "../Util/Util.h"
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
using s = ScaleDegree;
using namespace std;


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



class Chords{
public:
    struct ChordFuncs {
        static Chord major(const NoteSymbol& rootNote, const int& octave){ return buildChord("Major", rootNote, octave, {s::_1, s::_3, s::_5}); };
        static Chord minor(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor", rootNote, octave, {s::_1, s::_3b, s::_5}); };
        static Chord major7th(const NoteSymbol& rootNote, const int& octave){ return buildChord("Major 7th", rootNote, octave, {s::_1, s::_3, s::_5, s::_7}); };
        static Chord minor7th(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 7th", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b}); };
        static Chord minorMajor7th(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor Major 7th", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7}); };
        static Chord sustained4(const NoteSymbol& rootNote, const int& octave){ return buildChord("Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, }); };
        static Chord sustained2(const NoteSymbol& rootNote, const int& octave){ return buildChord("Sustained 2", rootNote, octave, {s::_1, s::_2, s::_5, }); };
        static Chord _6(const NoteSymbol& rootNote, const int& octave){ return buildChord("6", rootNote, octave, {s::_1, s::_3, s::_5, s::_6 }); };
        static Chord minor6(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 6", rootNote, octave, {s::_1, s::_3b, s::_5, s::_6 }); };
        static Chord _9(const NoteSymbol& rootNote, const int& octave){ return buildChord("9", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9 }); };
        static Chord minor9(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 9", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b, s::_9 }); };
        static Chord major9(const NoteSymbol& rootNote, const int& octave){ return buildChord("Major 9", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_9 }); };
        static Chord minorMajor9(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor Major 9", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7, s::_9 }); };
        static Chord _11(const NoteSymbol& rootNote, const int& octave){ return buildChord("11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9, s::_11 }); };
        static Chord minor11(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 11", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b, s::_9, s::_11 }); };
        static Chord major11(const NoteSymbol& rootNote, const int& octave){ return buildChord("Major 11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_9, s::_11 }); };
        static Chord minorMajor11(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor Major 11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_9, s::_11 }); };
        static Chord _13(const NoteSymbol& rootNote, const int& octave){ return buildChord("13", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9, s::_13 }); };
        static Chord minor13(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 13", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b, s::_9, s::_13 }); };
        static Chord major13(const NoteSymbol& rootNote, const int& octave){ return buildChord("Major 13", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_9, s::_13 }); };
        static Chord minorMajor13(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor Major 13", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7, s::_9, s::_13 }); };
        static Chord add9(const NoteSymbol& rootNote, const int& octave){ return buildChord("Add 9", rootNote, octave, {s::_1, s::_3, s::_5, s::_9, }); };
        static Chord minorAdd9(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor Add 9", rootNote, octave, {s::_1, s::_3b, s::_5, s::_9, }); };
        static Chord _6add9(const NoteSymbol& rootNote, const int& octave){ return buildChord("6 Add 9", rootNote, octave, {s::_1, s::_3, s::_5, s::_6, s::_9, }); };
        static Chord minor6add9(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 6 Add 9", rootNote, octave, {s::_1, s::_3b, s::_5, s::_6, s::_9, }); };
        static Chord dominant7th(const NoteSymbol& rootNote, const int& octave){ return buildChord("Dominant 7th", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, }); };
        static Chord dominant7thAdd11(const NoteSymbol& rootNote, const int& octave){ return buildChord("Dominant 7th Add 11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_11 }); };
        static Chord major7thAdd11(const NoteSymbol& rootNote, const int& octave){ return buildChord("Major 7th Add 11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_11 }); };
        static Chord minor7thAdd11(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 7th Add 11", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b, s::_11 }); };
        static Chord minorMajor7thAdd11(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor Major 7th Add 11", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7, s::_11 }); };
        static Chord dominant7thAdd13(const NoteSymbol& rootNote, const int& octave){ return buildChord("Dominant 7th Add 13", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_13 }); };
        static Chord major7thAdd13(const NoteSymbol& rootNote, const int& octave){ return buildChord("Major 7th Add 13", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_13 }); };
        static Chord minor7thAdd13(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 7th Add 13", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b, s::_13 }); };
        static Chord minorMajor7thAdd13(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor Major 7th Add 13", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7, s::_13 }); };
        static Chord dominant7thFlat5(const NoteSymbol& rootNote, const int& octave){ return buildChord("Dominant 7th Flat 5", rootNote, octave, {s::_1, s::_3, s::_5b, s::_7b, }); };
        static Chord dominant7thSharp5(const NoteSymbol& rootNote, const int& octave){ return buildChord("Dominant 7th Sharp 5", rootNote, octave, {s::_1, s::_3, s::_5s, s::_7b, }); };
        static Chord dominant7thFlat9(const NoteSymbol& rootNote, const int& octave){ return buildChord("Dominant 7th Flat 9", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9b}); };
        static Chord dominant7thSharp9(const NoteSymbol& rootNote, const int& octave){ return buildChord("Dominant 7th Sharp 9", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9s}); };
        static Chord dominant7thSharp5Flat9(const NoteSymbol& rootNote, const int& octave){ return buildChord("Dominant 7th Sharp 5 Flat 9", rootNote, octave, {s::_1, s::_3, s::_5s, s::_7b, s::_9b}); };
        static Chord diminished(const NoteSymbol& rootNote, const int& octave){ return buildChord("Diminished / Minor Flat 5", rootNote, octave, {s::_1, s::_3b, s::_5b,}); };
        static Chord minor7Flat5(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 7 Flat 5", rootNote, octave, {s::_1, s::_3b, s::_5b, s::_7b}); };
        static Chord minor7Sharp5(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 7 Sharp 5", rootNote, octave, {s::_1, s::_3b, s::_5s, s::_7b}); };
        static Chord minor7Flat9(const NoteSymbol& rootNote, const int& octave){ return buildChord("Minor 7 Flat 9", rootNote, octave, {s::_1, s::_3b, s::_5s, s::_7b, s::_9b}); };
        static Chord _9Sharp11(const NoteSymbol& rootNote, const int& octave){ return buildChord("9 Sharp 11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9, s::_11s}); };
        static Chord _9Flat13(const NoteSymbol& rootNote, const int& octave){ return buildChord("9 Flat 13", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9, s::_13b}); };
        static Chord _6Sustained4(const NoteSymbol& rootNote, const int& octave){ return buildChord("6 Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, s::_6, }); };
        static Chord _7Sustained4(const NoteSymbol& rootNote, const int& octave){ return buildChord("7 Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, s::_7b, }); };
        static Chord major7thSustained4(const NoteSymbol& rootNote, const int& octave){ return buildChord("Major 7th Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, s::_7, }); };
        static Chord _9Sustained4(const NoteSymbol& rootNote, const int& octave){ return buildChord("9 Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, s::_7b, s::_9 }); };
        static Chord major9thSustained4(const NoteSymbol& rootNote, const int& octave){ return buildChord("Major 9th Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, s::_7, s::_9 }); };
        static Chord root(const NoteSymbol& rootNote, const int& octave){ return buildChord("Root", rootNote, octave, {s::_1 }); };
        static Chord dyad1And5(const NoteSymbol& rootNote, const int& octave){ return buildChord("Dyad 1 & 5", rootNote, octave, {s::_1, s::_5 }); };
        static Chord dyad1And3(const NoteSymbol& rootNote, const int& octave){ return buildChord("Dyad 1 & 3", rootNote, octave, {s::_1, s::_3 }); };
    };

    static Chord createChord(const string& chordType, const string& rootNoteAsString, const int& octave){
        NoteSymbol rootNote = stringToNoteSymbol(rootNoteAsString);
        if(chordType == "major"){ return ChordFuncs::major(rootNote, octave); }
        if(chordType == "minor"){ return ChordFuncs::minor(rootNote, octave); }
        if(chordType == "major7th"){ return ChordFuncs::major7th(rootNote, octave); }
        if(chordType == "minor7th"){ return ChordFuncs::minor7th(rootNote, octave); }
        if(chordType == "minorMajor7th"){ return ChordFuncs::minorMajor7th(rootNote, octave); }
        if(chordType == "sustained4"){ return ChordFuncs::sustained4(rootNote, octave); }
        if(chordType == "sustained2"){ return ChordFuncs::sustained2(rootNote, octave); }
        if(chordType == "_6"){ return ChordFuncs::_6(rootNote, octave); }
        if(chordType == "minor6"){ return ChordFuncs::minor6(rootNote, octave); }
        if(chordType == "_9"){ return ChordFuncs::_9(rootNote, octave); }
        if(chordType == "minor9"){ return ChordFuncs::minor9(rootNote, octave); }
        if(chordType == "major9"){ return ChordFuncs::major9(rootNote, octave); }
        if(chordType == "minorMajor9"){ return ChordFuncs::minorMajor9(rootNote, octave); }
        if(chordType == "_11"){ return ChordFuncs::_11(rootNote, octave); }
        if(chordType == "minor11"){ return ChordFuncs::minor11(rootNote, octave); }
        if(chordType == "major11"){ return ChordFuncs::major11(rootNote, octave); }
        if(chordType == "minorMajor11"){ return ChordFuncs::minorMajor11(rootNote, octave); }
        if(chordType == "_13"){ return ChordFuncs::_13(rootNote, octave); }
        if(chordType == "minor13"){ return ChordFuncs::minor13(rootNote, octave); }
        if(chordType == "major13"){ return ChordFuncs::major13(rootNote, octave); }
        if(chordType == "minorMajor13"){ return ChordFuncs::minorMajor13(rootNote, octave); }
        if(chordType == "add9"){ return ChordFuncs::add9(rootNote, octave); }
        if(chordType == "minorAdd9"){ return ChordFuncs::minorAdd9(rootNote, octave); }
        if(chordType == "_6add9"){ return ChordFuncs::_6add9(rootNote, octave); }
        if(chordType == "minor6add9"){ return ChordFuncs::minor6add9(rootNote, octave); }
        if(chordType == "dominant7th"){ return ChordFuncs::dominant7th(rootNote, octave); }
        if(chordType == "dominant7thAdd11"){ return ChordFuncs::dominant7thAdd11(rootNote, octave); }
        if(chordType == "major7thAdd11"){ return ChordFuncs::major7thAdd11(rootNote, octave); }
        if(chordType == "minor7thAdd11"){ return ChordFuncs::minor7thAdd11(rootNote, octave); }
        if(chordType == "minorMajor7thAdd11"){ return ChordFuncs::minorMajor7thAdd11(rootNote, octave); }
        if(chordType == "dominant7thAdd13"){ return ChordFuncs::dominant7thAdd13(rootNote, octave); }
        if(chordType == "major7thAdd13"){ return ChordFuncs::major7thAdd13(rootNote, octave); }
        if(chordType == "minor7thAdd13"){ return ChordFuncs::minor7thAdd13(rootNote, octave); }
        if(chordType == "minorMajor7thAdd13"){ return ChordFuncs::minorMajor7thAdd13(rootNote, octave); }
        if(chordType == "dominant7thFlat5"){ return ChordFuncs::dominant7thFlat5(rootNote, octave); }
        if(chordType == "dominant7thSharp5"){ return ChordFuncs::dominant7thSharp5(rootNote, octave); }
        if(chordType == "dominant7thFlat9"){ return ChordFuncs::dominant7thFlat9(rootNote, octave); }
        if(chordType == "dominant7thSharp9"){ return ChordFuncs::dominant7thSharp9(rootNote, octave); }
        if(chordType == "dominant7thSharp5Flat9"){ return ChordFuncs::dominant7thSharp5Flat9(rootNote, octave); }
        if(chordType == "diminished"){ return ChordFuncs::diminished(rootNote, octave); }
        if(chordType == "minor7Flat5"){ return ChordFuncs::minor7Flat5(rootNote, octave); }
        if(chordType == "minor7Sharp5"){ return ChordFuncs::minor7Sharp5(rootNote, octave); }
        if(chordType == "minor7Flat9"){ return ChordFuncs::minor7Flat9(rootNote, octave); }
        if(chordType == "_9Sharp11"){ return ChordFuncs::_9Sharp11(rootNote, octave); }
        if(chordType == "_9Flat13"){ return ChordFuncs::_9Flat13(rootNote, octave); }
        if(chordType == "_6Sustained4"){ return ChordFuncs::_6Sustained4(rootNote, octave); }
        if(chordType == "_7Sustained4"){ return ChordFuncs::_7Sustained4(rootNote, octave); }
        if(chordType == "major7thSustained4"){ return ChordFuncs::major7thSustained4(rootNote, octave); }
        if(chordType == "_9Sustained4"){ return ChordFuncs::_9Sustained4(rootNote, octave); }
        if(chordType == "major9thSustained4"){ return ChordFuncs::major9thSustained4(rootNote, octave); }
        if(chordType == "root"){ return ChordFuncs::root(rootNote, octave); }
        if(chordType == "dyad1And5"){ return ChordFuncs::dyad1And5(rootNote, octave); }
        if(chordType == "dyad1And3"){ return ChordFuncs::dyad1And3(rootNote, octave); }
        return ChordFuncs::major(rootNote, octave);
    }

    static Chord buildChord(const string& type, const NoteSymbol& rootNote, int octave, const vector<ScaleDegree>& pattern){
        auto majorScaleNotes = getMajorScaleNotesNeededToBuildAChordUsingScaleDegrees(rootNote, octave);
        auto notes = getNotesFromPattern(pattern, majorScaleNotes);
        auto id = Util::generateId("chord_");
        string label = noteSymbolToString(rootNote) + " " + type;
        Chord chord = Chord{ id, label, octave, rootNote, type, notes };
        return chord;
    }

    static vector<PredefinedNote> getMajorScaleNotesNeededToBuildAChordUsingScaleDegrees(const NoteSymbol& rootNote, const int& octave){
        auto notesWithStartingOctave = PredefinedNotes::getNotesWithinOctaveRange(octave, octave + 2);
        auto majorScaleNotes = Scales::getNotesForKey(ScaleType::majorIonian, rootNote, notesWithStartingOctave);
        return majorScaleNotes;
    }

    static vector<PredefinedNote> getNotesFromPattern(const vector<ScaleDegree>& pattern, const vector<PredefinedNote>& majorScaleNotes){
        vector<PredefinedNote> result = {};
        for(auto & scaleDegree : pattern){
            switch (scaleDegree) {
                case ScaleDegree::_1: {
                    auto note = majorScaleNotes[1 - 1];
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_2: {
                    auto note = majorScaleNotes[2 - 1];
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_3b: {
                    auto note = majorScaleNotes[3 - 1];
                    note = PredefinedNotes::flattenNote(note);
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_3: {
                    auto note = majorScaleNotes[3 - 1];
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_4: {
                    auto note = majorScaleNotes[4 - 1];
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_5b: {
                    auto note = majorScaleNotes[5 - 1];
                    note = PredefinedNotes::flattenNote(note);
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_5: {
                    auto note = majorScaleNotes[5 - 1];
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_5s: {
                    auto note = majorScaleNotes[5 - 1];
                    note = PredefinedNotes::sharpenNote(note);
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_6: {
                    auto note = majorScaleNotes[6 - 1];
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_7b: {
                    auto note = majorScaleNotes[7 - 1];
                    note = PredefinedNotes::flattenNote(note);
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_7: {
                    auto note = majorScaleNotes[7 - 1];
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_9b: {
                    auto note = majorScaleNotes[9 - 1];
                    note = PredefinedNotes::flattenNote(note);
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_9: {
                    auto note = majorScaleNotes[9 - 1];
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_9s: {
                    auto note = majorScaleNotes[9 - 1];
                    note = PredefinedNotes::sharpenNote(note);
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_11: {
                    auto note = majorScaleNotes[11 - 1];
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_11s: {
                    auto note = majorScaleNotes[11 - 1];
                    note = PredefinedNotes::flattenNote(note);
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_13b: {
                    auto note = majorScaleNotes[13 - 1];
                    note = PredefinedNotes::flattenNote(note);
                    result.push_back(note);
                    break;
                }
                case ScaleDegree::_13: {
                    auto note = majorScaleNotes[13 - 1];
                    result.push_back(note);
                    break;
                }

            }
        }
        return result;
    }

};

//
//void main(){
//    map<string, std::function<Chord(NoteSymbol, int)> > m = {
//            {"major", [](NoteSymbol rootNote, int octave){ return Chords::ChordFuncs::major(rootNote, octave); } },
//    };
////    m.emplace("major", &Chords::ChordFuncs::major);
////    m["major"] = [](NoteSymbol rootNote, int octave){ Chords::ChordFuncs::major(rootNote, octave); };
//}
