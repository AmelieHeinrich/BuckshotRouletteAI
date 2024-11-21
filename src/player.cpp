//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:44:53
//

#include <iostream>

#include "player.h"
#include "util.h"

static constexpr std::array<EPlayerItem, 5> POSSIBLE_ITEMS =
{
    EPlayerItem::CIGARETTE,
    EPlayerItem::MAGNIFYING_GLASS,
    EPlayerItem::BEER,
    EPlayerItem::HANDCUFFS,
    EPlayerItem::HANDSAW
};

void IPlayer::Initialize()
{
    std::fill(stlItems.begin(), stlItems.end(), EPlayerItem::NONE);
}

void IPlayer::FillItems()
{
    for (auto& eItem : stlItems)
    {
        if (eItem == EPlayerItem::NONE)
        {
            eItem = POSSIBLE_ITEMS[util::RandomInt(0, POSSIBLE_ITEMS.size() - 1)];
        }
    }
}

bool IPlayer::DoAction(CShotgun* pShotgun, IPlayer* pOtherPlayer)
{
    TurnResult Result = GetAction(pShotgun, pOtherPlayer);

    if (Result.eAction == EPlayerAction::SHOOT_OPPONENT)
    {
        EBulletType eBullet = pShotgun->PopBullet();
        if (eBullet == EBulletType::BLANK)
        {
            std::cout << "Shot opponent with blank." << std::endl;
            return false || Result.bHandcuffedOpponent;
        }
        if (eBullet == EBulletType::LIVE)
        {
            if (Result.bUsedHandsaw)
            {
                pOtherPlayer->RemoveLife();
                pOtherPlayer->RemoveLife();
            }
            else
            {
                pOtherPlayer->RemoveLife();
            }
            std::cout << "Shot opponent with live. Opponent now has " << pOtherPlayer->GetLives() << " lives left." << std::endl;
            return false || Result.bHandcuffedOpponent;
        }
    }
    else if (Result.eAction == EPlayerAction::SHOOT_YOURSELF)
    {
        EBulletType eBullet = pShotgun->PopBullet();
        if (eBullet == EBulletType::BLANK)
        {
            std::cout << "Shot yourself with blank. You get another turn." << std::endl;
            return true || Result.bHandcuffedOpponent;
        }
        if (eBullet == EBulletType::LIVE)
        {
            if (Result.bUsedHandsaw)
            {
                this->RemoveLife();
                this->RemoveLife();
            }
            else
            {
                this->RemoveLife();
            }
            std::cout << "Shot yourself with live. You now have " << this->GetLives() << " lives left." << std::endl;
            return false || Result.bHandcuffedOpponent;
        }
    }

    return false || Result.bHandcuffedOpponent;
}
