#ifndef unit_hpp__
#define unit_hpp__

#include <vector>
#include <string>

    class Game;
    class Player;

    class UnitModel {
    protected:
        std::string name;
        int maxHP = 10;
        int price = 0;
        int attackScore = 1;
        int range = 1;
        int exclusiveRange = 0;
        int speed = 1;

    public:

        friend class Unit;

        UnitModel(std::string name, int maxHP, int price, int attackScore, int range, int exclusiveRange);

        int getMaxHealth();
    };

    class Unit {
    protected:
        UnitModel& model;
        Player& owner;
        int health;
        int pos;

        bool attack(Unit&);

    public:
        Unit(Player&,UnitModel&);

        virtual int engage(Game&);

        std::vector<Unit*> checkLineOfSight(std::vector<Unit*>);
        bool advance(Game&); // mobile

        void takeDamage(int);
        bool alive();

        void setPosition(int);
        void setHealth(int);

        int getHealth();
        int getPosition();

        Player& getOwner();
    };

    class Building : public Unit {

    };

    class MobileUnit : public Unit {
    public:
        MobileUnit(Player&, UnitModel&);
    };

#endif // unit_hpp__
