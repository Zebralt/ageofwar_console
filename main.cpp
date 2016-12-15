#include <iostream>
#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

int main()
{
    Human red("Satan");
    Human blue("Lucifer");
    Game aowg(red,blue,100);

    aowg.addUnitModel(UnitModel("Base",100,0,1,1,0));

    std::cout << true+4 << std::endl;
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

BuildingModel : EntityModel {

}

FactoryBuildingModel : BuildingModel, Factory {

}

AttackBuildingModel : Damager, BuildingModel {

}

PowerUpModel : Model { // ?

}

*/
