
#include "game.hpp"
#include "unit.hpp"

    UnitModel::UnitModel(std::string name, int maxHP, int price, int attackScore, int range, int exclusiveRange) {

        this->name = name;
        this->maxHP = maxHP;
        this->price = price;
        this->attackScore = attackScore;
        this->range = range;
        this->exclusiveRange = exclusiveRange;

    }

    int UnitModel::getMaxHealth() {
        return maxHP;
    }

    Unit::Unit(Player& player, UnitModel& um) : owner(player), model(um) {
        health = um.maxHP;
    }

    std::vector<Unit*> Unit::checkLineOfSight(std::vector<Unit*> units) {
        std::vector<Unit*> spotted;
        for (std::vector<Unit*>::iterator it = units.begin(); it != units.end(); ++it) {
            if ((*it)->getPosition() > model.exclusiveRange && (*it)->getPosition() <= model.range)
                spotted.push_back(*it);
        }
        return spotted;
    }

    bool Unit::attack(Unit& unit) {
        if (unit.alive()) {
            unit.takeDamage(model.attackScore);
            return true;
        }
        else {
            return false;
        }
    }

    bool Unit::advance(Game& g) {
        int newpos = pos + 1;
        if (g.checkPosition(newpos)) {
            return false;
        }
        else {
            pos = newpos;
        }
    }

    int Unit::engage(Game& game) {
    // 0 no action
    // 1 attack successful;
    // 2 attack successful; killed target
    // 4 moved
        std::vector<Unit*> potential_targets = checkLineOfSight(game.getUnits());
        if (potential_targets.size()) {
            for (std::vector<Unit*>::iterator it = potential_targets.begin(); it != potential_targets.end(); ++it) {
                if (attack(**it)) return 1 + (*it)->alive();
            }
        }
        else { // try to move
            return advance(game)*4;
        }
        return 0;
    }

    void Unit::takeDamage(int damage) {
        // apply damage modifiers if there is any ?
        health -= damage;
    }

    bool Unit::alive() {
        return health > 0;
    }

    int Unit::getHealth() {
        return health;
    }

    int Unit::getPosition() {
        return pos;
    }
