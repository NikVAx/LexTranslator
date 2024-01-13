#pragma once

#include "syntax_char.h"

// TODO: не понятно, это часть конфигурации или глобальный набор значений
// коды - индексы столбцов, т.е. часть конфигурации?
namespace SyntaxChars {
    const SyntaxChar OR(0, " or ", TokenType::TERMINAL);
    const SyntaxChar XOR(1, " xor ", TokenType::TERMINAL);
    const SyntaxChar AND(2, " and ", TokenType::TERMINAL);
    const SyntaxChar NOT(3, " not ", TokenType::TERMINAL);
    const SyntaxChar OPEN_BRACKET(4, "(", TokenType::TERMINAL);
    const SyntaxChar CLOSE_BRACKET(5, ")", TokenType::TERMINAL);
    const SyntaxChar IDENTIFIER(6, "I", TokenType::NONTERMINAL);
    const SyntaxChar NONTERMINAL(7, "S", TokenType::NONTERMINAL);
    const SyntaxChar ASSIGNMENT(8, ":=", TokenType::TERMINAL);
    const SyntaxChar SEMICOLON(9, ";", TokenType::TERMINAL);
    const SyntaxChar LIMIT(10, "#", TokenType::TERMINAL);
}

