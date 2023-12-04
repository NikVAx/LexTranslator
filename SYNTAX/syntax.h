#pragma once

#include <stack>
#include <sstream>
#include <list>

#include "../Core/stack_item.h"
#include "../Core/syntax_node.h"
#include "../Core/syntax_rule.h"
#include "../Core/command.h"
#include "../Core/status_codes.h"

std::map<TermType, SyntaxChar> TOKEN_TO_SYNTAX_CHAR
{
    { TermTypes::PLUS, SyntaxChars::PLUS },
    { TermTypes::MINUS, SyntaxChars::MINUS },
    { TermTypes::MULTIPLY, SyntaxChars::MULTIPLY },
    { TermTypes::DIVIDE,  SyntaxChars::DIVIDE },
    { TermTypes::IDENTIFIER,  SyntaxChars::IDENTIFIER },
    { TermTypes::NUMBER,  SyntaxChars::IDENTIFIER },
    { TermTypes::OPEN_BRACKET,  SyntaxChars::OPEN_BRACKET },
    { TermTypes::CLOSE_BRACKET,  SyntaxChars::CLOSE_BRACKET },
    { TermTypes::SEMICOLON,  SyntaxChars::SEMICOLON },
    { TermTypes::ASSIGNMENT,  SyntaxChars::ASSIGNMENT },
    { TermTypes::LIMIT,  SyntaxChars::LIMIT },
};

std::map<int, std::string> MAP_INPUT_STRING = {
    { SyntaxChars::PLUS.code, SyntaxChars::PLUS.tokenString }, // +
    { SyntaxChars::MINUS.code, SyntaxChars::MINUS.tokenString }, // -
    { SyntaxChars::MULTIPLY.code, SyntaxChars::MULTIPLY.tokenString }, // *
    { SyntaxChars::DIVIDE.code,  SyntaxChars::DIVIDE.tokenString }, // /
    { SyntaxChars::IDENTIFIER.code,  SyntaxChars::IDENTIFIER.tokenString }, // идентификатор
    { SyntaxChars::OPEN_BRACKET.code,  SyntaxChars::OPEN_BRACKET.tokenString }, // (
    { SyntaxChars::CLOSE_BRACKET.code,  SyntaxChars::CLOSE_BRACKET.tokenString }, // )
    { SyntaxChars::SEMICOLON.code,  SyntaxChars::SEMICOLON.tokenString }, // ;
    { SyntaxChars::ASSIGNMENT.code,  SyntaxChars::ASSIGNMENT.tokenString }, // :=
    { SyntaxChars::LIMIT.code,  SyntaxChars::LIMIT.tokenString }, // #
    { SyntaxChars::NONTERMINAL.code,  SyntaxChars::NONTERMINAL.tokenString}, // S
};

class SyntaxResult {
public:
    std::list<SyntaxNode> nodes;
    
    bool error = false;
    std::string message;

    bool isSuccess() {
        return !error;
    }

    void err(std::string message) {
        this->message = message;
        error = true;
    }


};

class SyntaxScanner {
private:
    SyntaxConfig& syntaxConfig;
    int head = 0;
    std::vector<Token> items;
    std::vector<StackItem> stack;
    std::list<SyntaxNode> nodes;
    bool error;

public:
    SyntaxScanner(SyntaxConfig& syntaxConfig)
        : syntaxConfig(syntaxConfig)
    { }

    int getTerminalIndex(int end) {
        for (int i = end; i >= 0; --i) {
            if (stack.at(i).isNotTerm()) {
                continue;
            }
            return i;
        }
        exit(-2);
    }

    void setup(Command command) {
        head = 0;
        stack.clear();
        nodes.clear();
        items = command.tokens;
    }

    void reduce(int input, Token token) {
        try {
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

            std::string ruleString = extractFrom(baseIndex);

            SyntaxRule syntaxRule = syntaxConfig.getRuleByString(ruleString);

            SyntaxNode node = SyntaxNode(syntaxRule);

            nodes.push_back(node);
            stack.push_back(NONTERM);

        }
        catch (std::exception ex) {
            error = true;
        }
    }

    std::string extractFrom(int baseIndex) {
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

    std::string stack_str(std::vector<StackItem> stackItem) {
        std::stringstream ss;
        for (auto& el : stackItem) {
            ss << MAP_INPUT_STRING[el.code];
        }
        return ss.str();
    }

    SyntaxResult proccess(Command command) {
        
        setup(command);
        
        stack.push_back(START_LIMIT);
       
        SyntaxResult result;

        bool end = false;

        int tokenIndex = 0;

        do {
            tokenIndex += 1;
            Token currentToken = items[head];

            if (tokenIndex == 1 && currentToken.termType != TermTypes::IDENTIFIER) {
                result.err(StatusCodes::SEM_ASSIGNTOCONST.toString());
                break;
            }

            if (tokenIndex == 2 && currentToken.termType != TermTypes::ASSIGNMENT) {
                result.err(StatusCodes::SYN_ASSIGNMENT_EXPECTED.toString());
                break;
            }

            //std::cout << " #IN >> " << currentToken.value << "\n";

            int topStackTermIndex = getTerminalIndex(stack.size() - 1);

            int top = stack.at(topStackTermIndex).code;
            int input = syntaxConfig.getIndex(currentToken.termType);


            Relations relation = syntaxConfig.getRelation(top, input);
            
            if (relation == Relations::PREV || relation == Relations::BASE) {
                shift(input, currentToken);
#pragma region  debug
                std::cout
                    << "  #AFTER SHIFT: "
                    << "\n    STACK: " << stack_str(stack) << " R[" << (char)relation << "]\n";
#pragma endregion  
                continue;
            }
            if (relation == Relations::NEXT) {
                reduce(input, currentToken);  

                if (error) {
                    result.err(StatusCodes::SYN_EXPR_EXPECT.toString());
                    break;
                }

#pragma region  debug
                std::cout
                    << "  #AFTER REDUCE: "
                    << "\n    STACK: " << stack_str(stack) << " R[" << (char)relation << "]\n";
#pragma endregion  
                continue;
            }
            if (relation == Relations::NONE) {
                if (input == START_LIMIT.code && head != 0) {
                    result.error = false;
                    result.nodes = nodes;
                }
                else {
                    result.err(syntaxConfig.getStatusCode(top, input));
                }
                end = true;
                break;
            }
        } while (head < items.size());

        if (!end && !error) {
            result.err(StatusCodes::SYN_END_OF_STATEMENT.toString());
        }

        return result;
    }

    void shift(int input, Token token) {
        stack.push_back(
            StackItem(
                syntaxConfig.getIndex(token.termType),
                token.value, 
                syntaxConfig.getSyntaxChar(token.termType)));
        head += 1;
    }
};

