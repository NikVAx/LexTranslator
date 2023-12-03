#pragma once

#include <string>
#include <ostream>

#include "token_types.h"

/*
Символ алфавита:
  struct AlphabetChar {
    bool isNotTerm() {
      return type == NONTERMINAL;
    }

    AlphabetChar(Type type)
        : type(type)
    { }
    
    type: term | nonterm;
  }

  struct Token : AlphabetChar
  {
      Token()
        : AlphabetChar(TERMINAL)
      { }
  }


  Терминальный
  Нетерминальный


*/

struct SyntaxChar {
    SyntaxChar() {}

    SyntaxChar(int code, std::string tokenString, TokenType type)
        : code(code)
        , tokenString(tokenString)
        , type(type)
    { }

    int code;
    std::string tokenString;
    TokenType type;

    bool operator ==(const SyntaxChar& token) const {
        return this->code == token.code;
    }

    friend std::ostream& operator<<(std::ostream& s, const SyntaxChar& token)
    {
        s << "code: " << token.code << " symbol: " << token.tokenString.c_str() << " type: " << (int)(token.type);
        return s;
    }
};
