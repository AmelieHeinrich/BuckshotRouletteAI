//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:03:24
//

#include <iostream>

#include "game.h"

CGame::CGame()
{
    pShotgun = new CShotgun();

    pPlayerOne = new CHumanPlayer;
    pPlayerOne->SetName("Player One");
    pPlayerOne->Initialize();

    pPlayerTwo = new CAIPlayer;
    pPlayerTwo->SetName("AI Player");
    pPlayerTwo->Initialize();
}

CGame::~CGame()
{
    delete pPlayerTwo;
    delete pPlayerOne;
    delete pShotgun;
}

void CGame::Run()
{
    while (!GameDone())
    {
        DoTurn();
    }

    if (pPlayerOne->IsDead())
    {
        std::cout << "Victory for " << pPlayerTwo->GetName();
    }

    if (pPlayerTwo->IsDead())
    {
        std::cout << "Victory for " << pPlayerOne->GetName();
    }
}

bool CGame::GameDone()
{
    return pPlayerOne->IsDead() || pPlayerTwo->IsDead();
}

void CGame::DoTurn()
{   
    if (pShotgun->GetBulletCount() == 0) {
        std::cout << std::endl;
        pShotgun->Generate(5);

        std::cout << "Giving items..." << std::endl;
        pPlayerOne->FillItems();
        pPlayerTwo->FillItems();
        std::cout << std::endl;
    }
    std::cout << "TURN " << nTurnCount << std::endl;

    bool bTurnResult = false;
    IPlayer* pNextPlayer = bTurn == PLAYER_TURN ? pPlayerOne : pPlayerTwo;
    IPlayer* pOtherPlayer = pNextPlayer == pPlayerOne ? pPlayerTwo : pPlayerOne;

    std::cout << "NEXT UP: " << pNextPlayer->GetName() << std::endl;
    bTurnResult = pNextPlayer->DoAction(pShotgun, pOtherPlayer);

    if (!bTurnResult)
    {
        bTurn = !bTurn;
    }
    nTurnCount++;
    std::cout << std::endl;
}
