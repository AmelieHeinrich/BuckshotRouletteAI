//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:09:14
//

#pragma once

#include <random>
#include <algorithm>

namespace util
{
    int RandomInt(int nMin, int nMax);

    template<typename Iterator>
    void ShuffleArray(Iterator iBegin, Iterator iEnd)
    {
        static std::random_device RandomDevice;
        static std::mt19937 Generator(RandomDevice());

        std::shuffle(iBegin, iEnd, Generator);
    }
}
