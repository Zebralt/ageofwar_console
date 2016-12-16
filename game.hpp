#ifndef game_hpp__
#define game_hpp__
#include <vector>

    class Player;
    class UnitModel;
    class Unit;

    class Game {
    private:
        Player& red;
        Player& blue;

        int nbturns;
        int currentTurn;

        std::vector<UnitModel> unitModels;
        std::vector<Unit*> units;

    public:
        Game(Player&, Player&, int nbt);

        int hasEnded();
        Player& getCurrentPlayer();

        void addUnitModel(UnitModel);
        const std::vector<Unit*> getUnits();

        int checkPosition(int);

        bool nextTurn();

        bool purchase(Player&, UnitModel&);

        Player& getBlue();
        Player& getRed();

        Player& getWinner();
    };

#endif // game_hpp__
