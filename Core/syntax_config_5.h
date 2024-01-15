#pragma once

#include "syntax_chars.h"
#include "syntax_rule.h"
#include "operators_matrices.h"
#include "syntax_config.h"
#include "term_types.h"

#include <map>

const std::map<TermType, SyntaxChar> TERM_TYPE_TO_MATRIX_INDEX = {
    { TermTypes::LIMIT, SyntaxChars::LIMIT },
    { TermTypes::IF, SyntaxChars::IF },
    { TermTypes::THEN, SyntaxChars::THEN },
    { TermTypes::ELSE, SyntaxChars::ELSE },
    { TermTypes::IDENTIFIER, SyntaxChars::IDENTIFIER },
    { TermTypes::NUMBER, SyntaxChars::IDENTIFIER },
    { TermTypes::GREATER, SyntaxChars::GREATER },
    { TermTypes::LESS, SyntaxChars::LESS },
    { TermTypes::EQUAL, SyntaxChars::EQUAL },
    { TermTypes::ASSIGNMENT, SyntaxChars::ASSIGNMENT },
    { TermTypes::SEMICOLON, SyntaxChars::SEMICOLON },
};

namespace SyntaxRules {
    const SyntaxRule R1 = SyntaxRule(1, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON }));
    const SyntaxRule R2 = SyntaxRule(2, BuildRule({ SyntaxChars::IF, SyntaxChars::NONTERMINAL, SyntaxChars::THEN, SyntaxChars::NONTERMINAL, SyntaxChars::ELSE, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R3 = SyntaxRule(3, BuildRule({ SyntaxChars::IF, SyntaxChars::NONTERMINAL, SyntaxChars::THEN, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R4 = SyntaxRule(4, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::ASSIGNMENT, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R5 = SyntaxRule(5, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::LESS, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R6 = SyntaxRule(6, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::GREATER, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R7 = SyntaxRule(7, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::EQUAL, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R8 = SyntaxRule(8, BuildRule({ SyntaxChars::IDENTIFIER }));
}

const std::vector<SyntaxRule> RULES = {
    SyntaxRules::R1,
    SyntaxRules::R2,
    SyntaxRules::R3,
    SyntaxRules::R4,
    SyntaxRules::R5,
    SyntaxRules::R6,
    SyntaxRules::R7,
    SyntaxRules::R8,
};

SyntaxConfig MathGrammarConfig(MATRIX_1, TERM_TYPE_TO_MATRIX_INDEX, RULES, MATRIX_1_ERRORS);