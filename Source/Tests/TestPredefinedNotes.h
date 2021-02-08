#pragma once
#include <JuceHeader.h>
#include "../Services/Music/PredefinedNotes.h"

class TestPredefinedNotes  : public UnitTest
{
public:
    TestPredefinedNotes()  : UnitTest ("PredefinedNotes") {}

    void runTest() override
    {
        std::cout << "RUNNING TESTS" << std::endl;

        beginTest ("Part 1");
        auto predefinedNotes = PredefinedNotes::getNotes();
        expectEquals((int)predefinedNotes.size(), 144);


        beginTest ("Part 2");

    }
};

// Creating a static instance will automatically add the instance to the array
// returned by UnitTest::getAllTests(), so the test will be included when you call
// UnitTestRunner::runAllTests()
static TestPredefinedNotes test;