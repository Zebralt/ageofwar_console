#include <iostream>
#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

struct Point { int* x; int* y;};

int main()
{
    Human red("Red");
    Human blue("Blue");
    Game aowg(red,blue);

    // main loop would look like this :

    while(!aowg.hasEnded()) {
        aowg.display();
        aowg.runPhases(aowg.getBlue());
    }

    Player& winner = aowg.getWinner();
    std::cout << winner << " won the game." << std::endl;

    return 0;
}

/*
Entity {
    - position
    - name
    - health
    - EntityModel& (limited by subclasses constructors)

    + int : takeDamage();

}

Building : Entity {

}

Unit : Entity {

    + void : move();
}

Factory { // is like an interface, i guess ...
    - list(Model&) // list products

    + bool : purchase(Model&)
    + std::vector<Model> : checkInventory()
    + int : produce(Model&)
    + std::vector<Model> : queue()
}

Damager {

}

Model {
    - price
    - name
    - desc

}

EntityModel : Model {
    - healthMax
    - range (min/max)
}

Model : EntityModel {

}

BuildingModel :     EntityModel {

}

FactoryBuildingModel : BuildingModel, Factory {

}

AttackBuildingModel : Damager, BuildingModel {

}

PowerUpModel : Model { // ?

}

*/
