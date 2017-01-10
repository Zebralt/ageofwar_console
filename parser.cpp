#include "game.hpp"
#include "parser.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>

#define stringList std::vector<std::string>

    Parser::Parser(Game& g) : game(g) {
    }

    Parser::Parser(Game& g, std::string path) : game(g)  {
        parse("info.cfg");
    }

    /// FILE PARSER
    bool Parser::parse(std::string path) {
        short status = PARSING;
        std::vector<std::string> content = parseFile(path);
        for (unsigned int i=0; i<content.size(); i++) {
            std::string& str = content[i];
            Parser::removeChar(str,' ');
        }

        for (unsigned int i=0; i<content.size(); i++) {
            std::string& line = content[i];
            std::cout << std::endl;
            if (line.empty() || line[0] == '#') continue; /* ligne vide ou commentaire */

            /* is it a header ? */
            if (line[0] == ';') return true;
            if (line[0] == '[') {
                std::string header = line.substr(1,line.length()-2);
                if (header == "Metadata") {
                    status = PARSING_METADATA; std::cout << ":STATUS CHANGED TO PARSING_METADATA";
                }
                else if (header == "Models") {
                    status = PARSING_MODELS; std::cout << ":STATUS CHANGED TO PARSING_MODELS";
                }
                else {
                    std::cout << ":UNKNOWN HEADER: " << header << std::endl;
                    return UNKNOWN_HEADER;
                }
            }
            else if (status == PARSING_METADATA) {
                stringList spl = split(line,':');
                std::string name = spl[0];
                std::string value = spl[1];
                int val = atoi(value.c_str());
                     if (name == "nbturns") game.nbturns = val;
                else if (name == "length")  game.battlefieldLength = val;
                else if (name == "goldperturn") game.goldPerTurn = val;
                else std::cout << "unrecognized syntax : " << line << std::endl;
            }
            else if (status == PARSING_MODELS) {
                stringList spl = split(line,':');
                if (spl.size() < 2) std::cout << ":syntax error" << std::endl;
                else {
                    std::string name = spl[0];
                    std::string stats = spl[1];
                    std::string actions;
                    int nbActions;
                    std::string flags;
                }
            }
            else std::cout << ": no meaning : " << line;
        }

        return true;
    }

    stringList Parser::getWords(std::string text) {
        stringList content;
        std::stringstream tstream(text);
        std::string word;
        while(tstream >> word) {
            content.push_back(word);
        }
        return content;
    }

    stringList Parser::split(std::string text, char delimiter) {
        stringList content;
        std::stringstream tstream(text);
        std::string word;
        while(std::getline(tstream,word,delimiter)) {
            content.push_back(word);
        }
        return content;
    }

    stringList Parser::parseFile(std::string filepath) {
        std::ifstream myfile;
        myfile.open(filepath.c_str(), std::ifstream::in);
        stringList content;
        std::string line;
        while (!myfile.eof() && std::getline(myfile,line)) {
            content.push_back(line);
        }
        myfile.close();
        return content;
    }

    void Parser::removeChar(std::string& str, char a) {
        std::string output; output.reserve(str.length());
        for (unsigned int i=0; i<str.length(); i++) {
            if (str[i] != a) output += str[i];
        }
        str = output;
    }
