#pragma once

#include "status_codes.h"
#include "token.h"

struct ParseItem {
    Token token;
    StatusCode statusCode;

    bool isValid() {
        return statusCode == StatusCodes::SUCCESS;
    }

    ParseItem(Token token, StatusCode statusCode = StatusCodes::SUCCESS)
        : token(token), statusCode(statusCode)
    {
    }
};
