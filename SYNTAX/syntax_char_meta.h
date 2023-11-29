#pragma once

#include <string>
#include <ostream>

#include "../Utils/cast_enum.h"
#include "../Core/token_types.h"

struct SyntaxCharMeta {
    SyntaxCharMeta(int code, std::string tokenString, TokenType type) 
        : code(code)
        , tokenString(tokenString)
        , type(type)  
    { }

    int code;
    std::string tokenString;
    TokenType type;

    bool operator ==(const SyntaxCharMeta& token) const {
        return this->code == token.code;
    }

    friend std::ostream& operator<<(std::ostream& s, const SyntaxCharMeta& token)
    {
        s << "code: " << token.code << " symbol: " << token.tokenString.c_str() << " type: " << (int)(token.type);
        return s;
    }
};