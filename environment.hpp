#pragma once
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>

#include "values.hpp" // Obsahuje definici typu RuntimeVal

class Environment {
private:
    Environment* parent;
    std::map<std::string, RuntimeVal> variables;
    std::set<std::string> constants;

public:
    Environment(Environment* parentENV = nullptr) : parent(parentENV) {}

    RuntimeVal declareVar(const std::string& varname, const RuntimeVal& value, bool constant) {
        if (variables.find(varname) != variables.end()) {
            throw std::runtime_error("Cannot declare variable '" + varname + "'. It is already defined.");
        }

        variables.insert(std::make_pair(varname, value));
        if (constant) {
            constants.insert(varname);
        }
        return value;
    }

    RuntimeVal assignVar(const std::string& varname, const RuntimeVal& value) {
        Environment* env = resolve(varname);

        // Cannot assign to constant
        if (env->constants.find(varname) != env->constants.end()) {
            throw std::runtime_error("Cannot reassign to variable '" + varname + "' as it was declared constant.");
        }

        env->variables.insert(std::make_pair(varname, value));
        return value;
    }

    RuntimeVal lookupVar(const std::string& varname) {
        Environment* env = resolve(varname);
        return env->variables.at(varname);
    }

private:
    Environment* resolve(const std::string& varname) {
        if (variables.find(varname) != variables.end()) {
            return this;
        }

        if (parent == nullptr) {
            throw std::runtime_error("Cannot resolve '" + varname + "'. It does not exist.");
        }

        return parent->resolve(varname);
    }
};
