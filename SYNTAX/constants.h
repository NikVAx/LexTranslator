#pragma once

#include "../Core/relations.h"

#include "../Utils/cast_enum.h"
#include "../Utils/iterator.h"
#include "../Core/term_types.h"
#include "../Core/relations.h"

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>

#include "syntax_char_meta.h"



class SYNTAX_TOKENS {
public:
    static const SyntaxCharMeta LIMIT;
    static const SyntaxCharMeta PLUS; 
    static const SyntaxCharMeta MINUS;
    static const SyntaxCharMeta MULTIPLY;
    static const SyntaxCharMeta DIVIDE;
    static const SyntaxCharMeta IDENTIFIER;
    static const SyntaxCharMeta OPEN_BRACKET;
    static const SyntaxCharMeta CLOSE_BRACKET;
    static const SyntaxCharMeta SEMICOLON;
    static const SyntaxCharMeta ASSIGNMENT;
    static const SyntaxCharMeta NONTERMINAL;
};

const SyntaxCharMeta SYNTAX_TOKENS::LIMIT(0, "#", TokenType::TERMINAL);
const SyntaxCharMeta SYNTAX_TOKENS::PLUS(1, "+", TokenType::TERMINAL);
const SyntaxCharMeta SYNTAX_TOKENS::MINUS(2, "-", TokenType::TERMINAL);
const SyntaxCharMeta SYNTAX_TOKENS::MULTIPLY(3, "*", TokenType::TERMINAL);
const SyntaxCharMeta SYNTAX_TOKENS::DIVIDE(4, "/", TokenType::TERMINAL);
const SyntaxCharMeta SYNTAX_TOKENS::IDENTIFIER(5, "I", TokenType::NONTERMINAL);
const SyntaxCharMeta SYNTAX_TOKENS::OPEN_BRACKET(6, "(", TokenType::TERMINAL);
const SyntaxCharMeta SYNTAX_TOKENS::CLOSE_BRACKET(7, ")", TokenType::TERMINAL);
const SyntaxCharMeta SYNTAX_TOKENS::SEMICOLON(8, ";", TokenType::TERMINAL);
const SyntaxCharMeta SYNTAX_TOKENS::ASSIGNMENT(9, ":=", TokenType::TERMINAL);
const SyntaxCharMeta SYNTAX_TOKENS::NONTERMINAL(10, "S", TokenType::NONTERMINAL);

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
    { TermTypes::LIMIT, SYNTAX_TOKENS::LIMIT.code}, // #
};

std::map<int, std::string> MAP_INPUT_STRING = {
    { SYNTAX_TOKENS::PLUS.code, SYNTAX_TOKENS::PLUS.tokenString }, // +
    { SYNTAX_TOKENS::MINUS.code, SYNTAX_TOKENS::MINUS.tokenString }, // -
    { SYNTAX_TOKENS::MULTIPLY.code, SYNTAX_TOKENS::MULTIPLY.tokenString }, // *
    { SYNTAX_TOKENS::DIVIDE.code,  SYNTAX_TOKENS::DIVIDE.tokenString }, // /
    { SYNTAX_TOKENS::IDENTIFIER.code,  SYNTAX_TOKENS::IDENTIFIER.tokenString }, // идентификатор
    { SYNTAX_TOKENS::OPEN_BRACKET.code,  SYNTAX_TOKENS::OPEN_BRACKET.tokenString }, // (
    { SYNTAX_TOKENS::CLOSE_BRACKET.code,  SYNTAX_TOKENS::CLOSE_BRACKET.tokenString }, // )
    { SYNTAX_TOKENS::SEMICOLON.code,  SYNTAX_TOKENS::SEMICOLON.tokenString }, // ;
    { SYNTAX_TOKENS::ASSIGNMENT.code,  SYNTAX_TOKENS::ASSIGNMENT.tokenString }, // :=
    { SYNTAX_TOKENS::LIMIT.code,  SYNTAX_TOKENS::LIMIT.tokenString }, // #
    { SYNTAX_TOKENS::NONTERMINAL.code,  SYNTAX_TOKENS::NONTERMINAL.tokenString}, // S
};

template <class T>
std::string join(std::vector<T> items, std::string delim = "") {
    std::ostringstream imploded;
    std::copy(items.begin(), items.end(),
        std::ostream_iterator<std::string>(imploded, delim.c_str()));
    return  imploded.str();
}

class BuildRule {
private:
    std::vector<SyntaxCharMeta> EXCLUDE_SYMBOLS = { SYNTAX_TOKENS::OPEN_BRACKET, SYNTAX_TOKENS::CLOSE_BRACKET, SYNTAX_TOKENS::SEMICOLON };

    std::vector<std::string> getTokenSymbols(std::vector<SyntaxCharMeta> items) {
        std::vector<std::string> symbols;
        for (auto& token : items) {
            symbols.push_back(token.tokenString);
        }
        return symbols;
    }

    std::vector<SyntaxCharMeta> getSimpleRule(std::vector<SyntaxCharMeta> items) {
        std::vector<SyntaxCharMeta> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](SyntaxCharMeta item) {
            return std::find(EXCLUDE_SYMBOLS.begin(), EXCLUDE_SYMBOLS.end(), item) != EXCLUDE_SYMBOLS.end();
        });
        return filteredItems;
    }

    std::vector<SyntaxCharMeta> _getTerminalItems(std::vector<SyntaxCharMeta> items) {
        std::vector<SyntaxCharMeta> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](SyntaxCharMeta item) {
            return item.type == TokenType::TERMINAL;
        });
        return filteredItems;
    }

    std::vector<SyntaxCharMeta> _getNonterminalItems(std::vector<SyntaxCharMeta> items) {
        std::vector<SyntaxCharMeta> filteredItems;
        std::copy_if(items.begin(), items.end(), std::back_inserter(filteredItems), [&](SyntaxCharMeta item) {
            return item.type == TokenType::NONTERMINAL;
        });
        return filteredItems;
    }

public:
    std::vector<SyntaxCharMeta> items;
    std::string ruleString;

    BuildRule() { }

    BuildRule(std::vector<SyntaxCharMeta> items) 
        : items(items)
        , ruleString(join(getTokenSymbols(items))) 
    {};

    std::string getRuleString(){
        return join(getTokenSymbols(getSimpleRule(items)));
    }

    std::string getTerminalsString() {
        return join(getTokenSymbols(_getTerminalItems(items)));
    }

    std::vector<SyntaxCharMeta> getNonTerminalItems() {
        return _getNonterminalItems(items);
    }

    std::vector<SyntaxCharMeta> getTerminalItems() {
        return _getTerminalItems(items);
    };

    friend std::ostream& operator<<(std::ostream& s, const BuildRule rule) {
        s << rule.ruleString << std::endl;
        return s;
    }
};

struct SyntaxRule {
    SyntaxRule() 
        : SyntaxRule(-1, BuildRule())
    { };

    SyntaxRule(int code, BuildRule rule) 
        : code(code)
        , rule(rule) 
    { }

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
