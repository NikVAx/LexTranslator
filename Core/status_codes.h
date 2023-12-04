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
    static const StatusCode SUCCESS__(0, "�������");
    static const StatusCode LEX_INVALID_INPUT_CHAR(1, "������������ ������� ������");
    static const StatusCode LEX_INVALID_OPERATOR(2, "����������� ��������");
    static const StatusCode LEX_INVALID_IDENTIFIER(3, "������������ ������ ��������������");
    static const StatusCode LEX_ENDLESS_COMMENT(4, "���������� �����������");

    static const StatusCode SYN_END_OF_STATEMENT(100, "������������� ����");
    static const StatusCode SYN_ERROR(101, "�������������� ������");
    static const StatusCode SYN_ASSIGNMENT_EXPECTED(102, "��������� ������������ (:=)");
    static const StatusCode SYN_OPEXP(103, "�������� �������� (*, /)"); // �������� 
    static const StatusCode SYN_UNCBR(104, "������ �� �������"); // ���������� ������
    static const StatusCode SYN_UEXBR(105, "����������� ������"); // ����������� ������
    static const StatusCode SYN_EXPR_EXPECT(106, "��������� ���������");
    static const StatusCode SEM_ASSIGNTOCONST(107, "������������ � ��������"); // ������������ � ��������
}