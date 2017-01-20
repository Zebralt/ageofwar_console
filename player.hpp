#ifndef player_hpp__
#define player_hpp__
#include <string>
#include <vector>
#include <memory>


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

        virtual void play(Game&) = 0;
        bool hasLost();

        std::string getName();
        int getHealth();

        unsigned int getGold();
        void debit(int i);
        void takeDamage(int i);
        virtual Model& buy(std::vector<std::shared_ptr<Model>>&) = 0;

        void give(unsigned int i) { gold += i;}

    };

    std::ostream& operator<<(std::ostream&, const Player&);

    class Human : public Player {

    public:
        Human(std::string);

        void play(Game&);
        Model& buy(std::vector<std::shared_ptr<Model>>&);
    };

    class AI : public Player {

    public:
        AI(std::string);
        AI();

        void play(Game&);
        Model& buy(std::vector<std::shared_ptr<Model>>&);
    };

#endif // player_hpp__
