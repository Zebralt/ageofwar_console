#include "model.hpp"

#define GET_ACTION_STR(a) (a == ATTACK?"ATTACK":a == MOVE?"MOVE":"IDLE")

    /// MODEL : CLASS

    Model::Model(std::string name, int maxHP, unsigned int price, int nbActions, int attackScore, int range, int minimumRange, int trample)
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

    unsigned int Model::getPrice() {
        return price;
    }

    std::string Model::toString() {
        std::string disp;
        disp = "[" +name + "\n";
        disp += "maxHealth=" + std::to_string(maxHP) + "\nprice=" + std::to_string(price)
        + "\nattackScore= " + std::to_string(attackScore) + "\nrange= " + std::to_string(range);
        std::string act;
        for (unsigned int i=0;i<actions.size();i++) {
            act = act + GET_ACTION_STR(actions[i]) + " ";
        }
        disp += "\nActions: " + act;
        disp += "\n]";
        return disp;
    }
