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
        int id;
        
        static int instanceCount;

    public:
        Unit(Player&,Model&);
        Unit();
        Unit(const Unit& u);

        void takeDamage(int);
        bool alive();

        bool attackEnemyCastle(Game&);
        bool checkForEnemyCastle(Game&); /* est-on a portee de la base ennemie ? */
        std::vector<std::shared_ptr<Unit>> checkLineOfSight(Game&);
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
        std::string getName() { return model.getName(); }
        int getId() { return id; }

        Player& getOwner() { return owner; }

        std::string toString();
        std::string healthRatio() 
        { return "[" + std::to_string(health) + "/" + std::to_string(model.maxHP) + "]"; }

        friend std::ostream& operator<<(std::ostream&, const Unit&);
        
        void replenish();
    };

    std::ostream& operator<<(std::ostream& o, const Unit& u);

#endif // unit_hpp__
