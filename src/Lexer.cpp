#include "Lexer.hpp"
#include <iostream>
#include <cctype>

Lexer::Lexer(const std::string& source)
    : source(source), currentPosition(0), currentLine(1) {}

char Lexer::getChar() {
    if (currentPosition >= source.size()) {
        return '\0';
    }
    return source[currentPosition++];
}

void Lexer::skipWhitespace() {
    char currentChar = getChar();
    while (std::isspace(currentChar)) {
        if (currentChar == '\n') {
            ++currentLine;
        }
        currentChar = getChar();
    }
    if (currentChar != '\0') {
        --currentPosition;
    }
}

Token Lexer::createIdentifierOrKeyword(const std::string& identifier) {
    if (keywords.find(identifier) != keywords.end()) {
        return Token(Token::Type::Keyword, identifier, currentLine);
    }
    return Token(Token::Type::Identifier, identifier, currentLine);
}

Token Lexer::createNumber(const std::string& number) {
    return Token(Token::Type::Number, number, currentLine);
}

Token Lexer::createOperator(const char op) {
    return Token(Token::Type::Operator, std::string(1, op), currentLine);
}

Token Lexer::createDelimiter(const char delimiter) {
    return Token(Token::Type::Delimiter, std::string(1, delimiter), currentLine);
}

Token Lexer::nextToken() {
    skipWhitespace();
    char currentChar = getChar();

    if (currentChar == '\0') {
        return Token(Token::Type::EndOfFile, "", currentLine);
    }

    if (std::isalpha(currentChar) || currentChar == '_') {
        std::string identifier;
        while (std::isalnum(currentChar) || currentChar == '_') {
            identifier += currentChar;
            currentChar = getChar();
        }
        --currentPosition;
        return createIdentifierOrKeyword(identifier);
    }

    if (std::isdigit(currentChar)) {
        std::string number;
        while (std::isdigit(currentChar)) {
            number += currentChar;
            currentChar = getChar();
        }
        --currentPosition;
        return createNumber(number);
    }

    if (std::string("=+-*/%<>&|!").find(currentChar) != std::string::npos) {
        return createOperator(currentChar);
    }

    if (std::string(";,:(){}[]").find(currentChar) != std::string::npos) {
        return createDelimiter(currentChar);
    }

    return Token(Token::Type::Unknown, std::string(1, currentChar), currentLine);
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token token = nextToken();

     while (token.getType() != Token::Type::EndOfFile) {
        tokens.push_back(token);
        token = nextToken();
    }
    tokens.push_back(token); 

    return tokens;
}
