//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:09:33
//

#include "util.h"

int util::RandomInt(int nMin, int nMax)
{
    static std::random_device RandomDevice;
    static std::mt19937 Generator(RandomDevice());

    std::uniform_int_distribution<int> Distribution(nMin, nMax);

    return Distribution(Generator);
}
