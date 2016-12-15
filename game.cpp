#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

    Game::Game(Player& r, Player& b, int nbt = 0) : red(r), blue(b), nbturns(nbt) {

    }

    int Game::hasEnded() {
        return 0;
    }

    Player& Game::getCurrentPlayer() {
        return (currentTurn%2?red:blue);
    }

    void Game::addUnitModel(UnitModel um) {
        unitModels.push_back(um);
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

