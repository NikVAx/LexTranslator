#pragma once

#include "../LEXER/lexer_config.h"

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>

template <typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

/* ----------------- RELATION MATRIX ----------------- */

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
    { Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::BASE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::BASE, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::BASE} ,
    { Relations::NONE, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::BASE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NONE, Relations::BASE, Relations::NONE} ,
});

/* ----------------- END RELATION MATRIX ----------------- */

/* ----------------- TOKENS ----------------- */

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

    bool operator ==(const TokenMeta& token) {
        return this->code == token.code && this->symbol == token.symbol && this->type == token.type;
    }

    friend std::ostream& operator<<(std::ostream& s, const TokenMeta& token)
    {
        s << "code: " << token.code << " symbol: " << token.symbol.c_str() << " type: " << as_integer(token.type) << std::endl;
        return s;
    }
};

class SYNTAX_TOKENS {
public:
    static const TokenMeta LIMIT;
    static const TokenMeta PLUS; 
    static const TokenMeta MINUS;
    static const TokenMeta MULTIPLY;
    static const TokenMeta DIVIDE;
    static const TokenMeta IDENTIFIER;
    static const TokenMeta OPEN_BRACKET;
    static const TokenMeta CLOSE_BRACKET;
    static const TokenMeta SEMICOLON;
    static const TokenMeta ASSIGNMENT;
    static const TokenMeta NONTERMINAL;
};

const TokenMeta SYNTAX_TOKENS::LIMIT = TokenMeta(0, "#", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_TOKENS::PLUS = TokenMeta(1, "+", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_TOKENS::MINUS = TokenMeta(2, "-", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_TOKENS::MULTIPLY = TokenMeta(3, "*", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_TOKENS::DIVIDE = TokenMeta(4, "/", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_TOKENS::IDENTIFIER = TokenMeta(5, "I", TOKEN_TYPE::NONTERMINAL);
const TokenMeta SYNTAX_TOKENS::OPEN_BRACKET = TokenMeta(6, "(", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_TOKENS::CLOSE_BRACKET = TokenMeta(7, ")", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_TOKENS::SEMICOLON = TokenMeta(8, ";", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_TOKENS::ASSIGNMENT = TokenMeta(9, ":=", TOKEN_TYPE::TERMINAL);
const TokenMeta SYNTAX_TOKENS::NONTERMINAL = TokenMeta(10, "S", TOKEN_TYPE::NONTERMINAL);

std::map<TermTypes, int> ROW_COLUMN_MAP = {
    { TermTypes::PLUS,  SYNTAX_TOKENS::PLUS.code}, // +
    { TermTypes::MINUS, SYNTAX_TOKENS::MINUS.code }, // -
    { TermTypes::MULTIPLY, SYNTAX_TOKENS::MULTIPLY.code }, // *
    { TermTypes::DIVIDE, SYNTAX_TOKENS::DIVIDE.code }, // /
    { TermTypes::IDENTIFIER,  SYNTAX_TOKENS::IDENTIFIER.code }, // идентификатор
    { TermTypes::NUMBER,  SYNTAX_TOKENS::IDENTIFIER.code }, // идентификатор
    { TermTypes::OPEN_BRACKET,  SYNTAX_TOKENS::OPEN_BRACKET.code }, // (
    { TermTypes::CLOSE_BRACKET,  SYNTAX_TOKENS::CLOSE_BRACKET.code }, // )
    { TermTypes::SEMICOLON,  SYNTAX_TOKENS::SEMICOLON.code }, // ;
    { TermTypes::ASSIGNMENT,  SYNTAX_TOKENS::ASSIGNMENT.code }, // :=
    { (TermTypes)20, SYNTAX_TOKENS::LIMIT.code}, // #
};

std::map<int, std::string> MAP_INPUT_STRING = {
    { SYNTAX_TOKENS::PLUS.code, SYNTAX_TOKENS::PLUS.symbol }, // +
    { SYNTAX_TOKENS::MINUS.code, SYNTAX_TOKENS::MINUS.symbol }, // -
    { SYNTAX_TOKENS::MULTIPLY.code, SYNTAX_TOKENS::MULTIPLY.symbol }, // *
    { SYNTAX_TOKENS::DIVIDE.code,  SYNTAX_TOKENS::DIVIDE.symbol }, // /
    { SYNTAX_TOKENS::IDENTIFIER.code,  SYNTAX_TOKENS::IDENTIFIER.symbol }, // идентификатор
    { SYNTAX_TOKENS::OPEN_BRACKET.code,  SYNTAX_TOKENS::OPEN_BRACKET.symbol }, // (
    { SYNTAX_TOKENS::CLOSE_BRACKET.code,  SYNTAX_TOKENS::CLOSE_BRACKET.symbol }, // )
    { SYNTAX_TOKENS::SEMICOLON.code,  SYNTAX_TOKENS::SEMICOLON.symbol }, // ;
    { SYNTAX_TOKENS::ASSIGNMENT.code,  SYNTAX_TOKENS::ASSIGNMENT.symbol }, // :=
    { SYNTAX_TOKENS::LIMIT.code,  SYNTAX_TOKENS::LIMIT.symbol }, // #
    { SYNTAX_TOKENS::NONTERMINAL.code,  SYNTAX_TOKENS::NONTERMINAL.symbol}, // S
};

/* ----------------- TOKENS END ----------------- */

/* ----------------- RULES ----------------- */

template <class T>
std::string join(std::vector<T> items, std::string delim = "") {
    std::ostringstream imploded;
    std::copy(items.begin(), items.end(),
        std::ostream_iterator<std::string>(imploded, delim.c_str()));
    return  imploded.str();
}

class BuildRule {
private:
    std::vector<TokenMeta> EXCLUDE_SYMBOLS = { SYNTAX_TOKENS::OPEN_BRACKET, SYNTAX_TOKENS::CLOSE_BRACKET, SYNTAX_TOKENS::SEMICOLON };

    std::vector<std::string> getTokenSymbols(std::vector<TokenMeta> items) {
        std::vector<std::string> symbols;
        for (auto token : items) {
            symbols.push_back(token.symbol);
        }
        return symbols;
    }

    std::vector<TokenMeta> getSimpleRule(std::vector<TokenMeta> items) {
        std::vector<TokenMeta> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](TokenMeta item) {
            return std::find(EXCLUDE_SYMBOLS.begin(), EXCLUDE_SYMBOLS.end(), item) != EXCLUDE_SYMBOLS.end();
        });
        return filteredItems;
    }

    std::vector<TokenMeta> _getTerminalItems(std::vector<TokenMeta> items) {
        std::vector<TokenMeta> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](TokenMeta item) {
            return item.type == TOKEN_TYPE::TERMINAL;
        });
        return filteredItems;
    }

    std::vector<TokenMeta> _getNonterminalItems(std::vector<TokenMeta> items) {
        std::vector<TokenMeta> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](TokenMeta item) {
            return item.type == TOKEN_TYPE::NONTERMINAL;
        });
        return filteredItems;
    }

public:
    std::vector<TokenMeta> items;
    std::string ruleString;

    BuildRule() { }

    BuildRule(std::vector<TokenMeta> items) : items(items), ruleString(join(getTokenSymbols(items))) {};

    std::string getRuleString(){
        return join(getTokenSymbols(getSimpleRule(items)));
    }

    std::string getTerminalsString() {
        return join(getTokenSymbols(_getTerminalItems(items)));
    }

    std::vector<TokenMeta> getNonTerminalItems() {
        return _getNonterminalItems(items);
    }

    std::vector<TokenMeta> getTerminalItems() {
        return _getTerminalItems(items);
    };

    friend std::ostream& operator<<(std::ostream& s, const BuildRule rule) {
        s << rule.ruleString << std::endl;
        return s;
    }
};

struct SyntaxRule {
    SyntaxRule() {}

    SyntaxRule(int code, BuildRule rule) {
        this->code = code;
        this->rule = rule;
    }

    int code;
    BuildRule rule;

    friend std::ostream& operator<<(std::ostream& s, const SyntaxRule& rule)
    {
        s << "code: " << rule.code << " rule: " << rule.rule << std::endl;
        return s;
    }
};

class SYNTAX_RULES {
public:
    static const SyntaxRule R1;
    static const SyntaxRule R2;
    static const SyntaxRule R4;
    static const SyntaxRule R5;
    static const SyntaxRule R7;
    static const SyntaxRule R8;
    static const SyntaxRule R9;
};

const SyntaxRule SYNTAX_RULES::R1 = SyntaxRule(1, BuildRule({ SYNTAX_TOKENS::IDENTIFIER, SYNTAX_TOKENS::ASSIGNMENT, SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::SEMICOLON }));
const SyntaxRule SYNTAX_RULES::R2 = SyntaxRule(2, BuildRule({ SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::PLUS, SYNTAX_TOKENS::NONTERMINAL }));
const SyntaxRule SYNTAX_RULES::R4 = SyntaxRule(3, BuildRule({ SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::MULTIPLY, SYNTAX_TOKENS::NONTERMINAL }));
const SyntaxRule SYNTAX_RULES::R5 = SyntaxRule(5, BuildRule({ SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::DIVIDE, SYNTAX_TOKENS::NONTERMINAL }));
const SyntaxRule SYNTAX_RULES::R7 = SyntaxRule(7, BuildRule({ SYNTAX_TOKENS::OPEN_BRACKET, SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::CLOSE_BRACKET }));
const SyntaxRule SYNTAX_RULES::R8 = SyntaxRule(8, BuildRule({ SYNTAX_TOKENS::MINUS, SYNTAX_TOKENS::OPEN_BRACKET, SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::CLOSE_BRACKET }));
const SyntaxRule SYNTAX_RULES::R9 = SyntaxRule(9, BuildRule({ SYNTAX_TOKENS::IDENTIFIER }));

std::map<std::string, SyntaxRule> REDUCE_RULES = {
    {SYNTAX_RULES::R1.rule.ruleString, SYNTAX_RULES::R1 },
    {SYNTAX_RULES::R2.rule.ruleString, SYNTAX_RULES::R2 },
    {SYNTAX_RULES::R4.rule.ruleString, SYNTAX_RULES::R4 },
    {SYNTAX_RULES::R5.rule.ruleString, SYNTAX_RULES::R5 },
    {SYNTAX_RULES::R7.rule.ruleString, SYNTAX_RULES::R7 },
    {SYNTAX_RULES::R8.rule.ruleString, SYNTAX_RULES::R8 },
    {SYNTAX_RULES::R9.rule.ruleString, SYNTAX_RULES::R9 }
};

std::map<int, BuildRule> BUILD_RULES = {
    { SYNTAX_RULES::R1.code,  SYNTAX_RULES::R1.rule },
    { SYNTAX_RULES::R2.code,  SYNTAX_RULES::R2.rule },
    { SYNTAX_RULES::R4.code,  SYNTAX_RULES::R4.rule },
    { SYNTAX_RULES::R5.code,  SYNTAX_RULES::R5.rule },
    { SYNTAX_RULES::R7.code,  SYNTAX_RULES::R7.rule },
    { SYNTAX_RULES::R8.code,  SYNTAX_RULES::R8.rule },
    { SYNTAX_RULES::R9.code,  SYNTAX_RULES::R9.rule },
};

/* ----------------- RULES END ----------------- */