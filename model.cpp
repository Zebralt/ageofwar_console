#include "model.hpp"

    Model::Model(std::string name, int maxHP, int price) {

        this->name = name;
        this->maxHP = maxHP;
        this->price = price;

    }

    int Model::getMaxHealth() {
        return maxHP;
    }

    HostileModel::HostileModel(std::string name, int maxHP, int price, int attackScore, int range, int exclusiveRange)
    : Model(name,maxHP,price)
    {

        this->attackScore = attackScore;
        this->range = range;
        this->exclusiveRange = exclusiveRange;

    }
