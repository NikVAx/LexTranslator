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

namespace StatusCodes {
    static const StatusCode SUCCESS(0, "Успешно");
    static const StatusCode LEX_INVALID_INPUT_CHAR(1, "Недопустимый входной символ");
    static const StatusCode LEX_INVALID_OPERATOR(2, "Неизвестный оператор");
    static const StatusCode LEX_INVALID_IDENTIFIER(3, "Недопустимый формат идентификатора");
}