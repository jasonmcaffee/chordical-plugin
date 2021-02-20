#pragma once
#include "../../Models/Scale/ScaleType.h"
#include<unordered_map>
#include<vector>
using namespace std;

unordered_map<ScaleType, vector<int>> scaleNoteIndexes = {
        { ScaleType::chromatic, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 } },
        { ScaleType::majorIonian, { 0, 2, 4, 5, 7, 9, 11 } },
        { ScaleType::naturalMinorAeolian, { 0, 2, 3, 5, 7, 8, 10 } },
        { ScaleType::majorPentatonic, { 0, 2, 4, 7, 9 } },
        { ScaleType::minorPentatonic, { 0, 3, 5, 7, 10 } },
        { ScaleType::dorian, { 0, 2, 3, 5, 7, 9, 10 } },
        { ScaleType::greekDorianPhrygian, { 0, 1, 3, 5, 7, 8, 10 } },
        { ScaleType::lydian, { 0, 2, 4, 6, 7, 9, 11 } },
        { ScaleType::mixolydian, { 0, 2, 4, 5, 7, 9, 10 } },
        { ScaleType::locrian, { 0, 1, 3, 5, 6, 8, 10 } },
        { ScaleType::ascendingMelodicMinor, { 0, 2, 3, 5, 7, 9, 11 } },
        { ScaleType::hexatonicBlues, { 0, 3, 5, 6, 7, 10 } },
        { ScaleType::heptatonicBlues, { 0, 2, 3, 5, 6, 9, 10 } },
        { ScaleType::nonatonicBlues, { 0, 2, 3, 4, 5, 7, 9, 10 } },
        { ScaleType::acoustic, { 0, 2, 4, 6, 7, 9, 10 } },
        { ScaleType::algerian, { 0, 2, 3, 6, 7, 8, 11 } },
        { ScaleType::altered, { 0, 1, 3, 4, 6, 8, 10 } },
        { ScaleType::augmented, { 0, 3, 4, 7, 8, 11 } },
        { ScaleType::bebopMajor, { 0, 2, 4, 5, 7, 8, 9, 11 } },
        { ScaleType::bebopDominant, { 0, 2, 4, 5, 7, 9, 10, 11 } },
        { ScaleType::bebopMinor, { 0, 2, 3, 5, 7, 9, 10, 11 } },
        { ScaleType::doubleHarmonic, { 0, 1, 4, 5, 7, 8, 11 } },
        { ScaleType::enigmatic, { 0, 1, 4, 6, 8, 10, 11 } },
        { ScaleType::eulerFokker, { 0, 2, 5, 7, 10, 11 } },
        { ScaleType::flamenco, { 0, 1, 4, 5, 7, 8, 11 } },
        { ScaleType::gypsy, { 0, 2, 3, 6, 7, 8, 10 } },
        { ScaleType::halfDiminished, { 0, 2, 3, 5, 6, 8, 10 } },
        { ScaleType::harmonicMajor, { 0, 2, 4, 5, 7, 8, 11 } },
        { ScaleType::harmonicMinor, { 0, 2, 3, 5, 7, 8, 11 } },
        { ScaleType::hirajoshi, { 0, 4, 6, 7, 11 } },
        { ScaleType::hungarianGypsy, { 0, 2, 3, 6, 7, 8, 11 } },
        { ScaleType::hungarianMinor, { 0, 2, 3, 6, 7, 8, 11 } },
        { ScaleType::in_, { 0, 1, 5, 7, 8 } },
        { ScaleType::insen, { 0, 1, 5, 7, 10 } },
        { ScaleType::iwato, { 0, 1, 5, 6, 10 } },
        { ScaleType::lydianAugmented, { 0, 2, 4, 6, 8, 9, 11 } },
        { ScaleType::neapolitanMajor, { 0, 1, 3, 5, 7, 9, 11 } },
        { ScaleType::neapolitanMinor, { 0, 1, 3, 5, 7, 8, 11 } },
        { ScaleType::persian, { 0, 1, 4, 5, 6, 8, 11 } },
        { ScaleType::phrygrianDominant, { 0, 1, 4, 5, 7, 8, 10 } },
        { ScaleType::prometheus, { 0, 2, 4, 6, 9, 10 } },
        { ScaleType::tritone, { 0, 1, 4, 6, 7, 10 } },
        { ScaleType::ukranianDorian, { 0, 2, 3, 6, 7, 9, 10 } },
        { ScaleType::yo, { 0, 3, 5, 7, 10 } }
};

class Scales{
public:
    static vector<int> getScaleNoteIndexes(const ScaleType& scaleType){
        auto noteIndexes = scaleNoteIndexes[scaleType];
        return noteIndexes;
    }

    static vector<PredefinedNote> getNotesForKey(const ScaleType& scaleType, const NoteSymbol& rootNote, const vector<PredefinedNote>& predefinedNotesParam = PredefinedNotes::getNotes()){
        auto notes = PredefinedNotes::getNotesStartingAtRootNote(rootNote, predefinedNotesParam);
        auto noteIndexes = getScaleNoteIndexes(scaleType);
        vector<PredefinedNote> result = {};
        int currentIndex = 0;
        for(auto & note : notes){
            if(std::find(noteIndexes.begin(), noteIndexes.end(), currentIndex++) != noteIndexes.end()){ //if the index is in the noteIndexes, then the note belongs to the key
                result.push_back(note);
            }
            if(currentIndex > 11){//set back to 0 once we complete an octave.
                currentIndex = 0;
            }
        }
        return result;
    }


};