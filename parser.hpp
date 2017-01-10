#ifndef parser_hpp__
#define parser_hpp__

#include <vector>
#include <string>

    class Game;

    class Parser {
    private:
        Game& game;

    public:
        Parser(Game&);
        Parser(Game&,std::string);
        bool parse(std::string);

        std::vector<std::string> split(std::string,char);
        std::vector<std::string> parseFile(std::string);
        std::vector<std::string> getWords(std::string);
        void removeChar(std::string&,char);
    };

#endif // parser_hpp__
