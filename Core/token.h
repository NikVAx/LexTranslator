#pragma once

#include "term_types.h"

#include <string>
#include <iostream>

struct Token {
    Token(std::string value, TermTypes typeCode) :
        value(value), typeCode(typeCode)
    { }

    std::string value = "";
    TermTypes typeCode = TermTypes::UNDEFINED;

    friend bool operator==(const Token& t1, const Token& t2) {
        return t1.value == t2.value &&
            t1.typeCode == t2.typeCode;
    }

    friend bool operator!=(const Token& t1, const Token& t2) {
        return !(t1 == t2);
    }

    friend std::ostream& operator<<(std::ostream& s, const Token& token)
    {
        s << "code: " << token.typeCode.name << " typeName: " << token.typeCode.name << " value: " << token.value;
        return s;
    }
};
