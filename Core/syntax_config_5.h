#pragma once

#include "syntax_chars.h"
#include "syntax_rule.h"
#include "operators_matrices.h"
#include "syntax_config.h"
#include "term_types.h"

#include <map>

const std::map<TermType, SyntaxChar> TERM_TYPE_TO_MATRIX_INDEX = {
    { TermTypes::OR, SyntaxChars::OR },
    { TermTypes::XOR, SyntaxChars::XOR },
    { TermTypes::AND, SyntaxChars::AND },
    { TermTypes::NOT, SyntaxChars::NOT },
    { TermTypes::OPEN_BRACKET, SyntaxChars::OPEN_BRACKET },
    { TermTypes::CLOSE_BRACKET, SyntaxChars::CLOSE_BRACKET },
    { TermTypes::IDENTIFIER, SyntaxChars::IDENTIFIER },
    { TermTypes::TRUE, SyntaxChars::IDENTIFIER },
    { TermTypes::FALSE, SyntaxChars::IDENTIFIER },
    { TermTypes::ASSIGNMENT, SyntaxChars::ASSIGNMENT },
    { TermTypes::SEMICOLON, SyntaxChars::SEMICOLON },
    { TermTypes::LIMIT, SyntaxChars::LIMIT },
};

namespace SyntaxRules {
    const SyntaxRule R1 = SyntaxRule(1, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::ASSIGNMENT, SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON }));
    const SyntaxRule R2 = SyntaxRule(2, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::OR, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R3 = SyntaxRule(3, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::XOR, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R4 = SyntaxRule(4, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::AND, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R5 = SyntaxRule(5, BuildRule({ SyntaxChars::NOT, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R6 = SyntaxRule(6, BuildRule({ SyntaxChars::OPEN_BRACKET, SyntaxChars::NONTERMINAL, SyntaxChars::CLOSE_BRACKET }));
    const SyntaxRule R7 = SyntaxRule(7, BuildRule({ SyntaxChars::IDENTIFIER }));
}

const std::vector<SyntaxRule> RULES = {
    SyntaxRules::R1,
    SyntaxRules::R2,
    SyntaxRules::R3,
    SyntaxRules::R4,
    SyntaxRules::R5,
    SyntaxRules::R6,
    SyntaxRules::R7,
};

SyntaxConfig MathGrammarConfig(MATRIX_1, TERM_TYPE_TO_MATRIX_INDEX, RULES, MATRIX_1_ERRORS);