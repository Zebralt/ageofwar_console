#include "player.hpp"
#include "model.hpp"
#include "game.hpp"

#include <iostream>

    Player::Player(std::string na) : name(na) {

    }

    bool Player::hasLost() {
        return health <= 0;
    }

    std::string Player::getName() {
        return name;
    }

    int Player::getHealth() {
        return health;
    }

    unsigned int Player::getGold() {
        return gold;
    }

    void Player::debit(int i) {
        gold -= i;
    }

    void Player::takeDamage(int i) {
        health -= i;
    }

    ///

    Human::Human(std::string na) : Player(na) {

    }

    void Human::play(Game& game) {
        game.purchase(*this, buy(game.getModels()));
    }

    Model& Human::buy(std::vector<Model> mods)
    {
        std::cout << "Rentrez le numero de l unite a acheter parmis les suivantes :" << std::endl;
        unsigned int i=0;
        while(mods[i].getPrice() <= gold)
        {
            std::cout << i+1 << " : " << mods[i].getName() << std::endl ;
            i++;
        }
        i = 0;
        while (i < 1 || i > mods.size()) std::cin >> i;
        return mods[i];
    }

    ///

    AI::AI(std::string na) : Player(na) {

    }

    void AI::play(Game& game) {
        game.purchase(*this, buy(game.getModels()));
    }



    Model& AI::buy(std::vector<Model> mods) {
        Model& temp = mods[0];
        for (unsigned int i=1; i<mods.size(); i++)
        {
            if(mods[i].getPrice() > temp.getPrice() && mods[i].getPrice()<=gold)
                {temp=mods[i];}
        }
        return temp;
    }

    std::ostream& operator<<(std::ostream& o, const Player& p) {
        o << p.name << "(" << p.gold << ")";
        return o;
    }
