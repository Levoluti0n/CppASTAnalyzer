#include "ASTTraversal.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <memory>

void ASTTraversal::traverse(const std::shared_ptr<ASTNode>& node) {
    if (!node) return;

    std::cout << "Node Type: " << ASTNode::typeToString(node->getType())
              << ", Value: " << node->getValue() << std::endl;

    for (const auto& child : node->getChildren()) {
        traverse(child);
    }
}

void ASTTraversal::generateGraph(const std::shared_ptr<ASTNode>& node, const std::string& outputFilename) {
    std::ofstream outFile(outputFilename + ".dot");
    if (!outFile) {
        std::cerr << "[-] Error creating dot file." << std::endl;
        return;
    }

    outFile << "digraph AST {" << std::endl;
    int nodeId = 0;
    writeNode(outFile, node, nodeId);
    outFile << "}" << std::endl;
    outFile.close();

    char choice;
    std::cout << "Generate an image from the AST? (y/*): ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        std::string command = "dot -Tpng " + outputFilename + ".dot -o " + outputFilename + ".png";
        if (popen(command.c_str(), "r")) {
            std::cout << "[+] Image saved as " << outputFilename << ".png" << std::endl;
        } else {
            std::cerr << "[-] Failed to generate image." << std::endl;
        }
    }
}

void ASTTraversal::writeNode(std::ofstream& outFile, const std::shared_ptr<ASTNode>& node, int& nodeId) {
    if (!node) return;

    int currentId = nodeId++;
    outFile << "  node" << currentId << " [label=\"" 
            << ASTNode::typeToString(node->getType()) << ": " 
            << node->getValue() << "\"];" << std::endl;

    for (const auto& child : node->getChildren()) {
        int childId = nodeId;
        writeNode(outFile, child, nodeId);
        outFile << "  node" << currentId << " -> node" << childId << ";" << std::endl;
    }
}
