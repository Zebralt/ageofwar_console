#ifndef unit_hpp__
#define unit_hpp__

#include <vector>
#include <string>
#include "model.hpp"

    class Game;
    class Player;

    class Unit {
    protected:
        Model& model;
        Player& owner;
        int health;
        int pos;
        int remainingActions = model.nbActions;

    public:
        Unit(Player&,Model&);

        virtual int engage(Game&); // try to attack
        void takeDamage(int);
        bool alive();

        int haveRemainingActions() { return remainingActions; }
        void act() { remainingActions--;}

        void setPosition(int);
        void setHealth(int);

        virtual void setModel(Model&);
        Model& getModel() { return model; }

        int getHealth();
        int getPosition();

        Player& getOwner();
    };


    class CombatUnit : public Unit {
        private:
        public:
            CombatUnit(Player&, CombatUnitModel&);
            std::vector<Unit*> checkLineOfSight(Unit*,int,int);
            bool attack(Unit&);
            bool advance(Game&); // mobile
            virtual int engage(Game&);
    };

#endif // unit_hpp__
