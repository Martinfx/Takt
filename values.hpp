#pragma once

#include <iostream>

// Definice enumerátoru pro ValueType
enum class ValueType {
    Null,
    Number,
    Boolean,
};

// Definice RuntimeVal struktury
class RuntimeVal {
public:
    ValueType type;
    std::string value;
    RuntimeVal(ValueType type):type(type) {}
    virtual ~RuntimeVal() { }
};

// Definice NullVal struktury dědící od RuntimeVal
class NullVal : public RuntimeVal {
public:
    std::string value = "null";
    NullVal() : RuntimeVal{ValueType::Null} {}
};

// Definice NumberVal
class NumberVal : public RuntimeVal {
public:
    NumberVal(std::string &value) : RuntimeVal{ValueType::Number} {}
    NumberVal():RuntimeVal{ValueType::Number} {}
    virtual ~NumberVal() {}
};

// Definice BooleanVal
class BooleanVal : public RuntimeVal {
public:
    bool value;
    BooleanVal(bool b = true) : RuntimeVal{ValueType::Boolean}, value(b) {}
};

// Funkce pro vytvoření NullVal
NullVal MK_NULL() {
    return NullVal{};
}

// Funkce pro vytvoření BooleanVal
BooleanVal MK_BOOL(bool b = true) {
    BooleanVal val;
    val.value = b;
    return val;
}

// Funkce pro vytvoření NumberVal
NumberVal MK_NUMBER(std::string &n) {
    NumberVal val(n);
    return n;
}
