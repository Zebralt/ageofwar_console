#ifndef game_hpp__
#define game_hpp_

#include <vector>
#include <memory>
#include "parser.hpp"

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

#define NEW(type, nb) (type*) calloc((unsigned) nb,sizeof(type))

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
//		std::vector<Unit> battlefieldUnits; /*Représentation du terrain et des unités présentes */
        std::vector<std::shared_ptr<Unit>> blueUnits;
        std::vector<std::shared_ptr<Unit>> redUnits;

        bool addUnit(std::shared_ptr<Unit>, Player&);
    public:
        Game(Player&, Player&);

        int hasEnded();

        std::vector<std::shared_ptr<Unit>> getUnits();
        std::vector<std::shared_ptr<Unit>>& getUnits(Player& p);

        std::vector<Model>& getModels();

        int getEnemyCursor(Player&);

        Player& getEnemy(Player&);

        int getDirection(Player&);

        int getCursor(Player&);

        int getBattlefieldLength();

        void addModel(Model);

        bool checkPosition(int); /* check if position is free */

        bool runPhases(Player&);

        bool purchase(Player&, Model&);

        Player& getBlue();
        Player& getRed();

        Player& getWinner();

        bool loadConfig();

        void display();

        /* main function of game running */
        void unravel();

        /* Met a jour les curseurs a la fin d'un tour */
        void updateCursors();

        short status();

        friend bool Parser::parse(std::string);

        void listModels();

        bool damageCastle(Player& p, int); // infliger des degats au chateau du joueur:

        // remove units if dead
        void checkUnits();

    };

    bool operator==(Player& p, Player& q);

#endif // game_hpp__
