#ifndef player_hpp__
#define player_hpp__

    class Player {
    protected:
        unsigned int hp;
        std::string name;
        unsigned int gold;


    public:
        Player(std::string);

        virtual void play() = 0;
        bool hasLost();
    };

    class Human : public Player {

    public:
        Human(std::string);
    };

    class AI : public Player {

        static int iaCount = 0;

    public:
        AI(std::string);
        AI();

        void play();
    };

#endif // player_hpp__
