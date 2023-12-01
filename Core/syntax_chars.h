#pragma once

#include "syntax_char.h"

// TODO: не понятно, это часть конфигурации или глобальный набор значений
// коды - индексы столбцов, т.е. часть конфигурации?
namespace SyntaxChars {
    const SyntaxChar LIMIT(0, "#", TokenType::TERMINAL);
    const SyntaxChar PLUS(1, "+", TokenType::TERMINAL);
    const SyntaxChar MINUS(2, "-", TokenType::TERMINAL);
    const SyntaxChar MULTIPLY(3, "*", TokenType::TERMINAL);
    const SyntaxChar DIVIDE(4, "/", TokenType::TERMINAL);
    const SyntaxChar IDENTIFIER(5, "I", TokenType::NONTERMINAL);
    const SyntaxChar OPEN_BRACKET(6, "(", TokenType::TERMINAL);
    const SyntaxChar CLOSE_BRACKET(7, ")", TokenType::TERMINAL);
    const SyntaxChar SEMICOLON(8, ";", TokenType::TERMINAL);
    const SyntaxChar ASSIGNMENT(9, ":=", TokenType::TERMINAL);
    const SyntaxChar NONTERMINAL(10, "S", TokenType::NONTERMINAL);
}