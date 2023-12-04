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
    static const StatusCode SUCCESS__(0, "Успешно");
    static const StatusCode LEX_INVALID_INPUT_CHAR(1, "Недопустимый входной символ");
    static const StatusCode LEX_INVALID_OPERATOR(2, "Неизвестный оператор");
    static const StatusCode LEX_INVALID_IDENTIFIER(3, "Недопустимый формат идентификатора");
    static const StatusCode LEX_ENDLESS_COMMENT(4, "Незакрытый комментарий");

    static const StatusCode SYN_END_OF_STATEMENT(100, "Незавершенный блок");
    static const StatusCode SYN_ERROR(101, "Синтаксическая ошибка");
    static const StatusCode SYN_ASSIGNMENT_EXPECTED(102, "Ожидалось присваивание (:=)");
    static const StatusCode SYN_OPEXP(103, "Ожидался оператор (*, /)"); // Ожидался 
    static const StatusCode SYN_UNCBR(104, "Скобка не закрыта"); // Незакрытая скобка
    static const StatusCode SYN_UEXBR(105, "Неожиданная скобка"); // Неожиданная скобка
    static const StatusCode SYN_EXPR_EXPECT(106, "Ожидалось выражение");
    static const StatusCode SEM_ASSIGNTOCONST(107, "Присваивание к литералу"); // Присваивание к литералу
}