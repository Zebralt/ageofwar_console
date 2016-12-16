#include <iostream>
#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

struct Point { int* x; int* y;};

Point get() {
    int a = 2;
    int b = 5;
    Point p; p.x = &a; p.y = &b;
    return p;
}

int main()
{
    Human red("Satan");
    Human blue("Lucifer");
    Game aowg(red,blue,100);

    aowg.addUnitModel(UnitModel("Base",100,0,1,1,0));

    // main loop would look like this :

    while(!aowg.hasEnded()) {

    }

    Player& winner = aowg.getWinner();
    std::cout << winner << " won the game." << std::endl;

    Point p = get();
    std::cout << *(p.x) << std::endl;
    std::string n = "ae"; std::string m = "bb"; char c = 'x';
    std::cout << n+m+c << std::endl;
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

UnitModel : EntityModel {

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
