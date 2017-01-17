#include <iostream>
#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

#include <fstream>
#include <string>

using namespace std;

void initFile(std::ofstream& file, Game&);
void printBattlefield(std::ofstream& file, Game& g);

int main()
{
    AI red("Red");
    AI blue("Blue");
    Game aowg(red,blue);

    std::ofstream AowFile;
    //AowFile.open("test.txt", std::ios::app); //open file

    // main loop would look like this :
    //initFile(AowFile, aowg);


    while(!aowg.hasEnded()) {
        std::cout << '{';
        aowg.display();
        aowg.unravel();
        std::cout << '}' << std::endl;
    }

    Player& winner = aowg.getWinner();
    std::cout << winner << " won the game." << std::endl;

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
