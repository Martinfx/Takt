#pragma once

#include <vector>
#include <iostream>

enum TokenType {
    // Literal Types
    Null = 0,
    Number,
    Identifier,

    // Keywords
    Let,
    Const,

    // Grouping * Operators
    BinaryOperator,
    Equals,
    Semicolon,
    OpenParen,
    CloseParen,
    EOFToken
};

/*std::map<std::string, TokenType> keywords
    {{"let", TokenType::Let}};*/

class Token {
public:
    Token(const std::string &value, TokenType type) : m_value(value), m_type(type) { }
    Token() {}
    ~Token() {}

    std::string m_value;
    TokenType m_type;

    const std::string getValue() {
        return m_value;
    }

     TokenType getTokenType() {
        return m_type;
    }

    bool isInt(char c) {
        const int bounds[] = {'0', '9'};
        return c >= bounds[0] && c <= bounds[1];
    }

    std::vector<Token> Tokenize(const std::string& src) {
        std::vector<Token> tokens;
        std::string::const_iterator it = src.begin();

        while (it != src.end()) {
            if (isInt(*it)) {
                std::string num = "";
                while (it != src.end() && isInt(*it)) {
                    num += *it;
                    ++it;

                    if (it == src.end()) {
                        break;
                    }
                }
                tokens.push_back(Token(num, TokenType::Number));

            } else {
                // Handle Identifier & Keyword Tokens.
                // Implement the logic for identifying Identifier and Keyword tokens.
                // For now, let's assume everything else is an Identifier.
                std::string identifier = "";
                while (it != src.end() && !isInt(*it) && !std::isspace(*it)) {
                    identifier += *it;
                    ++it;

                    if (it == src.end()) {
                        break;
                    }
                }

                if(identifier == "("){
                    tokens.push_back(Token(identifier, TokenType::OpenParen));
                }
                else if (identifier == ")") {
                    tokens.push_back(Token(identifier, TokenType::CloseParen));
                }
                else if ((identifier == "+") || (identifier == "-") || (identifier == "*") || (identifier == "/")) {
                    tokens.push_back(Token(identifier, TokenType::BinaryOperator));
                }
                else if(identifier == "=") {
                    tokens.push_back(Token(identifier, TokenType::Equals));
                }
                else if(identifier == ";") {
                    tokens.push_back(Token(identifier, TokenType::Semicolon));
                }
                else if (identifier == "let") {
                    tokens.push_back(Token(identifier, TokenType::Let));
                }
                else if (identifier == "const") {
                    tokens.push_back(Token(identifier, TokenType::Const));
                }
                else if (identifier == "null") {
                    tokens.push_back(Token(identifier, TokenType::Null));
                }
                else{
                    tokens.push_back(Token(identifier, TokenType::Identifier));
                }

            }

            // Skip whitespaces
            while (it != src.end() && std::isspace(*it)) {
                ++it;

                if (it == src.end()) {
                    break;
                }
            }
        }

        //tokens.push_back(Token("EndOfFile", TokenType::EOFToken));
        return tokens;
    }

};


/*
bool isIsalpha(char ch)
{
    return std::isalpha(static_cast<unsigned char>(ch));
}

bool isDigit(char ch)
{
    return std::isdigit(static_cast<unsigned char>(ch));
}

std::string charToString(char ch){
    std::string str = {ch};
    return str;
}*/
/*
std::vector<Token> Tokenize(std::string s) {
    std::vector<Token> tokens;
    size_t pos = 0;
    std::string delimiter = " ";

    while ((pos = s.find(delimiter)) != std::string::npos) {
        std::string src = s.substr(0, pos);

        for (int var = 0; var < src.length(); ++var) {
            if(src[var] == '(') {
                tokens.push_back(Token("(", TokenType::OpenParen));
            }
            else if(src[var] == ')') {
                 tokens.push_back(Token(")", TokenType::CloseParen));
            }
            else if ((src[var] == '+') || (src[var] == '-') || (src[var] == '*') || (src[var] == '/')) {
                 tokens.push_back(Token(charToString(src[var]), TokenType::BinaryOperator));
            }
            else if(src[var] == '=') {
                tokens.push_back(Token("=", TokenType::Equals));
            }
            else{
                if(isDigit(src[var])){
                    tokens.push_back(Token(charToString(src[var]),TokenType::Number));
                }

                std::string keyword = {};
                if(isIsalpha(src[var])) {

                    for (int key = 0; key < src.length(); ++key) {
                        const char ch = src[key];
                        keyword += ch;
                    }

                    std::string reserved = {};
                    reserved = keywords[keyword];
                    if(keyword == "let") {
                        tokens.push_back(Token(keyword, TokenType::Let));
                    } else {
                        tokens.push_back(Token(charToString(src[var]), TokenType::Indentifier));
                    }
                }
            }
        }
         s.erase(0, pos + delimiter.length());
    }

    return tokens;
}*/
