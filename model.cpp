#include "model.hpp"

    /// MODEL : CLASS

    Model::Model(std::string name, int maxHP, int price, int nbActions) {

        this->name = name;
        this->maxHP = maxHP;
        this->price = price;
        this->nbActions = nbActions;

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

    /// COMBAT_UNIT_MODEL : CLASS

    CombatUnitModel::CombatUnitModel(std::string name, int maxHP, int price, int nbActions, int attackScore, int range, int exclusiveRange)
    : Model(name,maxHP,price,nbActions) {

        this->attackScore = attackScore;
        this->range = range;
        this->exclusiveRange = exclusiveRange;

    }
