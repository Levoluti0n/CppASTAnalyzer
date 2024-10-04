#ifndef PARSER_HPP
#define PARSER_HPP

#include "ASTNode.hpp"
#include "Token.hpp"
#include <vector>
#include <memory>

class Parser {
public:
    Parser(const std::vector<Token>&);
    std::shared_ptr<ASTNode> parse();

private:
    std::vector<Token> tokens;
    size_t currentPosition;

    Token currentToken() const;
    Token nextToken();

    std::vector<std::string> parseParameters();
    std::shared_ptr<ASTNode> parseVariable();
    std::shared_ptr<ASTNode> parseOperator();
    std::shared_ptr<ASTNode> parseMethod();
    std::shared_ptr<ASTNode> parseClass();
};

#endif
