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

        /// GETTERS/SETTERS

        void setPosition(int i) { pos = i;};
        void setHealth(int);
        virtual void setModel(Model&);
        Model& getModel() { return model; }
        int getHealth();
        int getPosition() { return pos; }
        std::string getName() { return model.getName(); }
        int getId() { return id; }
        Player& getOwner() { return owner; }

        /// INGAME BEHAVIOURS

        /* inflige des dommages a l'unite */
        void takeDamage(int);
        /* renvoie TRUE si la vie de l'unite > 0 */
        bool alive();
        /* cherche la base ennemie et determine si elle est a portee */
        bool checkForEnemyCastle(Game&);
        /* attaque la base ennemie */
        void attackEnemyCastle(Game&);
        /* repere les unites ennemies et cibles potentielles */
        std::vector<std::shared_ptr<Unit>> checkLineOfSight(Game&);
        bool attack(Unit&);
        /* tente d'avancer sur le champ de bataille */
        bool advance(Game&); // mobile
        /* tente d'effectuer une action d'attaque, soit : chercher des cibles et attaquer si possible OU chercher la base ennemie et attaquer si possible */
        int engage(Game&);
        /* renvoie le nombre d'actions restantes */
        int haveRemainingActions();
        /* utilise un point d'action */
        void useAction() { remainingActions--;}
        /* restaure les points d'action */
        void replenish();

        /// DISPLAY

        std::string toString();
        std::string healthRatio()
        { return "[" + std::to_string(health) + "/" + std::to_string(model.maxHP) + "]"; }

        friend std::ostream& operator<<(std::ostream&, const Unit&);
    };

    std::ostream& operator<<(std::ostream& o, const Unit& u);

#endif // unit_hpp__
