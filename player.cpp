#include "player.hpp"

    Player::Player(std::string na) : name(na) {

    }

    Human::Human(std::string na) : Player(na) {

    }

    void Human::play() {

    }

    Model Human::buy(std::vector<Model> mods)
    {
        std::cout << "Rentrez le numero de l unite a acheter parmis les suivantes :" << endl;
        int i=0;
        while(mods[i].getPrice() <= gold)
        {
            std::cout << i+1 << " : " << mods[i].getName() << endl ;
            i++;
        }
        std::cin >> i;
        return mods[i];
    }

    AI::AI(std::string na) : Player(na) {

    }

    Model AI::buy(std::vector<Model> mods) {
        Model temp;
        temp = mods[0]
        for (int i=1; i<models.size(); i++)
        {
            if(mods[i].getPrice() > temp.getPrice() && mods[i].getPrice()<=gold)
                {temp=mods[i];}
        }

    }

    void AI::play(){}


    std::ostream& operator<<(std::ostream& o, const Player& p) {
        o << p.name;
        return o;
    }
