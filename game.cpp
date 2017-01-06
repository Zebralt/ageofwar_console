#include "player.hpp"
#include "model.hpp"
#include "unit.hpp"
#include "game.hpp"

#include <stdlib.h>

    bool operator==(Player& p, Player& q) {
        return p.getName() == q.getName();
    }

 //getDirection(joueur) > si b 0 sinon 1
 //getEnemyCursor > renvoie curseur de l'autre joueur

    Game::Game(Player& b, Player& r) : red(r), blue(b)
    {
        loadConfig();
        currentTurn=0;
        battlefieldUnits=(Unit*)malloc(battlefieldLength);
        redCursor=battlefieldLength-1;
        blueCursor=0;
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
        //read info.cfg
        //initialiser la taille du terrain, nbtoursmax
        return true;
    }

    int Game::getEnemyCursor(Player& p) {
        if (p == red) {
            return blueCursor;
        }
        else return redCursor;
    }

    int Game::getDirection(Player& p) {
        return p == blue;
    }

    bool Game::runPhases(Player& currentPlayer) {
        Unit* tmp;
        int cursor = getCursor(currentPlayer);
        int direction = getDirection(currentPlayer);
        if (direction) {
            for (int i=0;i<cursor;i++) {

            }
        }
        else {
            fo (int i=battlefieldLength-1;i>=;i--)
        }
    }
