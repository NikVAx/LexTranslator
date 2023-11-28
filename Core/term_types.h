#pragma once

#include <string>

typedef struct TermType : EnumStruct {
public:
    TermType(const int code, const std::string string)
        : EnumStruct(code, string)
    { }

    int code() const {
        return _code;
    }

    operator std::string() const {
        return toString();
    }

    TermType operator=(TermType& a) {
        return a;
    }

private:
    const std::string name;
};

struct TermTypes {
    static const TermType UNDEFINED;
    static const TermType IDENTIFIER;
    static const TermType NUMBER;
    static const TermType ASSIGNMENT;
    static const TermType OPEN_BRACKET;
    static const TermType CLOSE_BRACKET;
    static const TermType PLUS;
    static const TermType SEMICOLON;
    static const TermType COMMENT;
    static const TermType KEYWORD;
    static const TermType MINUS;
    static const TermType MULTIPLY;
    static const TermType DIVIDE;
    static const TermType OR;
    static const TermType XOR;
    static const TermType AND;
    static const TermType NOT;
    static const TermType IF;
    static const TermType THEN;
    static const TermType ELSE;
    static const TermType END_TERMINAL;
    static const TermType FOR;
    static const TermType DO;
    static const TermType LESS;
    static const TermType GREATER;
    static const TermType EQUAL;
    static const TermType TRUE;
    static const TermType FALSE;
};

const TermType TermTypes::UNDEFINED(0, "������������");
const TermType TermTypes::IDENTIFIER(1, "�������������");
const TermType TermTypes::NUMBER(2, "�������� �������");
const TermType TermTypes::ASSIGNMENT(3, "�������� ������������");
const TermType TermTypes::OPEN_BRACKET(4, "����������� ������");
const TermType TermTypes::CLOSE_BRACKET(5, "����������� ������");
const TermType TermTypes::PLUS(6, "�������� \"+\"");
const TermType TermTypes::SEMICOLON(7, "����� � �������");
const TermType TermTypes::COMMENT(8, "�����������");
const TermType TermTypes::KEYWORD(9, "�������� �����");
const TermType TermTypes::MINUS(10, "�����");
const TermType TermTypes::MULTIPLY(11, "�������� \"*\"");
const TermType TermTypes::DIVIDE(12, "�������� \"/\"");
const TermType TermTypes::OR(13, "�������� OR");
const TermType TermTypes::XOR(14, "�������� XOR");
const TermType TermTypes::AND(15, "�������� AND");
const TermType TermTypes::NOT(16, "�������� NOT");
const TermType TermTypes::IF(17, "�������� IF");
const TermType TermTypes::THEN(18, "�������� THEN");
const TermType TermTypes::ELSE(19, "�������� ELSE");
const TermType TermTypes::END_TERMINAL(20, "����� ������");
const TermType TermTypes::FOR(21, "�������� FOR");
const TermType TermTypes::DO(22, "�������� DO");
const TermType TermTypes::LESS(23, "�������� <");
const TermType TermTypes::GREATER(24, "�������� >");
const TermType TermTypes::EQUAL(25, "�������� =");
const TermType TermTypes::TRUE(26, "������");
const TermType TermTypes::FALSE(27, "����");
