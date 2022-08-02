#include "PCH.h"
#pragma once

namespace App
{
    void resetFile(std::string fileName);
    void ComputeHands(std::string fileName, Deck deck, int start, int end, int *handcount);
}