#ifndef game_hpp__
#define game_hpp__

    class AgeOfWarGame {
    private:
        Player& red;
        Player& blue;

        int nbturns;
        int currentTurn;

        std::vector<UnitModel> unitModels;
        std::vector<Unit*> units;

    public:
        AgeOfWarGame(Player&, Player&, int nbt);

        int hasEnded();
        Player& getCurrentPlayer();

        void addUnitModel(UnitModel);
        const std::vector<Unit*> getUnits();

        bool nextTurn();

        bool purchase(Player&, UnitModel&);
    };

#endif // game_hpp__
