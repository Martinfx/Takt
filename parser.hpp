#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <cassert>
#include <optional>
#include "ast.hpp"
#include "token.hpp"

class Parser {
private:
    std::vector<Token> tokens;
    Token tok;

    using TokenIterator = std::vector<Token>::iterator;

    Token at(TokenIterator it) {
        if (it != tokens.end()) {
            return *it;
        } else {
            throw std::out_of_range("Trying to access token beyond the end of the vector");
        }
    }

    Token eat(TokenIterator& it) {
        if (it != tokens.end()) {
            Token prev = *it;
            ++it;
            return prev;
        } else {
            throw std::out_of_range("Trying to eat token beyond the end of the vector");
        }
    }

    Token expect(TokenIterator& it, TokenType type, const std::string& err) {
        if (it != tokens.end()) {
            Token prev = *it;
            if (prev.getTokenType() != type) {
                std::cerr << "Parser Error:\n" << err << " - Expecting: " << static_cast<int>(type) << std::endl;
                std::exit(1);
            }
            ++it;
            return prev;
        } else {
            throw std::runtime_error("Trying to expect token beyond the end of the vector");
        }
    }

public:
      Parser() {}
      std::shared_ptr<ast::Program> produceAST(const std::string& sourceCode) {
        tokens = tok.Tokenize(sourceCode);
        std::shared_ptr<ast::Program> programNode = std::make_shared<ast::Program>();

        TokenIterator it = tokens.begin();
        while (it != tokens.end()) {
            std::cout << "begin - programNode.body.capacity(): " << programNode->body.capacity() << std::endl;
            programNode->body.push_back(parse_stmt(it));
            std::cout << "end - programNode.body.capacity(): " << programNode->body.capacity() << std::endl;

        }

        return programNode;
    }

    std::shared_ptr<ast::Stmt> parse_stmt(TokenIterator& it) {
        switch (at(it).getTokenType()) {
        case TokenType::Let:
        case TokenType::Const:
           return parse_var_declaration(it);
           break;
        default:
            return parse_expr(it);
            break;
        }
    }

    std::shared_ptr<ast::Stmt>  parse_var_declaration(TokenIterator& it) {
        bool isConstant = eat(it).getTokenType() == TokenType::Const;
        Token identifierToken = expect(it, TokenType::Identifier, "Expected identifier name following let | const keywords.");
        std::string identifier = identifierToken.getValue();

        if (at(it).getTokenType() == TokenType::Semicolon) {
            eat(it); // expect semicolon

            if (isConstant) {
                throw "Must assign value to constant expression. No value provided.";
            }

           return std::make_shared<ast::VarDeclaration>(identifier, false);
        }

        expect(it, TokenType::Equals, "Expected equals token following identifier in var declaration.");

        std::shared_ptr<ast::Expr> value = parse_expr(it);

        expect(it, TokenType::Semicolon, "Variable declaration statement must end with semicolon.");
        return std::make_shared<ast::VarDeclaration>(identifier, isConstant, value);
    }

    std::shared_ptr<ast::Expr> parse_expr(TokenIterator& it) {
        return parse_assignment_expr(it);
    }

    std::shared_ptr<ast::Expr> parse_assignment_expr(TokenIterator& it) {
        std::shared_ptr<ast::Expr> left = parse_additive_expr(it);

        if (at(it).getTokenType() == TokenType::Equals) {
           eat(it); // advance past equals
           std::shared_ptr<ast::Expr> value = parse_assignment_expr( it);
           return std::make_shared<ast::AssignmentExpr>(value, left, ast::NodeType::AssignmentExpr);
        }

        return left;
    }

    std::shared_ptr<ast::Expr> parse_additive_expr(TokenIterator& it) {
        auto left = parse_multiplicative_expr(it);

        while (it != tokens.end() && (at(it).getValue() == "+" || at(it).getValue() == "-")) {
            const std::string& operatorStr = eat(it).getValue();
            std::shared_ptr<ast::Expr> right = parse_multiplicative_expr(it);
            std::shared_ptr<ast::BinaryExpr> binaryExpr = std::make_shared<ast::BinaryExpr>();
            binaryExpr->left = std::move(left);
            binaryExpr->right = std::move(right);
            binaryExpr->op = operatorStr;
            left = std::move(binaryExpr);
        }

        return left;
    }

    std::shared_ptr<ast::Expr> parse_multiplicative_expr(TokenIterator& it) {
        std::shared_ptr<ast::Expr> left = parse_primary_expr(it);

        while (it != tokens.end() && (at(it).getValue() == "/" || at(it).getValue() == "*" || at(it).getValue() == "%")) {
            const std::string& operatorStr = eat(it).getValue();
            std::shared_ptr<ast::Expr> right = parse_primary_expr(it);
            std::shared_ptr<ast::BinaryExpr> binaryExpr = std::make_shared<ast::BinaryExpr>();
            binaryExpr->left = std::move(left);
            binaryExpr->right = std::move(right);
            binaryExpr->op = operatorStr;
            left = std::move(binaryExpr);
        }

        return left;
    }

    std::shared_ptr<ast::Expr> parse_primary_expr(TokenIterator& it) {
        TokenType tk = at(it).getTokenType();

        switch (tk) {
        case TokenType::Identifier:
        {
            auto identifier = std::make_shared<ast::Identifier>();
            identifier->kind = ast::NodeType::Identifier;
            identifier->symbol = eat(it).getValue();
            return identifier;
        }
        case TokenType::Null:
        {
            auto nullLiteral = std::make_shared<ast::NullLiteral>() ;
            nullLiteral->kind = ast::NodeType::NullLiteral;
            nullLiteral->value = eat(it).getValue();
            return nullLiteral;
        }
        case TokenType::Number:
        {
            auto numericLiteral = std::make_shared<ast::NumericLiteral>() ;
            numericLiteral->kind = ast::NodeType::NumericLiteral;
            numericLiteral->value = eat(it).getValue();
            return numericLiteral;
        }
        case TokenType::OpenParen: {
            eat(it); // eat the opening paren
            std::shared_ptr<ast::Expr> value = parse_expr(it);
            expect(it, TokenType::CloseParen, "Unexpected token found inside parenthesized expression. Expected closing parenthesis.");
            return value;
        }
        default:
            std::cerr << "Unexpected token found during parsing!" << std::endl;
            std::cout << "Unexpected: " << eat(it).getValue();
            std::exit(1);
        }
    }
};
