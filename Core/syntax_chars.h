#pragma once

#include "syntax_char.h"

// TODO: не понятно, это часть конфигурации или глобальный набор значений
// коды - индексы столбцов, т.е. часть конфигурации?
namespace SyntaxChars {
    const SyntaxChar LESS(0, "<", TokenType::TERMINAL);
    const SyntaxChar GREATER(1, ">", TokenType::TERMINAL);
    const SyntaxChar EQUAL(2, "=", TokenType::TERMINAL);
    const SyntaxChar IF(3, "if", TokenType::TERMINAL);
    const SyntaxChar THEN(4, "then", TokenType::TERMINAL);
    const SyntaxChar ELSE(5, "else", TokenType::TERMINAL);
    const SyntaxChar IDENTIFIER(6, "I", TokenType::NONTERMINAL);
    const SyntaxChar NONTERMINAL(7, "S", TokenType::NONTERMINAL);
    const SyntaxChar ASSIGNMENT(8, ":=", TokenType::TERMINAL);
    const SyntaxChar SEMICOLON(9, ";", TokenType::TERMINAL);
    const SyntaxChar LIMIT(10, "#", TokenType::TERMINAL);
}

