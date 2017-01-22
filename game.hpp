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
#define SETTLED     0x10
#define DRAW        0x100
#define BLUE_WINS   0x1000
#define RED_WINS    0x0000

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
        /* renvoie 1 pour le joueur de gauche, 0 pour le joueur de droite */
        int getDirection(Player&);
        int getBattlefieldLength();
        Player& getBlue();
        Player& getRed();
        std::shared_ptr<Player> getWinner();
        unit_ptr getUnitAt(int);
        int getCurrentTurn() { return currentTurn; }

        /// DISPLAY
        void minimalDisplay();
        void display();
        void printCorrectWidth(int,int);
        void listModels();
		bool VERBOSE = 0;
		bool MDISPLAY = 0;
		void setVerbose(bool);

		/// INGAME BEHAVIOURS
		/* renvoie TRUE si aucune Unit a cette position */
        bool positionTaken(int);
        /* deroule les phases d'action d'un joueur */
        bool runPhases(Player&);
        /* enregistre l'achat d'une Unit par un joueur */
        bool purchase(Player&, model_ptr);
        /* Fonction principale de deroulement du jeu */
        void update();
        /* Inflige des degats au chateau (a la base) du joueur */
        void damageCastle(Player& p, int); // infliger des degats au chateau du joueur:
        // remove units if dead
        /* supprimes les unites mortes, et met a jour les points d'actions des unites */
        void checkUnits();
        /* ajoute une unite sur le champ de bataille */
        bool addUnit(std::shared_ptr<Unit>, Player&);
        /* supprime une unite du champ du bataille */
		void killUnit(unit_ptr);
		/* bombarde un emplacement ; utilisé par trample(catapulte, plusieurs cases attaquees)*/
		void bombard(int spot, int attackScore);

    };

    bool operator==(Player& p, Player& q);

#endif // game_hpp__
