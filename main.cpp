#include <iostream>
#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

using namespace std;

int main()
{
    Player red("Satan");
    Player blue("Lucifer");
    AgeOfWarGame aowg(red,blue);
    return 0;
}
