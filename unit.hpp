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

    public:
        Unit(Player&,Model&);

        virtual int engage(Game&); // une action par temps t
        void takeDamage(int);
        bool alive();

        void setPosition(int);
        void setHealth(int);

        virtual void setModel(Model&);

        int getHealth();
        int getPosition();

        Player& getOwner();
    };


    class HostileUnit : public Unit {
        protected:
        public:
            HostileUnit(Player&, HostileModel&);
            std::vector<Unit*> checkLineOfSight(std::vector<Unit*>);
            bool attack(Unit&);
    };


    class Building : public Unit {
        public:

    };

    class MobileUnit : public Unit {
    private:
    public:
        MobileUnit(Player&, MobileModel&);
        bool advance(Game&); // mobile
    };

#endif // unit_hpp__
