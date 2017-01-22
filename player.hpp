#ifndef player_hpp__
#define player_hpp__
#include <string>
#include <vector>
#include <memory>
#include "globals.hpp"


    class Game;
    class Model;

    class Player {
    protected:
        std::string name;
        unsigned int gold = 0;
        int health = 100;
        friend std::ostream& operator<<(std::ostream&, const Player&);

    public:
        Player(std::string);

        /// GETTERS/SETTERS

        std::string getName();
        void setName(std::string);
        int getHealth();
        unsigned int getGold();

        /// INGAME BEHAVIOURS

        /* Fonction globale d'action du joueur */
        virtual void play(Game&) = 0;
        /* renvoie TRUE si la vie du joueur est <= 0 */
        bool hasLost();
        /* retire de l'argent au joueur */
        void debit(int i);
        /* inflige des degats au joueur */
        void takeDamage(int i);
        /* comportement d'achat */
        virtual model_ptr buy(std::vector<model_ptr>&) = 0;
        /* donne de l'argent au joueur */
        void give(unsigned int i) { gold += i;}

        /// DISPLAY

        std::string toString();

    };

    std::ostream& operator<<(std::ostream&, const Player&);

    class Human : public Player {

    public:
        Human(std::string);

        void play(Game&);
        model_ptr buy(std::vector<model_ptr>&);
    };

    class AI : public Player {

    public:
        AI(std::string);
        AI();

        virtual void play(Game&);
        virtual model_ptr buy(std::vector<model_ptr>&);
    };

#endif // player_hpp__
