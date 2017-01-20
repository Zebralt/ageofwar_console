#include "player.hpp"
#include "model.hpp"
#include "unit.hpp"
#include "game.hpp"
#include "parser.hpp"

#include <iostream>
#include <cstdlib>

#define stringList std::vector<std::string>
#define print std::cout <<
#define newLine std::cout << std::endl;
#define lend std::endl
#define ask(p) p.play()
#define say if(VERBOSE)

typedef unsigned int uint;

bool VERBOSE = 1;

    bool operator==(Player& p, Player& q) {
        return p.getName() == q.getName();
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
        std::vector<std::shared_ptr<Unit>> units = getUnits();
		for (unsigned int i=0;i<units.size();i++) {
            if (units[i]->getPosition() == pos)
                return true;
		}
		return false;
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
//        for (int i=0;i<blueUnits.size();i++) units.push_back(blueUnits[i]);
//        for (int i=0;i<redUnits.size();i++) units.push_back(redUnits[i]);
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
            say std::cout << "Phase " << phase << ":" << std::endl;
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
                                    say std::cout << unit->getName() << " succeeded in attacking" << std::endl;
                                }
                                else {
                                    say std::cout << unit->getName() << " couldn't attack" << std::endl;
                                }
                            break;
                            case MOVE:
                                if (unit->advance(*this)) {
                                    unit->act();
                                    say std::cout << unit->getName() << "succeeded in moving" << std::endl;
                                }
                                else {
                                    say std::cout << unit->getName() <<  " couldn't move" << std::endl;
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
        std::cout << "Turn " << currentTurn << ':';
        std::cout << "\t";
        //for (int i=0;i<12;i++) std::cout << i+1 << " ";
        std::cout << std::endl << '\t';
        std::cout << blue;
        for (int i=0;i<battlefieldLength;i++)
        {
            if (0/*std::shared_ptr<Unit> un = positionTaken(i)*/) std::cout << " a ";// std::cout << un->getName();
            else std::cout << " _ ";
        }
        std::cout << red;
        std::cout << std::endl;
    }

    void Game::unravel() {
        red.give(goldPerTurn);
        blue.give(goldPerTurn);
        runPhases(blue);
        blue.play(*this);
        runPhases(red);
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
            say std::cout << "added unit" << std::endl;
            return true;
        }
        say std::cout << "failed to add unit" << std::endl;
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
        // TODO
    }
