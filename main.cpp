#include <iostream>
#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"x

int main()
{
    Player red("Satan");
    Player blue("Lucifer");
    AgeOfWarGame aowg(red,blue);

    aowg.addUnitModel(UnitModel("Base",100,0,1,1,0));

    return 0;
}
