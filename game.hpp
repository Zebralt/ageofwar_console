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

        std::vector<Model> models;
        std::vector<Unit*> units;

    public:
        Game(Player&, Player&, int nbt);

        int hasEnded();
        Player& getCurrentPlayer();

        void addModel(Model);
        const std::vector<Unit*> getUnits();

        int checkPosition(int);

        bool nextTurn();

        bool purchase(Player&, Model&);

        Player& getBlue();
        Player& getRed();

        Player& getWinner();

        bool loadModels();
    };

#endif // game_hpp__
