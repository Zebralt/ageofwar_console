#include "model.hpp"

    /// MODEL : CLASS

    Model::Model(std::string name, int maxHP, int price, int nbActions, int attackScore, int range, int minimumRange, int trample)
    {

        this->name = name;
        this->maxHP = maxHP;
        this->price = price;
        this->nbActions = nbActions;
        this->attackScore = attackScore;
        this->range = range;
        this->minimumRange = minimumRange;
        this->trample = trample;

    }

    Model::Model(std::string name, int* stats) {

        this->name = name;
        this->maxHP          = stats[0];
        this->price          = stats[1];
        this->attackScore    = stats[2];
        this->range          = stats[3];
        this->minimumRange = stats[4];
        this->trample        = stats[5];

    }

    int Model::getMaxHealth() {
        return maxHP;
    }

    std::string Model::getName() {
        return name;
    }

    int Model::getPrice() {
        return price;
    }

    std::string Model::toString() {
        std::string disp;
        disp = "[" +name + "\nmaxHealth=" + std::to_string(maxHP) + "\nprice=" + std::to_string(price)
        + "\nattackScore= " + std::to_string(attackScore) + "\nrange= " + std::to_string(range) + "\n]";
        return disp;
    }
