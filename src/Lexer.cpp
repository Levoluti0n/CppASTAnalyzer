#include "Lexer.hpp"

Lexer::Lexer(const std::string& sourceCode)
    : sourceCode(sourceCode), currentPosition(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (currentPosition < sourceCode.length()) {
        skipWhitespace();
        tokens.push_back(nextToken());
    }
    tokens.emplace_back(Token::Type::EndOfFile, "", currentPosition);
    return tokens;
}

Token Lexer::nextToken() {
    char currentChar = getChar();

    if (std::isalpha(currentChar)) {
        std::string identifier;
        while (std::isalnum(currentChar)) {
            identifier += currentChar;
            currentChar = getChar();
        }
        --currentPosition;
        return Token(Token::Type::Identifier, identifier, currentPosition);
    }


}

char Lexer::peekChar() const {
    return currentPosition < sourceCode.length() ? sourceCode[currentPosition] : '\0';
}

char Lexer::getChar() {
    return peekChar() ? sourceCode[currentPosition++] : '\0';
}

void Lexer::skipWhitespace() {
    while (std::isspace(peekChar())) {
        currentPosition++;
    }
}
