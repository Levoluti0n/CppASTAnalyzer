cmake_minimum_required(VERSION 3.10)

project(CppASTParser)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
    src/ASTNode.cpp
    src/ASTTraversal.cpp
    src/FileHandler.cpp
    src/Lexer.cpp
    src/Parser.cpp
    src/Token.cpp
    src/main.cpp
)

add_executable(cppASTParser ${SOURCES})
