#pragma once

#include "constants.h"
#include "../Core/term_types.h"

#include <string>

struct StackItem {
    StackItem(int code, std::string value = "")
        : code(code)
        , value(value)
    { }

    int code;

    std::string value;

    bool isNotTerm() {
        return code == SYNTAX_TOKENS::NONTERMINAL.code;
    }
};

StackItem START_LIMIT = StackItem(SYNTAX_TOKENS::LIMIT.code, "Í");
StackItem NOT_TERM = StackItem(SYNTAX_TOKENS::NONTERMINAL.code, SYNTAX_TOKENS::NONTERMINAL.symbol);