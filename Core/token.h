#pragma once

#include "term_type.h"
#include "term_types.h"

#include <string>
#include <iostream>

struct Token {
    Token(std::string value, TermType termType) 
        : value(value)
        , termType(termType)
    { }

    std::string value = "";
    TermType termType = TermTypes::UNDEFINED;

    friend bool operator==(const Token& t1, const Token& t2) {
        return t1.value == t2.value &&
            t1.termType == t2.termType;
    }

    friend bool operator!=(const Token& t1, const Token& t2) {
        return !(t1 == t2);
    }

    friend std::ostream& operator<<(std::ostream& s, const Token& token)
    {
        s << "{code: " << token.termType.code() << ",typeName: " << token.termType.toString() << ",value: " << token.value << "}";
        return s;
    }
};
