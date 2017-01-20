#include "player.hpp"
#include "model.hpp"
#include "unit.hpp"
#include "game.hpp"
#include "parser.hpp"

#include <iostream>
#include <cstdlib>
#include <algorithm>

#define stringList std::vector<std::string>
#define print std::cout <<
#define newLine std::cout << std::endl;
#define lend std::endl
#define ask(p) p.play()
#define say if(VERBOSE)

typedef unsigned int uint;

    bool operator==(Player& p, Player& q) {
        return p.getName() == q.getName();
    }
    
    void Game::setVerbose(bool b) {
		VERBOSE = b;
	}

    Game::Game(Player& b, Player& r) : red(r), blue(b)
    {
        loadConfig();
        currentTurn = 0;
        redCursor = battlefieldLength-1;
        blueCursor = 0;
    }

    int Game::hasEnded() {
        return status() & SETTLED || status() & DRAW;
    }

    Player& Game::getEnemy(Player& p) {
        return (p == blue?red:blue);
    }

    void Game::addModel(std::shared_ptr<Model> um) {
        models.push_back(um);
    }

    /*std::shared_ptr<Unit> Game::positionTaken(int pos) {
        std::vector<std::shared_ptr<Unit>> units = getUnits();
		for (unsigned int i=0;i<units.size();i++) {
            if (units[i]->getPosition() == pos)
                return units[i];
		}
		return nullptr;
    }*/
     bool Game::positionTaken(int pos) {
        std::vector<unit_ptr> units = getUnits();
		for (unsigned int i=0;i<units.size();i++) {
            if (units[i]->getPosition() == pos)
                return true;
		}
		return false;
    }
    
    unit_ptr Game::getUnitAt(int pos) {
		std::vector<unit_ptr> units = getUnits();
		for (unsigned int i=0;i<units.size();i++) {
            if (units[i]->getPosition() == pos)
                return units[i];
		}
		return nullptr;
	}

    Player& Game::getBlue() {
        return blue;
    }

    Player& Game::getRed() {
        return red;
    }

    Player& Game::getWinner() {
        return blue;
    }

    std::vector<std::shared_ptr<Unit>> Game::getUnits() {
        std::vector<std::shared_ptr<Unit>> units;
        units.insert(std::end(units), std::begin(blueUnits), std::end(blueUnits));
        units.insert(std::end(units), std::begin(redUnits), std::end(redUnits));
        return units;
    }

    std::vector<std::shared_ptr<Unit>>& Game::getUnits(Player& p) {
        return (p == blue ? blueUnits : redUnits);
    }

    std::vector<std::shared_ptr<Model>>& Game::getModels() {
        return models;
    }

    bool Game::loadConfig() {
        Parser parser(*this);
        bool b = parser.parse("info.cfg");
//        listModels();
        return b;
    }

    int Game::getEnemyCursor(Player& p) {
        if (p == red) {
            return blueCursor;
        }
        else return redCursor;
    }

    int Game::getCursor(Player& p) {
        return (p == red?redCursor:blueCursor);
    }

    int Game::getDirection(Player& p) {
        return p == blue;
    }

    bool Game::runPhases(Player& currentPlayer) {
//        int cursor = getCursor(currentPlayer);
        //int direction = getDirection(currentPlayer);
        std::vector<std::shared_ptr<Unit>>& units = getUnits(currentPlayer);
        for (int phase=0;phase < nbPhases; phase++) {
            say std::cout <<"(" << currentPlayer.toString() << ")" << "Phase " << phase << ": " << std::endl;
            for (std::vector<std::shared_ptr<Unit>>::const_iterator it = units.begin(); it != units.end(); ++it) { /* reste a ajouter la gestion dans l'autre sens */

                std::shared_ptr<Unit> unit = *it;
                if (unit != nullptr) {
                    if (unit->haveRemainingActions()) {
                        std::vector<Action>& actions = unit->getModel().getActions();
                        if (actions.size() >= nbPhases)
                        switch (actions.at(phase)) {
                            case ATTACK:
                                if (unit->engage(*this)) {
                                    unit->act();
                                    //say std::cout << '\t' << unit->toString() << " engaged " << "(" << unit->haveRemainingActions() << " action" << (unit->haveRemainingActions() > 1?"s":"") <<  " left)" << std::endl;
                                }
                                else {
                                    //say std::cout << '\t' << unit->toString() << " couldn't attack" << std::endl;
                                }
                            break;
                            case MOVE:
                                if (unit->advance(*this)) {
                                    unit->act();
                                    //say std::cout << '\t' << unit->toString() << " moved " << "(" << unit->haveRemainingActions() << " action" << (unit->haveRemainingActions() > 1?"s":"") <<  " left)" << std::endl;
                                }
                                else {
                                    //say std::cout << '\t' << unit->toString() <<  " couldn't move" << std::endl;
                                }
                            break;
                            case IDLE:
                            default:
                            break;
                        }
                        else std::cout << "what? " << actions.size() << std::endl;
                    }
                }
            }
        }
        return true;
    }

    void Game::display() {
        std::cout << "Turn " << currentTurn << ':' << std::endl;
        //std::cout << blue;
        for (int i=0;i<battlefieldLength;i++)
        {
            if (positionTaken(i)) std::cout << " " << getUnitAt(i)->getName()[0] << " ";
            else std::cout << " _ ";
        }
        //std::cout << red;
        std::cout << std::endl;
        //std::cout << "       ";
        for (int i=0;i<battlefieldLength;i++) {
			std::cout << " " << i << " ";
		}
		std::cout << std::endl;
    }

    void Game::unravel() {
        red.give(goldPerTurn);
        blue.give(goldPerTurn);
        display();
        runPhases(blue);
        if (VERBOSE) std::cout << std::endl << blue.toString() << " move is " << std::endl;
        blue.play(*this);
        runPhases(red);
        if (VERBOSE)  std::cout << std::endl << red.toString() << " move is " << std::endl;
        red.play(*this);
        checkUnits();
        //updateCursors();
        currentTurn++;
    }

    short Game::status() {
        if (!red.getHealth() && !blue.getHealth()) return DRAW;
        else if (!red.getHealth() && blue.getHealth()) return SETTLED & BLUE_WINS;
        else if (red.getHealth() && !blue.getHealth()) return SETTLED & RED_WINS;
        else if (currentTurn >= nbturns) return DRAW;
        else return PLAYING;
    }

    void Game::listModels() {
        print "Registered models:" << lend;
        for (uint i=0; i<models.size(); i++) {
            print models[i]->toString() << lend;
        }
        newLine;
    }

    bool Game::purchase(Player& p, Model& m) {
        //say std::cout << p.getName() << " is trying to buy " << m.getName() << std::endl;
        if (p.getGold() >= m.getPrice()) {
            std::shared_ptr<Unit> u(new Unit(p,m));
            if (addUnit(u,p)) {
                p.debit(m.getPrice());
                say std::cout << p << " bought model:" << m.getName() << "(price=" << m.getPrice() << ")" << std::endl;
                return true;
            }
        }
        return false;
    }

    bool Game::addUnit(std::shared_ptr<Unit> u, Player& p) {
        int pos = (p == blue?0:battlefieldLength-1);
        u->setPosition(pos);
        std::vector<std::shared_ptr<Unit>>& lordUnits = (p == blue?blueUnits:redUnits);
        if (!positionTaken(pos)) {
            lordUnits.push_back(u);
            //say std::cout << "added unit " << u->toString() << std::endl;
            return true;
        }
        //say std::cout << "failed to add unit " << u->toString() << std::endl;
        return false;
    }

    void Game::updateCursors() {
        short sblue = 0x01;
        short sred  = 0x10;
        short searching = sblue | sred;
        for (int i=0;i<battlefieldLength && searching;i++) {
            if (sblue & searching && blueUnits[i] != nullptr) {
                blueCursor = i;
                searching -= sblue;
            }
            if (sred & searching && redUnits[battlefieldLength-1-i] != nullptr) {
                redCursor = battlefieldLength-1-i;
                searching -= sred;
            }
        }
        if (searching & sred) redCursor = battlefieldLength;
        if (searching & sblue) blueCursor = -1;
    }

    int Game::getBattlefieldLength() {
        return battlefieldLength;
    }

    bool Game::damageCastle(Player& p, int dam) {
        if (p == blue || p == red) {
            if (getCursor(p) < 0 || getCursor(p) > battlefieldLength - 1) {
                p.takeDamage(dam);
                return true;
            }
        }
        return false;
    }

    void Game::checkUnits() {
		std::vector<unit_ptr> units = getUnits();
		for (std::vector<unit_ptr>::const_iterator it = units.begin(); it != units.end(); ++it) {
			if ((*it)->alive()) {
				(*it)->replenish();
			}
			else {
				if (VERBOSE) std::cout << (*it)->toString() << " was defeated " << std::endl;
				killUnit((*it));
			}
		}
        // TODO
    }
    
    void Game::killUnit(unit_ptr unit) {
		std::vector<unit_ptr>& list = (unit->getOwner() == blue ? blueUnits : redUnits);
		std::vector<unit_ptr>::const_iterator it = std::find(list.begin(), list.end(), unit);
		if (it != list.end())
			list.erase(it);
	}
