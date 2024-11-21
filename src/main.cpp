//
// $Notice: Xander Studios @ 2024
// $Author: Amélie Heinrich
// $Create Time: 2024-11-21 12:57:05
//

#include "game.h"

int main(void)
{
    CGame* pGame = new CGame();
    pGame->Run();
    delete pGame;
    return 0;
}
