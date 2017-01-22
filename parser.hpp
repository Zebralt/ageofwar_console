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

        /* separe une string selon un delimiteur */
        std::vector<std::string> split(std::string,char);
        /* lit un fichier texte ligne par ligne et stocke chaque ligne as a std::string in a std::vector */
        std::vector<std::string> parseFile(std::string);
        /* split the string with the ' ' delimiter */
        std::vector<std::string> getWords(std::string);
        /* supprime un char de la std::string */
        void removeChar(std::string&,char);
    };

#endif // parser_hpp__
