//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:30:33
//

#pragma once

#include <string>
#include <array>

#include "shotgun.h"

enum class EPlayerItem
{
    NONE,
    CIGARETTE,
    MAGNIFYING_GLASS,
    BEER,
    HANDCUFFS,
    HANDSAW
};

enum class EPlayerAction
{
    SHOOT_YOURSELF,
    SHOOT_OPPONENT
};

struct TurnResult
{
    EPlayerAction eAction;
    bool bHandcuffedOpponent = false;
    bool bUsedHandsaw = false;
};

class IPlayer
{
public:
    void Initialize();
    void FillItems();

    void SetName(const std::string& sInputName) { sName = sInputName; }
    std::string GetName() const { return sName; }

    bool IsDead() { return nLives == 0; }
    void AddLife() { nLives += 1; }
    int GetLives() const { return nLives; }
    void RemoveLife() { nLives -= 1; }

    bool DoAction(CShotgun* pShotgun, IPlayer* pOtherPlayer);
    virtual TurnResult GetAction(CShotgun* pShotgun, IPlayer* pOtherPlayer) = 0;
protected:
    std::array<EPlayerItem, 4> stlItems;

    std::string sName;
    int nLives = 4;
};
