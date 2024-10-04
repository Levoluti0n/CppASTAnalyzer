#ifndef LEXER_HPP
#define LEXER_HPP

#include <unordered_set>
#include "Token.hpp"
#include <string>
#include <vector>

class Lexer {
    public:
        explicit Lexer(const std::string&);
        std::vector<Token> tokenize();
    private:
        std::string source;
        size_t currentPosition;
        int currentLine;

        Token createIdentifierOrKeyword(const std::string&);
        Token createNumber(const std::string&);
        Token createDelimiter(const char);
        Token createOperator(const char);
        void skipWhitespace();
        Token nextToken();
        char getChar();

        const std::unordered_set<std::string> keywords = {
            "int", "float", "double", "char", "void", "class", "public", "private", "protected",
            "if", "else", "while", "for", "return", "static", "namespace", "using", "include"
        };
};

#endif