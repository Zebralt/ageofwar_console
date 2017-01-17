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

bool VERBOSE = true;

    bool operator==(Player& p, Player& q) {
        return p.getName() == q.getName();
    }

    Game::Game(Player& b, Player& r) : red(r), blue(b)
    {
        loadConfig();
        currentTurn = 0;
       // battlefieldUnits = std::vector<Unit>(battlefieldLength);
        blueUnits = std::vector<Unit*>(battlefieldLength);
        redUnits = std::vector<Unit*>(battlefieldLength);
        redCursor = battlefieldLength-1;
        blueCursor = 0;
    }

    int Game::hasEnded() {
        return status() & SETTLED || status() & DRAW;
    }

    Player& Game::getEnemy(Player& p) {
        return (p == blue?red:blue);
    }

    void Game::addModel(Model um) {
        models.push_back(um);
    }

    bool Game::checkPosition(int pos) {
		for (Unit* u : getUnits()) {
            if (u->getPosition() == pos)
                return false;
		}
		return true;
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

    std::vector<Unit*> Game::getUnits() {
        std::vector<Unit*> units;
        units.insert(std::end(units), std::begin(blueUnits), std::end(blueUnits));
        units.insert(std::end(units), std::begin(redUnits), std::end(redUnits));
        return units;
    }

    std::vector<Unit*>& Game::getUnits(Player& p) {
        return (p == blue ? blueUnits : redUnits);
    }

    std::vector<Model>& Game::getModels() {
        return models;
    }

    bool Game::loadConfig() {
        Parser parser(*this);
        bool b = parser.parse("info.cfg");
     //   listModels();
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
        std::vector<Unit*>& units = getUnits(currentPlayer);
        for (int phase=0;phase < nbPhases; phase++) {
            for (std::vector<Unit*>::const_iterator it = units.begin(); it != units.end(); ++it) { /* reste a ajouter la gestion dans l'autre sens */
                if (*it) {

                    if ((*it)->haveRemainingActions()) {
                        switch ((*it)->getModel().getActions()[phase]) {
                            case ATTACK:
                                if ((*it)->engage(*this)) (*it)->act();
                            break;
                            case MOVE:
                                if ((*it)->advance(*this)) (*it)->act();
                            break;
                            case IDLE:
                            default:
                            break;
                        }
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
            if (!checkPosition(i)) std::cout << " a ";
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
        updateCursors();
        currentTurn++;
    }

    short Game::status() {
        unravel();
        if (!red.getHealth() && !blue.getHealth()) return DRAW;
        else if (!red.getHealth() && blue.getHealth()) return SETTLED & BLUE_WINS;
        else if (red.getHealth() && !blue.getHealth()) return SETTLED & RED_WINS;
        else if (currentTurn >= nbturns) return DRAW;
        else return PLAYING;
    }

    void Game::listModels() {
        print "Registered models:" << lend;
        for (uint i=0; i<models.size(); i++) {
            print models[i].toString() << lend;
        }
        newLine;
    }

    bool Game::purchase(Player& p, Model& m) {
        say std::cout << p.getName() << " is trying to buy " << m.getName() << std::endl;
        if (p.getGold() >= m.getPrice()) {
            Unit u(p,m);
            if (addUnit(u,p)) {
                p.debit(m.getPrice());
                return true;
            }
        }
        return false;
    }

    bool Game::addUnit(Unit& u, Player& p) {
        int pos = (p == blue?0:battlefieldLength-1);
        u.setPosition(pos);
        std::vector<Unit*>& lordUnits = (p == blue?blueUnits:redUnits);
        if (checkPosition(pos)) {
            lordUnits.push_back(&u);
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
