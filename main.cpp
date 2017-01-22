#include <iostream>
#include "player.hpp"
#include "unit.hpp"
#include "game.hpp"

#include <string>
#include <string.h>
#include <memory>

int main(int argc, char* argv[])
{

    std::cout << "Welcome to ageofwar_console !" << std::endl;

    AI red("RedAI");
    AI blue("BlueAI");
    Human humanPlayer("");
    int status;
    std::unique_ptr<Game> aowg;

    /* CHoix du mode de jeu */
	std::cout << "Choose game mode :" << std::endl;
	std::cout << "1 - AI vs AI" << std::endl << "2 - You vs AI" << std::endl;
	int ch = 0;
    while (!ch) {
        std::cin >> ch;
        std::cin.ignore();
    }
    if (ch == 1) {
        aowg = std::unique_ptr<Game>(new Game(blue, red));
    }
    else {
        /* Choix du nom */
        std::string name;
        while (name.empty()) {
            std::cout << "Enter a name :" << std::endl;
            std::cin >> name;
        }
        humanPlayer.setName(name);
        aowg = std::unique_ptr<Game>(new Game(humanPlayer, red));
    }
    for (int i=1;i<argc;i++) {
        if (!strcmp(argv[i], "-m")) {
            aowg->MDISPLAY = 1;
        }
        if (!strcmp(argv[i],"-v")) {
            aowg->setVerbose(1);
        };
    }
    /* Boucle principale du jeu */
    while(!(status = aowg->hasEnded())) {
        std::cout << "\n\n{";
        std::cout << "Turn " << aowg->getCurrentTurn() << ":" << std::endl;
        aowg->update();
        std::cout << "status is 0x" << std::hex << aowg->status() << std::dec << "}"<< std::endl;
    }

    return 0;
}
