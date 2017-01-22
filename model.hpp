#ifndef model_hpp__
#define model_hpp__

#include <string>
#include <vector>

    enum Action {ATTACK = 0, MOVE, IDLE};

    class Model {
    protected:
        std::string name;
        int maxHP = 10;
        unsigned int price = 0;
        int nbActions = 0;
        std::vector<Action> actions;
        int flags;

        int attackScore = 1;
        int range = 1;          // portée maximale
        int minimumRange = 0; // portée minimale
        int trample = 0;        // area of effect

    public:

        friend class Unit;
        friend class Parser;

        Model(std::string name,
              int maxHP,
              unsigned int price,
              int nbActions,
              int attackScore,
              int range,
              int minimumRange,
              int trample = 0);


        Model(std::string, int*);
        Model() {}

        /// GETTERS

        int getMaxHealth();
        std::string getName();
        unsigned int getPrice();
        std::vector<Action>& getActions() { return actions; }

        virtual ~Model() {}

        /// DISPLAY

        std::string toString();
        std::string stats();
    };

#endif
