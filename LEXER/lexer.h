#pragma once

#include <vector>
#include "shared_types.h"
#include "lexer_config.h"

struct TransitionInfo {
protected:
    std::vector<int> args;
    int code;
    char input;
public:
    TransitionInfo(char input, int code, std::vector<int> args);

    int getInputChar();

    int getInputCode();

    int getNextState();

    bool isTokenBoundary();

    int getStatusCode();

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

        std::vector<int> args;

        for (int arg = 0; arg < _smConfig.getArgumentsCount(); ++arg) {
            args.push_back(_smConfig.mapMatrix(arg, currentState, inputType));
        }

        return TransitionInfo(inputChar, inputType, args);
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