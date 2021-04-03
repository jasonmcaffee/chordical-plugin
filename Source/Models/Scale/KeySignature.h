#pragma once

#include "../Note/NoteSymbol.h"
#include "../Scale/ScaleType.h"
#include <cereal/archives/json.hpp>

class KeySignature{
public:
    NoteSymbol rootNote;
    ScaleType scale;

//    template<class Archive>
//    void serialize(Archive & archive)
//    {
//        archive(
//                cereal::make_nvp("rootNote", rootNote),
//                cereal::make_nvp("scale", scale)
//                );
//    }
};