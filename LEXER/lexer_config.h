#pragma once

#include "lex_config_5.h"

#include <string>
#include <map>
#include <exception>

#include "term_types.h"
#include "status_codes.h"

static const int IS_BOUNDARY_CODE = 1;

static const int ARGUMENTS_COUNT = 3;

static bool inRange(int value, int first, int second) {
    return first <= value && value < second;
}

class StateMachineConfiguration {
public:
    int initialState;

    int getInitialState() {
        return INITIAL_STATE;
    }

    int getInputAlphabetSize() {
        return INPUT_ALPHABET_SIZE;
    }

    int getCountOfStates() {
        return STATES_MATRIX.size();
    }

    int getArgumentsCount() {
        return ARGUMENTS_COUNT;
    }

    int getCountOfInputs() {
        return STATES_MATRIX[0].size();
    }

    int getNextState(int state, int inputType) {
        return STATES_MATRIX[state][inputType];
    }

    int getBoundary(int state, int inputType) {
        return BOUNDS_MATRIX[state][inputType];
    }

    int getStatusCode(int state, int inputType) {
        return ERRORS_MATRIX[state][inputType];
    }

    int mapMatrix(int arg, int state, int inputType) {
        switch (arg) {
        case 0:
            return getNextState(state, inputType);
     
        case 1: 
            return getBoundary(state, inputType);
            
        case 2: 
            return getStatusCode(state, inputType);
     
        default:
            exit(-1);
        }
    }

    int mapInputAlpha(int inputChar) {
        int inputType = inRange(inputChar, 0, getInputAlphabetSize())
            ? INPUT_ALPHABET_MAP[inputChar]
            : 0; // Любой символ не входящий в грамматику
        return inputType;
    }
};

class LexerConfiguration {
private:
    StateMachineConfiguration _smConfig;
public:
    LexerConfiguration() 
        : _smConfig(StateMachineConfiguration())
    { }

    StateMachineConfiguration& getSmConfig() {
        return _smConfig;
    }

    TermTypes mapTokenType(int state) {
        TermTypes typeCode = inRange(state, 0, _smConfig.getCountOfStates())
            ? TOKEN_TYPE_MAP[state]
            : TermTypes::UNDEFINED;
        return typeCode;
    }

    std::string getTokenTypeName(TermTypes termType) {
        return termType.name;
    }
};