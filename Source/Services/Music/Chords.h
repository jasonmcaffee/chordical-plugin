#pragma once
#include "./PredefinedNotes.h"
#include "./Scales.h"
#include "../../Models/Chord/Chord.h"
#include "../../Models/Scale/ScaleDegree.h"
#include "../Util/Util.h"
#include<vector>
using s = ScaleDegree;
using namespace std;

class Chords{
public:
    struct ChordFuncs {
        static Chord major(NoteSymbol rootNote, int octave){ return buildChord("Major", rootNote, octave, {s::_1, s::_3, s::_5}); };
        static Chord minor(NoteSymbol rootNote, int octave){ return buildChord("Minor", rootNote, octave, {s::_1, s::_3b, s::_5}); };
        static Chord major7th(NoteSymbol rootNote, int octave){ return buildChord("Major 7th", rootNote, octave, {s::_1, s::_3, s::_5, s::_7}); };
        static Chord minor7th(NoteSymbol rootNote, int octave){ return buildChord("Minor 7th", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b}); };
        static Chord minorMajor7th(NoteSymbol rootNote, int octave){ return buildChord("Minor Major 7th", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7}); };
        static Chord sustained4(NoteSymbol rootNote, int octave){ return buildChord("Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, }); };
        static Chord sustained2(NoteSymbol rootNote, int octave){ return buildChord("Sustained 2", rootNote, octave, {s::_1, s::_2, s::_5, }); };
        static Chord _6(NoteSymbol rootNote, int octave){ return buildChord("6", rootNote, octave, {s::_1, s::_3, s::_5, s::_6 }); };
        static Chord minor6(NoteSymbol rootNote, int octave){ return buildChord("Minor 6", rootNote, octave, {s::_1, s::_3b, s::_5, s::_6 }); };
        static Chord _9(NoteSymbol rootNote, int octave){ return buildChord("9", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9 }); };
        static Chord minor9(NoteSymbol rootNote, int octave){ return buildChord("Minor 9", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b, s::_9 }); };
        static Chord major9(NoteSymbol rootNote, int octave){ return buildChord("Major 9", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_9 }); };
        static Chord minorMajor9(NoteSymbol rootNote, int octave){ return buildChord("Minor Major 9", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7, s::_9 }); };
        static Chord _11(NoteSymbol rootNote, int octave){ return buildChord("11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9, s::_11 }); };
        static Chord minor11(NoteSymbol rootNote, int octave){ return buildChord("Minor 11", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b, s::_9, s::_11 }); };
        static Chord major11(NoteSymbol rootNote, int octave){ return buildChord("Major 11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_9, s::_11 }); };
        static Chord minorMajor11(NoteSymbol rootNote, int octave){ return buildChord("Minor Major 11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_9, s::_11 }); };
        static Chord _13(NoteSymbol rootNote, int octave){ return buildChord("13", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9, s::_13 }); };
        static Chord minor13(NoteSymbol rootNote, int octave){ return buildChord("Minor 13", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b, s::_9, s::_13 }); };
        static Chord major13(NoteSymbol rootNote, int octave){ return buildChord("Major 13", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_9, s::_13 }); };
        static Chord minorMajor13(NoteSymbol rootNote, int octave){ return buildChord("Minor Major 13", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7, s::_9, s::_13 }); };
        static Chord add9(NoteSymbol rootNote, int octave){ return buildChord("Add 9", rootNote, octave, {s::_1, s::_3, s::_5, s::_9, }); };
        static Chord minorAdd9(NoteSymbol rootNote, int octave){ return buildChord("Minor Add 9", rootNote, octave, {s::_1, s::_3b, s::_5, s::_9, }); };
        static Chord _6add9(NoteSymbol rootNote, int octave){ return buildChord("6 Add 9", rootNote, octave, {s::_1, s::_3, s::_5, s::_6, s::_9, }); };
        static Chord minor6add9(NoteSymbol rootNote, int octave){ return buildChord("Minor 6 Add 9", rootNote, octave, {s::_1, s::_3b, s::_5, s::_6, s::_9, }); };
        static Chord dominant7th(NoteSymbol rootNote, int octave){ return buildChord("Dominant 7th", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, }); };
        static Chord dominant7thAdd11(NoteSymbol rootNote, int octave){ return buildChord("Dominant 7th Add 11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_11 }); };
        static Chord major7thAdd11(NoteSymbol rootNote, int octave){ return buildChord("Major 7th Add 11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_11 }); };
        static Chord minor7thAdd11(NoteSymbol rootNote, int octave){ return buildChord("Minor 7th Add 11", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b, s::_11 }); };
        static Chord minorMajor7thAdd11(NoteSymbol rootNote, int octave){ return buildChord("Minor Major 7th Add 11", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7, s::_11 }); };
        static Chord dominant7thAdd13(NoteSymbol rootNote, int octave){ return buildChord("Dominant 7th Add 13", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_13 }); };
        static Chord major7thAdd13(NoteSymbol rootNote, int octave){ return buildChord("Major 7th Add 13", rootNote, octave, {s::_1, s::_3, s::_5, s::_7, s::_13 }); };
        static Chord minor7thAdd13(NoteSymbol rootNote, int octave){ return buildChord("Minor 7th Add 13", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7b, s::_13 }); };
        static Chord minorMajor7thAdd13(NoteSymbol rootNote, int octave){ return buildChord("Minor Major 7th Add 13", rootNote, octave, {s::_1, s::_3b, s::_5, s::_7, s::_13 }); };
        static Chord dominant7thFlat5(NoteSymbol rootNote, int octave){ return buildChord("Dominant 7th Flat 5", rootNote, octave, {s::_1, s::_3, s::_5b, s::_7b, }); };
        static Chord dominant7thSharp5(NoteSymbol rootNote, int octave){ return buildChord("Dominant 7th Sharp 5", rootNote, octave, {s::_1, s::_3, s::_5s, s::_7b, }); };
        static Chord dominant7thFlat9(NoteSymbol rootNote, int octave){ return buildChord("Dominant 7th Flat 9", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9b}); };
        static Chord dominant7thSharp9(NoteSymbol rootNote, int octave){ return buildChord("Dominant 7th Sharp 9", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9s}); };
        static Chord dominant7thSharp5Flat9(NoteSymbol rootNote, int octave){ return buildChord("Dominant 7th Sharp 5 Flat 9", rootNote, octave, {s::_1, s::_3, s::_5s, s::_7b, s::_9b}); };
        static Chord diminished(NoteSymbol rootNote, int octave){ return buildChord("Diminished / Minor Flat 5", rootNote, octave, {s::_1, s::_3b, s::_5b,}); };
        static Chord minor7Flat5(NoteSymbol rootNote, int octave){ return buildChord("Minor 7 Flat 5", rootNote, octave, {s::_1, s::_3b, s::_5b, s::_7b}); };
        static Chord minor7Sharp5(NoteSymbol rootNote, int octave){ return buildChord("Minor 7 Sharp 5", rootNote, octave, {s::_1, s::_3b, s::_5s, s::_7b}); };
        static Chord minor7Flat9(NoteSymbol rootNote, int octave){ return buildChord("Minor 7 Flat 9", rootNote, octave, {s::_1, s::_3b, s::_5s, s::_7b, s::_9b}); };
        static Chord _9Sharp11(NoteSymbol rootNote, int octave){ return buildChord("9 Sharp 11", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9, s::_11s}); };
        static Chord _9Flat13(NoteSymbol rootNote, int octave){ return buildChord("9 Flat 13", rootNote, octave, {s::_1, s::_3, s::_5, s::_7b, s::_9, s::_13b}); };
        static Chord _6Sustained4(NoteSymbol rootNote, int octave){ return buildChord("6 Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, s::_6, }); };
        static Chord _7Sustained4(NoteSymbol rootNote, int octave){ return buildChord("7 Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, s::_7b, }); };
        static Chord major7thSustained4(NoteSymbol rootNote, int octave){ return buildChord("Major 7th Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, s::_7, }); };
        static Chord _9Sustained4(NoteSymbol rootNote, int octave){ return buildChord("9 Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, s::_7b, s::_9 }); };
        static Chord major9thSustained4(NoteSymbol rootNote, int octave){ return buildChord("Major 9th Sustained 4", rootNote, octave, {s::_1, s::_4, s::_5, s::_7, s::_9 }); };
        static Chord root(NoteSymbol rootNote, int octave){ return buildChord("Root", rootNote, octave, {s::_1 }); };
        static Chord dyad1And5(NoteSymbol rootNote, int octave){ return buildChord("Dyad 1 & 5", rootNote, octave, {s::_1, s::_5 }); };
        static Chord dyad1And3(NoteSymbol rootNote, int octave){ return buildChord("Dyad 1 & 3", rootNote, octave, {s::_1, s::_3 }); };
    };


    static Chord buildChord(string type, NoteSymbol rootNote, int octave, vector<ScaleDegree> pattern){
        auto majorScaleNotes = getMajorScaleNotesNeededToBuildAChordUsingScaleDegrees(rootNote, octave);
        auto notes = getNotesFromPattern(pattern, majorScaleNotes);
        auto id = Util::generateId("chord_");
        string label = noteSymbolToString(rootNote) + " " + type;
        Chord chord = Chord{ id, label, octave, rootNote, type, notes };
        return chord;
    }

    static vector<PredefinedNote> getMajorScaleNotesNeededToBuildAChordUsingScaleDegrees(NoteSymbol rootNote, int octave){
        auto notesWithStartingOctave = PredefinedNotes::getNotesWithinOctaveRange(octave, octave + 2);
        auto majorScaleNotes = Scales::getNotesForKey(ScaleType::majorIonian, rootNote, notesWithStartingOctave);
        return majorScaleNotes;
    }

    static vector<PredefinedNote> getNotesFromPattern(vector<ScaleDegree> pattern, vector<PredefinedNote> majorScaleNotes){
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
//    function buildChord({type='Major', rootNote='c', octave=3, pattern=[], id=generateRandomId(), label=`${rootNote} ${type}`}: Partial<IBuildChordParam>){
//        // console.log('buildChord called for ', type, rootNote, octave, pattern);
//        const majorScaleNotes = getMajorScaleNotes({rootNote, octave});
//        // console.log('majorScaleNotes', majorScaleNotes);
//        const notes = getNotesFromPattern({pattern, notes: majorScaleNotes});
//        // console.log('notes', notes);
//        const chord: IChord = {
//                id,
//                label,
//                octave, //useful when we need to regenerate a chord based on type. let's us construct a new chord with settings of previous.
//                rootNote,
//                type,
//                notes,
//        };
//        return chord;
//    }



    //function getMajorScaleNotes({rootNote='c', octave=3}: {rootNote: NoteSymbolTypes, octave: number}){
    //  const notesWithStartingOctave = getNotesWithinOctaveRange({begin: octave, end: octave + 2});
    //  const majorScaleNotes = getNotesForScale({scale: ScaleTypesEnum.majorIonian, rootNote, notes: notesWithStartingOctave});
    //  return majorScaleNotes;
    //}
};