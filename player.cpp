#include "player.hpp"
#include "model.hpp"
#include "game.hpp"

#include <iostream>

    /// ABSTRACT CLASS PLAYER

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

    std::string Player::toString() {
		return name;
	}

    /// HUMAN CLASS

    Human::Human(std::string na) : Player(na) {

    }

    void Human::play(Game& game) {
        if (game.positionTaken((!game.getDirection(*this))*(game.getBattlefieldLength()-1))) {
            std::cout << "You can't do anything. " << std::endl;
            std::string str;
            std::getline(std::cin, str);
            return;
        }
        std::vector<model_ptr>& models = game.getModels();
        game.purchase(*this, buy(models));
    }

    bool canBuy(std::vector<model_ptr>& mods, int ind, int gold) {
        if (ind < 0 || ind >= mods.size()) return false;
        else return mods[ind]->getPrice() <= gold;
    }

    model_ptr Human::buy(std::vector<model_ptr>& mods)
    {
        std::cout << "You have " << std::to_string(gold) << " gold. Do you want to buy a unit ?" << std::endl;
        unsigned int i;
        std::cout << "0 : I'll pass, thanks" << std::endl;
        for (i=0;i< mods.size(); i++)
        {
            std::cout << i+1 << " : " << mods[i]->stats() << std::endl ;
        }
        std::cin >> i;
        while (i < 0 || i > mods.size() || !canBuy(mods,i-1,gold)) {
            if (!i) break;
            std::cout << "You can't buy this ";
            if (i-1 >= 0 && i-1 < mods.size()) std::cout << ": " << mods[i-1]->getName();
            std::cout << std::endl;
            std::cin >> i;
        }
        if (!i) return nullptr;
        else return mods[i-1];
    }

    /// ARTIFICIAL INTELLIGENCE AI CLASS

    AI::AI(std::string na) : Player(na) {

    }

    void AI::play(Game& game) {
        game.purchase(*this, buy(game.getModels()));
    }



    model_ptr AI::buy(std::vector<model_ptr>& mods) {
        model_ptr temp = mods[0];
        for (unsigned int i=1; i<mods.size(); i++)
        {
            if(mods[i]->getPrice() > temp->getPrice() && mods[i]->getPrice()<=gold)
                {temp=mods[i];}
        }
        return temp;
    }

    std::ostream& operator<<(std::ostream& o, const Player& p) {
        o << p.name << "(" << p.gold << ")";
        return o;
    }

    void Player::setName(std::string n) {
        name = n;
    }
