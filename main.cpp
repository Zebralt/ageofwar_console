#include <iostream>
#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

#include <fstream>
#include <string>
#include <string.h>

using namespace std;

void initFile(std::ofstream& file, Game&);
void printBattlefield(std::ofstream& file, Game& g);

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
    //AowFile.open("test.txt", std::ios::app); //open file
    //initFile(AowFile, aowg);

    ///if (false)

    while(!aowg.hasEnded()) {
        std::cout << '{';
        aowg.unravel();
        std::cout << '}' << std::endl;
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
//void initFile(std::ofstream& file, Game& g)
//{
//    if(file)
//    {
//        file << g.getRed().getName() << "\t";
//        for(int i = 0; i<g.getBattlefieldLength(); i++)
//        {
//            file << "     " ;
//        }
//        file << "\t" << g.getBlue().getName() << endl;
//        for(int i=0; i<g.getBattlefieldLength(); i++)
//        {
//            file << "  _  " ;
//        }
//    }
//}
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
//    //Unités rouges
//    for(i=0; i<g.getCursor(red) ; i++)
//    {
//        if(g.getUnits()[i]==nullptr)   {file << " _ ";}
//        else{file <<g.getUnits()[i]->getModel().getName() ; }
//    }
//    file << "\t" ;
//    //No Man's Land
//    for (i=g.getCursor(red); i<g.getCursor(blue) ; i++)
//    {
//        file << " _ ";
//    }
//    file << "\t";
//    //Unités bleues
//    for(i=g.getCursor(blue); i<g.getBattlefieldLength() ; i++)
//    {
//        if(g.getUnits()[i]==nullptr)   {file << " _ ";} /*!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//        else{file << g.getUnits()[i]->getModel().getName() ; }
//    }
//
//    std::cerr << "Impossible d ouvrir le fichier" << endl;
//}
