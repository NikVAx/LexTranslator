// SYNTAX.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"
#include "syntax.h"

#include "../LEXER/lexer.h"
#include "../Utils/utils.h"
#include "../Utils/cast_enum.h"
#include "stack_item.h"
#include "constants.h"
#include "command.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <functional>
#include <vector>
#include <map>

class SyntaxScanner {
private:
    int head = 0;
    std::vector<Token> items;
public:
    std::vector<SyntaxNode> rules;
    std::vector<StackItem> stack;

    std::vector<SyntaxValue> values;

    void init(Command command) {
        items = command.tokens;
    }

    int getTerminalIndex(int end) {
        for (int i = end; i >= 0; --i) {
            if (stack.at(i).isNotTerm()) {
                continue;
            }
            return i;
        }
    }

    int getIndexInDictionary(TermType tokenTypeCode) {
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
            Relations innerRelation = getRelation(elAt2, elAt1);

            if (innerRelation == Relations::BASE && index2 > 0) {
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

        std::string ruleString = popIfLaterOrNotTerminal(baseIndex);

        SyntaxRule rule = REDUCE_RULES[ruleString];

        //if (values.size() == 2) {
        //    SyntaxNode lastNode = SyntaxNode(rule, values[0]);
        //    rules.push_back(lastNode);
        //}

        SyntaxNode node = SyntaxNode(rule, values.size() != 0 ? values[values.size() - 1] : SyntaxValue());

        values.clear();

        rules.push_back(node);
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
        stack.push_back(START_LIMIT);

        int limit = 0;
        int k = 1;

        do {
            Token currentToken = items[head];

            int topStackTermIndex = getTerminalIndex(stack.size() - 1);

            int top = stack.at(topStackTermIndex).code;
            int input = getIndexInDictionary(currentToken.typeCode);

            // Шаг 2: получения отношения по таблице
            Relations relation = getRelation(top, input);

            if (shouldAddValue(currentToken.typeCode)) {
                SyntaxValue value = SyntaxValue(currentToken.typeCode, currentToken.value);
                values.push_back(value);
            }

        #pragma region  debug
            std::cout
                << (relation == Relations::NEXT ? "#СВЕРТКА" : "#СДВИГ  ")
               /* << " [ " << as_integer(relation) << " ] "
                << "["<< std::setw(2) << top << ";"
                << std::setw(2) << MAP_INPUT_STRING[top] << "]"
                << "[ " << std::setw(2) << input << ";"
                << std::setw(2) << MAP_INPUT_STRING[input] << "]"*/
                << "\n  СТЕК: " << stack_str(stack) << " " << cast_enum(relation) << "\n";
        #pragma endregion         

            if (relation == Relations::PREV || relation == Relations::BASE) {
                shift(input, currentToken); //сдвиг
                continue;
            }
            if (relation == Relations::NEXT) {
                reduce(input, currentToken); // свертка             
                continue;
            }
            if (relation == Relations::NONE) {
                end(input); // конец алгоритма (успешный или ошибочный)
                return;
            }
        } while (head < items.size());
    }

    void shift(int input, Token token) {
        stack.push_back(StackItem(input, "", token.value));
        head += 1;
    }

    void end(int input) {
        if (input == START_LIMIT.code && head != 0) {
            std::cout << "РАЗБОР ЗАВЕРШЕН\n";
        }
        else {
            std::cout << "ОШИБКА\n";
        }
    }
};
