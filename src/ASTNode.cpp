#include "ASTNode.hpp"

ASTNode::ASTNode(Type type) : type{type} {}

void ASTNode::setValue(const std::string& value) {
    this->value = value;
}

const std::string& ASTNode::getValue() const {
    return value;
}

ASTNode::Type ASTNode::getType() const {
    return type;
}

void ASTNode::addChild(std::shared_ptr<ASTNode> child) {
    children.push_back(child);
}

const std::vector<std::shared_ptr<ASTNode>>& ASTNode::getChildren() const {
    return children;
}

std::string ASTNode::typeToString(Type type) {
    switch (type) {
        case Type::Program: return "Program";
        case Type::Class: return "Class";
        case Type::Method: return "Method";
        case Type::Variable: return "Variable";
        case Type::Unknown: return "Unknown";
        default: return "Unknown Type";
    }
}