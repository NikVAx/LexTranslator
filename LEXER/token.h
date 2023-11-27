#pragma once

#include <string>
#include <iostream>

#include "../Utils/cast_enum.h"
#include "lexer_config.h"

struct Token {
    Token(std::string value, TermTypes typeCode, std::string typeName) {
        this->value = value;
        this->typeCode = typeCode;
        this->typeName = typeName;
    }

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
        s << "code: " << cast_enum(token.typeCode) << " typeName: " << token.typeName << " value: " << token.value;
        return s;
    }
};