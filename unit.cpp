#include "model.hpp"
#include "game.hpp"
#include "unit.hpp"

    Unit::Unit(Player& player, Model& um) : model(um), owner(player) {
        health = um.maxHP;
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

    void Unit::setModel(Model& m) {
        model = m;
    }

    std::vector<Unit*> HostileUnit::checkLineOfSight(std::vector<Unit*> units) {
        std::vector<Unit*> spotted;
        HostileModel& mod = dynamic_cast<HostileModel&>(model);
        for (std::vector<Unit*>::iterator it = units.begin(); it != units.end(); ++it) {
            if ((*it)->getPosition() > mod.exclusiveRange && (*it)->getPosition() <= mod.range)
                spotted.push_back(*it);
        }
        return spotted;
    }

    bool HostileUnit::attack(Unit& unit) {
        if (unit.alive()) {
            unit.takeDamage(dynamic_cast<HostileModel&>(model).attackScore);
            return true;
        }
        else {
            return false;
        }
    }

    int Unit::engage(Game& game) {
       /* std::vector<Unit*> potential_targets = checkLineOfSight(game.getUnits());
        if (potential_targets.size()) {
            for (std::vector<Unit*>::iterator it = potential_targets.begin(); it != potential_targets.end(); ++it) {
                if (attack(**it)) return 1 + (*it)->alive();
            }
        }
        else { // try to move
            return advance(game)*4;
        }*/
        return 0;
    }

    bool MobileUnit::advance(Game& g) {
        int newpos = pos + (&owner==&g.getBlue()?1:-1);
        if (g.checkPosition(newpos)) {
            return false;
        }
        else {
            pos = newpos;
        }
        return true;
    }

