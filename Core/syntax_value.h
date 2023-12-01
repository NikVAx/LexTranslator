#pragma once

#include "term_types.h"

#include <iostream>

struct SyntaxValue {
    SyntaxValue(TermType type = TermTypes::UNDEFINED, std::string value = "")
        : type(type)
        , value(value)
    { };

    TermType type;
    std::string value;

    friend std::ostream& operator<<(std::ostream& s, const SyntaxValue& token)
    {
        s << "type: " << token.type.toString() << " value: " << token.value;
        return s;
    }
};
