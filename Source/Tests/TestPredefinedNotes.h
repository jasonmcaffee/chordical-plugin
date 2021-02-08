#pragma once
#include <JuceHeader.h>
#include "../Services/Music/PredefinedNotes.h"

class TestPredefinedNotes  : public UnitTest
{
public:
    TestPredefinedNotes()  : UnitTest ("PredefinedNotes") {}

    void runTest() override
    {
        beginTest ("Part 1");

        auto predefinedNote = PredefinedNotes::findNoteByNoteSymbolAndOctave(NoteSymbol::c, 0);
        expectEquals(predefinedNote->octave, 0);
        expectEquals(predefinedNote->noteSymbol, NoteSymbol::c);

        auto note = PredefinedNotes::createNoteWithRandomOctave(NoteSymbol::dSharp, 0, 1);
        expectEquals(note.noteSymbol, NoteSymbol::dSharp);
        expect((note.octave == 0) || (note.octave == 1));

        note = PredefinedNotes::createNoteWithRandomOctave(NoteSymbol::g, 0, 1);
        expectEquals(note.noteSymbol, NoteSymbol::g);
        expect((note.octave == 1));//should always be 1 since a0 is not on 88 key keyboard

        beginTest ("Part 2");

    }
};

// Creating a static instance will automatically add the instance to the array
// returned by UnitTest::getAllTests(), so the test will be included when you call
// UnitTestRunner::runAllTests()
static TestPredefinedNotes test;