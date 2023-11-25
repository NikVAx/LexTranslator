#pragma once

#include <string>

// Данные и преобразователи, которые можно использовать независимо от варианта
class SharedData {
public:
    enum TermTypes {
        UNDEFINED, COMMENT, ID, ASSIGNMENT, SEMICOLON,
        PLUS, MULTIPLY, DIVIDE, MINUS, // Математические операторы
        OR, XOR, AND, NOT, // Побитовые операторы
        IF, THEN, ELSE, // Условный оператор
        FOR, DO, // Оператор цикла
        LESS, GREATER, EQUAL, // Операторы сравнения
        OPEN_PRT, CLOSE_PRT, // Скобки
        TRUE, FALSE, // Логические константы (true-false, 1-0, 'T'-'F')
        FLOAT, // Числа с правающей точкой
        ROMAN,// Римские литералы
        HEX, // Шестнадцитиричные литералы

        COUNT_OF_TYPES
    };

    std::string getTermTypeName(TermTypes type) {
        static std::string NAMES[COUNT_OF_TYPES];

        NAMES[UNDEFINED] = "Неопределенный";
        NAMES[COMMENT] = "Комментарий";
        NAMES[ID] = "Идентификатор";
        NAMES[ASSIGNMENT] = "Оператор присваивания";
        NAMES[SEMICOLON] = "Точка с запятой";
        NAMES[PLUS] = "Оператор \"+\"";
        NAMES[MULTIPLY] = "Оператор \"*\"";
        NAMES[DIVIDE] = "Оператор \"/\"";
        NAMES[MINUS] = "Оператор \"-\"";
        NAMES[OR] = "Оператор OR";
        NAMES[XOR] = "Оператор XOR";
        NAMES[AND] = "Оператор AND";
        NAMES[NOT] = "Оператор NOT";
        NAMES[IF] = "Оператор IF";
        NAMES[THEN] = "Оператор THEN";
        NAMES[ELSE] = "Оператор ELSE";
        NAMES[FOR] = "Оператор FOR";
        NAMES[DO] = "Оператор DO";
        NAMES[LESS] = "Оператор \"<\"";
        NAMES[GREATER] = "Оператор \">\"";
        NAMES[EQUAL] = "Оператор \"=\"";
        NAMES[OPEN_PRT] = "Открывающая скобка";
        NAMES[CLOSE_PRT] = "Закрывающая скобка";
        NAMES[TRUE] = "ИСТИНА";
        NAMES[FALSE] = "ЛОЖЬ";
        NAMES[FLOAT] = "Число с плавающей точкой";
        NAMES[ROMAN] = "Римское число";
        NAMES[HEX] = "Шестнадцатиричное число";

        return type <= 0 || type >= COUNT_OF_TYPES
            ? NAMES[UNDEFINED]
            : NAMES[type];
    }
};