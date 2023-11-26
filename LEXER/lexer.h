#pragma once

#include <vector>
#include "lexer_config.h"
#include "parse.h"

struct TransitionInfo {
protected:
    std::vector<int> args;
    int code;
    char input;

    int nextState;
    bool isBoundary;
    StatusCodes statusCode;

public:
    TransitionInfo(char input, int code, int nextState, bool isBoundary, StatusCodes statusCode);

    int getInputCode();

    int getNextState();

    bool isTokenBoundary();

    StatusCodes getStatusCode();

    bool isNotSuccess();

    bool isEmptyChar();
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
        StatusCodes statusCode = (StatusCodes)_smConfig.getStatusCode(currentState, inputType);

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

            ParseResult parse(std::string input);
    };
}