//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:02:06
//

#pragma once

#include "shotgun.h"
#include "player.h"
#include "human_player.h"
#include "ai_player.h"

static constexpr bool PLAYER_TURN = false;
static constexpr bool DEALER_TURN = true;

class CGame
{
public:
    CGame();
    ~CGame();

    void Run();

private:
    bool GameDone();
    void DoTurn();

    CShotgun* pShotgun;
    IPlayer* pPlayerOne;
    IPlayer* pPlayerTwo;

    /// NOTE(ame): false is player's turn, true is dealer's turn
    bool bTurn = PLAYER_TURN;
    int nTurnCount = 0;
};
