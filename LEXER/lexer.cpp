#include "pch.h"
#include "framework.h"
#include "lexer_config.h"
#include "shared_types.h"

#include <vector>
#include <iostream>
#include <sstream>

struct TransArgs {
protected:
    std::vector<int> args;
    int code;
    char input;
public:
    TransArgs(char input, int code, std::vector<int> args)
        : input(input)
        , code(code)
        , args(args)
    { }

    int getInputChar() {
        return input;
    }

    int getInputCode() {
        return code;
    }

    int getNextState() {
        return args[0];
    }
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

struct T_TransArg : TransArgs {
    T_TransArg(char input, int code, std::vector<int> args)
        : TransArgs(input, code, args)
    { }

    bool isSplit() {
        return args[1] == 1; // 1 - split code
    }

    int getStatusCode() {
        return args[2];
    }

    bool isNotSuccess() {
        return getStatusCode() != 0; // 0 - success code
    }

    bool isEmptyChar() {
        return input == '\n' || input == '\t' || input == ' ' || input == '\r';
    }
};

namespace LexAnalizer {
    class Lexer {
    private:
        LexerConfiguration _lexConfig;
        StateMachine<T_TransArg>  _sm;


    public:
        Lexer()
            : _lexConfig(LexerConfiguration())
            , _sm(LexerConfiguration().getSmConfig())
        { }

        Shared::ParseResult parse(std::string input) {
            Shared::ParseResult result;

            _sm.reset();

            std::string text = input + "\n";
            std::string tokenString = "";

            for (int head = 0; head < text.length() && result.success(); head++) {
                char ch = text[head];
                      
                //std::stringstream ess;
                //ess << _sm.currentState << " -> ";

                result.move(ch);
                    
                T_TransArg args = _sm.getTransit(ch);

                if (args.isNotSuccess()) {
                    int statusCode = args.getStatusCode();
                    result.setError(statusCode, _lexConfig.mapStatusMessage(statusCode));
                    break;
                }

                //std::cout << tokenString << "\n";

                if (args.isSplit() && !tokenString.empty()) {
                    int tokenTypeCode = _lexConfig.mapTokenType(_sm.currentState);

                    if (tokenTypeCode != _lexConfig.getCommentTypeCode()) {
                        std::string tokenTypeName = _lexConfig.mapTokenTypeName(tokenTypeCode);
                        result.add(tokenString, tokenTypeCode, tokenTypeName);
                    } // else ingore comment

                    tokenString.clear();
                }

                if (!args.isEmptyChar()) {
                    tokenString.append(1, args.getInputChar());
                }

                _sm.currentState = args.getNextState();

                //ess << _sm.currentState;

                //std::cout << ess.str() << "\n";
            }

            if (result.success() && (_sm.currentState != 1 || 
                _sm.currentState == _sm.getInitialState())) {
                result.setError(3, _lexConfig.mapStatusMessage(3));
            }

            return result;
        }
    };
}