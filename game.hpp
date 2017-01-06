#ifndef game_hpp__
#define game_hpp__
#include <vector>

    class Player;
    class Model;
    class Unit;

    class Game {
    private:
        Player& red;
        Player& blue;

        int nbturns;
        int currentTurn;
        int battlefieldLength;

        std::vector<Model> models;
        int redCursor, blueCursor; /* positions des unités de A et B les plus avancées */
		Unit *battlefieldUnits; /*Représentation du terrain et des unités présentes */

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

        friend bool operator==(Player& p, Player& q);
    };

#endif // game_hpp__
