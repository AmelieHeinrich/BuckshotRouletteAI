//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 13:44:53
//

#include <iostream>

#include "player.h"

bool IPlayer::DoAction(CShotgun* pShotgun, IPlayer* pOtherPlayer)
{
    EPlayerAction eAction = GetAction(pShotgun, pOtherPlayer);

    if (eAction == EPlayerAction::ShootOpponent)
    {
        EBulletType eBullet = pShotgun->PopBullet();
        if (eBullet == EBulletType::BLANK)
        {
            std::cout << "Shot opponent with blank." << std::endl;
            return false;
        }
        if (eBullet == EBulletType::LIVE)
        {
            pOtherPlayer->RemoveLife();
            std::cout << "Shot opponent with live. Opponent now has " << pOtherPlayer->GetLives() << " lives left." << std::endl;
            return false;
        }
    }
    else if (eAction == EPlayerAction::ShootYourself)
    {
        EBulletType eBullet = pShotgun->PopBullet();
        if (eBullet == EBulletType::BLANK)
        {
            std::cout << "Shot yourself with blank. You get another turn." << std::endl;
            return true;
        }
        if (eBullet == EBulletType::LIVE)
        {
            this->RemoveLife();
            std::cout << "Shot yourself with live. You now have " << this->GetLives() << " lives left." << std::endl;
            return false;
        }
    }

    return false;
}
