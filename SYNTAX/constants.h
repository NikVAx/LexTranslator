#pragma once


#include "../Core/term_types.h"
#include "../Core/syntax_chars.h"

#include <vector>
#include <string>
#include <map>
#include <algorithm>



std::map<int, std::string> MAP_INPUT_STRING = {
    { SyntaxChars::PLUS.code, SyntaxChars::PLUS.tokenString }, // +
    { SyntaxChars::MINUS.code, SyntaxChars::MINUS.tokenString }, // -
    { SyntaxChars::MULTIPLY.code, SyntaxChars::MULTIPLY.tokenString }, // *
    { SyntaxChars::DIVIDE.code,  SyntaxChars::DIVIDE.tokenString }, // /
    { SyntaxChars::IDENTIFIER.code,  SyntaxChars::IDENTIFIER.tokenString }, // идентификатор
    { SyntaxChars::OPEN_BRACKET.code,  SyntaxChars::OPEN_BRACKET.tokenString }, // (
    { SyntaxChars::CLOSE_BRACKET.code,  SyntaxChars::CLOSE_BRACKET.tokenString }, // )
    { SyntaxChars::SEMICOLON.code,  SyntaxChars::SEMICOLON.tokenString }, // ;
    { SyntaxChars::ASSIGNMENT.code,  SyntaxChars::ASSIGNMENT.tokenString }, // :=
    { SyntaxChars::LIMIT.code,  SyntaxChars::LIMIT.tokenString }, // #
    { SyntaxChars::NONTERMINAL.code,  SyntaxChars::NONTERMINAL.tokenString}, // S
};

std::vector<TermType> SHOULD_ADD_VALUES = {
    TermTypes::NUMBER, TermTypes::IDENTIFIER
};

// TODO: remove from code
bool shouldAddValue(TermType type) {
    return std::find(SHOULD_ADD_VALUES.begin(), SHOULD_ADD_VALUES.end(), type) != SHOULD_ADD_VALUES.end();
}
