#include "Parser.hpp"

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), currentPosition(0) {}

Token Parser::currentToken() const {
    return tokens[currentPosition];
}

Token Parser::nextToken() {
    return tokens[++currentPosition];
}

std::shared_ptr<ASTNode> Parser::parse() {
    std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode::Type::Program);

    while (currentPosition < tokens.size() && currentToken().getType() != Token::Type::EndOfFile) {
        if (currentToken().getValue() == "class") {
            root->addChild(parseClass());
        } else if (currentToken().getType() == Token::Type::Keyword) {
            if (currentToken().getValue() == "void" || currentToken().getValue() == "int" ||
                currentToken().getValue() == "float" || currentToken().getValue() == "double" ||
                currentToken().getValue() == "char") {
                root->addChild(parseMethod());
            } else {
                root->addChild(parseVariable());
            }
        } else {
            nextToken();
        }
    }
    return root;
}

std::shared_ptr<ASTNode> Parser::parseClass() {
    if (currentToken().getValue() == "class") {
        nextToken();
        std::shared_ptr<ASTNode> classNode = std::make_shared<ASTNode>(ASTNode::Type::Class);
        classNode->setValue(currentToken().getValue());
        nextToken();

        if (currentToken().getValue() == "{") {
            nextToken();

            while (currentPosition < tokens.size() && currentToken().getValue() != "}") {
                if (currentToken().getType() == Token::Type::Keyword) {
                    if (currentToken().getValue() == "void" || currentToken().getValue() == "int" ||
                        currentToken().getValue() == "float" || currentToken().getValue() == "double" ||
                        currentToken().getValue() == "char") {
                        classNode->addChild(parseMethod());
                    } else {
                        classNode->addChild(parseVariable());
                    }
                } else {
                    nextToken();
                }
            }
            nextToken();
        }

        return classNode;
    }
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseMethod() {
    if (currentToken().getType() == Token::Type::Keyword) {
        std::shared_ptr<ASTNode> methodNode = std::make_shared<ASTNode>(ASTNode::Type::Method);
        methodNode->setValue(currentToken().getValue());
        nextToken();

        if (currentToken().getType() == Token::Type::Identifier) {
            methodNode->setValue(methodNode->getValue() + " " + currentToken().getValue());
            nextToken();
        }

        if (currentToken().getValue() == "(") {
            nextToken();
            auto parameters = parseParameters();
            for (const auto& param : parameters) {
                std::shared_ptr<ASTNode> paramNode = std::make_shared<ASTNode>(ASTNode::Type::Variable);
                paramNode->setValue(param);
                methodNode->addChild(paramNode);
            }
            if (currentToken().getValue() == ")") {
                nextToken();
            }
        }

        if (currentToken().getValue() == "{") {
            nextToken(); 
            while (currentPosition < tokens.size() && currentToken().getValue() != "}") {
                nextToken();
            }
            nextToken();
        }
        return methodNode;
    }
    return nullptr;
}

std::vector<std::string> Parser::parseParameters() {
    std::vector<std::string> params;

    while (currentPosition < tokens.size() && currentToken().getValue() != ")") {
        if (currentToken().getType() == Token::Type::Keyword) {
            std::string paramType = currentToken().getValue();
            nextToken();

            if (currentToken().getType() == Token::Type::Identifier) {
                params.push_back(paramType + " " + currentToken().getValue());
                nextToken();
            }

            if (currentToken().getValue() == ",") {
                nextToken();
            }
        }
    }

    return params;
}

std::shared_ptr<ASTNode> Parser::parseVariable() {
    if (currentToken().getType() == Token::Type::Keyword) {
        std::shared_ptr<ASTNode> variableNode = std::make_shared<ASTNode>(ASTNode::Type::Variable);
        variableNode->setValue(currentToken().getValue());
        nextToken();

        if (currentToken().getType() == Token::Type::Identifier) {
            variableNode->setValue(variableNode->getValue() + " " + currentToken().getValue());
            nextToken();
        }

        if (currentToken().getValue() == "=") {
            nextToken();
            if (currentToken().getType() == Token::Type::Number) {
                variableNode->setValue(variableNode->getValue() + " = " + currentToken().getValue());
                nextToken();
            }
        }

        if (currentToken().getValue() == ";") {
            nextToken();
        }

        return variableNode;
    }
    return nullptr;
}