#pragma once

#include <vector>

#include "status_codes.h"

struct TransitionInfo {
protected:
    std::vector<int> args;
    int code;
    char input;

    int nextState;
    bool isBoundary;
    StatusCode statusCode;

public:
    TransitionInfo(char input, int code, int nextState, bool isBoundary, StatusCode statusCode)
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

    StatusCode getStatusCode() {
        return statusCode;
    }

    bool isNotSuccess() {
        StatusCode code = getStatusCode();

        return code != StatusCodes::SUCCESS__;
    }

    bool isEmptyChar() {
        return input == '\n' || input == '\t' || input == ' ' || input == '\r';
    }

    friend std::ostream& operator<<(std::ostream& s, const TransitionInfo& transitionInfo)
    {
        s << "code: " << transitionInfo.code << " input: " << transitionInfo.input << " next: " << transitionInfo.nextState << " status: " << transitionInfo.statusCode;
        return s;
    }
};