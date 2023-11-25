// SYNTAX.cpp : Определяет функции для статической библиотеки.
//

#include "../LEXER/lexer.cpp"

#include "pch.h"
#include "framework.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <functional>
#include <map>

using namespace Shared;

const int SHIFT_PACK_SIZE = 11;

std::map<int, int> ROW_COLUMN_MAP = {
    { 6,  0 }, // +
    { 10, 1 }, // -
    { 11, 2 }, // *
    { 12, 3 }, // /
    { 1,  4 }, // идентификатор
    { 2,  5 }, // число
    { 4,  6 }, // (
    { 5,  7 }, // )
    { 7,  8 }, // ;
    { 3,  9 }, // :=
    { 20, 10}, // :=
};

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

const int RELATION_MTX_SIZE = 11;

char RELATION_MATRIX[RELATION_MTX_SIZE][RELATION_MTX_SIZE] = {
    { '>', '<', '<', '<', '<', '<', '<', '>', '>', '-', '-'} ,
    { '-', '-', '-', '-', '-', '-', '=', '-', '-', '-', '-'} ,
    { '>', '<', '>', '>', '<', '<', '<', '>', '>', '-', '-'} ,
    { '>', '<', '>', '>', '<', '<', '<', '>', '>', '-', '-'} ,
    { '>', '-', '>', '>', '-', '-', '-', '>', '>', '=', '-'} ,
    { '>', '-', '>', '>', '-', '-', '-', '>', '-', '-', '-'} ,
    { '<', '<', '<', '<', '<', '<', '<', '=', '-', '-', '-'} ,
    { '>', '-', '>', '>', '-', '-', '-', '>', '>', '-', '-'} ,
    { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '>'} ,
    { '<', '<', '<', '<', '<', '<', '<', '-', '=', '-', '-'} ,
    { '-', '-', '-', '-', '<', '-', '-', '-', '<', '-', '-'} ,
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

std::vector<std::string> BUILD_RULES = {
    "",
    "I:=S;",
    "S+S",
    "",
    "S*S",
    "S/S",
    "",
    "(S)",
    "-(S)",
    "I",
    "R"
};

const int NOT_TERMINAL = 11;
const int NOT_FOUND = -1;

const int ROMAN_ID = 4;
const int IDENT_ID = 5;

struct store_item {
    store_item(int code, std::string tag = "", std::string value = "") {
        this->code = code;
        this->value = value;
        this->tag = tag == "" ? MAP_INPUT_STRING[code] : tag;
    }

    int code;
    std::string typeString;
    std::string value;
    std::string tag;

    bool isNotTerm() {
        return code == NOT_TERMINAL;
    }
};

store_item NOT_TERM = store_item(NOT_TERMINAL, "S");

class SyntaxScanner {
private:
    int head = 0;
    std::vector<Token> tokens;
public:
    std::vector<int> rules;
    std::vector<std::string> terms;


    std::vector<store_item>  store;
    std::string baseString;

    void init(std::vector<Token> input) {
        for (auto& token : input) {
            tokens.push_back(token);
        }
        int head = 0;
    }

    int getTerminalIndex(int end) {
        for (int i = end; i >= 0; --i) {
            if (store.at(i).isNotTerm()) {
                continue;
            }
            return i;
        }
    }

    int getIndexInDictionary(int tokenTypeCode) {
        return ROW_COLUMN_MAP[tokenTypeCode];
    }

    char getRelation(int leftTermIndex, int rightTermIndex) {
        if (leftTermIndex >= RELATION_MTX_SIZE || rightTermIndex >= RELATION_MTX_SIZE)
            throw std::exception("Relation matrix out of range");

        return RELATION_MATRIX[leftTermIndex][rightTermIndex];
    }


    void reduce(int input, Token token) {
        int index1 = getTerminalIndex(store.size() - 1);
        int index2 = getTerminalIndex(index1 - 1);
        int elAt1 = store.at(index1).code;
        int elAt2 = store.at(index2).code;

        bool notFound = true;

        do {
            //std::cout << " > INDEX1 = " << MAP_INPUT_STRING[elAt1] << " (" << index1 << ")" << "\n";
            //std::cout << " > INDEX2 = " << MAP_INPUT_STRING[elAt2] << " (" << index2 << ")" << "\n";
            char innerRelation = getRelation(elAt2, elAt1);
            //std::cout << "RELATION " << innerRelation << "\n";

            if (innerRelation == '=') {
                notFound = false;
                index1 = index2;
                index2 = getTerminalIndex(index1 - 1);
                elAt1 = store.at(index1).code;
                elAt2 = store.at(index2).code;
            }
            else {
                break;
            }
        } while (true);

        int baseIndex = notFound
            ? getTerminalIndex(store.size() - 1)
            : index1;


        if (store.back().code == ROMAN_ID || store.back().code == IDENT_ID)
            terms.push_back(store.back().value);

        popIfLaterOrNotTerminal(baseIndex);

        rules.push_back(REDUCE_RULES[baseString].number);

        store.push_back(NOT_TERM);
    }

    // Удалить из стека все символы до переданного
    void popIfLaterOrNotTerminal(int baseIndex) {
        baseString = "";
        std::stack<std::string> revert;

        for (int i = store.size() - 1; (i >= baseIndex || store.back().isNotTerm()); --i) {
            revert.push(MAP_INPUT_STRING[store.back().code]);
            store.pop_back();
        }

        while (!revert.empty()) {
            baseString.append(revert.top());
            revert.pop();
        }
    }

    std::string stack_str(std::vector<store_item> st) {
        std::stringstream ss;
        for (auto& el : st) {
            ss << MAP_INPUT_STRING[el.code];
        }
        return ss.str();
    }

    // разбор одной команды
    void proccess() {
        std::cout << "НАЧАЛО\n";
        //store.push_back(10); // Шаг 2: помещения в стек символа #

        store.push_back(store_item(10, "Н"));

        int limit = 0;
        int k = 1;

        do {
            Token currentToken = tokens[head];

            int topStackTermIndex = getTerminalIndex(store.size() - 1);

            int top = store.at(topStackTermIndex).code;
            int input = getIndexInDictionary(currentToken.typeCode);

            // Шаг 2: получения отношения по таблице
            char relation = getRelation(top, input);

#pragma region  debug
            std::cout
                << (relation == '>' ? "#СВЕРТКА" : "#СДВИГ  ")
                /* << " [ " << relation << " ] "
                << "["<< std::setw(2) << top << ";"
                << std::setw(2) << MAP_INPUT_STRING[top] << "]"
                << "[ " << std::setw(2) << input << ";"
                << std::setw(2) << MAP_INPUT_STRING[input] << "]"*/
                << "\n  СТЕК: " << stack_str(store) << "\n";
#pragma endregion            

            if (relation == '<' || relation == '=') {
                shift(input, currentToken); //сдвиг
                continue;
            }
            else if (relation == '>') {
                reduce(input, currentToken); // свертка
                continue;
            }
            else if (relation == '-') {
                end(input); // конец алгоритма (успешный или ошибочный)
                return;
            }
        } while (head < tokens.size());
    }

    void shift(int input, Token token) {
        store.push_back(store_item(input, "", token.value));
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
