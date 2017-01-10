#ifndef game_hpp__
#define game_hpp__
#include <vector>

/// GAME STATUS FLAGS

#define PLAYING     0x1
#define BLUE_WINS   0x10
#define RED_WINS    0x100
#define SETTLED     0x1000
#define DRAW        0x10

/// PARSER FLAGS

#define PARSING             0
#define PARSING_METADATA    1
#define PARSING_MODELS      2

#define UNKNOWN_HEADER      1
#define SYNTAX_ERROR        2

/// CONFIG FILE FLAGS

///

    class Player;
    class Model;
    class Unit;

    class Game {
    private:
        Player& red;
        Player& blue;

        int nbturns = 0;
        int currentTurn = 0;
        int battlefieldLength = 0;
        int goldPerTurn = 0;
        int nbPhases = 3; /* nombre de phases d'action */

        std::vector<Model> models;
        int redCursor = 0;
        int blueCursor = 0; /* positions des unités de A et B les plus avancées */ /* du front en somme */
		Unit* battlefieldUnits; /*Représentation du terrain et des unités présentes */

    public:
        Game(Player&, Player&);

        int hasEnded();
        Player& getCurrentPlayer();

        Unit* getUnits();

        int getEnemyCursor(Player&);

        int getDirection(Player&);

        int getCursor(Player&);

        void addModel(Model);

        bool checkPosition(int);

        bool runPhases(Player&);

        bool purchase(Player&, Model&);

        Player& getBlue();
        Player& getRed();

        Player& getWinner();

        bool loadConfig();

        void display();

        void update();

        short status();

        friend class Parser;
    };

    bool operator==(Player& p, Player& q);

#endif // game_hpp__
