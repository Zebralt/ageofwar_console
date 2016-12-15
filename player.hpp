#ifndef player_hpp__
#define player_hpp__
#include <string>

    class Player {
    protected:
        std::string name;
        unsigned int gold = 0;

    public:
        Player(std::string);

        virtual void play() = 0;
        bool hasLost();
    };

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
