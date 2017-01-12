#ifndef player_hpp__
#define player_hpp__
#include <string>

    class Player {
    protected:
        std::string name;
        unsigned int gold = 0;
        int health = 100;
        friend std::ostream& operator<<(std::ostream&, const Player&);

    public:
        Player(std::string);

        virtual void play() = 0;
        bool hasLost();

        std::string getName() { return name; }
        int getHealth() { return health; }

        int getGold() { return gold; }
        void debit(int i) { gold -= i; }
        void takeDamage(int i) { health -= i;}
    };

    std::ostream& operator<<(std::ostream&, const Player&);

    class Human : public Player {

    public:
        Human(std::string);

        void play();
    };

    class AI : public Player {

    public:
        AI(std::string);
        AI();

        void play();
    };

#endif // player_hpp__
