#include "player.hpp"
#include "model.hpp"
#include "unit.hpp"
#include "game.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

#define stringList std::vector<std::string>

    bool operator==(Player& p, Player& q) {
        return p.getName() == q.getName();
    }

    Game::Game(Player& b, Player& r) : red(r), blue(b)
    {
        loadConfig();
        currentTurn = 0;
        battlefieldUnits = (Unit*) calloc(battlefieldLength,sizeof(Unit));
        redCursor = battlefieldLength-1;
        blueCursor = 0;
    }

    int Game::hasEnded() {
        return 1;
    }

    Player& Game::getCurrentPlayer() {
        return (currentTurn%2?red:blue);
    }

    void Game::addModel(Model um) {
        models.push_back(um);
    }

    bool Game::checkPosition(int pos) {
		if (&battlefieldUnits[pos]==nullptr)
			return true;
		return false;
    }

    Player& Game::getBlue() {
        return blue;
    }

    Player& Game::getRed() {
        return red;
    }

    Player& Game::getWinner() {
        return blue;
    }

    Unit* Game::getUnits() {
        return battlefieldUnits;
    }

    bool Game::loadConfig() {
        short status = PARSING;
        std::vector<std::string> content = parseFile("info.cfg");
        for (unsigned int i=0; i<content.size(); i++) {
            std::string& str = content[i];
            removeChar(str,' ');
        }

        for (unsigned int i=0; i<content.size(); i++) {
            std::string& line = content[i];
            std::cout << std::endl << i;
            if (line.empty() || line[0] == '#') continue; /* ligne vide ou commentaire */

            /* is it a header ? */
            if (line[0] == '[') {
                std::string header = line.substr(1,line.length()-2);
                if (header == "Metadata") {
                    status = PARSING_METADATA; std::cout << ":STATUS CHANGED TO PARSING_METADATA";
                }
                else if (header == "Units") {
                    status = PARSING_UNITS; std::cout << ":STATUS CHANGED TO PARSING_UNITS";
                }
                else {
                    std::cout << ":UNKNOWN HEADER: " << header << std::endl;
                    return UNKNOWN_HEADER;
                }
            }
            else if (status == PARSING_METADATA) {
                stringList spl = split(line,':');
                std::string name = spl[0];
                //std::string value = spl[1]; int val = std::atoi(value);
            }
            else std::cout << "SYNTAX UNKNOWN";
        }

        return true;
    }

    int Game::getEnemyCursor(Player& p) {
        if (p == red) {
            return blueCursor;
        }
        else return redCursor;
    }

    int Game::getDirection(Player& p) {
        return p == blue;
    }

    bool Game::runPhases(Player& currentPlayer) {
      /*  Unit* tmp;
        int cursor = getCursor(currentPlayer);
        int direction = getDirection(currentPlayer);
        if (direction) {
            for (int i=0;i<cursor;i++) {

            }
        }
        else {
            //for (int i=battlefieldLength-1;i>=;i--)
        }*/
        return true;
    }

    void Game::display() {
        std::cout << "\t";
        for (int i=0;i<12;i++) std::cout << i+1 << "\t";
        std::cout << std::endl;
        std::cout << "\t";
        std::cout << blue.getHealth();
        for (int i=0;i<10;i++)
        std::cout << "\t_";
        std::cout << "\t";
        std::cout << red.getHealth();
        std::cout << std::endl;
    }

    void Game::update() {

    }

    short Game::status() {
        update();
        if (!red.getHealth() && !blue.getHealth()) return DRAW;
        else if (!red.getHealth() && blue.getHealth()) return SETTLED & BLUE_WINS;
        else if (red.getHealth() && !blue.getHealth()) return SETTLED & RED_WINS;
        else if (currentTurn >= nbturns) return DRAW;
        else return PLAYING;
    }

    /// FILE PARSER

    std::vector<std::string> getWords(std::string text) {
        std::vector<std::string> content;
        std::stringstream tstream(text);
        std::string word;
        while(tstream >> word) {
            content.push_back(word);
        }
        return content;
    }

    std::vector<std::string> split(std::string text, char delimiter) {
        std::vector<std::string> content;
        std::stringstream tstream(text);
        std::string word;
        while(std::getline(tstream,word,delimiter)) {
            content.push_back(word);
        }
        return content;
    }

    std::vector<std::string> parseFile(std::string filepath) {
        std::ifstream myfile;
        myfile.open(filepath.c_str(), std::ifstream::in);
        std::vector<std::string> content;
        std::string line;
        while (!myfile.eof() && std::getline(myfile,line)) {
            content.push_back(line);
        }
        myfile.close();
        return content;
    }

    void removeChar(std::string& str, char a) {
        std::string output; output.reserve(str.length());
        for (unsigned int i=0; i<str.length(); i++) {
            if (str[i] != a) output += str[i];
        }
        str = output;
    }
