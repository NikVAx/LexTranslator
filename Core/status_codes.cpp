#include "pch.h"
#include "status_codes.h"

const std::map<int, StatusCode> StatusCode::INSTANCES = {
    { 0, StatusCodes::SUCCESS },
    { 1, StatusCodes::LEX_INVALID_INPUT_CHAR },
    { 2, StatusCodes::LEX_INVALID_OPERATOR },
    { 3, StatusCodes::LEX_INVALID_IDENTIFIER },
};