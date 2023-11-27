#pragma once

#include <string>
#include <iostream>

#include "lexer_config.h"

struct Token {
    Token(std::string value, TermTypes typeCode) : 
        value(value), typeCode(typeCode), typeName(typeCode.name) {}

    std::string value = "";
    std::string typeName = "";
    TermTypes typeCode = TermTypes::UNDEFINED;

    friend bool operator==(const Token& t1, const Token& t2) {
        return t1.value == t2.value &&
            t1.typeCode == t2.typeCode &&
            t1.typeName == t2.typeName;
    }

    friend bool operator!=(const Token& t1, const Token& t2) {
        return !(t1 == t2);
    }

    friend std::ostream& operator<<(std::ostream& s, const Token& token)
    {
        s << "code: " << token.typeCode.name << " typeName: " << token.typeName << " value: " << token.value;
        return s;
    }
};