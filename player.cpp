#include "player.hpp"

    Player::Player(std::string na) : name(na) {

    }

    Human::Human(std::string na) : Player(na) {

    }

    void Human::play() {

    }

    AI::AI(std::string na) : Player(na) {

    }

    void AI::play() {

    }


    std::ostream& operator<<(std::ostream& o, const Player& p) {
        o << p.name;
        return o;
    }
