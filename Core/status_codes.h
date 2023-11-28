#pragma once

#include "enum_struct.h"

#include <string>
#include <map>

typedef struct StatusCode : EnumStruct {    
    StatusCode(const int code, const std::string string)
        : EnumStruct(code, string)
    { }

    StatusCode(const int code)
        : EnumStruct(INSTANCES.at(code)._code, INSTANCES.at(code).toString())
    { }

    operator std::string() const {
        return toString();
    }

    bool operator==(const StatusCode& a) const {
        return a._code == _code;
    }

private:
    static const std::map<int, StatusCode> INSTANCES;
};

struct StatusCodes {
    static const StatusCode SUCCESS;
    static const StatusCode INVALID_INPUT_CHAR;
    static const StatusCode INVALID_OPERATOR;
    static const StatusCode INVALID_IDENTIFIER;
};

const StatusCode StatusCodes::SUCCESS(0, "Успешно");
const StatusCode StatusCodes::INVALID_INPUT_CHAR(1, "Недопустимый входной символ");
const StatusCode StatusCodes::INVALID_OPERATOR(2, "Неизвестный оператор");
const StatusCode StatusCodes::INVALID_IDENTIFIER(3, "Недопустимый формат идентификатора");

const std::map<int, StatusCode> StatusCode::INSTANCES = {
    { 0, StatusCodes::SUCCESS },
    { 1, StatusCodes::INVALID_INPUT_CHAR },
    { 2, StatusCodes::INVALID_OPERATOR },
    { 3, StatusCodes::INVALID_IDENTIFIER },
};
