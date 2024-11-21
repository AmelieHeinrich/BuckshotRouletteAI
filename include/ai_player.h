//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 14:45:32
//

#pragma once

#include "player.h"

class CAIPlayer : public IPlayer
{
public:
    TurnResult GetAction(CShotgun* pShotgun, IPlayer* pOtherPlayer) override;

private:
    bool HasItemAndUse(EPlayerItem eItem);
};
