#include "player.hpp"
#include "model.hpp"
#include "unit.hpp"
#include "game.hpp"

    Game::Game(Player& b, Player& r, int nbt = 0) : red(r), blue(b), nbturns(nbt) {

        loadModels();

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

    const std::vector<Unit*> Game::getUnits() {
        return units;
    }

    int Game::checkPosition(int pos) {
        int checked = 0;
        for (std::vector<Unit*>::iterator it = units.begin(); it != units.end(); ++it) {
            checked += ((*it)->getPosition() == pos);
        }
        return checked;
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

    bool Game::loadModels() {
        //read info.cfg
        return true;
    }
