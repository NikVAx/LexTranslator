#pragma once

#include <vector>
#include <string>
#include <map>

enum class Relations : char {
    BASE = '=',
    NEXT = '>',
    PREV = '<',
    NONE = '-'
};

class RelationMatrix {
public:
    const std::vector<std::vector<Relations>> MATRIX;

    const int SIZE() {
        return MATRIX.size();
    }

    RelationMatrix(const std::vector<std::vector<Relations>> matrix)
        : MATRIX(matrix) { 
        if (MATRIX.size() != MATRIX[0].size()) {
            throw std::exception("It is not relation matrix");
        } 
    }
};

RelationMatrix MATH_MATRIX({
    { Relations::NEXT, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::BASE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::NEXT, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE} ,
    { Relations::NEXT, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE} ,
    { Relations::NEXT, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::BASE, Relations::NONE} ,
    { Relations::NEXT, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::BASE, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::NEXT, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NEXT} ,
    { Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NONE, Relations::BASE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::PREV, Relations::NONE, Relations::NONE, Relations::NONE, Relations::PREV, Relations::NONE, Relations::NONE} ,
});



enum class TOKEN_TYPE {
    TERMINAL,
    NONTERMINAL
};

struct TokenMeta {
    TokenMeta(int code, std::string symbol, TOKEN_TYPE type) {
        this->code = code;
        this->symbol = symbol;
        this->type = type;
    }

    int code;
    std::string symbol;
    TOKEN_TYPE type;
};

class SYNTAX_CONSTANTS {
public:
    static const TokenMeta PLUS; 
    static const TokenMeta MINUS;
    static const TokenMeta MULTIPLY;
    static const TokenMeta DIVIDE;
    static const TokenMeta INDENTIFIER;
    static const TokenMeta NUMBER;
    static const TokenMeta OPEN_BRACKET;
    static const TokenMeta CLOSE_BRACKET;
    static const TokenMeta SEMICOLON;
    static const TokenMeta ASSIGNMENT;
    static const TokenMeta LIMIT;
};

const TokenMeta SYNTAX_CONSTANTS::PLUS = TokenMeta(0, "+", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_CONSTANTS::MINUS = TokenMeta(1, "-", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_CONSTANTS::MULTIPLY = TokenMeta(2, "*", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_CONSTANTS::DIVIDE = TokenMeta(3, "/", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_CONSTANTS::INDENTIFIER = TokenMeta(4, "I", TOKEN_TYPE::NONTERMINAL);
const TokenMeta SYNTAX_CONSTANTS::NUMBER = TokenMeta(5, "R", TOKEN_TYPE::NONTERMINAL);
const TokenMeta SYNTAX_CONSTANTS::OPEN_BRACKET = TokenMeta(6, "(", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_CONSTANTS::CLOSE_BRACKET = TokenMeta(7, ")", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_CONSTANTS::SEMICOLON = TokenMeta(8, ";", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_CONSTANTS::ASSIGNMENT = TokenMeta(9, ":=", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_CONSTANTS::LIMIT = TokenMeta(10, "#", TOKEN_TYPE::TERMINAL);

std::map<int, int> ROW_COLUMN_MAP = {
    { 6,  SYNTAX_CONSTANTS::PLUS.code}, // +
    { 10, SYNTAX_CONSTANTS::MINUS.code }, // -
    { 11, SYNTAX_CONSTANTS::MULTIPLY.code }, // *
    { 12, SYNTAX_CONSTANTS::DIVIDE.code }, // /
    { 1,  SYNTAX_CONSTANTS::INDENTIFIER.code }, // идентификатор
    { 2,  SYNTAX_CONSTANTS::NUMBER.code }, // число
    { 4,  SYNTAX_CONSTANTS::OPEN_BRACKET.code }, // (
    { 5,  SYNTAX_CONSTANTS::CLOSE_BRACKET.code }, // )
    { 7,  SYNTAX_CONSTANTS::SEMICOLON.code }, // ;
    { 3,  SYNTAX_CONSTANTS::ASSIGNMENT.code }, // :=
    { 20, SYNTAX_CONSTANTS::LIMIT.code}, // #
};