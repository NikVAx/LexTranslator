#include "pch.h"
#include "framework.h"
#include "lexer_config.h"

#include <vector>
#include <iostream>

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
    StateMachine(StateMachineConfiguration _smConfig) 
        : _smConfig(_smConfig)
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
    struct Token {
        Token(std::string value, int typeCode, std::string typeName) {
            this->value = value;
            this->typeCode = typeCode;
            this->typeName = typeName;
        }

        std::string value = "";
        std::string typeName = "";
        int typeCode = 0;

        friend bool operator==(const Token& t1, const Token& t2) {
            return t1.value == t2.value &&
                t1.typeCode == t2.typeCode &&
                t1.typeName == t2.typeName;
        }

        friend bool operator!=(const Token& t1, const Token& t2) {
            return !(t1 == t2);
        }
    };

    struct ParseResult {
    private:
        bool _error = false;
        int _code = 0;
        std::string _message = "";
    public:
        struct Location {
            int index = 0;
            int row = 1;
            int column = 1;
        };

        std::vector<Token> tokens;
        Location current;

        void setError(int code, std::string errorMessage) {
            _message = errorMessage;
            _error = true;
            _code = code;
        }

        std::string message() {
            return _message;
        }

        bool success() {
            return !_error;
        }

        int code() {
            return _code;
        }

        void add(Token token) {
            tokens.push_back(token);
        }

        void move(char ch) {
            current.index += 1;
            current.column += 1;
            if (ch == '\n') {
                current.row += 1;
                current.column = 1;
            }
        }
    };

    class Lexer {
    private:
        LexerConfiguration _lexConfig;
        StateMachine<T_TransArg>  _sm;

        
    public:
        Lexer()
            : _lexConfig(LexerConfiguration())
            , _sm(LexerConfiguration().getSmConfig())
        { }

        ParseResult parse(std::string input) {
            ParseResult result;

            _sm.reset();

            std::string text = input + "\n";
            std::string tokenString = "";

            for (int head = 0; head < text.length() && result.success(); head++) {
                char ch = text[head];
                
                result.move(ch);
                    
                T_TransArg args = _sm.getTransit(ch);

                if (args.isNotSuccess()) {
                    int statusCode = args.getStatusCode();
                    result.setError(statusCode, _lexConfig.mapStatusMessage(statusCode));
                    break;
                }

                if (args.isSplit() && !tokenString.empty()) {
                    int tokenTypeCode = _lexConfig.mapTokenType(_sm.currentState);

                    if (tokenTypeCode != _lexConfig.getCommentTypeCode()) {
                        std::string tokenTypeName = _lexConfig
                            .mapTokenTypeName(tokenTypeCode);
                        result.add(Token(tokenString, tokenTypeCode,
                            tokenTypeName));
                    } // else ingore comment

                    tokenString.clear();
                }

                if (!args.isEmptyChar()) {
                    tokenString.append(1, args.getInputChar());
                }

                _sm.currentState = args.getNextState();
            }

            if (result.success() && (_sm.currentState != 1 || 
                _sm.currentState == _sm.getInitialState())) {
                result.setError(3, _lexConfig.mapStatusMessage(3));
            }

            return result;
        }
    };
}