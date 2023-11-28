#pragma once

#include "term_types.h"

#include <string>
#include <iostream>

struct Token {
    Token(std::string value, TermType typeCode) :
        value(value), typeCode(typeCode)
    { }

    std::string value = "";
    TermType typeCode = TermTypes::UNDEFINED;

    friend bool operator==(const Token& t1, const Token& t2) {
        return t1.value == t2.value &&
            t1.typeCode == t2.typeCode;
    }

    friend bool operator!=(const Token& t1, const Token& t2) {
        return !(t1 == t2);
    }

    friend std::ostream& operator<<(std::ostream& s, const Token& token)
    {
        s << "code: " << token.typeCode.code() << " typeName: " << token.typeCode.toString() << " value: " << token.value;
        return s;
    }
};
