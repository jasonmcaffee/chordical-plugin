#pragma once
#include <JuceHeader.h>
#include "../Services/Music/PredefinedNotes.h"
#include "../Services/Music/Scales.h"
#include "../Services/Music/Chords.h"
#include "../Factories/PredefinedNoteFactory.h"
#include "../Factories/ChordFactory.h"
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

        chord = Chords::ChordFuncs::minor(NoteSymbol::c, 0);
        expectEquals(chord.rootNote, NoteSymbol::c);
        expectEquals(chord.octave, 0);
        expectEquals((int)chord.notes.size(), 3);
        expectEquals(chord.notes[0].noteSymbol, NoteSymbol::c);
        expectEquals(chord.notes[1].noteSymbol, NoteSymbol::dSharp);
        expectEquals(chord.notes[2].noteSymbol, NoteSymbol::g);

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

        chord = Chords::ChordFuncs::major(NoteSymbol::d, 0);
        expectEquals(chord.rootNote, NoteSymbol::d);
        expectEquals(chord.octave, 0);
        expectEquals((int)chord.notes.size(), 3);
        expectEquals(chord.notes[0].noteSymbol, NoteSymbol::d);
        expectEquals(chord.notes[1].noteSymbol, NoteSymbol::fSharp);
        expectEquals(chord.notes[2].noteSymbol, NoteSymbol::a);

        chord = Chords::createChord("major", "c", 0);
        expectEquals(chord.rootNote, NoteSymbol::c);
        expectEquals(chord.octave, 0);
        expectEquals((int)chord.notes.size(), 3);
        expectEquals(chord.notes[0].noteSymbol, NoteSymbol::c);
        expectEquals(chord.notes[1].noteSymbol, NoteSymbol::e);
        expectEquals(chord.notes[2].noteSymbol, NoteSymbol::g);

        chord = Chords::createChord("minor", "d", 0);
        expectEquals(chord.rootNote, NoteSymbol::d);
        expectEquals(chord.octave, 0);
        expectEquals((int)chord.notes.size(), 3);
        expectEquals(chord.notes[0].noteSymbol, NoteSymbol::d);
        expectEquals(chord.notes[1].noteSymbol, NoteSymbol::f);
        expectEquals(chord.notes[2].noteSymbol, NoteSymbol::a);

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