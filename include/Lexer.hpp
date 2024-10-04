#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"
#include <string>
#include <vector>

class Lexer {
    public:
        Lexer(const std::string&);
        std::vector<Token> tokenize();
    private:
        std::string sourceCode;
        size_t currentPosition;

        char getChar();
        Token nextToken();
        char peekChar() const;
        void skipWhitespace();
};

#endif