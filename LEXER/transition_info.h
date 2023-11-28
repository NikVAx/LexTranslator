#pragma once

#include "../Core/status_codes.h"

#include <vector>

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

        return code != StatusCodes::SUCCESS;
    }

    bool isEmptyChar() {
        return input == '\n' || input == '\t' || input == ' ' || input == '\r';
    }
};