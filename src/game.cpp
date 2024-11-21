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

    pPlayerTwo = new CHumanPlayer;
    pPlayerTwo->SetName("Player Two");
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
    }

    bool bTurnResult = false;

    if (bTurn == PLAYER_TURN)
    {
        bTurnResult = pPlayerOne->DoAction(pShotgun, pPlayerTwo);
    }
    else if (bTurn == DEALER_TURN)
    {
        bTurnResult = pPlayerTwo->DoAction(pShotgun, pPlayerOne);
    }
    std::cout << std::endl;

    if (!bTurnResult)
    {
        bTurn = !bTurn;
    }
}
