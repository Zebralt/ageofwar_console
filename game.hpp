#ifndef game_hpp__
#define game_hpp__

    class AgeOfWarGame {
    private:
        Player& red;
        Player& blue;

        int nbturns;
        int currentTurn;

        std::vector<UnitModel> unitModels;

    public:
        AgeOfWarGame(Player&, Player&, int nbt);

        int hasEnded();
        Player& getCurrentPlayer();

        void addUnitModel(UnitModel);
    };

#endif // game_hpp__
