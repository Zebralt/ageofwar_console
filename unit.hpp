#ifndef unit_hpp__
#define unit_hpp__

    class UnitModel {
    protected:
        int maxHP = 10;
        int price = 0;
        int attackScore = 1;
        int range = 1;
        int exclusiveRange = 0;
        int speed = 1;

    public:
        UnitModel(std::string name, int maxHP, int price, int attackScore, int range, int exclusiveRange);

    };

    class Unit {
    private:
        UnitModel& model;
        Player& owner;
        int health;
        int pos;

    public:
        Unit(Player&,UnitModel&);

        int engage(Game&);

        std::vector<Unit*> checkLineOfSight(std::vector<Unit*>);
        bool attack(Unit&);
        void advance(Game&);

        void takeDamage(int);
        bool alive();

        void setPosition(int);
        void setHealth(int);

        int getHealth();
        int getPosition();

        Player& owner();
    };

    class Base : public Unit {
    private:

    };

#endif // unit_hpp__
