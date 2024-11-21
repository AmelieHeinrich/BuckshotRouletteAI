//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:34:05
//

#include <iostream>
#include <string>

#include "human_player.h"

std::string ItemToString(EPlayerItem eItem)
{
    switch (eItem)
    {
        case EPlayerItem::CIGARETTE:
            return "Cigarette";
        case EPlayerItem::MAGNIFYING_GLASS:
            return "Magnifying Glass";
        case EPlayerItem::BEER:
            return "Beer";
        case EPlayerItem::HANDCUFFS:
            return "Handcuffs";
        case EPlayerItem::HANDSAW:
            return "Handsaw";
        case EPlayerItem::NONE:
            return "";
    }
    return "";
}

TurnResult CHumanPlayer::GetAction(CShotgun* pShotgun, IPlayer* pOtherPlayer)
{
    TurnResult Result = {};

    bool bEndOfTurn = false;
    while (!bEndOfTurn)
    {
        std::string Input;
        std::cout << sName << ": 'ME' to shoot yourself, 'YOU' to shoot the other. 'M' for magnifying glass, 'C' for cigarette, 'B' for beer, 'S' for handsaw and 'H' for handcuffs." << std::endl;
        std::cout << "Your items: ";
        for (auto eItem : stlItems)
        {
            std::string sItemString = ItemToString(eItem);
            if (!sItemString.empty()) {
                std::cout << sItemString << ", ";
            }
        }
        std::cout << std::endl;

        std::cin >> Input;

        // shoot you
        if (Input == "ME")
        {
            Result.eAction = EPlayerAction::SHOOT_YOURSELF;
        }

        // shoot opponent
        if (Input == "YOU")
        {
            Result.eAction = EPlayerAction::SHOOT_OPPONENT;
        }

        // handle magnifying glass
        if (Input == "M")
        {
            bool bLookedBullet = false;
            for (auto& eItem : stlItems)
            {
                if (eItem == EPlayerItem::MAGNIFYING_GLASS)
                {
                    eItem = EPlayerItem::NONE;
                    std::cout << "Next bullet in barrel is... " << (pShotgun->ShowNextBullet() == EBulletType::BLANK ? "blank." : "live.") << std::endl;
                    bLookedBullet = true;
                    break;
                }
            }

            if (!bLookedBullet)
            {
                std::cout << "You don't have a magnifying glass" << std::endl;
            }
        }

        // handle cigarette
        if (Input == "C")
        {
            bool bSmokedCigarette = false;
            for (auto& eItem : stlItems)
            {
                if (eItem == EPlayerItem::CIGARETTE)
                {
                    eItem = EPlayerItem::NONE;
                    std::cout << GetName() << " smokes a cigarette. You gain a life." << std::endl;
                    bSmokedCigarette = true;
                    break;
                }
            }

            if (!bSmokedCigarette)
            {
                std::cout << "You don't have a cigarette to smoke." << std::endl;
            }
        }

        // handle beer
        if (Input == "B")
        {
            bool bDrankBeer = false;
            for (auto& eItem : stlItems)
            {
                if (eItem == EPlayerItem::BEER)
                {
                    eItem = EPlayerItem::NONE;
                    std::cout << "Next bullet in barrel is... " << (pShotgun->ShowNextBullet() == EBulletType::BLANK ? "blank." : "live.") << std::endl;
                    std::cout << "Popped bullet." << std::endl;
                    pShotgun->PopBullet();
                    bDrankBeer = true;
                    break;
                }
            }

            if (!bDrankBeer)
            {
                std::cout << "You don't have a beer to drink." << std::endl;
            }
        }

        // handle handsaw
        if (Input == "S")
        {
            if (!Result.bUsedHandsaw)
            {
                bool bCutBarrel = false;
                for (auto& eItem : stlItems)
                {
                    if (eItem == EPlayerItem::HANDSAW)
                    {
                        eItem = EPlayerItem::NONE;
                        std::cout << "Used handsaw. Next bullet will do twice as much damage." << std::endl;
                        Result.bUsedHandsaw = true;
                        bCutBarrel = true;
                        break;
                    }
                }

                if (!bCutBarrel)
                {
                    std::cout << "You don't have a handsaw." << std::endl;
                }
            }
            else
            {
                std::cout << "Already used handsaw." << std::endl;
            }
        }

        // handle handcuffs
        if (Input == "H")
        {
            if (!Result.bHandcuffedOpponent)
            {
                bool bCuffedOpponent = false;
                for (auto& eItem : stlItems)
                {
                    if (eItem == EPlayerItem::HANDCUFFS)
                    {
                        eItem = EPlayerItem::NONE;
                        std::cout << "Used handcuffs. Next turn will be yours no matter the output." << std::endl;
                        Result.bHandcuffedOpponent = true;
                        bCuffedOpponent = true;
                        break;
                    }
                }

                if (!bCuffedOpponent)
                {
                    std::cout << "You don't have handcuffs." << std::endl;
                }
            }
            else
            {
                std::cout << "Already handcuffed opponent." << std::endl;
            }
        }

        // end the turn
        bEndOfTurn = (Input == "ME" || Input == "YOU");
    }

    return Result;
}
