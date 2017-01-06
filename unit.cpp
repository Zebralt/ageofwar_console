#include "model.hpp"
#include "game.hpp"
#include "unit.hpp"

    /// UNIT : CLASS

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

    int Unit::engage(Game& g) {
        return 1;
    }

    /// COMBAT UNIT MODEL : CLASS

    /* Prend :
    - units : le tableau d'unités de game
    - ptr : pointeur sur la première unité du joueur opposé
    - direction : la direction dans laquelle regarder (correspond au joueur) : 1 = blue, 0 = red
    */
    std::vector<Unit*> CombatUnit::checkLineOfSight(Unit* units, int cursor, int direction) {
        std::vector<Unit*> spotted;
        CombatUnitModel& mod = dynamic_cast<CombatUnitModel&>(model);
        /*for (std::vector<Unit*>::iterator it = units.begin(); it != units.end(); ++it) {
            if ((*it)->getPosition() > mod.exclusiveRange && (*it)->getPosition() <= mod.range)
                spotted.push_back(*it);
        }*/
        for (int i=mod.exclusiveRange;i<mod.range;i++) {
            if (direction) { if (i + pos >= cursor) {
                spotted.push_back(&units[cursor + i]);
            }}
            else if (pos - i < cursor) {
                spotted.push_back(&units[cursor - i]);
            }

        }
        return spotted;
    }

    bool CombatUnit::attack(Unit& unit) {
        if (!remainingActions) return 0;
        if (unit.alive()) {
            unit.takeDamage(dynamic_cast<CombatUnitModel&>(model).attackScore);
            return true;
        }
        else {
            return false;
        }
    }

    bool CombatUnit::advance(Game& g) {
        if (!remainingActions) return 0;
        int newpos = pos + (&owner==&g.getBlue()?1:-1);
        if (g.checkPosition(newpos)) {
            return false;
        }
        else {
            pos = newpos;
        }
        return true;
    }

    int CombatUnit::engage(Game& game) {
       std::vector<Unit*> potential_targets = checkLineOfSight(game.getUnits(),game.getEnemyCursor(owner),game.getDirection(owner));
        if (potential_targets.size()) {
            for (std::vector<Unit*>::iterator it = potential_targets.begin(); it != potential_targets.end(); ++it) {
                if (attack(**it)) return 1 + (*it)->alive();
            }
        }
        return 0;
    }

