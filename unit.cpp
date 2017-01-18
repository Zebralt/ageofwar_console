#include "model.hpp"
#include "game.hpp"
#include "unit.hpp"

#include <iostream>

    /// UNIT : CLASS

    Unit::Unit(Player& player, Model& um) : model(um), owner(player) {
        health = um.maxHP;
    }

    Unit::Unit(Unit const& u) : model(u.model), owner(u.owner) {
        health = u.health;
        pos = u.pos;
        remainingActions = u.remainingActions;
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

//    int Unit::getPosition() {
//        return pos;
//    }

    void Unit::setModel(Model& m) {
        model = m;
    }

    int Unit::haveRemainingActions() {
        return remainingActions;
    }

    /* Prend :
    - units : le tableau d'unités de game
    - ptr : pointeur sur la première unité du joueur opposé
    - direction : la direction dans laquelle regarder (correspond au joueur) : 1 = blue, 0 = red
    */
    std::vector<std::shared_ptr<Unit>> Unit::checkLineOfSight(std::vector<std::shared_ptr<Unit>> units, int pos, int cursor, int direction) {
        std::vector<std::shared_ptr<Unit>> spotted;
        short ratio = (direction?1:-1);
        if ( // si on n'atteint meme pas la premiere unite ennemie
            (direction && pos + ratio < cursor)
        ||  (!direction && pos + ratio > cursor)
        ) {
            return spotted;
        }
        for (int i=model.minimumRange; i<model.range;i++) {
            if ((direction && pos + ratio >= cursor) || (!direction && pos + ratio <= cursor)) {
                //if (units[i] != nullptr) spotted.push_back(units[i]);
                // TODO
            }
        }
        return spotted;
    }

    bool Unit::attack(Unit& unit) {
        if (!remainingActions) return 0;
        if (unit.alive()) {
            unit.takeDamage(model.attackScore);
            return true;
        }
        else {
            return false;
        }
    }

    bool Unit::advance(Game& g) {
        if (!remainingActions) return 0;
        int newpos = pos + (owner==g.getBlue()?1:-1);
        std::cout << toString() << ": trying to move from " << pos << " to " << newpos << std::endl;
        if (g.positionTaken(newpos)) {
            return false;
        }
        else {
            pos = newpos;
            return true;
        }
    }

    int Unit::engage(Game& game) {
       std::vector<std::shared_ptr<Unit>> potential_targets = checkLineOfSight(game.getUnits(), pos, game.getEnemyCursor(owner),game.getDirection(owner));
        if (potential_targets.size()) {
            for (std::vector<std::shared_ptr<Unit>>::iterator it = potential_targets.begin(); it != potential_targets.end(); ++it) {
                if (attack(**it)) return 1 + (*it)->alive();
                //TODO
            }
        }
        return 0;
    }

    bool Unit::checkForEnemyCastle(Game& game) {
        int dir = game.getDirection(owner);
        if ((dir && game.getEnemyCursor(owner) < 0) || (!dir && game.getEnemyCursor(owner) >= game.getBattlefieldLength())) {
            if ((dir && pos + model.range >= game.getBattlefieldLength()-1) || (!dir && pos - model.range <= 0)) {
                attackEnemyCastle(game);
                return true;
            }
        }
        return false;
    }

    bool Unit::attackEnemyCastle(Game& game) {
        return game.damageCastle(owner, model.attackScore);
    }

    std::string Unit::toString() {
        std::string fin;
        fin += getName() + "(" + std::to_string(pos) + ")";
        return fin;
    }

   /* std::ostream& operator<<(std::ostream& o, const Unit& u) {
        o << u.toString();
        return o;
    }*/
