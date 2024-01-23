#pragma once

#include "syntax_char.h"

// TODO: не понятно, это часть конфигурации или глобальный набор значений
// коды - индексы столбцов, т.е. часть конфигурации?
namespace SyntaxChars {
    const SyntaxChar LIMIT(0, "#", TokenType::TERMINAL);
    const SyntaxChar IF(1, "if ", TokenType::TERMINAL);
    const SyntaxChar THEN(2, " then ", TokenType::TERMINAL);
    const SyntaxChar ELSE(3, " else ", TokenType::TERMINAL);
    const SyntaxChar IDENTIFIER(4, "I", TokenType::TERMINAL);
    const SyntaxChar GREATER(5, ">", TokenType::TERMINAL);
    const SyntaxChar LESS(6, "<", TokenType::TERMINAL);
    const SyntaxChar ASSIGNMENT(7, ":=", TokenType::TERMINAL);
    const SyntaxChar PLUS(8, "+", TokenType::TERMINAL);
    const SyntaxChar MINUS(9, "-", TokenType::TERMINAL);
    const SyntaxChar EQUAL(10, "=", TokenType::TERMINAL);
    const SyntaxChar SEMICOLON(11, ";", TokenType::TERMINAL);
    const SyntaxChar NONTERMINAL(12, "S", TokenType::NONTERMINAL);
    

    const SyntaxChar OPEN_BRACKET(101, "#", TokenType::TERMINAL);
    const SyntaxChar CLOSE_BRACKET(102, "#", TokenType::TERMINAL);
}

