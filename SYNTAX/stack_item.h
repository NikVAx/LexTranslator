#pragma once

#include "../Core/term_types.h"
#include "../Core/syntax_chars.h"

#include <string>

struct StackItem {
    StackItem(int code, std::string value, SyntaxChar currentChar)
        : code(code)
        , value(value)
        , currentChar(currentChar)
    { }

    int code;
    SyntaxChar currentChar;

    std::string value;

    bool isNotTerm() {
        return code == SyntaxChars::NONTERMINAL.code;
    }
};

StackItem START_LIMIT = StackItem(SyntaxChars::LIMIT.code, "�", SyntaxChars::LIMIT);
StackItem NOT_TERM = StackItem(SyntaxChars::NONTERMINAL.code, SyntaxChars::NONTERMINAL.tokenString, SyntaxChars::NONTERMINAL);