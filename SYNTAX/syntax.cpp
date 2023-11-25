// SYNTAX.cpp : Определяет функции для статической библиотеки.
//

#include "../LEXER/lexer.cpp"
#include "../LEXER/shared_types.h"
#include "../Utils/utils.h"
#include "utils.h"

#include "pch.h"
#include "framework.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <functional>
#include <vector>
#include <map>

const int SHIFT_PACK_SIZE = 11;

std::map<int, std::string> MAP_INPUT_STRING = {
    { 0, "+" }, // +
    { 1, "-"}, // -
    { 2, "*"}, // *
    { 3, "/"}, // /
    { 4, "I"}, // идентификатор
    { 5, "R"}, // число
    { 6, "("}, // (
    { 7, ")"}, // )
    { 8, ";"}, // ;
    { 9, ":="}, // :=
    { 10, "#"}, // #
    { 11, "S"}, // S
};
 




struct ReduceRule {
    ReduceRule() {
        number = -1;
        value = "";
    }

    ReduceRule(int num, std::string arg = "") {
        number = num;
        value = value;
    }

    int number;
    std::string value;
};

std::map<std::string, ReduceRule> REDUCE_RULES = {
    {"I:=S;", ReduceRule(1) },
    {"S+S",   ReduceRule(2) },
    {"S*S",   ReduceRule(4) },
    {"S/S",   ReduceRule(5) },
    {"(S)",   ReduceRule(7) },
    {"-(S)",  ReduceRule(8) },
    {"I",     ReduceRule(9) },
    {"R",     ReduceRule(10) },
};

struct BuildRule {
    std::vector<std::string> items;
    std::string ruleString;

    BuildRule() { }

    BuildRule(std::vector<std::string> items) {
        const char* const delim = "";

        std::ostringstream imploded;
        std::copy(items.begin(), items.end(),
            std::ostream_iterator<std::string>(imploded, delim));

        this->ruleString = imploded.str();
    }
};

std::map<int, BuildRule> BUILD_RULES = {
    { 1,  BuildRule({ "I", ":=", "S"}) },
    { 2,  BuildRule({ "S", "+", "S" }) },
    { 4,  BuildRule({ "S", "*", "S" }) },
    { 5,  BuildRule({ "S", "/", "S" }) },
    { 7,  BuildRule({ "S" }) },
    { 8,  BuildRule({  "-", "S"})},
    { 9,  BuildRule({  "I" }) },
    { 10, BuildRule({  "R" }) },
};

const int NOT_TERMINAL = 11;
const int NOT_FOUND = -1;

const int ROMAN_ID = 4;
const int IDENT_ID = 5;

struct StackItem {
    StackItem(int code, std::string tag = "", std::string value = "") {
        this->code = code;
        this->value = value;
        this->tag = tag == "" ? MAP_INPUT_STRING[code] : tag;
    }

    int code;

    std::string value;
    std::string tag;

    bool isNotTerm() {
        return code == NOT_TERMINAL;
    }
};

StackItem NOT_TERM = StackItem(NOT_TERMINAL, "S");

class SyntaxScanner {
private:
    int head = 0;
    std::vector<Token> tokens;
public:
    std::vector<int> rules;
    std::vector<std::string> terms;
    Tree<int> rulesTree;


    std::vector<StackItem> stack;

    void init(std::vector<Token> input) {
        for (auto& token : input) {
            tokens.push_back(token);
        }
        int head = 0;
    }

    int getTerminalIndex(int end) {
        for (int i = end; i >= 0; --i) {
            if (stack.at(i).isNotTerm()) {
                continue;
            }
            return i;
        }
    }

    int getIndexInDictionary(int tokenTypeCode) {
        return ROW_COLUMN_MAP[tokenTypeCode];
    }

    Relations getRelation(int leftTermIndex, int rightTermIndex) {
        if (leftTermIndex >= MATH_MATRIX.SIZE() || rightTermIndex >= MATH_MATRIX.SIZE())
            throw std::exception("Relation matrix out of range");

        return MATH_MATRIX.MATRIX[leftTermIndex][rightTermIndex];
    }

    void reduce(int input, Token token) {
        int index1 = getTerminalIndex(stack.size() - 1);
        int index2 = getTerminalIndex(index1 - 1);
        int elAt1 = stack.at(index1).code;
        int elAt2 = stack.at(index2).code;

        bool notFound = true;

        do {
            //std::cout << " > INDEX1 = " << MAP_INPUT_STRING[elAt1] << " (" << index1 << ")" << "\n";
            //std::cout << " > INDEX2 = " << MAP_INPUT_STRING[elAt2] << " (" << index2 << ")" << "\n";
            Relations innerRelation = getRelation(elAt2, elAt1);
            //std::cout << "RELATION " << innerRelation << "\n";

            if (innerRelation == Relations::BASE) {
                notFound = false;
                index1 = index2;
                index2 = getTerminalIndex(index1 - 1);
                elAt1 = stack.at(index1).code;
                elAt2 = stack.at(index2).code;
            }
            else {
                break;
            }
        } while (true);

        int baseIndex = notFound
            ? getTerminalIndex(stack.size() - 1)
            : index1;


        if (stack.back().code == ROMAN_ID || stack.back().code == IDENT_ID)
            terms.push_back(stack.back().value);

        std::string baseString = popIfLaterOrNotTerminal(baseIndex);

        rules.push_back(REDUCE_RULES[baseString].number);

        stack.push_back(NOT_TERM);
    }

    // Удалить из стека все символы до переданного
    std::string popIfLaterOrNotTerminal(int baseIndex) {
        std::string baseString = "";
        std::stack<std::string> revert;

        for (int i = stack.size() - 1; (i >= baseIndex || stack.back().isNotTerm()); --i) {
            revert.push(MAP_INPUT_STRING[stack.back().code]);
            stack.pop_back();
        }

        while (!revert.empty()) {
            baseString.append(revert.top());
            revert.pop();
        }
        return baseString;
    }

    std::string stack_str(std::vector<StackItem> st) {
        std::stringstream ss;
        for (auto& el : st) {
            ss << MAP_INPUT_STRING[el.code];
        }
        return ss.str();
    }

    // разбор одной команды
    void proccess() {
        std::cout << "НАЧАЛО\n";
        stack.push_back(StackItem(10, "Н"));

        int limit = 0;
        int k = 1;

        do {
            Token currentToken = tokens[head];

            int topStackTermIndex = getTerminalIndex(stack.size() - 1);

            int top = stack.at(topStackTermIndex).code;
            int input = getIndexInDictionary((int)currentToken.typeCode);

            // Шаг 2: получения отношения по таблице
            Relations relation = getRelation(top, input);

#pragma region  debug
            std::cout
                << (relation == Relations::NEXT ? "#СВЕРТКА" : "#СДВИГ  ")
                /* << " [ " << relation << " ] "
                << "["<< std::setw(2) << top << ";"
                << std::setw(2) << MAP_INPUT_STRING[top] << "]"
                << "[ " << std::setw(2) << input << ";"
                << std::setw(2) << MAP_INPUT_STRING[input] << "]"*/
                << "\n  СТЕК: " << stack_str(stack) << "\n";
#pragma endregion            

            if (relation == Relations::PREV || relation == Relations::BASE) {
                shift(input, currentToken); //сдвиг
                continue;
            }
            else if (relation == Relations::NEXT) {
                reduce(input, currentToken); // свертка
                continue;
            }
            else if (relation == Relations::NONE) {
                end(input); // конец алгоритма (успешный или ошибочный)
                return;
            }
        } while (head < tokens.size());
    }

    void shift(int input, Token token) {
        stack.push_back(StackItem(input, "", token.value));
        head += 1;
    }

    void end(int input) {
        if (input == 10 && head != 0) {
            std::cout << "РАЗБОР ЗАВЕРШЕН\n";
        }
        else {
            std::cout << "ОШИБКА\n";
        }
    }
};
