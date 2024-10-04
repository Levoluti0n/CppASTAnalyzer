#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <string>
#include <vector>
#include <memory>

class ASTNode {
    public:
        enum class Type {
            Program,
            Class,
            Method,
            Variable,
            Unknown
        };
        ASTNode(Type type);

        Type getType() const;
        const std::string& getValue() const;
        void setValue(const std::string& value);
        void addChild(std::shared_ptr<ASTNode> child);
        const std::vector<std::shared_ptr<ASTNode>>& getChildren() const;

    private:
        Type type;
        std::string value;
        std::vector<std::shared_ptr<ASTNode>> children;
};

#endif