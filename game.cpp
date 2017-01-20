#include "player.hpp"
#include "model.hpp"
#include "unit.hpp"
#include "game.hpp"
#include "parser.hpp"

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

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
        red.give(initialGold);
        blue.give(initialGold);
        currentTurn = 0;
    }

    int Game::hasEnded() {
        return status() & SETTLED || status() & DRAW;
    }

    void Game::addModel(model_ptr um) {
        models.push_back(um);
    }

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

    Player* Game::getWinner() {
		if (status() & BLUE_WINS) return &blue;
		else if (status() & RED_WINS) return &red;
		else return nullptr;
    }

    std::vector<unit_ptr> Game::getUnits() {
        std::vector<unit_ptr> units;
        units.insert(std::end(units), std::begin(blueUnits), std::end(blueUnits));
        units.insert(std::end(units), std::begin(redUnits), std::end(redUnits));
        return units;
    }

    std::vector<unit_ptr>& Game::getUnits(Player& p) {
        return (p == blue ? blueUnits : redUnits);
    }

    std::vector<std::shared_ptr<Model>>& Game::getModels() {
        return models;
    }

    bool Game::loadConfig() {
        Parser parser(*this);
        bool b = parser.parse("info.cfg");
		if (VERBOSE) {
			std::cout << "Loading models: " << std::endl;
			listModels();
		}
        return b;
    }

    /*int Game::getEnemyCursor(Player& p) {
        if (p == red) {
            return blueCursor;
        }
        else return redCursor;
    }*/

    /*int Game::getCursor(Player& p) {
        return (p == red?redCursor:blueCursor);
    }*/

    int Game::getDirection(Player& p) {
        return p == blue;
    }

    bool Game::runPhases(Player& currentPlayer) {
        std::vector<std::shared_ptr<Unit>>& units = getUnits(currentPlayer);
        for (int phase=0;phase < nbPhases; phase++) {
            if (VERBOSE) std::cout <<"(" << currentPlayer.toString() << ")" << "Phase " << phase << ": " << std::endl;
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
        int i;
        int width = 7;
        unit_ptr temp;
        std::string s;

        //1ere ligne : noms
        std::cout << blue.getName() ;
        printCorrectWidth(blue.getName().size() ,width);
        std::cout << "||| " ;
        for(i=0; i<battlefieldLength ;i++)
        {
            temp = getUnitAt(i);
            if(temp == nullptr)
            {
                printCorrectWidth(0,width);
            }
            else
            {
                std::cout << " " <<temp->getName();
                printCorrectWidth(temp->getName().size() ,width);
            }
            std::cout << " ||" ;
        }
        std::cout << "| "  << red.getName() << std::endl;

        //2e ligne : santé
        s = " HP";
        std::cout << blue.getHealth() << s;
        printCorrectWidth(s.size() + SSTR(blue.getHealth()).size() ,width);
        std::cout << "||| ";
        for(i=0; i<battlefieldLength ;i++)
        {
            temp = getUnitAt(i);
            if(temp == nullptr)
            {
                printCorrectWidth(1,width);
            }
            else
            {
                std::cout << " " << temp->getHealth() << s;
                printCorrectWidth(s.size() + SSTR(temp->getHealth()).size() +1,width);
            }
            std::cout << "  ||" ;
        }
        std::cout << "| "  << red.getHealth() << s << std::endl;

        //3e ligne : gold
        s=" gold";
        std::cout << blue.getGold() << s;
        printCorrectWidth(s.size() + SSTR(blue.getGold()).size() ,width);
        std::cout << "||| ";
        for(i=0; i<battlefieldLength ;i++)
        {
            temp = getUnitAt(i);
            if(temp == nullptr)
            {
                printCorrectWidth(1,width);
            }
            else
            {
                temp->getOwner()==blue?std::cout<<" >":std::cout<<" <";
                printCorrectWidth(2,width);
            }
            std::cout << "  ||" ;
        }
        std::cout << "| "  << red.getGold() << s << std::endl;
    }

    void Game::printCorrectWidth(int actualSize, int width)
    {
        if(actualSize<width)
        {
            int j=width-actualSize;
            for(j; j>=0; j--)
            {
                std::cout << " ";
            }
        }
    }

    void Game::unravel() {
        red.give(goldPerTurn);
        blue.give(goldPerTurn);
        if (VERBOSE) display();
        runPhases(blue);
        if (VERBOSE) std::cout << std::endl << blue.toString() << " move is " << std::endl;
        blue.play(*this);
        if (VERBOSE) display();
        runPhases(red);
        if (VERBOSE) display();
        if (VERBOSE)  std::cout << std::endl << red.toString() << " move is " << std::endl;
        red.play(*this);
        checkUnits();
        //updateCursors();
        display();
        currentTurn++;
    }

    short Game::status() {
		/// TODO : GAME STATUS CHECK
        if (!red.getHealth() && !blue.getHealth()) return DRAW;
        else if (!red.getHealth() && blue.getHealth()) return SETTLED & BLUE_WINS;
        else if (red.getHealth() && !blue.getHealth()) return SETTLED & RED_WINS;
        else if (currentTurn >= nbturns) return DRAW;
        else return PLAYING;
    }

    void Game::listModels() {
        std::cout << "Registered models:" << std::endl;
        for (uint i=0; i<models.size(); i++) {
            std::cout << models[i]->toString() << std::endl;
        }
        std::cout << std::endl;
    }

    bool Game::purchase(Player& p, Model& m) {
        //say std::cout << p.getName() << " is trying to buy " << m.getName() << std::endl;
        if (p.getGold() >= m.getPrice()) {
            std::shared_ptr<Unit> u(new Unit(p,m));
            if (addUnit(u,p)) {
                p.debit(m.getPrice());
                if (VERBOSE) std::cout << p << " bought model:" << m.getName() << "(price=" << m.getPrice() << ")" << std::endl;
                return true;
            }
        }
        return false;
    }

    bool Game::addUnit(std::shared_ptr<Unit> u, Player& p) {
        int pos = (p == blue?0:battlefieldLength-1);
        u->setPosition(pos);
        std::vector<std::shared_ptr<Unit>>& lordUnits = getUnits(p);
        if (!positionTaken(pos)) {
            lordUnits.push_back(u);
            return true;
        }
        return false;
    }

    /*void Game::updateCursors() {
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
    }*/

    int Game::getBattlefieldLength() {
        return battlefieldLength;
    }

    bool Game::damageCastle(Player& p, int dam) {
        /*if (p == blue || p == red) {
            if (getCursor(p) < 0 || getCursor(p) > battlefieldLength - 1) {
                p.takeDamage(dam);
                return true;
            }
        }*/
        /// TODO : GAME::DAMAGE_CASTLE
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
    }

    void Game::killUnit(unit_ptr unit) {
		std::vector<unit_ptr>& list = getUnits(unit->getOwner());
		std::vector<unit_ptr>::iterator it = std::find(list.begin(), list.end(), unit);
		if (it != list.end())
			list.erase(it);
	}
