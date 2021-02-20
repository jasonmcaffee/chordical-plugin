#pragma once

#include "../Note/NoteSymbol.h"
#include "../Scale/ScaleType.h"

class KeySignature{
public:
    NoteSymbol rootNote;
    ScaleType scale;
};