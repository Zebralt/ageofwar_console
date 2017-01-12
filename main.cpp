#include <iostream>
#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

int main()
{
    AI red("Red");
    AI blue("Blue");
    Game aowg(red,blue);

    // main loop would look like this :

    while(!aowg.hasEnded()) {
        aowg.display();
        std::cout << std::endl;
        aowg.update();
        std::cout << std::endl;
    }

    Player& winner = aowg.getWinner();
    std::cout << winner << " won the game." << std::endl;

    return 0;
}
