#include "model.hpp"
#include "game.hpp"
#include "unit.hpp"
#include "player.hpp"

#include <iostream>

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
    - units : le tableau d'unités de game
    - ptr : pointeur sur la première unité du joueur opposé
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
		for (int i=model.minimumRange; i<model.range; i++) {
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
        if (g.positionTaken(newpos)) {
            return false;
        }
        else {
			if (g.VERBOSE) std::cout << '\t' << toString() << "moves to " << std::to_string(newpos) << std::endl;
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
                //if (attack(**it)) return 1 + (*it)->alive();
                //TODO
                if (attack(**it)) {
					if (game.VERBOSE) std::cout << '\t' << (*it)->toString() << " took " << std::to_string(model.attackScore) << " damage : " << (*it)->healthRatio() << std::endl;
					return 1;	
				}
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
        fin += owner.getName() + "::" + getName() + "(" + std::to_string(id) +")" + "(pos=" + std::to_string(pos) + ")";
        return fin;
    }
    
    void Unit::replenish() {
		remainingActions = model.nbActions;
	}
