#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token {
    public:
        enum class Type {
            Identifier,
            Keyword,
            Number,
            Operator,
            Delimiter,
            Unknown,
            EndOfFile
        };

        int getLine() const;
        Type getType() const;
        const std::string& getValue() const;
        Token(Type, const std::string&, int);

    private:
        std::string value;
        Type type;
        int line;
};

#endif