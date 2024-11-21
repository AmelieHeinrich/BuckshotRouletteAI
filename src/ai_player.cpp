//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 14:45:52
//

#include <iostream>

#include "ai_player.h"
#include "util.h"

enum class ELiveChance
{
    CERTAIN,
    LIKELY,
    EVEN,
    UNLIKELY,
    IMPOSSIBLE
};

std::string LiveChanceToString(ELiveChance eChance)
{
    switch (eChance)
    {
        case ELiveChance::CERTAIN:
            return "CERTAIN.";
        case ELiveChance::IMPOSSIBLE:
            return "IMPOSSIBLE.";
        case ELiveChance::LIKELY:
            return "LIKELY."; 
        case ELiveChance::UNLIKELY:
            return "UNLIKELY.";
        case ELiveChance::EVEN:
            return "EVEN.";
    }
    return "";
}

TurnResult CAIPlayer::GetAction(CShotgun* pShotgun, IPlayer* pOtherPlayer)
{
    TurnResult Result;

    bool bMadeMove = false;
    while (!bMadeMove)
    {
        std::cout << pShotgun->GetBlankCount() << " blanks, " << pShotgun->GetLiveCount() << " lives." << std::endl;
        std::cout << "Evaluating chances of next bullet being live..." << std::endl;

        // NOTE(ame): Calculate odds of current bullet being a live
        ELiveChance eChance;
        if (pShotgun->GetBlankCount() > pShotgun->GetLiveCount())
        {
            eChance = ELiveChance::UNLIKELY;
        }
        else if (pShotgun->GetLiveCount() > pShotgun->GetBlankCount())
        {
            eChance = ELiveChance::LIKELY;
        }
        else if (pShotgun->GetLiveCount() == 0)
        {
            eChance = ELiveChance::IMPOSSIBLE;
        }
        else if (pShotgun->GetBlankCount() == 0)
        {
            eChance = ELiveChance::CERTAIN;
        }
        else if (pShotgun->GetBlankCount() == pShotgun->GetLiveCount())
        {
            eChance = ELiveChance::EVEN;
        }
        std::cout << "Chances of next bullet being live is " << LiveChanceToString(eChance) << std::endl;

        if (HasItemAndUse(EPlayerItem::CIGARETTE))
        {
            std::cout << "AI uses cigarette." << std::endl;
            this->AddLife();
        }

        if (pShotgun->GetBulletCount() > 1)
        {
            if (HasItemAndUse(EPlayerItem::HANDCUFFS))
            {
                std::cout << "AI uses handcuffs." << std::endl;
                Result.bHandcuffedOpponent = true;
            }
        }

        if (eChance != ELiveChance::CERTAIN || eChance != ELiveChance::IMPOSSIBLE)
        {
            if (HasItemAndUse(EPlayerItem::MAGNIFYING_GLASS))
            {
                std::cout << "AI uses magnifying glass." << std::endl;
                EBulletType eType = pShotgun->ShowNextBullet();
                if (eType == EBulletType::BLANK)
                {
                    std::cout << "He sees a blank." << std::endl;
                    eChance = ELiveChance::IMPOSSIBLE;
                }
                else
                {
                    std::cout << "He sees a live." << std::endl;
                    eChance = ELiveChance::CERTAIN;
                }
            }
        }

        switch (eChance)
        {
            // In case its 100% sure its a live, use a handsaw if possible to maximize damage and shoot the human
            case ELiveChance::CERTAIN:
            {
                /// Use handsaw if possible
                if (HasItemAndUse(EPlayerItem::HANDSAW))
                {
                    std::cout << "AI uses handsaw." << std::endl;
                    Result.bUsedHandsaw = true;
                }
                Result.eAction = EPlayerAction::SHOOT_OPPONENT;
                bMadeMove = true;
                break;
            }
            // In case it's 100% a blank, shoot yourself
            case ELiveChance::IMPOSSIBLE:
            {
                Result.eAction = EPlayerAction::SHOOT_YOURSELF;
                bMadeMove = true;
                break;
            };
            // In case it's likely a live, just shoot the opponent
            case ELiveChance::LIKELY:
            {
                Result.eAction = EPlayerAction::SHOOT_OPPONENT;
                bMadeMove = true;
                break;
            };
            // In case it's unlikely a live, use an item if you can, otherwise just pick what is the best
            case ELiveChance::UNLIKELY:
            {
                bool bUsedItem = false;
                if (HasItemAndUse(EPlayerItem::BEER))
                {
                    std::cout << "AI used beer." << std::endl;
                    bUsedItem = true;
                }

                if (!bUsedItem)
                {
                    Result.eAction = EPlayerAction::SHOOT_YOURSELF;
                    bMadeMove = true;
                }
                break;
            };
            // In case it's odd, use an item or take the 50/50
            case ELiveChance::EVEN:
            {
                bool bUsedItem = false;
                if (HasItemAndUse(EPlayerItem::BEER))
                {
                    std::cout << "AI used beer." << std::endl;
                    bUsedItem = true;
                }

                if (!bUsedItem)
                {
                    // Coinflip
                    int nChoice = util::RandomInt(0, 1);
                    Result.eAction = nChoice == 0 ? EPlayerAction::SHOOT_YOURSELF : EPlayerAction::SHOOT_OPPONENT;
                    bMadeMove = true;
                }
                break;
            }
        }
    }

    return Result;
}

bool CAIPlayer::HasItemAndUse(EPlayerItem eItem)
{
    for (auto& eElement : stlItems)
    {
        if (eElement == eItem)
        {
            eElement = EPlayerItem::NONE;
            return true;
        }
    }
    return false;
}
