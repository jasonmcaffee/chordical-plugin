#pragma once
#include <JuceHeader.h>
#include "../Services/Music/PredefinedNotes.h"
#include "../Services/Music/Scales.h"
#include "../Services/Music/Chords.h"
#include "../Factories/PredefinedNoteFactory.h"
#include "../Factories/ChordFactory.h"
#include "../Factories/SlotFactory.h"
#include "../Models/Preset/Slot.h"
#include "../Factories/KeySignatureGroupFactory.h"
#include "../Factories/KeySignatureFactory.h"
#include "../Models/Scale/KeySignature.h"
#include "../Models/Preset/KeySignatureGroup.h"
#include "../Models/Preset/Preset.h"
#include "../Factories/PresetFactory.h"
#include "../Models/Chord/ChordType.h"

#include <JuceHeader.h>
#include <vector>
using namespace juce;
using namespace std;

class TestPredefinedNotes  : public UnitTest
{
public:
    TestPredefinedNotes()  : UnitTest ("PredefinedNotes") {}

    void runTest() override
    {
        testPredefinedNotes();
        testScales();
        testChords();
        testFactories();
    }

    void testFactories(){
        beginTest("Factories");
        testPredefinedNotesFactory();
        testChordFactory();
        testSlotFactory();
        keySignatureFactory();
        keySignatureGroupFactory();
        presetFactory();
    }

    void presetFactory(){
        auto chord = Chords::ChordFuncs::major(NoteSymbol::c, 0);
        int midiNoteTrigger = 11;
        int qwertyKeyCodeTrigger = 12;
        auto slot = Slot{chord, midiNoteTrigger, qwertyKeyCodeTrigger};
        vector<Slot> slots = {slot};
        auto key = KeySignature {NoteSymbol::c, ScaleType::majorIonian};
        auto k1 = KeySignatureGroup {"id", slots, key, 1, 1,};
        vector<KeySignatureGroup> keySignatureGroups = {k1};

        auto preset = Preset {"id", keySignatureGroups};
        auto presetString = PresetFactory::toJSONString(preset);
        auto parsedPreset = PresetFactory::fromJSONString(presetString);

        expectEquals(preset.id, parsedPreset.id);
        expectEquals(preset.keySignatureGroups.size(), parsedPreset.keySignatureGroups.size());
        expectEquals(preset.keySignatureGroups[0].id, parsedPreset.keySignatureGroups[0].id);
        expectEquals(preset.keySignatureGroups[0].keySignature.rootNote, parsedPreset.keySignatureGroups[0].keySignature.rootNote);
        expectEquals(preset.keySignatureGroups[0].slots.size(), parsedPreset.keySignatureGroups[0].slots.size());
    }

    void keySignatureGroupFactory(){
        beginTest("KeySignatureGroupFactory");
        auto chord = Chords::ChordFuncs::major(NoteSymbol::c, 0);
        int midiNoteTrigger = 11;
        int qwertyKeyCodeTrigger = 12;
        auto slot = Slot{chord, midiNoteTrigger, qwertyKeyCodeTrigger};
        vector<Slot> slots = {slot};
        auto key = KeySignature {NoteSymbol::c, ScaleType::majorIonian};
        auto k1 = KeySignatureGroup {"id", slots, key, 1, 1,};

        auto kString = KeySignatureGroupFactory::toJSONString(k1);
        auto parsedK1 = KeySignatureGroupFactory::fromJSONString(kString);
        expectEquals(k1.id, parsedK1.id);
        expectEquals(k1.randomizationMinOctave, parsedK1.randomizationMinOctave);
        expectEquals(k1.randomizationMaxOctave, parsedK1.randomizationMaxOctave);
        expectEquals(k1.keySignature.scale, parsedK1.keySignature.scale);
        expectEquals(k1.keySignature.rootNote, parsedK1.keySignature.rootNote);
        expectEquals(k1.slots.size(), parsedK1.slots.size());
        expectEquals(k1.slots[0].chord.rootNote, parsedK1.slots[0].chord.rootNote);

    }
    void keySignatureFactory(){
        beginTest("KeySignatureFactory");
        auto key = KeySignature {NoteSymbol::c, ScaleType::majorIonian};
        auto keyString = KeySignatureFactory::toJSONString(key);
        auto parsedKey = KeySignatureFactory::fromJSONString(keyString);
        expectEquals(key.rootNote, parsedKey.rootNote);
        expectEquals(key.scale, parsedKey.scale);
    }

    void testSlotFactory(){
        beginTest("SlotFactory");
        auto chord = Chords::ChordFuncs::major(NoteSymbol::c, 0);
        int midiNoteTrigger = 11;
        int qwertyKeyCodeTrigger = 12;
        auto slot = Slot{chord, midiNoteTrigger, qwertyKeyCodeTrigger};
        String slotString = SlotFactory::toJSONString(slot);
        auto parsedSlot = SlotFactory::fromJSONString(slotString);
        expectEquals(slot.chord.id, parsedSlot.chord.id);
        expectEquals(slot.chord.rootNote, parsedSlot.chord.rootNote);
        expectEquals(slot.chord.notes.size(), parsedSlot.chord.notes.size());
        expectEquals(slot.qwertyKeyCodeTrigger, parsedSlot.qwertyKeyCodeTrigger);
        expectEquals(slot.midiNoteTrigger, parsedSlot.midiNoteTrigger);

        auto chord2 = Chords::ChordFuncs::major(NoteSymbol::c, 0);
        int midiNoteTrigger2 = 11;
        int qwertyKeyCodeTrigger2 = 12;
        auto slot2 = Slot{chord2, midiNoteTrigger2, qwertyKeyCodeTrigger2};

        vector<Slot> slots = {slot, slot2};
        String slotsString = SlotFactory::toJSONString(slots);
        auto parsedSlots = SlotFactory::fromJsonStringArray(slotsString);
        expectEquals(slots.size(), parsedSlots.size());
        expectEquals(slots[0].chord.rootNote, parsedSlots[0].chord.rootNote);
        expectEquals(slots[0].chord.octave, parsedSlots[0].chord.octave);
        expectEquals(slots[0].chord.type, parsedSlots[0].chord.type);
        expectEquals(slots[1].chord.rootNote, parsedSlots[1].chord.rootNote);
        expectEquals(slots[1].chord.octave, parsedSlots[1].chord.octave);
        expectEquals(slots[1].chord.type, parsedSlots[1].chord.type);

    }

    void testChordFactory(){
        beginTest("ChordFactory");
        auto chord = Chords::ChordFuncs::major(NoteSymbol::c, 0);
        String chordString = ChordFactory::toJsonString(chord);
        auto parsedChord = ChordFactory::fromJSONString(chordString);
        expectEquals(chord.id, parsedChord.id);
        expectEquals(chord.label, parsedChord.label);
        expectEquals(chord.octave, parsedChord.octave);
        expectEquals(chord.rootNote, parsedChord.rootNote);
        expectEquals(chord.type, parsedChord.type);
        expectEquals(chord.notes.size(), parsedChord.notes.size());
        expectEquals(chord.notes[0].noteSymbol, parsedChord.notes[0].noteSymbol);
        expectEquals(chord.notes[1].noteSymbol, parsedChord.notes[1].noteSymbol);
        expectEquals(chord.notes[2].noteSymbol, parsedChord.notes[2].noteSymbol);

        auto chord2 = Chords::ChordFuncs::major(NoteSymbol::d, 0);
        vector<Chord> chords = {chord, chord2};
        auto chordsString = ChordFactory::toJsonString(chords);
        auto parsedChords = ChordFactory::fromJSONStringArray(chordsString);
        expectEquals(chords.size(), parsedChords.size());
        expectEquals(chords[0].notes.size(), parsedChords[0].notes.size());
        expectEquals(chords[1].notes.size(), parsedChords[1].notes.size());
        expectEquals(chords[0].notes[0].noteSymbol, parsedChords[0].notes[0].noteSymbol);
        expectEquals(chords[0].notes[1].noteSymbol, parsedChords[0].notes[1].noteSymbol);
        expectEquals(chords[1].notes[0].noteSymbol, parsedChords[1].notes[0].noteSymbol);
        expectEquals(chords[1].notes[1].noteSymbol, parsedChords[1].notes[1].noteSymbol);

    }

    void testPredefinedNotesFactory(){
        beginTest("PredefinedNotesFactory");
        auto note = PredefinedNote{"c0", NoteSymbol::c, 0, 12, 8.175798915643707};
        String noteString = PredefinedNoteFactory::toJSONString(note);
        auto parsedNote = PredefinedNoteFactory::fromJSONString(noteString);
        expectEquals(note.id, parsedNote.id);
        expectEquals(note.noteSymbol, parsedNote.noteSymbol);
        expectEquals(note.octave, parsedNote.octave);
        expectEquals(note.midiNoteNumber, parsedNote.midiNoteNumber);
        expectEquals(note.frequency, parsedNote.frequency);

        auto note2 = PredefinedNote{"d0", NoteSymbol::d, 0, 14, 9.177023997418988};
        vector<PredefinedNote> notes = {note, note2};
        String notesString = PredefinedNoteFactory::toJSONString(notes);
        auto parsedNotes = PredefinedNoteFactory::fromJSONStringArray(notesString);
        expectEquals(notes.size(), parsedNotes.size());
        expectEquals(notes[0].noteSymbol, parsedNotes[0].noteSymbol);
        expectEquals(notes[1].noteSymbol, parsedNotes[1].noteSymbol);
        expectEquals(notes[0].frequency, parsedNotes[0].frequency);
        expectEquals(notes[1].frequency, parsedNotes[1].frequency);
    }

    void testChords(){
        beginTest("Chords");
        auto notes = Chords::getMajorScaleNotesNeededToBuildAChordUsingScaleDegrees(NoteSymbol::c, 1);
        expectEquals(notes[0].noteSymbol, NoteSymbol::c);
        expectEquals(notes[0].octave, 1);
        expectEquals(notes[1].noteSymbol, NoteSymbol::d);
        expectEquals(notes[7].noteSymbol, NoteSymbol::c);
        expectEquals(notes[7].octave, 2);

        auto chord = Chords::ChordFuncs::major(NoteSymbol::c, 0);
        expectEquals(chord.rootNote, NoteSymbol::c);
        expectEquals(chord.octave, 0);
        expectEquals((int)chord.notes.size(), 3);
        expectEquals(chord.notes[0].noteSymbol, NoteSymbol::c);
        expectEquals(chord.notes[1].noteSymbol, NoteSymbol::e);
        expectEquals(chord.notes[2].noteSymbol, NoteSymbol::g);
        expectEquals(chord.type, chordTypeToFormattedString(ChordType::major));

        chord = Chords::ChordFuncs::minor(NoteSymbol::c, 0);
        expectEquals(chord.rootNote, NoteSymbol::c);
        expectEquals(chord.octave, 0);
        expectEquals((int)chord.notes.size(), 3);
        expectEquals(chord.notes[0].noteSymbol, NoteSymbol::c);
        expectEquals(chord.notes[1].noteSymbol, NoteSymbol::dSharp);
        expectEquals(chord.notes[2].noteSymbol, NoteSymbol::g);
        expectEquals(chord.type, chordTypeToFormattedString(ChordType::minor));

        chord = Chords::ChordFuncs::major13(NoteSymbol::c, 0);
        expectEquals(chord.rootNote, NoteSymbol::c);
        expectEquals(chord.octave, 0);
        expectEquals((int)chord.notes.size(), 6);
        expectEquals(chord.notes[0].noteSymbol, NoteSymbol::c);
        expectEquals(chord.notes[1].noteSymbol, NoteSymbol::e);
        expectEquals(chord.notes[2].noteSymbol, NoteSymbol::g);
        expectEquals(chord.notes[3].noteSymbol, NoteSymbol::b);
        expectEquals(chord.notes[4].noteSymbol, NoteSymbol::d);
        expectEquals(chord.notes[4].octave, 1);
        expectEquals(chord.notes[5].noteSymbol, NoteSymbol::a);
        expectEquals(chord.notes[5].octave, 1);
        expectEquals(chord.type, chordTypeToFormattedString(ChordType::major13));

        chord = Chords::ChordFuncs::major(NoteSymbol::d, 0);
        expectEquals(chord.rootNote, NoteSymbol::d);
        expectEquals(chord.octave, 0);
        expectEquals((int)chord.notes.size(), 3);
        expectEquals(chord.notes[0].noteSymbol, NoteSymbol::d);
        expectEquals(chord.notes[1].noteSymbol, NoteSymbol::fSharp);
        expectEquals(chord.notes[2].noteSymbol, NoteSymbol::a);
        expectEquals(chord.type, chordTypeToFormattedString(ChordType::major));

        chord = Chords::createChord("major", "c", 0);
        expectEquals(chord.rootNote, NoteSymbol::c);
        expectEquals(chord.octave, 0);
        expectEquals((int)chord.notes.size(), 3);
        expectEquals(chord.notes[0].noteSymbol, NoteSymbol::c);
        expectEquals(chord.notes[1].noteSymbol, NoteSymbol::e);
        expectEquals(chord.notes[2].noteSymbol, NoteSymbol::g);
        expectEquals(chord.type, chordTypeToFormattedString(ChordType::major));

        chord = Chords::createChord("minor", "d", 0);
        expectEquals(chord.rootNote, NoteSymbol::d);
        expectEquals(chord.octave, 0);
        expectEquals((int)chord.notes.size(), 3);
        expectEquals(chord.notes[0].noteSymbol, NoteSymbol::d);
        expectEquals(chord.notes[1].noteSymbol, NoteSymbol::f);
        expectEquals(chord.notes[2].noteSymbol, NoteSymbol::a);
        expectEquals(chord.type, chordTypeToFormattedString(ChordType::minor));

        auto cMajorNotes = Chords::getMajorScaleNotesNeededToBuildAChordUsingScaleDegrees(NoteSymbol::c, 1);
        chord = Chords::ChordFuncs::major(NoteSymbol::c, 1);

        bool result = Chords::doesChordContainOnlyTheseNotes(chord, cMajorNotes);
        expect(result == true);
        auto gSharpMajor = Chords::getMajorScaleNotesNeededToBuildAChordUsingScaleDegrees(NoteSymbol::gSharp, 1);
        result = Chords::doesChordContainOnlyTheseNotes(chord, gSharpMajor);
        expect(result == false);

        notes = Chords::getMajorScaleNotesNeededToBuildAChordUsingScaleDegrees(NoteSymbol::c, 1);
        auto chords = Chords::buildChordProgressionUsingAuto(notes);
        expect(chords.size() == 21); //notes spans 3 octaves. 7 notes in major. 7 x 3 = 21
        expectEquals(chords[0].rootNote, NoteSymbol::c);
        expectEquals(chords[0].octave, 1);
        expectEquals(chords[0].type, chordTypeToFormattedString(ChordType::major));
        expect(chords[0].notes.size() == 3);
        expectEquals(chords[1].rootNote, NoteSymbol::d);
        expectEquals(chords[1].octave, 1);
        expectEquals(chords[1].type, chordTypeToFormattedString(ChordType::minor));
        expect(chords[1].notes.size() == 3);
        expectEquals(chords[2].rootNote, NoteSymbol::e);
        expectEquals(chords[2].octave, 1);
        expectEquals(chords[2].type, chordTypeToFormattedString(ChordType::minor));
        expect(chords[2].notes.size() == 3);
        expectEquals(chords[3].rootNote, NoteSymbol::f);
        expectEquals(chords[3].octave, 1);
        expectEquals(chords[3].type, chordTypeToFormattedString(ChordType::major));
        expect(chords[3].notes.size() == 3);
        expectEquals(chords[4].rootNote, NoteSymbol::g);
        expectEquals(chords[4].octave, 1);
        expectEquals(chords[4].type, chordTypeToFormattedString(ChordType::major));
        expect(chords[4].notes.size() == 3);
        expectEquals(chords[5].rootNote, NoteSymbol::a);
        expectEquals(chords[5].octave, 1);
        expectEquals(chords[5].type, chordTypeToFormattedString(ChordType::minor));
        expect(chords[5].notes.size() == 3);
        expectEquals(chords[6].rootNote, NoteSymbol::b);
        expectEquals(chords[6].octave, 1);
        expectEquals(chords[6].type, chordTypeToFormattedString(ChordType::diminished));
        expect(chords[6].notes.size() == 3);

        chords = Chords::buildChordProgression(NoteSymbol::c, ScaleType::majorIonian, 1);
        expect(chords.size() == 7);
        expectEquals(chords[0].rootNote, NoteSymbol::c);
        expectEquals(chords[0].octave, 1);
        expectEquals(chords[0].type, chordTypeToFormattedString(ChordType::major));
        expect(chords[0].notes.size() == 3);
        expectEquals(chords[1].rootNote, NoteSymbol::d);
        expectEquals(chords[1].octave, 1);
        expectEquals(chords[1].type, chordTypeToFormattedString(ChordType::minor));
        expect(chords[1].notes.size() == 3);
        expectEquals(chords[2].rootNote, NoteSymbol::e);
        expectEquals(chords[2].octave, 1);
        expectEquals(chords[2].type, chordTypeToFormattedString(ChordType::minor));
        expect(chords[2].notes.size() == 3);
        expectEquals(chords[3].rootNote, NoteSymbol::f);
        expectEquals(chords[3].octave, 1);
        expectEquals(chords[3].type, chordTypeToFormattedString(ChordType::major));
        expect(chords[3].notes.size() == 3);
        expectEquals(chords[4].rootNote, NoteSymbol::g);
        expectEquals(chords[4].octave, 1);
        expectEquals(chords[4].type, chordTypeToFormattedString(ChordType::major));
        expect(chords[4].notes.size() == 3);
        expectEquals(chords[5].rootNote, NoteSymbol::a);
        expectEquals(chords[5].octave, 1);
        expectEquals(chords[5].type, chordTypeToFormattedString(ChordType::minor));
        expect(chords[5].notes.size() == 3);
        expectEquals(chords[6].rootNote, NoteSymbol::b);
        expectEquals(chords[6].octave, 1);
        expectEquals(chords[6].type, chordTypeToFormattedString(ChordType::diminished));
        expect(chords[6].notes.size() == 3);
    }

    void testScales(){
        beginTest ("Scales");
        auto noteIndexes = Scales::getScaleNoteIndexes(ScaleType::majorIonian);
        vector<int> majorIndexes = { 0, 2, 4, 5, 7, 9, 11 };
        expectEquals(noteIndexes.size(), majorIndexes.size());
        expectEquals(noteIndexes[0], majorIndexes[0]);
        expectEquals(noteIndexes[3], majorIndexes[3]);
        expectEquals(noteIndexes[4], majorIndexes[4]);

        auto notesForKey = Scales::getNotesForKey(ScaleType::majorIonian, NoteSymbol::c);
        expectEquals(notesForKey[0].noteSymbol, NoteSymbol::c);
        expectEquals(notesForKey[0].octave, 0);
        expectEquals(notesForKey[1].noteSymbol, NoteSymbol::d);
        expectEquals(notesForKey[2].noteSymbol, NoteSymbol::e);
        expectEquals(notesForKey[3].noteSymbol, NoteSymbol::f);
        expectEquals(notesForKey[4].noteSymbol, NoteSymbol::g);
        expectEquals(notesForKey[5].noteSymbol, NoteSymbol::a);
        expectEquals(notesForKey[6].noteSymbol, NoteSymbol::b);
        expectEquals(notesForKey[7].noteSymbol, NoteSymbol::c);
        expectEquals(notesForKey[7].octave, 1);
    }

    void testPredefinedNotes(){
        beginTest ("Predefined Notes");

        auto predefinedNote = PredefinedNotes::findNoteByNoteSymbolAndOctave(NoteSymbol::c, 0);
        expectEquals(predefinedNote->octave, 0);
        expectEquals(predefinedNote->noteSymbol, NoteSymbol::c);

        auto note = PredefinedNotes::createNoteWithRandomOctave(NoteSymbol::dSharp, 0, 1);
        expectEquals(note.noteSymbol, NoteSymbol::dSharp);
        expect((note.octave == 0) || (note.octave == 1));

        note = PredefinedNotes::createNoteWithRandomOctave(NoteSymbol::g, 0, 1);
        expectEquals(note.noteSymbol, NoteSymbol::g);
        expect((note.octave == 1));//should always be 1 since a0 is not on 88 key keyboard

        note = *PredefinedNotes::getNoteByMidiNoteNumber(108);
        expectEquals(note.noteSymbol, NoteSymbol::c);
        expectEquals(note.octave, 8);

        auto predefinedNotes = PredefinedNotes::getNotesStartingAtRootNote(NoteSymbol::c);
        expectEquals((int)predefinedNotes.size(), 144);
        expectEquals(predefinedNotes[0].noteSymbol, NoteSymbol::c);
        predefinedNotes = PredefinedNotes::getNotesStartingAtRootNote(NoteSymbol::d);
        expectEquals((int)predefinedNotes.size(), 142);
        expectEquals(predefinedNotes[0].noteSymbol, NoteSymbol::d);

        predefinedNotes = PredefinedNotes::getNotesWithinOctaveRange(0, 0);
        expectEquals((int)predefinedNotes.size(), 12);
        expectEquals(predefinedNotes[0].noteSymbol, NoteSymbol::c);

        //flatten note
        note = PredefinedNotes::getNotes()[1]; //cSharp 0
        auto flattenedNote = PredefinedNotes::flattenNote(note);
        expectEquals(flattenedNote.noteSymbol, NoteSymbol::c);
        expectEquals(flattenedNote.octave, 0);
        //if first note, flatten should return first note (rather than have to deal with null checking all the time)
        note = PredefinedNotes::getNotes()[0]; //c 0
        flattenedNote = PredefinedNotes::flattenNote(note);
        expectEquals(note.midiNoteNumber, flattenedNote.midiNoteNumber);

        //sharpen note
        note = PredefinedNotes::getNotes()[0]; //c 0
        auto sharpenedNote = PredefinedNotes::sharpenNote(note);
        expectEquals(sharpenedNote.noteSymbol, NoteSymbol::cSharp);
        expectEquals(sharpenedNote.octave, 0);
        //if last note, sharpen should return the last not (rather than have to deal with null checking all the time)
        note = PredefinedNotes::getNotes()[143];
        sharpenedNote = PredefinedNotes::sharpenNote(note);
        expectEquals(note.midiNoteNumber, sharpenedNote.midiNoteNumber);
    }
};

// Creating a static instance will automatically add the instance to the array
// returned by UnitTest::getAllTests(), so the test will be included when you call
// UnitTestRunner::runAllTests()
static TestPredefinedNotes test;