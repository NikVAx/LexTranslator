#pragma once


#include "lexer_config.h"
#include "StatusCodes.h"
#include "ParseResult.h"
#include "Token.h"

#include <string>
#include <sstream>
#include <vector>


struct TransitionInfo {
protected:
    std::vector<int> args;
    int code;
    char input;

    int nextState;
    bool isBoundary;
    StatusCodes statusCode;

public:
    TransitionInfo(char input, int code, int nextState, bool isBoundary, StatusCodes statusCode)
        : input(input)
        , code(code)
        , nextState(nextState)
        , isBoundary(isBoundary)
        , statusCode(statusCode)
    { }

    int getInputCode() {
        return code;
    }

    int getNextState() {
        return nextState;
    }

    bool isTokenBoundary() {
        return isBoundary;
    }

    StatusCodes getStatusCode() {
        return statusCode;
    }

    bool isNotSuccess() {
        StatusCodes code = getStatusCode();

        return code != StatusCodes::SUCCESS;
    }

    bool isEmptyChar() {
        return input == '\n' || input == '\t' || input == ' ' || input == '\r';
    }
};

class StateMachine {
protected:
    StateMachineConfiguration _smConfig;
public:
    StateMachine(StateMachineConfiguration smConfig)
        : _smConfig(smConfig)
        , currentState(smConfig.getInitialState())
    { }

    int currentState = 1;

    TransitionInfo getTransition(char inputChar) {
        int inputType = _smConfig.mapInputAlpha(inputChar);
        int nextState = _smConfig.getNextState(currentState, inputType);
        bool isBoundary = _smConfig.getBoundary(currentState, inputType) == IS_BOUNDARY_CODE;
        StatusCodes statusCode = _smConfig.getStatusCode(currentState, inputType);

        return TransitionInfo(inputChar, inputType, nextState, isBoundary, statusCode);
    }

    int getInitialState() {
        return _smConfig.getInitialState();
    }

    void reset() {
        currentState = _smConfig.getInitialState();
    }
};

namespace LEX {
    class Lexer {
    private:
        LexerConfiguration _lexConfig;
        StateMachine _sm;
    public:
        Lexer() : _lexConfig(LexerConfiguration()) , _sm(LexerConfiguration().getSmConfig()) { }

        ParseResult parse(std::string input) {
            ParseResult result;

            _sm.reset();

            std::string text = input + "\n";
            std::string tokenString = "";

            for (int head = 0; head < text.length(); head++) {
                char ch = text[head];

                TransitionInfo info = _sm.getTransition(ch);

                if (info.isNotSuccess()) {
                    result.addError(tokenString, info.getStatusCode());
                    continue;
                }

                if (info.isTokenBoundary() && !tokenString.empty()) {
                    TermTypes tokenType = _lexConfig.mapTokenType(_sm.currentState);

                    if (tokenType != TermTypes::COMMENT) {
                        result.add(tokenString, tokenType);
                    } // else ingore comment

                    tokenString.clear();
                }

                if (!info.isEmptyChar()) {
                    tokenString.append(1, ch);
                }

                _sm.currentState = info.getNextState();
            }

            return result;
        }
    };
}