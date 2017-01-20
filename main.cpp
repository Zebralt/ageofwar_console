#include <iostream>
#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

#include <fstream>
#include <string>
#include <string.h>

using namespace std;

//void printBattlefield(std::ofstream& file, Game& g);

struct Point { int x,y; Point(int a, int b) : x(a), y(b){}};

std::ostream& operator<<(ostream& o, const Point& p) {
    o << p.x << ':' << p.y;
    return o;
}

void  inst(std::vector<Point*>& ae) {
    Point* i = new Point(1,2);
    std::cout << "instanciated " << i << std::endl;
    ae.push_back(i);
}

int main(int argc, char* argv[])
{

    AI red("Red");
    AI blue("Blue");
    Game aowg(blue, red);
	if (argc > 1 && !strcmp(argv[1],"-v")) {
		aowg.setVerbose(1);
	}

    std::ofstream AowFile;
    AowFile.open("AoWGame.txt", std::ios::app); //open file
//    printBattlefield(AowFile,aowg);

    ///if (false)

    while(!aowg.hasEnded()) {
        std::cout << "\n\n{";
        std::cout << "Turn " << aowg.getCurrentTurn() << ":" << std::endl;
        aowg.unravel();
        std::cout << "}"<< std::endl;
//        printBattlefield(AowFile,aowg);
    }

    /*std::vector<Point*> ae;
    inst(ae);
    inst(ae);
    for (unsigned int i=0;i<ae.size();i++)
        std::cout << *ae[i] << std::endl;*/
   /* Player& winner = aowg.getWinner();
    std::cout << winner << " won the game." << std::endl;*/

    return 0;
}
//
//void printBattlefield(ofstream& file, Game& g)
//{
//    Player& red = g.getRed();
//    Player& blue = g.getBlue();
//    int i;
//    if(file)
//    {
//        file << endl;
//    }
//
//    else
//    {
//        std::cerr << "Impossible d ouvrir le fichier" << endl;
//    }
//}
