#pragma once

#include "../../Models/Note/PredefinedNote.h"
#include "../../Models/Note/NoteSymbol.h"
#include "../Util/Util.h"
#include<vector>
#include<optional>
using namespace std;

vector<PredefinedNote> predefinedNotesVector = {
    PredefinedNote{"c0", NoteSymbol::c, 0, 12, 8.175798915643707},
    PredefinedNote{"c#0", NoteSymbol::cSharp, 0, 13, 8.661957218027252},
    PredefinedNote{"d0", NoteSymbol::d, 0, 14, 9.177023997418988},
    PredefinedNote{"d#0", NoteSymbol::dSharp, 0, 15, 9.722718241315029},
    PredefinedNote{"e0", NoteSymbol::e, 0, 16, 10.300861153527183},
    PredefinedNote{"f0", NoteSymbol::f, 0, 17, 10.913382232281373},
    PredefinedNote{"f#0", NoteSymbol::fSharp, 0, 18, 11.562325709738575},
    PredefinedNote{"g0", NoteSymbol::g, 0, 19, 12.249857374429663},
    PredefinedNote{"g#0", NoteSymbol::gSharp, 0, 20, 12.978271799373287},
    PredefinedNote{"a0", NoteSymbol::a, 0, 21, 13.75},
    PredefinedNote{"a#0", NoteSymbol::aSharp, 0, 22, 14.567617547440307},
    PredefinedNote{"b0", NoteSymbol::b, 0, 23, 15.433853164253883},
    PredefinedNote{"c1", NoteSymbol::c, 1, 24, 16.351597831287414},
    PredefinedNote{"c#1", NoteSymbol::cSharp, 1, 25, 17.323914436054505},
    PredefinedNote{"d1", NoteSymbol::d, 1, 26, 18.354047994837977},
    PredefinedNote{"d#1", NoteSymbol::dSharp, 1, 27, 19.445436482630058},
    PredefinedNote{"e1", NoteSymbol::e, 1, 28, 20.601722307054366},
    PredefinedNote{"f1", NoteSymbol::f, 1, 29, 21.826764464562746},
    PredefinedNote{"f#1", NoteSymbol::fSharp, 1, 30, 23.12465141947715},
    PredefinedNote{"g1", NoteSymbol::g, 1, 31, 24.499714748859326},
    PredefinedNote{"g#1", NoteSymbol::gSharp, 1, 32, 25.956543598746574},
    PredefinedNote{"a1", NoteSymbol::a, 1, 33, 27.5},
    PredefinedNote{"a#1", NoteSymbol::aSharp, 1, 34, 29.13523509488062},
    PredefinedNote{"b1", NoteSymbol::b, 1, 35, 30.86770632850775},
    PredefinedNote{"c2", NoteSymbol::c, 2, 36, 32.70319566257483},
    PredefinedNote{"c#2", NoteSymbol::cSharp, 2, 37, 34.64782887210901},
    PredefinedNote{"d2", NoteSymbol::d, 2, 38, 36.70809598967594},
    PredefinedNote{"d#2", NoteSymbol::dSharp, 2, 39, 38.890872965260115},
    PredefinedNote{"e2", NoteSymbol::e, 2, 40, 41.20344461410875},
    PredefinedNote{"f2", NoteSymbol::f, 2, 41, 43.653528929125486},
    PredefinedNote{"f#2", NoteSymbol::fSharp, 2, 42, 46.2493028389543},
    PredefinedNote{"g2", NoteSymbol::g, 2, 43, 48.999429497718666},
    PredefinedNote{"g#2", NoteSymbol::gSharp, 2, 44, 51.91308719749314},
    PredefinedNote{"a2", NoteSymbol::a, 2, 45, 55},
    PredefinedNote{"a#2", NoteSymbol::aSharp, 2, 46, 58.27047018976124},
    PredefinedNote{"b2", NoteSymbol::b, 2, 47, 61.7354126570155},
    PredefinedNote{"c3", NoteSymbol::c, 3, 48, 65.40639132514966},
    PredefinedNote{"c#3", NoteSymbol::cSharp, 3, 49, 69.29565774421802},
    PredefinedNote{"d3", NoteSymbol::d, 3, 50, 73.41619197935188},
    PredefinedNote{"d#3", NoteSymbol::dSharp, 3, 51, 77.78174593052023},
    PredefinedNote{"e3", NoteSymbol::e, 3, 52, 82.4068892282175},
    PredefinedNote{"f3", NoteSymbol::f, 3, 53, 87.30705785825097},
    PredefinedNote{"f#3", NoteSymbol::fSharp, 3, 54, 92.4986056779086},
    PredefinedNote{"g3", NoteSymbol::g, 3, 55, 97.99885899543733},
    PredefinedNote{"g#3", NoteSymbol::gSharp, 3, 56, 103.82617439498628},
    PredefinedNote{"a3", NoteSymbol::a, 3, 57, 110},
    PredefinedNote{"a#3", NoteSymbol::aSharp, 3, 58, 116.54094037952248},
    PredefinedNote{"b3", NoteSymbol::b, 3, 59, 123.47082531403103},
    PredefinedNote{"c4", NoteSymbol::c, 4, 60, 130.8127826502993},
    PredefinedNote{"c#4", NoteSymbol::cSharp, 4, 61, 138.59131548843604},
    PredefinedNote{"d4", NoteSymbol::d, 4, 62, 146.8323839587038},
    PredefinedNote{"d#4", NoteSymbol::dSharp, 4, 63, 155.56349186104046},
    PredefinedNote{"e4", NoteSymbol::e, 4, 64, 164.81377845643496},
    PredefinedNote{"f4", NoteSymbol::f, 4, 65, 174.61411571650194},
    PredefinedNote{"f#4", NoteSymbol::fSharp, 4, 66, 184.9972113558172},
    PredefinedNote{"g4", NoteSymbol::g, 4, 67, 195.99771799087463},
    PredefinedNote{"g#4", NoteSymbol::gSharp, 4, 68, 207.65234878997256},
    PredefinedNote{"a4", NoteSymbol::a, 4, 69, 220},
    PredefinedNote{"a#4", NoteSymbol::aSharp, 4, 70, 233.08188075904496},
    PredefinedNote{"b4", NoteSymbol::b, 4, 71, 246.94165062806206},
    PredefinedNote{"c5", NoteSymbol::c, 5, 72, 261.6255653005986},
    PredefinedNote{"c#5", NoteSymbol::cSharp, 5, 73, 277.1826309768721},
    PredefinedNote{"d5", NoteSymbol::d, 5, 74, 293.6647679174076},
    PredefinedNote{"d#5", NoteSymbol::dSharp, 5, 75, 311.1269837220809},
    PredefinedNote{"e5", NoteSymbol::e, 5, 76, 329.6275569128699},
    PredefinedNote{"f5", NoteSymbol::f, 5, 77, 349.2282314330039},
    PredefinedNote{"f#5", NoteSymbol::fSharp, 5, 78, 369.9944227116344},
    PredefinedNote{"g5", NoteSymbol::g, 5, 79, 391.99543598174927},
    PredefinedNote{"g#5", NoteSymbol::gSharp, 5, 80, 415.3046975799451},
    PredefinedNote{"a5", NoteSymbol::a, 5, 81, 440},
    PredefinedNote{"a#5", NoteSymbol::aSharp, 5, 82, 466.1637615180899},
    PredefinedNote{"b5", NoteSymbol::b, 5, 83, 493.8833012561241},
    PredefinedNote{"c6", NoteSymbol::c, 6, 84, 523.2511306011972},
    PredefinedNote{"c#6", NoteSymbol::cSharp, 6, 85, 554.3652619537442},
    PredefinedNote{"d6", NoteSymbol::d, 6, 86, 587.3295358348151},
    PredefinedNote{"d#6", NoteSymbol::dSharp, 6, 87, 622.2539674441618},
    PredefinedNote{"e6", NoteSymbol::e, 6, 88, 659.2551138257398},
    PredefinedNote{"f6", NoteSymbol::f, 6, 89, 698.4564628660078},
    PredefinedNote{"f#6", NoteSymbol::fSharp, 6, 90, 739.9888454232688},
    PredefinedNote{"g6", NoteSymbol::g, 6, 91, 783.9908719634985},
    PredefinedNote{"g#6", NoteSymbol::gSharp, 6, 92, 830.6093951598903},
    PredefinedNote{"a6", NoteSymbol::a, 6, 93, 880},
    PredefinedNote{"a#6", NoteSymbol::aSharp, 6, 94, 932.3275230361799},
    PredefinedNote{"b6", NoteSymbol::b, 6, 95, 987.7666025122483},
    PredefinedNote{"c7", NoteSymbol::c, 7, 96, 1046.5022612023945},
    PredefinedNote{"c#7", NoteSymbol::cSharp, 7, 97, 1108.7305239074883},
    PredefinedNote{"d7", NoteSymbol::d, 7, 98, 1174.6590716696303},
    PredefinedNote{"d#7", NoteSymbol::dSharp, 7, 99, 1244.5079348883237},
    PredefinedNote{"e7", NoteSymbol::e, 7, 100, 1318.5102276514797},
    PredefinedNote{"f7", NoteSymbol::f, 7, 101, 1396.9129257320155},
    PredefinedNote{"f#7", NoteSymbol::fSharp, 7, 102, 1479.9776908465376},
    PredefinedNote{"g7", NoteSymbol::g, 7, 103, 1567.981743926997},
    PredefinedNote{"g#7", NoteSymbol::gSharp, 7, 104, 1661.2187903197805},
    PredefinedNote{"a7", NoteSymbol::a, 7, 105, 1760},
    PredefinedNote{"a#7", NoteSymbol::aSharp, 7, 106, 1864.6550460723597},
    PredefinedNote{"b7", NoteSymbol::b, 7, 107, 1975.533205024496},
    PredefinedNote{"c8", NoteSymbol::c, 8, 108, 2093.004522404789},
    PredefinedNote{"c#8", NoteSymbol::cSharp, 8, 109, 2217.4610478149766},
    PredefinedNote{"d8", NoteSymbol::d, 8, 110, 2349.31814333926},
    PredefinedNote{"d#8", NoteSymbol::dSharp, 8, 111, 2489.0158697766474},
    PredefinedNote{"e8", NoteSymbol::e, 8, 112, 2637.02045530296},
    PredefinedNote{"f8", NoteSymbol::f, 8, 113, 2793.825851464031},
    PredefinedNote{"f#8", NoteSymbol::fSharp, 8, 114, 2959.955381693075},
    PredefinedNote{"g8", NoteSymbol::g, 8, 115, 3135.9634878539946},
    PredefinedNote{"g#8", NoteSymbol::gSharp, 8, 116, 3322.437580639561},
    PredefinedNote{"a8", NoteSymbol::a, 8, 117, 3520},
    PredefinedNote{"a#8", NoteSymbol::aSharp, 8, 118, 3729.3100921447194},
    PredefinedNote{"b8", NoteSymbol::b, 8, 119, 3951.066410048992},
    PredefinedNote{"c9", NoteSymbol::c, 9, 120, 4186.009044809578},
    PredefinedNote{"c#9", NoteSymbol::cSharp, 9, 121, 4434.922095629953},
    PredefinedNote{"d9", NoteSymbol::d, 9, 122, 4698.63628667852},
    PredefinedNote{"d#9", NoteSymbol::dSharp, 9, 123, 4978.031739553295},
    PredefinedNote{"e9", NoteSymbol::e, 9, 124, 5274.04091060592},
    PredefinedNote{"f9", NoteSymbol::f, 9, 125, 5587.651702928062},
    PredefinedNote{"f#9", NoteSymbol::fSharp, 9, 126, 5919.91076338615},
    PredefinedNote{"g9", NoteSymbol::g, 9, 127, 6271.926975707989},
    PredefinedNote{"g#9", NoteSymbol::gSharp, 9, 128, 6644.875161279122},
    PredefinedNote{"a9", NoteSymbol::a, 9, 129, 7040},
    PredefinedNote{"a#9", NoteSymbol::aSharp, 9, 130, 7458.620184289437},
    PredefinedNote{"b9", NoteSymbol::b, 9, 131, 7902.132820097988},
    PredefinedNote{"c10", NoteSymbol::c, 10, 132, 8372.018089619156},
    PredefinedNote{"c#10", NoteSymbol::cSharp, 10, 133, 8869.844191259906},
    PredefinedNote{"d10", NoteSymbol::d, 10, 134, 9397.272573357044},
    PredefinedNote{"d#10", NoteSymbol::dSharp, 10, 135, 9956.06347910659},
    PredefinedNote{"e10", NoteSymbol::e, 10, 136, 10548.081821211836},
    PredefinedNote{"f10", NoteSymbol::f, 10, 137, 11175.303405856126},
    PredefinedNote{"f#10", NoteSymbol::fSharp, 10, 138, 11839.8215267723},
    PredefinedNote{"g10", NoteSymbol::g, 10, 139, 12543.853951415975},
    PredefinedNote{"g#10", NoteSymbol::gSharp, 10, 140, 13289.750322558246},
    PredefinedNote{"a10", NoteSymbol::a, 10, 141, 14080},
    PredefinedNote{"a#10", NoteSymbol::aSharp, 10, 142, 14917.240368578874},
    PredefinedNote{"b10", NoteSymbol::b, 10, 143, 15804.265640195976},
    PredefinedNote{"c11", NoteSymbol::c, 11, 144, 16744.036179238312},
    PredefinedNote{"c#11", NoteSymbol::cSharp, 11, 145, 17739.688382519813},
    PredefinedNote{"d11", NoteSymbol::d, 11, 146, 18794.54514671409},
    PredefinedNote{"d#11", NoteSymbol::dSharp, 11, 147, 19912.12695821318},
    PredefinedNote{"e11", NoteSymbol::e, 11, 148, 21096.16364242367},
    PredefinedNote{"f11", NoteSymbol::f, 11, 149, 22350.606811712252},
    PredefinedNote{"f#11", NoteSymbol::fSharp, 11, 150, 23679.6430535446},
    PredefinedNote{"g11", NoteSymbol::g, 11, 151, 25087.70790283195},
    PredefinedNote{"g#11", NoteSymbol::gSharp, 11, 152, 26579.50064511649},
    PredefinedNote{"a11", NoteSymbol::a, 11, 153, 28160},
    PredefinedNote{"a#11", NoteSymbol::aSharp, 11, 154, 29834.480737157748},
    PredefinedNote{"b11", NoteSymbol::b, 11, 155, 31608.53128039195},
};


class PredefinedNotes{
public:

    const static vector<PredefinedNote> &getNotes(){
        return predefinedNotesVector;
    }

    static PredefinedNote *findNoteByNoteSymbolAndOctave(const NoteSymbol& noteSymbol, const int& octave){
        for(auto & note : predefinedNotesVector){
            if(note.noteSymbol == noteSymbol && note.octave == octave){
                return &note;
            }
        }
        return nullptr;
    }

    static bool isNoteOn88KeyKeyboard(const PredefinedNote& note){
        return note.midiNoteNumber >= 21 && note.midiNoteNumber <= 108;
    }

    /**
     * When we want to get a predefined note with random octave for a note symbol.
     * Useful when randomizing the voicings of a chord.
     * @param noteSymbol
     * @param minOctave
     * @param maxOctave
     * @return
     */
    static PredefinedNote createNoteWithRandomOctave(const NoteSymbol& noteSymbol, const int& minOctave, const int& maxOctave){
        int octave = Util::generateRandomNumber(minOctave, maxOctave);
        // console.error(`octave is : ${octave}`);
        auto note = findNoteByNoteSymbolAndOctave(noteSymbol, octave);
        //if the random octave isn't on the keyboard, try min then max
        if(note && !isNoteOn88KeyKeyboard(*note)){
            //find lowest note for note symbol that is on the keyboard
            PredefinedNote* lowestNoteOnKeyboard;
            for(int i = minOctave; i <= maxOctave; ++i){
                auto n = findNoteByNoteSymbolAndOctave(noteSymbol, i);
                if(n && isNoteOn88KeyKeyboard(*n)){
                    lowestNoteOnKeyboard = n;
                    break;
                }
            }
            //find highest note for note symbol on the keyboard
            PredefinedNote* highestNoteOnKeyboard;
            for(int i = maxOctave; i >= minOctave; --i){
                auto n = findNoteByNoteSymbolAndOctave(noteSymbol, i);
                if(n && isNoteOn88KeyKeyboard(*n)){
                    highestNoteOnKeyboard = n;
                    break;
                }
            }
            if(lowestNoteOnKeyboard && highestNoteOnKeyboard){
                octave = Util::generateRandomNumber(lowestNoteOnKeyboard->octave, highestNoteOnKeyboard->octave);
                note = findNoteByNoteSymbolAndOctave(noteSymbol, octave);
            }
        }
        return *note;
    }

    static PredefinedNote *getNoteByMidiNoteNumber(const int& midiNoteNumber){
        for(auto & note : predefinedNotesVector){
            if(note.midiNoteNumber == midiNoteNumber){
                return &note;
            }
        }
        return nullptr;
    }

    static vector<PredefinedNote> getNotesStartingAtRootNote(const NoteSymbol& rootNoteSymbol, const vector<PredefinedNote>& predefinedNotesParam = predefinedNotesVector){
        int beginIndex = 0;
        int endIndex = predefinedNotesParam.size();
        for(int i = 0; i < predefinedNotesParam.size(); ++i){
            auto note = predefinedNotesParam[i];
            if(note.noteSymbol == rootNoteSymbol){
                beginIndex = i;
                break;
            }
        }
        auto first = predefinedNotesParam.begin() + beginIndex;
        auto last = predefinedNotesParam.begin() + endIndex;
        return vector<PredefinedNote>(first, last);
    }

    static vector<PredefinedNote> getNotesWithinOctaveRange(const int& minOctave, const int& maxOctave){
        vector<PredefinedNote> result = {};
        for(auto & note : predefinedNotesVector){
            if(note.octave >= minOctave && note.octave <= maxOctave){
                result.push_back(note);
            }
        }
        return result;
    }

    static PredefinedNote flattenNote(const PredefinedNote& note){
        //find the index
        vector<PredefinedNote>::iterator it = std::find(predefinedNotesVector.begin(), predefinedNotesVector.end(), note);
        if(it != predefinedNotesVector.end()){ // If element is found then it returns an iterator to the first element in the given range that’s equal to given element, else it returns an end of the list
            auto index = std::distance(predefinedNotesVector.begin(), it);
            auto newIndex = index - 1 >= 0 ? index - 1 : 0;
            auto flattenedNote = predefinedNotesVector[newIndex];
            return flattenedNote;
        }
        return note;
    }

    static PredefinedNote sharpenNote(const PredefinedNote& note){
        vector<PredefinedNote>::iterator it = std::find(predefinedNotesVector.begin(), predefinedNotesVector.end(), note);
        if(it != predefinedNotesVector.end()){ // If element is found then it returns an iterator to the first element in the given range that’s equal to given element, else it returns an end of the list
            auto index = std::distance(predefinedNotesVector.begin(), it);
            auto newIndex = index + 1 >= predefinedNotesVector.size() ? predefinedNotesVector.size() - 1 : index + 1;
            auto sharpenedNote = predefinedNotesVector[newIndex];
            return sharpenedNote;
        }
        return note;
    }
};

//
//static optional<PredefinedNote> findNoteByNoteSymbolAndOctave(NoteSymbol noteSymbol, int octave){
//    for(auto & note : predefinedNotesVector){
//        if(note.noteSymbol == noteSymbol && note.octave == octave){
//            return note;
//        }
//    }
//    return nullopt;
//}

//
//static optional<PredefinedNote> getNoteById(string id){
//    for(auto & note : predefinedNotesVector){
//        if(note.id == id){
//            return note;
//        }
//    }
//    return nullopt;
//}