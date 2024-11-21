//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:34:05
//

#include <iostream>
#include <string>

#include "human_player.h"

EPlayerAction CHumanPlayer::GetAction(CShotgun* pShotgun, IPlayer* pOtherPlayer)
{
    EPlayerAction eAction;

    bool bValidInput = false;
    while (!bValidInput)
    {
        std::string Input;
        std::cout << sName << ": 'ME' to shoot yourself, 'YOU' to shoot the other." << std::endl;
        std::cin >> Input;

        if (Input == "ME")
        {
            eAction = EPlayerAction::ShootYourself;
        }
        if (Input == "YOU")
        {
            eAction = EPlayerAction::ShootOpponent;
        }
        bValidInput = (Input == "ME" || Input == "YOU");
    }

    return eAction;
}
