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
    { TermTypes::ASSIGNMENT, SyntaxChars::ASSIGNMENT },
    { TermTypes::PLUS, SyntaxChars::PLUS },
    { TermTypes::MINUS, SyntaxChars::MINUS },
    { TermTypes::EQUAL, SyntaxChars::EQUAL },
    { TermTypes::SEMICOLON, SyntaxChars::SEMICOLON },
};

namespace SyntaxRules {
    const SyntaxRule R1 = SyntaxRule(1, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::SEMICOLON }));
    const SyntaxRule R2 = SyntaxRule(2, BuildRule({ SyntaxChars::IF, SyntaxChars::NONTERMINAL, SyntaxChars::THEN, SyntaxChars::NONTERMINAL, SyntaxChars::ELSE, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R3 = SyntaxRule(3, BuildRule({ SyntaxChars::IF, SyntaxChars::NONTERMINAL, SyntaxChars::THEN, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R4 = SyntaxRule(4, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::ASSIGNMENT, SyntaxChars::IDENTIFIER }));
    const SyntaxRule R5 = SyntaxRule(5, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::LESS, SyntaxChars::IDENTIFIER }));
    const SyntaxRule R6 = SyntaxRule(6, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::GREATER, SyntaxChars::IDENTIFIER }));
    const SyntaxRule R7 = SyntaxRule(7, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::EQUAL, SyntaxChars::IDENTIFIER }));

    const SyntaxRule R8 = SyntaxRule(8, BuildRule({ SyntaxChars::PLUS, SyntaxChars::IDENTIFIER }));
    const SyntaxRule R9 = SyntaxRule(9, BuildRule({ SyntaxChars::MINUS, SyntaxChars::IDENTIFIER }));

    const SyntaxRule R10 = SyntaxRule(10, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::ASSIGNMENT, SyntaxChars::PLUS, SyntaxChars::IDENTIFIER }));
    const SyntaxRule R11 = SyntaxRule(11, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::ASSIGNMENT, SyntaxChars::MINUS, SyntaxChars::IDENTIFIER }));

    const SyntaxRule R12 = SyntaxRule(12, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::EQUAL, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R13 = SyntaxRule(13, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::EQUAL, SyntaxChars::IDENTIFIER }));
    const SyntaxRule R14 = SyntaxRule(13, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::EQUAL, SyntaxChars::NONTERMINAL }));

    const SyntaxRule R15 = SyntaxRule(14, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::GREATER, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R16 = SyntaxRule(15, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::GREATER, SyntaxChars::IDENTIFIER }));
    const SyntaxRule R17 = SyntaxRule(16, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::GREATER, SyntaxChars::NONTERMINAL }));

    const SyntaxRule R18 = SyntaxRule(17, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::LESS, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R19 = SyntaxRule(18, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::LESS, SyntaxChars::IDENTIFIER }));
    const SyntaxRule R20 = SyntaxRule(19, BuildRule({ SyntaxChars::NONTERMINAL, SyntaxChars::LESS, SyntaxChars::NONTERMINAL }));
    const SyntaxRule R21 = SyntaxRule(21, BuildRule({ SyntaxChars::IDENTIFIER }));
    const SyntaxRule R22 = SyntaxRule(22, BuildRule({ SyntaxChars::IDENTIFIER, SyntaxChars::ASSIGNMENT, SyntaxChars::NONTERMINAL }));
}

/*
if a > -1.5e-3 then
 if a > -1.5e-3 then
   x:=+1.0
 else
   x:=-1.0
else
  x:=0;

*/

const std::vector<SyntaxRule> RULES = {
    SyntaxRules::R1,
    SyntaxRules::R2,
    SyntaxRules::R3,
    SyntaxRules::R4,
    SyntaxRules::R5,
    SyntaxRules::R6,
    SyntaxRules::R7,
    SyntaxRules::R8,
    SyntaxRules::R9,
    SyntaxRules::R10,
    SyntaxRules::R11,
    SyntaxRules::R12,
    SyntaxRules::R13,
    SyntaxRules::R14,
    SyntaxRules::R15,
    SyntaxRules::R16,
    SyntaxRules::R17,
    SyntaxRules::R18,
    SyntaxRules::R19,
    SyntaxRules::R20,
    SyntaxRules::R21,
    SyntaxRules::R22

};

SyntaxConfig MathGrammarConfig(MATRIX_1, TERM_TYPE_TO_MATRIX_INDEX, RULES, MATRIX_1_ERRORS);