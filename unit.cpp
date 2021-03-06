#include "model.hpp"
#include "game.hpp"
#include "unit.hpp"
#include "player.hpp"

#include <iostream>
#include <iomanip>

	int Unit::instanceCount = 0;

    /// UNIT : CLASS

    Unit::Unit(Player& player, Model& um) : model(um), owner(player) {
        health = um.maxHP;
        remainingActions = um.nbActions;
        id = instanceCount++;
    }

    Unit::Unit(Unit const& u) : model(u.model), owner(u.owner) {
        health = u.health;
        pos = u.pos;
        remainingActions = u.remainingActions;
        id = instanceCount++;
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
    - units : le tableau d'unit�s de game
    - ptr : pointeur sur la premi�re unit� du joueur oppos�
    - direction : la direction dans laquelle regarder (correspond au joueur) : 1 = blue, 0 = red
    */
    std::vector<unit_ptr> Unit::checkLineOfSight(Game& game) {
        std::vector<unit_ptr> spotted;
        int dir = (game.getDirection(owner) ? 1 : -1);
        int len = game.getBattlefieldLength();
        int start = (dir ? 0 : len-1);

        // CURSORS ?
        /*short ratio = (direction?1:-1);
        if ( // si on n'atteint meme pas la premiere unite ennemie
            (direction && pos + ratio < cursor)
        ||  (!direction && pos + ratio > cursor)
        ) {
            return spotted;
        }*/
		for (int i=model.minimumRange; i<=model.range; i++) {
			unit_ptr unit = game.getUnitAt(pos+i*dir);
			if (unit != nullptr) {
				if (!(unit->getOwner() == owner)) {
					spotted.push_back(unit);
				}
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
        if (g.positionTaken(newpos) || newpos == (owner == g.getBlue()?g.getBattlefieldLength()-1:0)) {
            return false;
        }
        else {
			if (g.VERBOSE) std::cout << '\t' << toString() << " moves to " << std::to_string(newpos) << std::endl;
            pos = newpos;
            return true;
        }
    }

    int Unit::engage(Game& game) {
		std::vector<std::shared_ptr<Unit>> potential_targets = checkLineOfSight(game);
		if (potential_targets.size()) {
			if (game.VERBOSE) {
				std::cout << '\t' << toString() << " spotted " << potential_targets.size() << " enemies :" << std::endl;
				//std::cout << toString() << " LOS is :" << std::endl;
				for (std::vector<unit_ptr>::iterator it = potential_targets.begin(); it != potential_targets.end(); ++it) {
					std::cout << "\t\t" << (*it)->toString() << std::endl;
				}
			}
            for (std::vector<unit_ptr>::iterator it = potential_targets.begin(); it != potential_targets.end(); ++it) {
                if (attack(**it)) {
					if (game.VERBOSE) std::cout << '\t' << std::setw(20) << toString() << "\tattacks\t" << std::setw(20) <<(*it)->toString() << "\tdealing\t" << std::to_string(model.attackScore) << " damage : " << (*it)->healthRatio() << std::endl;

                    /// TRAMPLE
                    if (model.trample)
                    for (int i=1;i<model.trample;i++) {
                        game.bombard((*it)->getPosition() + i*(game.getDirection(owner)?1:-1), model.attackScore);
                    }
					return 1;
				}
            }
        }
        else
        {
            return checkForEnemyCastle(game);
        }
        return 0;
    }

    bool Unit::checkForEnemyCastle(Game& game) {
        if( (game.getDirection(owner) && pos + model.range >= game.getBattlefieldLength()-1) || (!game.getDirection(owner) && pos - model.range <= 0) )
        {
            if (game.VERBOSE) std::cout << toString() << " attacks enemy castle" << std::endl;
            attackEnemyCastle(game);
            return true;
        }
        return false;
    }

    void Unit::attackEnemyCastle(Game& game) {
       (owner==game.getBlue()) ? game.damageCastle(game.getRed(), model.attackScore) : game.damageCastle(game.getBlue(),model.attackScore);
    }

    std::string Unit::toString() {
        std::string fin;
        fin += owner.getName() + "::" + getName() + "(" + std::to_string(id) +")";// + "(pos=" + std::to_string(pos) + ")";
        return fin;
    }

    void Unit::replenish() {
		remainingActions = model.nbActions;
	}
