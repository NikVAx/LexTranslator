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

const TermTypes TermTypes::UNDEFINED(0, "Неопределено");
const TermTypes TermTypes::IDENTIFIER(1, "Идентификатор");
const TermTypes TermTypes::NUMBER(2, "Числовой литерал");
const TermTypes TermTypes::ASSIGNMENT(3, "Оператор присваивания");
const TermTypes TermTypes::OPEN_BRACKET(4, "Открывающая скобка");
const TermTypes TermTypes::CLOSE_BRACKET(5, "Закрывающая скобка");
const TermTypes TermTypes::PLUS(6, "Оператор \"+\"");
const TermTypes TermTypes::SEMICOLON(7, "Точка с запятой");
const TermTypes TermTypes::COMMENT(8, "Комментарий");
const TermTypes TermTypes::KEYWORD(9, "Ключевое слово");
const TermTypes TermTypes::MINUS(10, "Минус");
const TermTypes TermTypes::MULTIPLY(11, "Оператор \"*\"");
const TermTypes TermTypes::DIVIDE(12, "Оператор \"/\"");
const TermTypes TermTypes::OR(13, "Оператор OR");
const TermTypes TermTypes::XOR(14, "Оператор XOR");
const TermTypes TermTypes::AND(15, "Оператор AND");
const TermTypes TermTypes::NOT(16, "Оператор NOT");
const TermTypes TermTypes::IF(17, "Оператор IF");
const TermTypes TermTypes::THEN(18, "Оператор THEN");
const TermTypes TermTypes::ELSE(19, "Оператор ELSE");
const TermTypes TermTypes::END_TERMINAL(20, "Конец строки");
const TermTypes TermTypes::FOR(21, "Оператор FOR");
const TermTypes TermTypes::DO(22, "Оператор DO");
const TermTypes TermTypes::LESS(23, "Оператор <");
const TermTypes TermTypes::GREATER(24, "Оператор >");
const TermTypes TermTypes::EQUAL(25, "Оператор =");
const TermTypes TermTypes::TRUE(26, "ИСТИНА");
const TermTypes TermTypes::FALSE(27, "ЛОЖЬ");