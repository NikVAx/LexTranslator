#pragma once

#include "current_config.h"

#include <map>
#include <exception>

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
        int inputType = (0 <= inputChar && inputChar < getInputAlphabetSize())
            ? INPUT_ALPHABET_MAP[inputChar]
            : 0; // Любой символ не входящий в грамматику
        return inputType;
    }
};