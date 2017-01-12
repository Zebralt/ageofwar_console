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

    bool operator==(Player& p, Player& q) {
        return p.getName() == q.getName();
    }

    Game::Game(Player& b, Player& r) : red(r), blue(b)
    {
        loadConfig();
        currentTurn = 0;
        battlefieldUnits = NEW(Unit*, battlefieldLength);
        blueUnits = NEW(Unit*, battlefieldLength);
        redUnits = NEW(Unit*, battlefieldLength);
        redCursor = battlefieldLength-1;
        blueCursor = 0;
    }

    int Game::hasEnded() {
        nbturns -= 10;
        return !nbturns || status() & SETTLED || status() & DRAW;
    }

    Player& Game::getEnemy(Player& p) {
        return (p == blue?red:blue);
    }

    void Game::addModel(Model um) {
        models.push_back(um);
    }

    bool Game::checkPosition(int pos) {
		if (&battlefieldUnits[pos]==nullptr)
			return true;
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

    Unit** Game::getUnits() {
        return battlefieldUnits;
    }

    bool Game::loadConfig() {
        Parser parser(*this);
        bool b = parser.parse("info.cfg");
        listModels();
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
        Unit* tmp;
        int cursor = getCursor(currentPlayer);
        //int direction = getDirection(currentPlayer);

        for (int phase=0;phase < nbPhases; phase++) {
            for (int i=0;i < cursor; i++) { /* reste a ajouter la gestion dans l'autre sens */
                if (true) {
                    tmp = (Unit*) &battlefieldUnits[cursor];
                    if (tmp->haveRemainingActions()) {
                        switch (tmp->getModel().getActions()[phase]) {
                            case ATTACK:
                                if (tmp->engage(*this)) tmp->act();
                            break;
                            case MOVE:
                                if (tmp->advance(*this)) tmp->act();
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
        std::cout << "\t";
        for (int i=0;i<12;i++) std::cout << i+1 << "\t";
        std::cout << std::endl;
        std::cout << "\t";
        std::cout << blue.getHealth();
        for (int i=0;i<10;i++)
        std::cout << "\t_";
        std::cout << "\t";
        std::cout << red.getHealth();
        std::cout << std::endl;
    }

    void Game::update() {
        runPhases(blue);
        blue.play();
        runPhases(red);
        red.play();
        updateCursors();
        currentTurn++;
    }

    short Game::status() {
        update();
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
        Unit** lordUnits = (p == blue?blueUnits:redUnits);
        if (checkPosition(pos)) {
            battlefieldUnits[pos] = &u;
            lordUnits[pos] = &u;
            return true;
        }
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
