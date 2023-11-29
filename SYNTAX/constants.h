#pragma once

#include "../Utils/cast_enum.h"
#include "../Utils/iterator.h"
#include "../Core/term_types.h"

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>

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

    const int size() {
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

RelationMatrix FOR_MATRIX({
    { Relations::NONE }
});
RelationMatrix IF_MATRIX({
    { Relations::NONE }
});
RelationMatrix BOOL_MATRIX({
    { Relations::NONE }
});

/* ----------------- END RELATION MATRIX ----------------- */

/* ----------------- TOKENS ----------------- */

enum class TokenType {
    TERMINAL,
    NONTERMINAL
};

struct SyntaxTokenMeta {
    SyntaxTokenMeta(int code, std::string symbol, TokenType type) {
        this->code = code;
        this->symbol = symbol;
        this->type = type;
    }

    int code;
    std::string symbol;
    TokenType type;

    bool operator ==(const SyntaxTokenMeta& token) const {
        return this->code == token.code;
    }

    friend std::ostream& operator<<(std::ostream& s, const SyntaxTokenMeta& token)
    {
        s << "code: " << token.code << " symbol: " << token.symbol.c_str() << " type: " << cast_enum(token.type);
        return s;
    }
};

class SYNTAX_TOKENS {
public:
    static const SyntaxTokenMeta LIMIT;
    static const SyntaxTokenMeta PLUS; 
    static const SyntaxTokenMeta MINUS;
    static const SyntaxTokenMeta MULTIPLY;
    static const SyntaxTokenMeta DIVIDE;
    static const SyntaxTokenMeta IDENTIFIER;
    static const SyntaxTokenMeta OPEN_BRACKET;
    static const SyntaxTokenMeta CLOSE_BRACKET;
    static const SyntaxTokenMeta SEMICOLON;
    static const SyntaxTokenMeta ASSIGNMENT;
    static const SyntaxTokenMeta NONTERMINAL;
};

const SyntaxTokenMeta SYNTAX_TOKENS::LIMIT = SyntaxTokenMeta(0, "#", TokenType::TERMINAL);
const SyntaxTokenMeta SYNTAX_TOKENS::PLUS = SyntaxTokenMeta(1, "+", TokenType::TERMINAL);
const SyntaxTokenMeta SYNTAX_TOKENS::MINUS = SyntaxTokenMeta(2, "-", TokenType::TERMINAL);
const SyntaxTokenMeta SYNTAX_TOKENS::MULTIPLY = SyntaxTokenMeta(3, "*", TokenType::TERMINAL);
const SyntaxTokenMeta SYNTAX_TOKENS::DIVIDE = SyntaxTokenMeta(4, "/", TokenType::TERMINAL);
const SyntaxTokenMeta SYNTAX_TOKENS::IDENTIFIER = SyntaxTokenMeta(5, "I", TokenType::NONTERMINAL);
const SyntaxTokenMeta SYNTAX_TOKENS::OPEN_BRACKET = SyntaxTokenMeta(6, "(", TokenType::TERMINAL);
const SyntaxTokenMeta SYNTAX_TOKENS::CLOSE_BRACKET = SyntaxTokenMeta(7, ")", TokenType::TERMINAL);
const SyntaxTokenMeta SYNTAX_TOKENS::SEMICOLON = SyntaxTokenMeta(8, ";", TokenType::TERMINAL);
const SyntaxTokenMeta SYNTAX_TOKENS::ASSIGNMENT = SyntaxTokenMeta(9, ":=", TokenType::TERMINAL);
const SyntaxTokenMeta SYNTAX_TOKENS::NONTERMINAL = SyntaxTokenMeta(10, "S", TokenType::NONTERMINAL);

std::map<TermType, int> ROW_COLUMN_MAP = {
    { TermTypes::PLUS, SYNTAX_TOKENS::PLUS.code}, // +
    { TermTypes::MINUS, SYNTAX_TOKENS::MINUS.code }, // -
    { TermTypes::MULTIPLY, SYNTAX_TOKENS::MULTIPLY.code }, // *
    { TermTypes::DIVIDE, SYNTAX_TOKENS::DIVIDE.code }, // /
    { TermTypes::IDENTIFIER,  SYNTAX_TOKENS::IDENTIFIER.code }, // идентификатор
    { TermTypes::NUMBER,  SYNTAX_TOKENS::IDENTIFIER.code }, // идентификатор
    { TermTypes::OPEN_BRACKET,  SYNTAX_TOKENS::OPEN_BRACKET.code }, // (
    { TermTypes::CLOSE_BRACKET,  SYNTAX_TOKENS::CLOSE_BRACKET.code }, // )
    { TermTypes::SEMICOLON,  SYNTAX_TOKENS::SEMICOLON.code }, // ;
    { TermTypes::ASSIGNMENT,  SYNTAX_TOKENS::ASSIGNMENT.code }, // :=
    { TermTypes::END_TERMINAL, SYNTAX_TOKENS::LIMIT.code}, // #
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
    std::vector<SyntaxTokenMeta> EXCLUDE_SYMBOLS = { SYNTAX_TOKENS::OPEN_BRACKET, SYNTAX_TOKENS::CLOSE_BRACKET, SYNTAX_TOKENS::SEMICOLON };

    std::vector<std::string> getTokenSymbols(std::vector<SyntaxTokenMeta> items) {
        std::vector<std::string> symbols;
        for (auto token : items) {
            symbols.push_back(token.symbol);
        }
        return symbols;
    }

    std::vector<SyntaxTokenMeta> getSimpleRule(std::vector<SyntaxTokenMeta> items) {
        std::vector<SyntaxTokenMeta> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](SyntaxTokenMeta item) {
            return std::find(EXCLUDE_SYMBOLS.begin(), EXCLUDE_SYMBOLS.end(), item) != EXCLUDE_SYMBOLS.end();
        });
        return filteredItems;
    }

    std::vector<SyntaxTokenMeta> _getTerminalItems(std::vector<SyntaxTokenMeta> items) {
        std::vector<SyntaxTokenMeta> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](SyntaxTokenMeta item) {
            return item.type == TokenType::TERMINAL;
        });
        return filteredItems;
    }

    std::vector<SyntaxTokenMeta> _getNonterminalItems(std::vector<SyntaxTokenMeta> items) {
        std::vector<SyntaxTokenMeta> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](SyntaxTokenMeta item) {
            return item.type == TokenType::NONTERMINAL;
        });
        return filteredItems;
    }

public:
    std::vector<SyntaxTokenMeta> items;
    std::string ruleString;

    BuildRule() { }

    BuildRule(std::vector<SyntaxTokenMeta> items) 
        : items(items)
        , ruleString(join(getTokenSymbols(items))) 
    {};

    std::string getRuleString(){
        return join(getTokenSymbols(getSimpleRule(items)));
    }

    std::string getTerminalsString() {
        return join(getTokenSymbols(_getTerminalItems(items)));
    }

    std::vector<SyntaxTokenMeta> getNonTerminalItems() {
        return _getNonterminalItems(items);
    }

    std::vector<SyntaxTokenMeta> getTerminalItems() {
        return _getTerminalItems(items);
    };

    friend std::ostream& operator<<(std::ostream& s, const BuildRule rule) {
        s << rule.ruleString << std::endl;
        return s;
    }
};

struct SyntaxRule {
    SyntaxRule() : rule(), code(-1) {};
    SyntaxRule(int code, BuildRule rule) : code(code), rule(rule) {}

    int code;
    BuildRule rule;

    friend std::ostream& operator<<(std::ostream& s, const SyntaxRule& rule)
    {
        s << "code: " << rule.code << " rule: " << rule.rule;
        return s;
    }

};

class SYNTAX_RULES {
public:
    static const SyntaxRule R0;
    static const SyntaxRule R1;
    static const SyntaxRule R2;
    static const SyntaxRule R4;
    static const SyntaxRule R5;
    static const SyntaxRule R7;
    static const SyntaxRule R8;
    static const SyntaxRule R9;
};

const SyntaxRule SYNTAX_RULES::R0 = SyntaxRule(0, BuildRule({ SYNTAX_TOKENS::IDENTIFIER }));
const SyntaxRule SYNTAX_RULES::R1 = SyntaxRule(1, BuildRule({ SYNTAX_TOKENS::IDENTIFIER, SYNTAX_TOKENS::ASSIGNMENT, SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::SEMICOLON }));
const SyntaxRule SYNTAX_RULES::R2 = SyntaxRule(2, BuildRule({ SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::PLUS, SYNTAX_TOKENS::NONTERMINAL }));
const SyntaxRule SYNTAX_RULES::R4 = SyntaxRule(3, BuildRule({ SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::MULTIPLY, SYNTAX_TOKENS::NONTERMINAL }));
const SyntaxRule SYNTAX_RULES::R5 = SyntaxRule(5, BuildRule({ SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::DIVIDE, SYNTAX_TOKENS::NONTERMINAL }));
const SyntaxRule SYNTAX_RULES::R7 = SyntaxRule(7, BuildRule({ SYNTAX_TOKENS::OPEN_BRACKET, SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::CLOSE_BRACKET }));
const SyntaxRule SYNTAX_RULES::R8 = SyntaxRule(8, BuildRule({ SYNTAX_TOKENS::MINUS, SYNTAX_TOKENS::OPEN_BRACKET, SYNTAX_TOKENS::NONTERMINAL, SYNTAX_TOKENS::CLOSE_BRACKET }));
const SyntaxRule SYNTAX_RULES::R9 = SyntaxRule(9, BuildRule({ SYNTAX_TOKENS::IDENTIFIER }));

std::map<std::string, SyntaxRule> REDUCE_RULES = {
    {SYNTAX_RULES::R0.rule.ruleString, SYNTAX_RULES::R0 },
    {SYNTAX_RULES::R1.rule.ruleString, SYNTAX_RULES::R1 },
    {SYNTAX_RULES::R2.rule.ruleString, SYNTAX_RULES::R2 },
    {SYNTAX_RULES::R4.rule.ruleString, SYNTAX_RULES::R4 },
    {SYNTAX_RULES::R5.rule.ruleString, SYNTAX_RULES::R5 },
    {SYNTAX_RULES::R7.rule.ruleString, SYNTAX_RULES::R7 },
    {SYNTAX_RULES::R8.rule.ruleString, SYNTAX_RULES::R8 },
    {SYNTAX_RULES::R9.rule.ruleString, SYNTAX_RULES::R9 }
};

std::map<int, BuildRule> BUILD_RULES = {
    { SYNTAX_RULES::R0.code,  SYNTAX_RULES::R0.rule },
    { SYNTAX_RULES::R1.code,  SYNTAX_RULES::R1.rule },
    { SYNTAX_RULES::R2.code,  SYNTAX_RULES::R2.rule },
    { SYNTAX_RULES::R4.code,  SYNTAX_RULES::R4.rule },
    { SYNTAX_RULES::R5.code,  SYNTAX_RULES::R5.rule },
    { SYNTAX_RULES::R7.code,  SYNTAX_RULES::R7.rule },
    { SYNTAX_RULES::R8.code,  SYNTAX_RULES::R8.rule },
    { SYNTAX_RULES::R9.code,  SYNTAX_RULES::R9.rule },
};

/* ----------------- RULES END ----------------- */

struct SyntaxValue {
    SyntaxValue(TermType type = TermTypes::UNDEFINED, std::string value = "") 
        : type(type)
        , value(value) 
    { };

    TermType type;
    std::string value;

    friend std::ostream& operator<<(std::ostream& s, const SyntaxValue& token)
    {
        s << "type: " << token.type.toString() << " value: " << token.value;
        return s;
    }
};

struct SyntaxNode {
    SyntaxNode() {};
    SyntaxNode(SyntaxRule rule, SyntaxValue value) : rule(rule), value(value) {};

    SyntaxRule rule;
    SyntaxValue value;

    friend std::ostream& operator<<(std::ostream& s, const SyntaxNode& token)
    {
        s << "[rule]: " << token.rule << "[value]: " << token.value << std::endl;
        return s;
    }
};

std::vector<TermType> SHOULD_ADD_VALUES = {
    TermTypes::NUMBER, TermTypes::IDENTIFIER
};

bool shouldAddValue(TermType type) {
    return std::find(SHOULD_ADD_VALUES.begin(), SHOULD_ADD_VALUES.end(), type) != SHOULD_ADD_VALUES.end();
}
