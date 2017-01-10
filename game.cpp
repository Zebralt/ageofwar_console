#include "player.hpp"
#include "model.hpp"
#include "unit.hpp"
#include "game.hpp"
#include "parser.hpp"

#include <iostream>
#include <cstdlib>

    bool operator==(Player& p, Player& q) {
        return p.getName() == q.getName();
    }

    Game::Game(Player& b, Player& r) : red(r), blue(b)
    {
        loadConfig();
        currentTurn = 0;
        battlefieldUnits = (Unit*) calloc(battlefieldLength,sizeof(Unit));
        redCursor = battlefieldLength-1;
        blueCursor = 0;
    }

    int Game::hasEnded() {
        return 1;
    }

    Player& Game::getCurrentPlayer() {
        return (currentTurn%2?red:blue);
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

    Unit* Game::getUnits() {
        return battlefieldUnits;
    }

    bool Game::loadConfig() {
        Parser parser(*this);
        return parser.parse("info.cfg");
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
        CombatUnit* tmp;
        int cursor = getCursor(currentPlayer);
        int direction = getDirection(currentPlayer);

        for (int phase=0;phase < nbPhases; phase++) {
            for (int i=0;i < cursor; i++) { /* reste a ajouter la gestion dans l'autre sens */
                if (true) {
                    tmp = (CombatUnit*) &battlefieldUnits[cursor];
                    if (tmp->haveRemainingActions()) {
                        switch (tmp->getModel().getActions()[phase]) {
                            case ATTACK:
                                if (tmp->engage(*this)) tmp->act();
                            break;
                            case MOVE:
                                if (tmp->advance(*this)) tmp->act();
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

    }

    short Game::status() {
        update();
        if (!red.getHealth() && !blue.getHealth()) return DRAW;
        else if (!red.getHealth() && blue.getHealth()) return SETTLED & BLUE_WINS;
        else if (red.getHealth() && !blue.getHealth()) return SETTLED & RED_WINS;
        else if (currentTurn >= nbturns) return DRAW;
        else return PLAYING;
    }
