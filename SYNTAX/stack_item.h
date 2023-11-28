#pragma once

#include "constants.h"
#include "../Core/term_types.h"

#include <string>

struct StackItem {
    StackItem(int code, std::string tag = "", std::string value = "")
        : code(code)
        , value(value)
        , tag(tag == "" ? MAP_INPUT_STRING[code] : tag)
    { }

    int code;

    std::string value;
    std::string tag;

    bool isNotTerm() {
        return code == SYNTAX_TOKENS::NONTERMINAL.code;
    }
};

StackItem START_LIMIT = StackItem(SYNTAX_TOKENS::LIMIT.code, "Í");
StackItem NOT_TERM = StackItem(SYNTAX_TOKENS::NONTERMINAL.code, SYNTAX_TOKENS::NONTERMINAL.symbol);