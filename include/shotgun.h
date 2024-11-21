//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:04:02
//

#pragma once

#include <stack>
#include <vector>

enum class EBulletType
{
    BLANK,
    LIVE
};

class CShotgun
{
public:
    CShotgun();
    ~CShotgun();

    void Generate(int nBulletCount);

    int GetBulletCount() { return stlChamber.size(); }

    /// NOTE(ame): Used to implement the magnifying glass item
    EBulletType ShowNextBullet();
    EBulletType PopBullet();
private:
    std::stack<EBulletType> stlChamber;
};
