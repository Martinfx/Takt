#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#include "parser.hpp"
#include "interpreter.hpp"
#include "environment.hpp"
#include "values.hpp"

std::string nodeType(ast::NodeType type) {
    switch (type) {
    case ast::NodeType::Program:
        return "ast::NodeType::Program";
        break;
    case ast::NodeType::VarDeclaration:
        return "ast::NodeType::VarDeclaration";
        break;
    case ast::NodeType::AssignmentExpr:
        return "ast::NodeType::AssignmentExpr" ;
        break;
    case ast::NodeType::MemberExpr:
        return "ast::NodeType::MemberExpr" ;
        break;
    case ast::NodeType::CallExpr:
        return "ast::NodeType::CallExpr" ;
        break;
    case ast::NodeType::Property:
        return "ast::NodeType::Property";
        break;
    case ast::NodeType::ObjectLiteral:
        return "ast::NodeType::ObjectLiteral";
        break;
    case ast::NodeType::NumericLiteral:
        return "ast::NodeType::NumericLiteral";
        break;
    case ast::NodeType::NullLiteral:
        return "ast::NodeType::NullLiteral";
        break;
    case ast::NodeType::Identifier:
        return "ast::NodeType::Identifier" ;
        break;
    case ast::NodeType::BinaryExpr:
        return "ast::NodeType::BinaryExpr" ;
        break;
    default:
         return "Unknown NodeType";
        break;
    }
}

std::string ValueType(ValueType type) {
    switch (type) {
    case ValueType::Boolean:
        return "Boolean";
        break;
    case ValueType::Null:
        return "Null";
        break;
    case ValueType::Number:
        return "Number";
        break;
    default:
        return "Unknown ValueType";
        break;
    }
}
int main() {
    /*std::string test =  "let r = (45 + 45) ";
    std::vector<Token> token = Tokenize(test);

    for (auto it : token) {
         std::cout << it.m_value << " = " << it.m_type << std::endl;
    }*/

    Environment env;
    // Create Default Global Environment
   //env.declareVar("x", MK_NUMBER("100"), false);
    env.declareVar("true", MK_BOOL(true), false);
    env.declareVar("false", MK_BOOL(false), false);
    env.declareVar("null", MK_NULL(), false);

    Parser parser;
    std::cout << "\nTakt v0.1" << std::endl;
    std::shared_ptr<ast::Program> program;
    // Continue Repl Until User Stops Or Types `exit`
   /* while (true) {
       std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);

        // Check for no user input or exit keyword.
        if (input.empty() || input.find("exit") != std::string::npos) {
            std::exit(0);
        }
*/
    // Produce AST From sourc-code
    program = parser.produceAST("let x = 45;");
    for(auto i : program->body) {
        std::cout << nodeType(i->kind)
                  << " val: " << i->value
                  << std::endl;

    }
    std::cout << "AST Produced:" << std::endl;
    auto result = evaluate(program, env);
    std::cout << ValueType(result.type) << std::endl;
    std::cout << result.value << std::endl;
 //   }

    return 0;
}
