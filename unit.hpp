#ifndef unit_hpp__
#define unit_hpp__

#include <vector>
#include <string>
#include <memory>
#include "model.hpp"

    class Game;
    class Player;

    class Unit {
    protected:
        Model& model;
        Player& owner;
        int health;
        int pos = -1;
        int remainingActions = model.nbActions;

    public:
        Unit(Player&,Model&);
        Unit();
        Unit(const Unit& u);

        void takeDamage(int);
        bool alive();

        bool attackEnemyCastle(Game&);
        bool checkForEnemyCastle(Game&); /* est-on a portee de la base ennemie ? */
        std::vector<std::shared_ptr<Unit>> checkLineOfSight(std::vector<std::shared_ptr<Unit>>,int from, int ennemyCursor, int direction);
        bool attack(Unit&);
        bool advance(Game&); // mobile
        int engage(Game&);

        int haveRemainingActions();
        void act() { remainingActions--;}

        void setPosition(int i) { pos = i;};
        void setHealth(int);

        virtual void setModel(Model&);

        Model& getModel() { return model; }
        int getHealth();
        int getPosition() { return pos; }

        Player& getOwner();
    };

#endif // unit_hpp__
