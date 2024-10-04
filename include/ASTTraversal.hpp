#ifndef ASTTRAVERSAL_HPP
#define ASTTRAVERSAL_HPP

#include "ASTNode.hpp"
#include <iostream>
#include <fstream>
#include <memory>
#include <string>

class ASTTraversal {
public:
    void traverse(const std::shared_ptr<ASTNode>& node);
    void generateGraph(const std::shared_ptr<ASTNode>& node, const std::string& outputFilename);

private:
    void writeNode(std::ofstream& outFile, const std::shared_ptr<ASTNode>& node, int& nodeId);
};

#endif
