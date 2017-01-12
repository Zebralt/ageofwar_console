#ifndef model_hpp__
#define model_hpp__

#include <string>
#include <vector>
#include "parser.hpp"

    #define AOE 0x10
    #define DISTANCE 0x100

    enum Action {ATTACK, MOVE, IDLE};

    class Model {
    protected:
        std::string name;
        int maxHP = 10;
        int price = 0;
        int nbActions = 0;
        std::vector<Action> actions;
        int flags;

        int attackScore = 1;
        int range = 1;          // portée maximale
        int minimumRange = 0; // portée minimale
        int trample = 0;        // area of effect

    public:

        friend class Unit;
        friend bool Parser::parse(std::string);

        Model(std::string name,
              int maxHP,
              int price,
              int nbActions,
              int attackScore,
              int range,
              int minimumRange,
              int trample = 0);

        Model(std::string, int*);

        int getMaxHealth();
        std::string getName();
        int getPrice();

        std::vector<Action>& getActions() { return actions; }

        virtual ~Model() {}

        std::string toString();
    };

#endif
