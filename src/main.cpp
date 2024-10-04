#include "main.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "[-] Error: Invalid number of arguments!" << std::endl;
        return 1;
    }
    std::string filePath = argv[1];
    
    FileHandler fileHandler;
    std::string code = fileHandler.readFile(filePath);

    Lexer lexer(code);
    auto tokens = lexer.tokenize();

    Parser parser(tokens);
    std::shared_ptr<ASTNode> root = std::shared_ptr<ASTNode>(parser.parse());

    ASTTraversal traversal;
    traversal.traverse(root);

    std::string outputFilename = "../output/ast_output";
    traversal.generateGraph(root, outputFilename);

    return 0;
}
