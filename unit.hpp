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

        void takeDamage(int);
        bool alive();

        bool attackEnemyCastle(Game&);
        bool checkForEnemyCastle(Game&); /* est-on a portee de la base ennemie ? */
        std::vector<Unit*> checkLineOfSight(Unit**,int from, int ennemyCursor, int direction);
        bool attack(Unit&);
        bool advance(Game&); // mobile
        int engage(Game&);

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

#endif // unit_hpp__
