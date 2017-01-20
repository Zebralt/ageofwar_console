#ifndef game_hpp__
#define game_hpp_

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <sstream>

#include "globals.hpp"

/// GAME STATUS FLAGS

#define PLAYING     0x1
#define BLUE_WINS   0x10
#define RED_WINS    0x100
#define SETTLED     0x1000
#define DRAW        0x10

#define UNKNOWN_HEADER      1
#define SYNTAX_ERROR        2


#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
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
        int initialGold = 0;
        int nbPhases = 3; /* nombre de phases d'action */

        std::vector<model_ptr> models;
        std::vector<unit_ptr> blueUnits;
        std::vector<unit_ptr> redUnits;

    public:
        Game(Player&, Player&);

		/// LOADER
        bool loadConfig();
        void addModel(model_ptr);
        friend class Parser;

		/// GAME STATUS CHECK
        int hasEnded();
        short status();

		/// GETTERS
        std::vector<unit_ptr> getUnits();
        std::vector<unit_ptr>& getUnits(Player& p);
        std::vector<model_ptr>& getModels();
        int getDirection(Player&);
        int getBattlefieldLength();
        Player& getBlue();
        Player& getRed();
        Player* getWinner();
        unit_ptr getUnitAt(int);
        //int getEnemyCursor(Player&);
        //Player& getEnemy(Player&);
        //int getCursor(Player&);
        int getCurrentTurn() { return currentTurn; }

        /// DISPLAY
        void display();
        void printCorrectWidth(int,int);
        void listModels();
		bool VERBOSE = 0;
		void setVerbose(bool);

		/// INGAME BEHAVIOURS
        bool positionTaken(int); /* check if position is free */
        bool runPhases(Player&);
        bool purchase(Player&, Model&);
        /* main function of game running */
        void unravel();
        bool damageCastle(Player& p, int); // infliger des degats au chateau du joueur:
        // remove units if dead
        void checkUnits();
        bool addUnit(std::shared_ptr<Unit>, Player&);
		void killUnit(unit_ptr);

		/* bombarde un emplacement ; utilisé par TRAMPLE(AOE)CATAPULTE*/
		std::vector<unit_ptr> bombard(int spot, int attackScore);

    };

    bool operator==(Player& p, Player& q);

#endif // game_hpp__
