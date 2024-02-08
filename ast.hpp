#pragma once

#include <iostream>
#include <vector>

namespace ast {

enum class NodeType {
    // STATEMENTS
    Program = 0,
    VarDeclaration,
    // EXPRESSIONS
    AssignmentExpr,
    MemberExpr,
    CallExpr,
    // Literals
    Property,
    ObjectLiteral,
    NumericLiteral,
    NullLiteral,
    Identifier,
    BinaryExpr
};



class Stmt {
public:

    std::string value;
    NodeType kind;
    Stmt(NodeType type) : kind(type) {}
    Stmt() {}
    virtual ~Stmt() {}
};

class Expr : public Stmt {
public:
    Expr(NodeType nodetype) : Stmt(nodetype){}
    Expr(){}
    virtual ~Expr() {}
};

// Defines a block that contains many statements.
// Only one program will be contained in a file.
class Program : public Stmt {
public:
    std::vector< std::shared_ptr<Stmt>  > body;
    Program():Stmt(NodeType::Program) {}
    virtual ~Program(){}
};

class VarDeclaration : public Stmt {
public:
    NodeType kind;
    bool constant;
    std::string identifier;
    std::shared_ptr<Expr> val;

    VarDeclaration(std::string identifier, bool constant) :
        constant(constant), identifier(identifier), Stmt(NodeType::VarDeclaration) { }
    VarDeclaration(std::string identifier,  bool constant, std::shared_ptr<Expr> value):
        constant(constant), identifier(identifier), val(value), Stmt(NodeType::VarDeclaration){ }
    virtual ~VarDeclaration() { }
};

// A operation with two sides separated by an operator.
// Both sides can be ANY Complex Expression.
// Supported Operators -> + | - | / | * | %
class BinaryExpr : public Expr {
public:
    std::shared_ptr<ast::Expr> left;
    std::shared_ptr<ast::Expr> right;
    std::string op;
    std::string val;
    BinaryExpr() : Expr(NodeType::BinaryExpr), left(nullptr), right(nullptr) {}
    virtual ~BinaryExpr() {}

  /*
    BinaryExpr(BinaryExpr&& other) noexcept
        : Expr(std::move(other)), left(std::move(other.left)),
                                  right(std::move(other.right)),
                                  op(std::move(other.op)) {}

    BinaryExpr& operator=(BinaryExpr&& other) noexcept {
        if (this != &other) {
            Expr::operator=(std::move(other));
            left = std::move(other.left);
            right = std::move(other.right);
            op = std::move(other.op);
        }
        return *this;
    }*/
};


class CallExpr : Expr {
    NodeType kind;
    std::vector<Expr*> args;
    Expr* caller;
};

class MemberExpr : Expr {
    NodeType kind;
    Expr* object;
    Expr* property;
    bool computed;
};

class NumericLiteral : public Expr {
public:
    NumericLiteral() : Expr(NodeType::NumericLiteral) { }
    virtual ~NumericLiteral() {}
};

class Identifier : public Expr {
public:
    std::string symbol;
    Identifier() : Expr(NodeType::Identifier) {}
};


class NullLiteral : public Expr {
public:
    NodeType kind;
    std::string value;

    NullLiteral() : kind(NodeType::NullLiteral), value("null") {}
    virtual ~NullLiteral() { }
};

} // namespace ast
