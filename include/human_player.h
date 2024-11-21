//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:33:29
//

#pragma once

#include "player.h"

class CHumanPlayer : public IPlayer
{
public:
    EPlayerAction GetAction(CShotgun* pShotgun, IPlayer* pOtherPlayer) override;
};
