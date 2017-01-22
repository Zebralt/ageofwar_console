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

    Game::Game(Player& b, Player& r) : red(r), blue(b)
    {
        loadConfig();
        red.give(initialGold);
        blue.give(initialGold);
        currentTurn = 0;
    }

    /// LOADER

    bool Game::loadConfig() {
        Parser parser(*this);
        bool b = parser.parse("info.cfg");
		if (VERBOSE) {
			std::cout << "Loading models: " << std::endl;
			listModels();
		}
        return b;
    }

    void Game::addModel(model_ptr um) {
        models.push_back(um);
    }

    /// GAME STATUS CHECK

    int Game::hasEnded() {
        short st = status();
        if (st & SETTLED) {
            std::cout << std::endl << "The winner is " << (st & BLUE_WINS?blue:red).toString() << "!" << std::endl;
        }
        else if (st & DRAW) {
            std::cout << std::endl << "End turn reached. The game is a draw. " << std::endl;
        }
        return st & SETTLED || st & DRAW;
    }

    short Game::status() {
        if (red.getHealth() <= 0 && blue.getHealth() <= 0) return DRAW; // 0x10
        else if (red.getHealth() <= 0 && blue.getHealth() > 0) return SETTLED | BLUE_WINS; // 0x110
        else if (red.getHealth() > 0 && blue.getHealth() <= 0) return SETTLED | RED_WINS; // 0x1010
        else if (currentTurn >= nbturns) return DRAW; // 0x10
        else return PLAYING; // 0x1
    }

        unit_ptr Game::getUnitAt(int pos) {
		std::vector<unit_ptr> units = getUnits();
		for (unsigned int i=0;i<units.size();i++) {
            if (units[i]->getPosition() == pos)
                return units[i];
		}
		return nullptr;
	}

	/// GETTERS

    Player& Game::getBlue() {
        return blue;
    }

    Player& Game::getRed() {
        return red;
    }

    std::shared_ptr<Player> Game::getWinner() {
		if (status() & BLUE_WINS) return std::shared_ptr<Player>(&blue);
		else if (status() & RED_WINS) return std::shared_ptr<Player>(&red);
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

    int Game::getDirection(Player& p) {
        return p == blue;
    }

    /// DISPLAY

    void Game::setVerbose(bool b) {
		VERBOSE = b;
	}

    void Game::minimalDisplay() {
		int wspace = 4;
		bool displayId = 0;
        std::cout << blue.toString() <<" gold=" << blue.getGold() << " health=" << blue.getHealth();
        for (int x=0;x<(wspace-2)*battlefieldLength;x++) std::cout << " ";
        std::cout << red.toString() <<" gold=" << red.getGold() << " health=" << red.getHealth();
        std::cout << std::endl;
        for (int i=0;i<battlefieldLength;i++)
			if (unit_ptr upt = getUnitAt(i)) {
				std::cout << std::setw(wspace) << (upt->getOwner() == blue?'>':'<');
			}
			else for (int y=0;y<wspace;y++) std::cout << ' ';
		std::cout << std::endl;
        if (displayId) {
			for (int i=0;i<battlefieldLength;i++)
			if (unit_ptr upt = getUnitAt(i)) {
				std::cout << std::setw(wspace) << upt->getId();
			}
			else for (int x=0;x<wspace;x++) std::cout << ' ';
			std::cout << std::endl;
		}
        for (int i=0;i<battlefieldLength;i++)
        {
            if (positionTaken(i)) std::cout << std::setw(4) << getUnitAt(i)->getName()[0];
            else std::cout << std::setw(wspace) << "_";
        }
        //std::cout << red;
        std::cout << std::endl;
        //std::cout << "       ";
        for (int i=0;i<battlefieldLength;i++) {
			std::cout << std::setw(wspace) << i;
		}
		std::cout << std::endl;
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

    void Game::listModels() {
        std::cout << "Registered models:" << std::endl;
        for (uint i=0; i<models.size(); i++) {
            std::cout << models[i]->toString() << std::endl;
        }
        std::cout << std::endl;
    }


    bool operator==(Player& p, Player& q) {
        return p.getName() == q.getName();
    }

    /// INGAME BEHAVIOURS

     bool Game::positionTaken(int pos) {
        std::vector<unit_ptr> units = getUnits();
		for (unsigned int i=0;i<units.size();i++) {
            if (units[i]->getPosition() == pos)
                return true;
		}
		return false;
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
                                    unit->useAction();
                                }
                            break;
                            case MOVE:
                                if (unit->advance(*this)) {
                                    unit->useAction();
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

    void Game::update() {
        red.give(goldPerTurn);
        blue.give(goldPerTurn);
        runPhases(blue);
        if (!MDISPLAY) minimalDisplay(); else display();
        blue.play(*this);
        runPhases(red);
        if (VERBOSE)  std::cout << std::endl << red.toString() << " move is " << std::endl;
        red.play(*this);
        checkUnits();
        if (!MDISPLAY) minimalDisplay(); else display();
        currentTurn++;
    }

    bool Game::purchase(Player& p, model_ptr m) {
        if (m == nullptr) return true;
        if (p.getGold() >= m->getPrice()) {
            std::shared_ptr<Unit> u(new Unit(p,*m));
            if (addUnit(u,p)) {
                p.debit(m->getPrice());
                if (VERBOSE) std::cout << p << " bought model:" << m->getName() << "(price=" << m->getPrice() << ")" << std::endl;
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

    int Game::getBattlefieldLength() {
        return battlefieldLength;
    }

   void Game::damageCastle(Player& p, int dam) {
        if (p == blue || p == red)
        {
            p.takeDamage(dam);
            if (VERBOSE) std::cout << p.toString() << "'s castle took " << std::to_string(dam) << " damage (" << std::to_string(p.getHealth()) << ")"<< std::endl;
        }
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

	void Game::bombard(int pos, int attackScore) {
        if (pos >= 0 && pos < battlefieldLength) {
            if (unit_ptr unit = getUnitAt(pos)) {
                unit->takeDamage(attackScore);
                if (VERBOSE) std::cout << unit->toString() << " was bombarded for " << std::to_string(attackScore) << " damage (" << unit->healthRatio() << ")" << std::endl;
            }
        }
	}
