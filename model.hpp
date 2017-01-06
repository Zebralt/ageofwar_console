#ifndef model_hpp__
#define model_hpp__

#include <string>

    public enum ACTION { ATTACK, MOVE };

    class Model {
    protected:
        std::string name;
        int maxHP = 10;
        int price = 0;
        int nbActions = 0;
        ACTION* actions;

    public:

        friend class Unit;

        Model(std::string name, int maxHP, int price, int nbActions);

        int getMaxHealth();
        std::string getName();
        int getPrice();

        virtual ~Model() {}
    };

    class CombatUnitModel : public virtual Model {
        protected:
            int attackScore = 1;
            int range = 1;          // portée maximale
            int exclusiveRange = 0; // portée minimale
            int trample = 0;        // area of effect

        public:
            friend class CombatUnit;

            CombatUnitModel(std::string name, int maxHP, int price, int nbActions, int attackScore, int range, int exclusiveRange);

            ~CombatUnitModel() {}
    };
#endif
