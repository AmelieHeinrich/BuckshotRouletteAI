//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:30:33
//

#pragma once

#include <string>

#include "shotgun.h"

enum EPlayerAction
{
    ShootYourself,
    ShootOpponent,
    // TODO: add items
};

class IPlayer
{
public:
    void SetName(const std::string& sInputName) { sName = sInputName; }
    std::string GetName() const { return sName; }

    bool IsDead() { return nLives == 0; }

    int GetLives() const { return nLives; }
    void RemoveLife() { nLives -= 1; }

    bool DoAction(CShotgun* pShotgun, IPlayer* pOtherPlayer);

    // Returns true if you shot yourself with a blank
    virtual EPlayerAction GetAction(CShotgun* pShotgun, IPlayer* pOtherPlayer) = 0;
protected:
    std::string sName;
    int nLives = 4;
};
