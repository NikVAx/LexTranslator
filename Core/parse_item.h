#pragma once

#include "status_codes.h"
#include "token.h"

struct ParseItem {
    Token token;
    StatusCode statusCode;

    bool isValid() {
        return statusCode == StatusCodes::SUCCESS__;
    }

    ParseItem(Token token, StatusCode statusCode = StatusCodes::SUCCESS__)
        : token(token), statusCode(statusCode)
    {
    }
};
