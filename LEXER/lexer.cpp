#include "pch.h"
#include "framework.h"
#include "lexer_config.h"
#include "shared_types.h"
#include "lexer.h"

#include <vector>
#include <iostream>
#include <sstream>

TransitionInfo::TransitionInfo(char input, int code, std::vector<int> args)
    : input(input)
    , code(code)
    , args(args)
{ }

int TransitionInfo::getInputChar() {
    return input;
}

int TransitionInfo::getInputCode() {
    return code;
}

int TransitionInfo::getNextState() {
    return args[0];
}

bool TransitionInfo::isTokenBoundary() {
    return args[1] == 1; // 1 - split code
}

int TransitionInfo::getStatusCode() {
    return args[2];
}

bool TransitionInfo::isNotSuccess() {
    return getStatusCode() != 0; // 0 - success code
}

bool TransitionInfo::isEmptyChar() {
    return input == '\n' || input == '\t' || input == ' ' || input == '\r';
}


#pragma region Lexer

ParseResult LEX::Lexer::parse(std::string input) {
    ParseResult result;

    _sm.reset();

    std::string text = input + "\n";
    std::string tokenString = "";

    for (int head = 0; head < text.length() && result.success(); head++) {
        char ch = text[head];

        result.updateCurrentCharLocationData(ch);

        TransitionInfo info = _sm.getTransition(ch);

        if (info.isNotSuccess()) {
            int statusCode = info.getStatusCode();
            result.setError(statusCode);
            break;
        }

        if (info.isTokenBoundary() && !tokenString.empty()) {
            TermTypes tokenTypeCode = _lexConfig.mapTokenType(_sm.currentState);

            if (tokenTypeCode != TermTypes::COMMENT) {
                std::string tokenTypeName = _lexConfig.mapTokenTypeName(tokenTypeCode);
                result.add(tokenString, tokenTypeCode, tokenTypeName);
            } // else ingore comment

            tokenString.clear();
        }

        if (!info.isEmptyChar()) {
            tokenString.append(1, ch);
        }

        _sm.currentState = info.getNextState();
    }

    if (result.success() && (_sm.currentState != 1 ||
        _sm.currentState == _sm.getInitialState())) {
        result.setError(3);
    }

    return result;
}