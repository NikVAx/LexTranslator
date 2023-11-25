#pragma once

#include <vector>
#include "shared_types.h"
#include "lexer_config.h"

struct TransArgs {
protected:
    std::vector<int> args;
    int code;
    char input;
public:
    TransArgs(char input, int code, std::vector<int> args);

    int getInputChar();

    int getInputCode();

    int getNextState();
};

struct T_TransArg : TransArgs {
    T_TransArg(char input, int code, std::vector<int> args);

    bool isSplit();

    int getStatusCode();

    bool isNotSuccess();

    bool isEmptyChar();
};

template <class TArgs>
class StateMachine {
protected:
    StateMachineConfiguration _smConfig;
public:
    StateMachine(StateMachineConfiguration smConfig)
        : _smConfig(smConfig)
        , currentState(smConfig.getInitialState())
    { }

    int currentState = 1;

    TArgs getTransit(char inputChar) {
        int inputType = _smConfig.mapInputAlpha(inputChar);

        std::vector<int> args;

        for (int arg = 0; arg < _smConfig.getArgumentsCount(); ++arg) {
            args.push_back(_smConfig.mapMatrix(arg, currentState, inputType));
        }

        return TArgs(inputChar, inputType, args);
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
        StateMachine<T_TransArg>  _sm;
    public:
        Lexer();

        Shared::ParseResult parse(std::string input);
    };
}