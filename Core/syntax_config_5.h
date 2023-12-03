#pragma once
#include "syntax_chars.h"
#include "syntax_rule.h"
#include "operators_matrices.h"
#include "syntax_config.h"
#include "term_types.h"
#include <map>

const std::map<TermType, int> TERM_TYPE_TO_MATRIX_INDEX = {
    { TermTypes::PLUS, SyntaxChars::PLUS.code},
    { TermTypes::MINUS, SyntaxChars::MINUS.code },
    { TermTypes::MULTIPLY, SyntaxChars::MULTIPLY.code },
    { TermTypes::DIVIDE, SyntaxChars::DIVIDE.code },
    { TermTypes::IDENTIFIER, SyntaxChars::IDENTIFIER.code },
    { TermTypes::NUMBER, SyntaxChars::IDENTIFIER.code },
    { TermTypes::OPEN_BRACKET, SyntaxChars::OPEN_BRACKET.code },
    { TermTypes::CLOSE_BRACKET, SyntaxChars::CLOSE_BRACKET.code },
    { TermTypes::SEMICOLON, SyntaxChars::SEMICOLON.code },
    { TermTypes::ASSIGNMENT, SyntaxChars::ASSIGNMENT.code },
    { TermTypes::LIMIT, SyntaxChars::LIMIT.code},
};

namespace SyntaxRules
{
    const SyntaxRule R0 = SyntaxRule(BuildRule({ SyntaxChars::IDENTIFIER }));
    const SyntaxRule R1 = SyntaxRule(BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::ASSIGNMENT, SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON }));
    const SyntaxRule R2 = SyntaxRule(BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::PLUS, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R3 = SyntaxRule(BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::MINUS, SyntaxChars::NONTERMINAL }));

    const SyntaxRule R5 = SyntaxRule(BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::MULTIPLY, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R6 = SyntaxRule(BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::DIVIDE, SyntaxChars::NONTERMINAL }));

    const SyntaxRule R8 = SyntaxRule(BuildRule({ SyntaxChars::OPEN_BRACKET, SyntaxChars::NONTERMINAL, SyntaxChars::CLOSE_BRACKET }));
    const SyntaxRule R9 = SyntaxRule(BuildRule({ SyntaxChars::MINUS, SyntaxChars::OPEN_BRACKET, SyntaxChars::NONTERMINAL, SyntaxChars::CLOSE_BRACKET }));
    const SyntaxRule R10 = SyntaxRule(BuildRule({ SyntaxChars::IDENTIFIER }));
}

const std::vector<SyntaxRule> RULES = {
    SyntaxRules::R0,
    SyntaxRules::R1,
    SyntaxRules::R2,
    SyntaxRules::R3,
    
    SyntaxRules::R5,
    SyntaxRules::R6,

    SyntaxRules::R8,
    SyntaxRules::R9,
    SyntaxRules::R10,
};

SyntaxConfig MathGrammarConfig(MATRIX_1, TERM_TYPE_TO_MATRIX_INDEX, RULES);