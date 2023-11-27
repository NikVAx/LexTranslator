#pragma once

#include "transition_info.h"
#include "state_machine_configuration.h"

class StateMachine {
protected:
    StateMachineConfiguration _smConfig;

    static const int IS_BOUNDARY_CODE = 1;
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