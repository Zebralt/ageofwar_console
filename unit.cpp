#include "unit.hpp"

    UnitModel::UnitModel(std::string name, int maxHP, int price, int attackScore, int range, int exclusiveRange) {

        this->name = name;
        this->maxHP = maxHP;
        this->price = price;
        this->attackScore = attackScore;
        this->range = range;
        this->exclusiveRange = exclusiveRange;

    }

    Unit::Unit(Player& player, UnitModel& um) : owner(player), model(um) {
        health = maxHP;
    }

    std::vector<Unit*> Unit::checkLineOfSight(std::vector<Unit*> units) {

    }

    bool Unit::attack(Unit& unit) {
        // if unit is in los
        // else return false

        // if unit is not dead
        // else return false

        unit.takeDamage(model.attackScore);
    }

    void Unit::advance(Game& g) {

    }

    int Unit::engage(Game& game) {
        std::vector<Unit*> potential_targets = checkLineOfSight(game.getUnits());
    }

    void Unit::takeDamage(int damage) {
        // apply damage modifiers if there is any ?
        health -= damage;
    }

    bool Unit::alive() {
        return health > 0;
    }
