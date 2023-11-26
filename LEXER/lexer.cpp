#include "pch.h"
#include "framework.h"
#include "lexer_config.h"
#include "shared_types.h"
#include "lexer.h"

#include <vector>
#include <iostream>
#include <sstream>

TransitionInfo::TransitionInfo(char input, int code, int nextState, bool isBoundary, StatusCodes statusCode)
    : input(input)
    , code(code)
    , nextState(nextState)
    , isBoundary(isBoundary)
    , statusCode(statusCode)
{ }

int TransitionInfo::getInputCode() {
    return code;
}

int TransitionInfo::getNextState() {
    return nextState;
}

bool TransitionInfo::isTokenBoundary() {
    return isBoundary;
}

StatusCodes TransitionInfo::getStatusCode() {
    return statusCode;
}

bool TransitionInfo::isNotSuccess() {
    return getStatusCode() != StatusCodes::SUCCESS;
}

bool TransitionInfo::isEmptyChar() {
    return input == '\n' || input == '\t' || input == ' ' || input == '\r';
}

ParseResult LEX::Lexer::parse(std::string input) {
    ParseResult result;

    _sm.reset();

    std::string text = input + "\n";
    std::string tokenString = "";

    for (int head = 0; head < text.length() && result.success(); head++) {
        char ch = text[head];

        TransitionInfo info = _sm.getTransition(ch);

        if (info.isNotSuccess()) {
            result.addError(tokenString, (StatusCodes)info.getStatusCode());
            continue;
        }

        if (info.isTokenBoundary() && !tokenString.empty()) {
            TermTypes tokenType = _lexConfig.mapTokenType(_sm.currentState);

            if (tokenType != TermTypes::COMMENT) {
                result.add(tokenString, tokenType);
            } // else ingore comment

            tokenString.clear();
        }

        if (!info.isEmptyChar()) {
            tokenString.append(1, ch);
        }

        _sm.currentState = info.getNextState();
    }

    return result;
}