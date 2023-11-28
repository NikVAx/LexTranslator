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

const TermType TermTypes::UNDEFINED(0, "Неопределено");
const TermType TermTypes::IDENTIFIER(1, "Идентификатор");
const TermType TermTypes::NUMBER(2, "Числовой литерал");
const TermType TermTypes::ASSIGNMENT(3, "Оператор присваивания");
const TermType TermTypes::OPEN_BRACKET(4, "Открывающая скобка");
const TermType TermTypes::CLOSE_BRACKET(5, "Закрывающая скобка");
const TermType TermTypes::PLUS(6, "Оператор \"+\"");
const TermType TermTypes::SEMICOLON(7, "Точка с запятой");
const TermType TermTypes::COMMENT(8, "Комментарий");
const TermType TermTypes::KEYWORD(9, "Ключевое слово");
const TermType TermTypes::MINUS(10, "Минус");
const TermType TermTypes::MULTIPLY(11, "Оператор \"*\"");
const TermType TermTypes::DIVIDE(12, "Оператор \"/\"");
const TermType TermTypes::OR(13, "Оператор OR");
const TermType TermTypes::XOR(14, "Оператор XOR");
const TermType TermTypes::AND(15, "Оператор AND");
const TermType TermTypes::NOT(16, "Оператор NOT");
const TermType TermTypes::IF(17, "Оператор IF");
const TermType TermTypes::THEN(18, "Оператор THEN");
const TermType TermTypes::ELSE(19, "Оператор ELSE");
const TermType TermTypes::END_TERMINAL(20, "Конец строки");
const TermType TermTypes::FOR(21, "Оператор FOR");
const TermType TermTypes::DO(22, "Оператор DO");
const TermType TermTypes::LESS(23, "Оператор <");
const TermType TermTypes::GREATER(24, "Оператор >");
const TermType TermTypes::EQUAL(25, "Оператор =");
const TermType TermTypes::TRUE(26, "ИСТИНА");
const TermType TermTypes::FALSE(27, "ЛОЖЬ");
