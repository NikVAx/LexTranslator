#pragma once

#pragma once

#include <string>

typedef struct TermTypes {
    const int code;
    const std::string name;

    TermTypes(const int code, const std::string string)
        : code(code)
        , name(string)
    { }

    operator int() const {
        return code;
    }

    operator std::string() const {
        return name;
    }

    TermTypes operator=(TermTypes& a) {
        return a;
    }

    static const TermTypes UNDEFINED;
    static const TermTypes IDENTIFIER;
    static const TermTypes NUMBER;
    static const TermTypes ASSIGNMENT;
    static const TermTypes OPEN_BRACKET;
    static const TermTypes CLOSE_BRACKET;
    static const TermTypes PLUS;
    static const TermTypes SEMICOLON;
    static const TermTypes COMMENT;
    static const TermTypes KEYWORD;
    static const TermTypes MINUS;
    static const TermTypes MULTIPLY;
    static const TermTypes DIVIDE;
    static const TermTypes OR;
    static const TermTypes XOR;
    static const TermTypes AND;
    static const TermTypes NOT;
    static const TermTypes IF;
    static const TermTypes THEN;
    static const TermTypes ELSE;
    static const TermTypes END_TERMINAL;
    static const TermTypes FOR;
    static const TermTypes DO;
    static const TermTypes LESS;
    static const TermTypes GREATER;
    static const TermTypes EQUAL;
    static const TermTypes TRUE;
    static const TermTypes FALSE;
};

const TermTypes TermTypes::UNDEFINED(0, "������������");
const TermTypes TermTypes::IDENTIFIER(1, "�������������");
const TermTypes TermTypes::NUMBER(2, "�������� �������");
const TermTypes TermTypes::ASSIGNMENT(3, "�������� ������������");
const TermTypes TermTypes::OPEN_BRACKET(4, "����������� ������");
const TermTypes TermTypes::CLOSE_BRACKET(5, "����������� ������");
const TermTypes TermTypes::PLUS(6, "�������� \"+\"");
const TermTypes TermTypes::SEMICOLON(7, "����� � �������");
const TermTypes TermTypes::COMMENT(8, "�����������");
const TermTypes TermTypes::KEYWORD(9, "�������� �����");
const TermTypes TermTypes::MINUS(10, "�����");
const TermTypes TermTypes::MULTIPLY(11, "�������� \"*\"");
const TermTypes TermTypes::DIVIDE(12, "�������� \"/\"");
const TermTypes TermTypes::OR(13, "�������� OR");
const TermTypes TermTypes::XOR(14, "�������� XOR");
const TermTypes TermTypes::AND(15, "�������� AND");
const TermTypes TermTypes::NOT(16, "�������� NOT");
const TermTypes TermTypes::IF(17, "�������� IF");
const TermTypes TermTypes::THEN(18, "�������� THEN");
const TermTypes TermTypes::ELSE(19, "�������� ELSE");
const TermTypes TermTypes::END_TERMINAL(20, "����� ������");
const TermTypes TermTypes::FOR(21, "�������� FOR");
const TermTypes TermTypes::DO(22, "�������� DO");
const TermTypes TermTypes::LESS(23, "�������� <");
const TermTypes TermTypes::GREATER(24, "�������� >");
const TermTypes TermTypes::EQUAL(25, "�������� =");
const TermTypes TermTypes::TRUE(26, "������");
const TermTypes TermTypes::FALSE(27, "����");