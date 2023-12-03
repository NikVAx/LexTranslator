#pragma once

#include <stack>
#include <sstream>
#include <list>

#include "../Core/stack_item.h"
#include "../Core/syntax_node.h"
#include "../Core/syntax_rule.h"
#include "../Core/command.h"
#include "constants.h"

std::map<TermType, SyntaxChar> TOKEN_TO_SYNTAX_CHAR
{
    { TermTypes::PLUS, SyntaxChars::PLUS },
    { TermTypes::MINUS, SyntaxChars::MINUS },
    { TermTypes::MULTIPLY, SyntaxChars::MULTIPLY },
    { TermTypes::DIVIDE,  SyntaxChars::DIVIDE },
    { TermTypes::IDENTIFIER,  SyntaxChars::IDENTIFIER },
    { TermTypes::OPEN_BRACKET,  SyntaxChars::OPEN_BRACKET },
    { TermTypes::CLOSE_BRACKET,  SyntaxChars::CLOSE_BRACKET },
    { TermTypes::SEMICOLON,  SyntaxChars::SEMICOLON },
    { TermTypes::ASSIGNMENT,  SyntaxChars::ASSIGNMENT },
    { TermTypes::LIMIT,  SyntaxChars::LIMIT },
};

class SyntaxScanner {
private:
    SyntaxConfig& syntaxConfig;

    int head = 0;
    std::vector<Token> items;


public:
    SyntaxScanner(SyntaxConfig& syntaxConfig)
        : syntaxConfig(syntaxConfig)
    { }

    std::list<SyntaxNode> syntaxNodes;
    std::vector<StackItem> stack;
    std::vector<SyntaxValue> values;

    SyntaxScanner& build(Command command) {
        items = command.tokens;
        return *this;
    }

    int getTerminalIndex(int end) {
        for (int i = end; i >= 0; --i) {
            if (stack.at(i).isNotTerm()) {
                continue;
            }
            return i;
        }
    }

    void reduce(int input, Token token) {
        int index1 = getTerminalIndex(stack.size() - 1);
        int index2 = getTerminalIndex(index1 - 1);

        int elAt1 = stack.at(index1).code;
        int elAt2 = stack.at(index2).code;

        bool notFound = true;

        do {
            Relations innerRelation = syntaxConfig.getRelation(elAt2, elAt1);

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

        std::cout << "  #RULE-STRING: " << ruleString << "\n";

        SyntaxRule syntaxRule = syntaxConfig.getRuleByString(ruleString);
        
        SyntaxNode node = SyntaxNode(syntaxRule, values.size() != 0 ? values[values.size() - 1] : SyntaxValue());

        values.clear();

        syntaxNodes.push_back(node);
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

    std::list<SyntaxNode> proccess() {
        std::cout << "COMMAND.BEGIN\n";
        stack.push_back(START_LIMIT);

        int limit = 0;
        int k = 1;

        do {
            Token currentToken = items[head];

            std::cout << " #IN >> " << currentToken.value << "\n";

            int topStackTermIndex = getTerminalIndex(stack.size() - 1);

            int top = stack.at(topStackTermIndex).code;
            int input = syntaxConfig.getIndex(currentToken.termType);

            // Шаг 2: получения отношения по таблице
            Relations relation = syntaxConfig.getRelation(top, input);

            if (shouldAddValue(currentToken.termType)) {
                SyntaxValue value = SyntaxValue(currentToken.termType, currentToken.value);
                values.push_back(value);
            }

#pragma region  debug
            std::cout
                << (relation == Relations::NEXT ? "#REDUCE" : "#SHIFT ")
                << "\n  STACK: " << stack_str(stack) << " R[" << (char) relation << "]\n";
#pragma endregion         

            if (relation == Relations::PREV || relation == Relations::BASE) {
                shift(currentToken);
#pragma region  debug
                std::cout
                    << "  #AFTER SHIFT: "
                    << "\n    STACK: " << stack_str(stack) << " R[" << (char)relation << "]\n";
#pragma endregion  
                continue;
            }
            if (relation == Relations::NEXT) {
                reduce(input, currentToken);      
#pragma region  debug
                std::cout
                    << "  #AFTER REDUCE: "
                    << "\n    STACK: " << stack_str(stack) << " R[" << (char)relation << "]\n";
#pragma endregion  
                continue;
            }
            if (relation == Relations::NONE) {
                end(input, currentToken);
                break;
            }



        } while (head < items.size());

        return syntaxNodes;
    }

    void shift(Token token) {
        stack.push_back(
            StackItem(
                syntaxConfig.getIndex(token.termType), 
                token.value, 
                TOKEN_TO_SYNTAX_CHAR[token.termType]));
        head += 1;
    }

    void end(int input, Token token) {
        if (input == START_LIMIT.code && head != 0) {
            std::cout << "COMMAND.END: SUCCESS\n";
        }
        else {
            std::cout << "COMMAND.END: ERROR\n";
        }
    }
};