﻿#include "pch.h"
#include "framework.h"
#include "lexer_config.h"
#include "shared_types.h"
#include "lexer.h"

#include <vector>
#include <iostream>
#include <sstream>

#pragma region TransArgs
TransArgs::TransArgs(char input, int code, std::vector<int> args)
    : input(input)
    , code(code)
    , args(args)
{ }

int TransArgs::getInputChar() {
    return input;
}

int TransArgs::getInputCode() {
    return code;
}

int TransArgs::getNextState() {
    return args[0];
}

bool TransArgs::isSplit() {
    return args[1] == 1; // 1 - split code
}

int TransArgs::getStatusCode() {
    return args[2];
}

bool TransArgs::isNotSuccess() {
    return getStatusCode() != 0; // 0 - success code
}

bool TransArgs::isEmptyChar() {
    return input == '\n' || input == '\t' || input == ' ' || input == '\r';
}

#pragma endregion

#pragma region Lexer

Shared::ParseResult LEX::Lexer::parse(std::string input) {
    Shared::ParseResult result;

    _sm.reset();

    std::string text = input + "\n";
    std::string tokenString = "";

    for (int head = 0; head < text.length() && result.success(); head++) {
        char ch = text[head];

        result.move(ch);

        TransArgs args = _sm.getTransit(ch);

        if (args.isNotSuccess()) {
            int statusCode = args.getStatusCode();
            result.setError(statusCode, _lexConfig.mapStatusMessage(statusCode));
            break;
        }

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
    }

    if (result.success() && (_sm.currentState != 1 ||
        _sm.currentState == _sm.getInitialState())) {
        result.setError(3, _lexConfig.mapStatusMessage(3));
    }

    return result;
}

#pragma endregion