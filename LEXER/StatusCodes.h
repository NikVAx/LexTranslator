#pragma once

#include <string>
#include <map>

typedef struct StatusCodes {
    const int code;
    const std::string message;

    StatusCodes(const int code, const std::string string)
        : code(code)
        , message(string)
    { }

    StatusCodes(const int code)
        : code(INSTANCES.at(code).code)
        , message(INSTANCES.at(code).message)
    { }

    operator int() const {
        return code;
    }

    operator std::string() const {
        return message;
    }

    bool operator==(const StatusCodes& a) const {
        return a.code == code;
    }

    static const StatusCodes SUCCESS;
    static const StatusCodes INVALID_INPUT_CHAR;
    static const StatusCodes INVALID_OPERATOR;
    static const StatusCodes INVALID_IDENTIFIER;

private:
    static const std::map<int, StatusCodes> INSTANCES;
};

const StatusCodes StatusCodes::SUCCESS(0, "�������");
const StatusCodes StatusCodes::INVALID_INPUT_CHAR(1, "������������ ������� ������");
const StatusCodes StatusCodes::INVALID_OPERATOR(2, "����������� ��������");
const StatusCodes StatusCodes::INVALID_IDENTIFIER(3, "������������ ������ ��������������");

const std::map<int, StatusCodes> StatusCodes::INSTANCES = {
    { 0, StatusCodes::SUCCESS },
    { 1, StatusCodes::INVALID_INPUT_CHAR },
    { 2, StatusCodes::INVALID_OPERATOR },
    { 3, StatusCodes::INVALID_IDENTIFIER },
};
