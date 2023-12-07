#pragma once

#include "syntax_chars.h"
#include "syntax_rule.h"
#include "operators_matrices.h"
#include "syntax_config.h"
#include "term_types.h"

#include <map>

const std::map<TermType, SyntaxChar> TERM_TYPE_TO_MATRIX_INDEX = {
    { TermTypes::PLUS, SyntaxChars::PLUS },
    { TermTypes::MINUS, SyntaxChars::MINUS },
    { TermTypes::MULTIPLY, SyntaxChars::MULTIPLY },
    { TermTypes::DIVIDE, SyntaxChars::DIVIDE },
    { TermTypes::IDENTIFIER, SyntaxChars::IDENTIFIER },
    { TermTypes::NUMBER, SyntaxChars::IDENTIFIER },
    { TermTypes::OPEN_BRACKET, SyntaxChars::OPEN_BRACKET },
    { TermTypes::CLOSE_BRACKET, SyntaxChars::CLOSE_BRACKET },
    { TermTypes::SEMICOLON, SyntaxChars::SEMICOLON },
    { TermTypes::ASSIGNMENT, SyntaxChars::ASSIGNMENT },
    { TermTypes::LIMIT, SyntaxChars::LIMIT },
};

namespace SyntaxRules {
    const SyntaxRule R1 = SyntaxRule(1, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::ASSIGNMENT, SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON }));
    const SyntaxRule R2 = SyntaxRule(2, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::PLUS, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R3 = SyntaxRule(3, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::MINUS, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R5 = SyntaxRule(5, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::MULTIPLY, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R6 = SyntaxRule(6, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::DIVIDE, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R8 = SyntaxRule(8, BuildRule({ SyntaxChars::OPEN_BRACKET, SyntaxChars::NONTERMINAL, SyntaxChars::CLOSE_BRACKET }));
    const SyntaxRule R10 = SyntaxRule(10, BuildRule({ SyntaxChars::IDENTIFIER }));
}

const std::vector<SyntaxRule> RULES = {
    SyntaxRules::R1,
    SyntaxRules::R2,
    SyntaxRules::R3,
    SyntaxRules::R5,
    SyntaxRules::R6,
    SyntaxRules::R8,
    SyntaxRules::R10,
};

SyntaxConfig MathGrammarConfig(MATRIX_1, TERM_TYPE_TO_MATRIX_INDEX, RULES, MATRIX_1_ERRORS);