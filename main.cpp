#include <iostream>
#include <fstream>

#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

using namespace std;

void initFile(fstream file, Game g, Player &r, Player &b);
void printBattlefield(fstream file, Game g);

int main()
{
    AI red("Red");
    AI blue("Blue");
    Game aowg(red,blue);

    std::fstream AowFile("test.txt", ios::in | ios::app); //open file

    // main loop would look like this :

    initFile(AowFile, aowg, red,blue);

    while(!aowg.hasEnded()) {
        aowg.display();
        std::cout << std::endl;
        aowg.update();
        std::cout << std::endl;
        printBattlefield(AowFile, aowg);
    }

    Player& winner = aowg.getWinner();
    std::cout << winner << " won the game." << std::endl;

    AowFile.close(); //close file

    return 0;
}

void initFile(std::fstream file, Player &r, Player &b)
{
    if(file)
    {
        file << r.getName() << "\t" ;
        for(int i = 0; i<g.battlefieldLenght; i++)
        {
            file << "     " ;
        }
        file << "\t" << b.getName() << endl;
        for(int i=0; i<g.battlefieldLenght; i++)
        {
            file << "  _  " ;
        }
    }
}

void printBattlefield( fstream file, Game g)
{
    int i;
    if(file)
    {
        file << endl;
    }
    //Unités rouges
    for(i=0; i<g.getCursor(red) ; i++)
    {
        if(g.getUnits()[i]==nullptr)   {file << " _ ";}
        else{file <<g.battlefieldUnits[i].getModel().getName() ; }
    }
    file << "\t" ;
    //No Man's Land
    for (i=g.redCursor; i<g.blueCursor ; i++)
    {
        file << " _ ";
    }
    file << "\t";
    //Unités bleues
    for(i=g.getCursor(blue); i<g.getBattlefieldLenght() ; i++)
    {
        if(g.battlefieldUnits[i]==0)   {file << " _ ";} /*!!!!!!!!!!!!!!!!!!!!!!!!!!*/
        else{file << g.battlefieldUnits[i].getModel().getName() ; }
    }

    std::cerr << "Impossible d ouvrir le fichier" << endl;
}
