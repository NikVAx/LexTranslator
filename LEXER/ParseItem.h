#pragma once

#include "StatusCodes.h"
#include "Token.h"

struct ParseItem {
    Token token;
    StatusCodes statusCode;

    bool isValid() {
        return statusCode == StatusCodes::SUCCESS;
    }

    ParseItem(Token token, StatusCodes statusCode = StatusCodes::SUCCESS)
        : token(token), statusCode(statusCode)
    {
    }
};