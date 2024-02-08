#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

#include "values.hpp"
#include "ast.hpp"
#include "environment.hpp"
/*
RuntimeVal eval_binary_expr(const ast::BinaryExpr& binop) {
    RuntimeVal lhs = evaluate(binop.left);
    RuntimeVal rhs = evaluate(binop.right);

    // Podporujeme pouze numerické operace
    if (lhs.type == ValueType::Number && rhs.type == ValueType::Number) {
        return eval_numeric_binary_expr(
            static_cast<NumberVal&>(lhs),
            static_cast<NumberVal&>(rhs),
            binop.op);
    }

    // Jedna nebo obě hodnoty jsou NULL
    return NullVal{};
}
*/
/*
RuntimeVal eval_var_declaration(const ast::VarDeclaration& declaration, Environment& env) {
    RuntimeVal value = declaration.value ? evaluate(declaration.value, env) : MK_NULL();
    return env.declareVar(declaration.identifier, value, declaration.constant);
}*/

RuntimeVal evaluate(const std::shared_ptr<ast::Stmt> astNode, Environment& env) {
    switch (astNode->kind) {
    case ast::NodeType::NumericLiteral:{
        std::cout << "Numeric literal: " << std::static_pointer_cast<ast::NumericLiteral>(astNode)->value << std::endl;
        NumberVal val;
        val.value = std::static_pointer_cast<const ast::NumericLiteral>(astNode)->value;
        return val;
    }
    case ast::NodeType::Identifier: {
        const RuntimeVal val = env.lookupVar(std::static_pointer_cast<const ast::Identifier>(astNode)->symbol);
        return val;

    }
    case ast::NodeType::BinaryExpr: {
            RuntimeVal lhs = evaluate(std::static_pointer_cast<const ast::BinaryExpr>(astNode)->left, env);
            RuntimeVal rhs = evaluate(std::static_pointer_cast<const ast::BinaryExpr>(astNode)->right, env);
            std::string op = std::static_pointer_cast<const ast::BinaryExpr>(astNode)->op;
            std::cout << std::static_pointer_cast<const ast::BinaryExpr>(astNode)->op;

            if (lhs.type == ValueType::Number && rhs.type == ValueType::Number) {
                NumberVal numLhs = static_cast<NumberVal&>(lhs);
                NumberVal numRhs = static_cast<NumberVal&>(rhs);
                double result;
                if (op == "+") {
                    result = std::stod(numLhs.value) + std::stod(numRhs.value);
                } else if (op == "-") {
                    result = std::stod(numLhs.value) - std::stod(numRhs.value);
                } else if (op == "*") {
                    result = std::stod(numLhs.value) * std::stod(numRhs.value);
                } else if (op == "/") {
                    // TODO: Division by zero checks
                    result = std::stod(numLhs.value) / std::stod(numRhs.value);
                } else {
                    result = std::fmod(std::stod(numLhs.value),std::stod(numRhs.value));
                }

                NumberVal val;
                val.value = std::to_string(result);
                return val;
            }

            // Jedna nebo obě hodnoty jsou NULL
            return MK_NULL();
            break;
        }


    case ast::NodeType::Program: {
        std::shared_ptr<const ast::Program> program = std::static_pointer_cast<const ast::Program>(astNode);
        if (program) {
            RuntimeVal lastEvaluated = MK_NULL();
            for (const std::shared_ptr<ast::Stmt>& statement : program->body) {
                lastEvaluated = evaluate(statement, env);
            }
            return lastEvaluated;
        } else {
            // Nepodařilo se přetypovat na ast::Program, zpracujte chybu podle potřeby.
            // Například můžete vyvolat výjimku nebo vrátit nějaký výchozí stav.
            std::cerr << "Error: Failed to cast astNode to ast::Program." << std::endl;
            return MK_NULL(); // nebo vyvolat výjimku nebo jinak zpracovat chybu
        }
        break;
    }



    case ast::NodeType::VarDeclaration: {
        auto declaration = std::static_pointer_cast<const ast::VarDeclaration>(astNode);
        RuntimeVal value = declaration->val ? evaluate(declaration->val, env) : MK_NULL();
        return env.declareVar(declaration->identifier, value, declaration->constant);
        std::cout << "fuck you" << std::endl;
        break;
    }
        // Handle unimplemented ast types as error.
    default:
        std::cerr << "This AST Node has not yet been set up for interpretation." << std::endl;
        std::exit(0);
    }
}


/*RuntimeVal eval_program(const ast::Program& program, Environment& env) {
   RuntimeVal lastEvaluated = MK_NULL();
    for (const ast::Stmt& statement : program.body) {
        lastEvaluated = evaluate(statement, env);
    }
    return lastEvaluated;
}*/
/*
NumberVal eval_numeric_binary_expr(const NumberVal& lhs, const NumberVal& rhs, const std::string& op) {
    double result;
    if (op == "+") {
        result = lhs.value + rhs.value;
    } else if (op == "-") {
        result = lhs.value - rhs.value;
    } else if (op == "*") {
        result = lhs.value * rhs.value;
    } else if (op == "/") {
        // TODO: Division by zero checks
        result = lhs.value / rhs.value;
    } else {
        result = fmod(lhs.value, rhs.value);
    }

    return {result};
}
*/
/*RuntimeVal eval_binary_expr(const ast::BinaryExpr& binop, Environment& env) {
    RuntimeVal lhs = evaluate(binop.left,env);
    RuntimeVal rhs = evaluate(binop.right,env);

    // Podporujeme pouze numerické operace
    if (lhs.type == ValueType::Number && rhs.type == ValueType::Number) {
        return eval_numeric_binary_expr(
            static_cast<NumberVal&>(lhs),
            static_cast<NumberVal&>(rhs),
            binop.op);
    }

    // Jedna nebo obě hodnoty jsou NULL
    return MK_NULL();
}*/

RuntimeVal eval_identifier(const ast::Identifier& ident, Environment& env) {
    const RuntimeVal val = env.lookupVar(ident.symbol);
    return val;
}



/*
RuntimeVal evaluate(const ast::Stmt& astNode) {
    switch (astNode.kind) {
    case ast::NodeType::NumericLiteral:
        // Předpokládáme implementaci evaluate_numeric_literal
        return evaluate_numeric_literal(static_cast<const ast::NumericLiteral&>(astNode));
        break;
    case "NullLiteral":
        return NullVal(); // Předpokládáme, že máte třídu NullVal
        break;
    case "BinaryExpr":
        return eval_binary_expr(static_cast<const ast::BinaryExpr&>(astNode));
        break;
    case "Program":
        return eval_program(static_cast<const ast::Program&>(astNode));
        break;
    default:
        std::cerr << "This AST Node has not yet been set up for interpretation." << std::endl;
        std::exit(0);
    }
}*/
