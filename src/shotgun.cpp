//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:06:22
//

#include <cstdio>
#include <algorithm>
#include <random>

#include "shotgun.h"
#include "util.h"

CShotgun::CShotgun()
{

}

CShotgun::~CShotgun()
{
    
}

void CShotgun::Generate(int nBulletCount)
{
    int nBlankCount = 0;
    int nLiveCount = 0;

    while ((nBlankCount + nLiveCount) != nBulletCount)
    {
        nBlankCount = util::RandomInt(1, nBulletCount - 1);
        nLiveCount = util::RandomInt(1, nBulletCount - 1);
    }

    std::printf("%d blanks. %d lives. All cartridges are inserted in a random order.\n", nBlankCount, nLiveCount);

    /// NOTE(ame): Generate random chamber
    std::vector<EBulletType> stlTempChamber;
    for (int iBullet = 0; iBullet < nBlankCount; iBullet++)
    {
        stlTempChamber.push_back(EBulletType::BLANK);
    }
    for (int iBullet = 0; iBullet < nLiveCount; iBullet++)
    {
        stlTempChamber.push_back(EBulletType::LIVE);
    }
    util::ShuffleArray(stlTempChamber.begin(), stlTempChamber.end());

    for (auto& eBullet : stlTempChamber)
    {
        stlChamber.push(eBullet);
    }
}

EBulletType CShotgun::ShowNextBullet()
{
    return stlChamber.top();
}

EBulletType CShotgun::PopBullet()
{
    EBulletType top = ShowNextBullet();
    stlChamber.pop();
    return top;
}
