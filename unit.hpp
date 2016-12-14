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
        int HP = maxHP;
        int pos;

    public:
        Unit(Player&,UnitModel&);

        void checkLineOfSight();
        void attack(Unit&);
        void advance();

        void takeDamage();
        bool alive();
    };

#endif // unit_hpp__
