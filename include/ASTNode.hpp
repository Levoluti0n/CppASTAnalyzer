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
        void setValue(const std::string&);
        const std::string& getValue() const;
        static std::string typeToString(Type);
        void addChild(std::shared_ptr<ASTNode>);
        const std::vector<std::shared_ptr<ASTNode>>& getChildren() const;


    private:
        Type type;
        std::string value;
        std::vector<std::shared_ptr<ASTNode>> children;
};

#endif