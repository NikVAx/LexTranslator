#pragma once

#include "TermTypes.h"

#include <string>

struct Token {
    Token(std::string value, TermTypes typeCode)
        : value(value)
        , typeCode(typeCode)
        , typeName(typeCode.name)
    { }

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
};