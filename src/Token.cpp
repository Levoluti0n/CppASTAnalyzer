#include "Token.hpp"

Token::Token(Type type, const std::string& value, int line)
    : value(value), type(type), line(line){}

Token::Type Token::getType() const {
    return type;
}

const std::string& Token::getValue() const {
    return value;
}

int Token::getLine() const {
    return line;
}

