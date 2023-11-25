#pragma once
/*
  Файл конфигурации конечного автомата лексического анализатора.
*/

#include "matrices.h"

#include <string>
#include <map>
#include <exception>

#include <string>

enum class TermTypes {
    UNDEFINED, COMMENT, ID, ASSIGNMENT, SEMICOLON,
    PLUS, MULTIPLY, DIVIDE, MINUS, // Математические операторы
    OR, XOR, AND, NOT, // Побитовые операторы
    IF, THEN, ELSE, // Условный оператор
    FOR, DO, // Оператор цикла
    LESS, GREATER, EQUAL, // Операторы сравнения
    OPEN_BRACKET, CLOSE_BRACKET, // Скобки
    TRUE, FALSE, // Логические константы (true-false, 1-0, 'T'-'F')
    FLOAT, // Числа с правающей точкой
    ROMAN,// Римские литералы
    HEX, // Шестнадцитиричные литералы

    COUNT_OF_TYPES
};

std::string getTermTypeName(TermTypes type) {
    static std::string NAMES[(int)TermTypes::COUNT_OF_TYPES];

    NAMES[(int)TermTypes::UNDEFINED] = "Неопределенный";
    NAMES[(int)TermTypes::COMMENT] = "Комментарий";
    NAMES[(int)TermTypes::ID] = "Идентификатор";
    NAMES[(int)TermTypes::ASSIGNMENT] = "Оператор присваивания";
    NAMES[(int)TermTypes::SEMICOLON] = "Точка с запятой";
    NAMES[(int)TermTypes::PLUS] = "Оператор \"+\"";
    NAMES[(int)TermTypes::MULTIPLY] = "Оператор \"*\"";
    NAMES[(int)TermTypes::DIVIDE] = "Оператор \"/\"";
    NAMES[(int)TermTypes::MINUS] = "Оператор \"-\"";
    NAMES[(int)TermTypes::OR] = "Оператор OR";
    NAMES[(int)TermTypes::XOR] = "Оператор XOR";
    NAMES[(int)TermTypes::AND] = "Оператор AND";
    NAMES[(int)TermTypes::NOT] = "Оператор NOT";
    NAMES[(int)TermTypes::IF] = "Оператор IF";
    NAMES[(int)TermTypes::THEN] = "Оператор THEN";
    NAMES[(int)TermTypes::ELSE] = "Оператор ELSE";
    NAMES[(int)TermTypes::FOR] = "Оператор FOR";
    NAMES[(int)TermTypes::DO] = "Оператор DO";
    NAMES[(int)TermTypes::LESS] = "Оператор \"<\"";
    NAMES[(int)TermTypes::GREATER] = "Оператор \">\"";
    NAMES[(int)TermTypes::EQUAL] = "Оператор \"=\"";
    NAMES[(int)TermTypes::OPEN_BRACKET] = "Открывающая скобка";
    NAMES[(int)TermTypes::CLOSE_BRACKET] = "Закрывающая скобка";
    NAMES[(int)TermTypes::TRUE] = "ИСТИНА";
    NAMES[(int)TermTypes::FALSE] = "ЛОЖЬ";
    NAMES[(int)TermTypes::FLOAT] = "Число с плавающей точкой";
    NAMES[(int)TermTypes::ROMAN] = "Римское число";
    NAMES[(int)TermTypes::HEX] = "Шестнадцатиричное число";

    return (int)type <= 0 || type >= TermTypes::COUNT_OF_TYPES
        ? NAMES[(int)TermTypes::UNDEFINED]
        : NAMES[(int)type];
}


static const int INITIAL_STATE = 53;
static const int INPUT_ALPHABET_SIZE = 128;
static const int COUNT_OF_STATES = 54;
static const int COUNT_OF_INPUTS = 22;
static const int ARGUMENTS_COUNT = 3;
static const int COMMENT_TYPE = 8;
static const int COUNT_OF_TYPES = 13;
static const int COUNT_OF_ERRORS = 11;

static const int INPUT_ALPHABET_MAP[INPUT_ALPHABET_SIZE] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 19, 0, 0, 20, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0,  0, 0, 0, 0, 0,
    20, 0, 0, 0, 0, 0,  0, 0, 12, 13, 16, 14, 0, 15, 0, 17,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 18, 0, 11, 0, 0,
    0, 8, 8, 5, 6, 8, 8, 8, 8, 1, 8, 8, 4, 7, 8, 8,
    8, 8, 8, 8, 8, 8, 2, 8, 3, 8, 8, 0, 0, 0, 0, 8,
    0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0
};

static const std::string TYPE_NAMES[COUNT_OF_TYPES] =
{
    "Ошибка                 ",
    "Идентификатор          ",
    "Римское число          ",
    "Присваивание           ",
    "Открывающая скобка     ",
    "Закрывающая скобка     ",
    "Оператор \"+\"         ",
    "Разделитель            ",
    "Комментарий            ",
    "Ключевое слово         ",
    "Оператор \"-\"         ",
    "Оператор \"*\"         ",
    "Оператор \"/\"         ",
};

static const std::string ERROR_NAMES[COUNT_OF_ERRORS] =
{
    "Успешно",
    "Неизвестная ошибка",
    "Недопустимый входной символ",
    "Неожиданный конец файла",
    "Встречен незавершенный комментарий",
    "Ожидалось присваивание",
    "Недопустимый формат идентификатора",
    "Незавершенный оператор присваивания",
    "Ожидалось выражение",
    "Ожидался оператор",
    "Ожидался идентификатор"
};


static const int TOKEN_TYPE_MAP[COUNT_OF_STATES] =
{
    0,7,1,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    0,3,
    6,10,11,12,
    4,5,
    0,8,0,0,8
};

static const int IDENTIFIER_TYPE = 1;
static const int KEYWORD_TYPE = 9;

static bool inRange(int value, int first, int second) {
    return first <= value && value < second;
}

class StateMachineConfiguration {
public:
    int initialState;

    int getInitialState() {
        return INITIAL_STATE;
    }

    int getInputAlphabetSize() {
        return INPUT_ALPHABET_SIZE;
    }

    int getCountOfStates() {
        return COUNT_OF_STATES;
    }

    int getArgumentsCount() {
        return ARGUMENTS_COUNT;
    }

    int getCountOfInputs() {
        return COUNT_OF_INPUTS;
    }

    int getState(int state, int inputType) {
        return STATES_MATRIX[state][inputType];
    }

    int getBound(int state, int inputType) {
        return BOUNDS_MATRIX[state][inputType];
    }

    int getError(int state, int inputType) {
        return ERRORS_MATRIX[state][inputType];
    }

    int mapMatrix(int arg, int state, int inputType) {
        switch (arg) {
        case 0:
            return getState(state, inputType);
     
        case 1: 
            return getBound(state, inputType);
            
        case 2: 
            return getError(state, inputType);
     
        default:
            exit(-1);
        }
    }

    int mapInputAlpha(int inputChar) {
        int inputType = inRange(inputChar, 0, getInputAlphabetSize())
            ? INPUT_ALPHABET_MAP[inputChar]
            : 0; // Любой символ не входящий в грамматику
        return inputType;
    }
};

class LexerConfiguration {
private:
    StateMachineConfiguration _smConfig;
public:
    LexerConfiguration() 
        : _smConfig(StateMachineConfiguration())
    { }

    StateMachineConfiguration& getSmConfig() {
        return _smConfig;
    }

    static int getCommentTypeCode() {
        return COMMENT_TYPE;
    }

    int mapTokenType(int state) {
        int typeCode = inRange(state, 0, _smConfig.getCountOfStates())
            ? TOKEN_TYPE_MAP[state]
            : 0; // Ошибка
        return typeCode;
    }

    std::string mapTokenTypeName(int tokenTypeCode) {
        return TYPE_NAMES[tokenTypeCode];
    }

    static std::string mapStatusMessage(int statusCode) {
        std::string setError = inRange(statusCode, 0, COUNT_OF_ERRORS)
            ? ERROR_NAMES[statusCode]
            : ERROR_NAMES[1]; // Неизвестная ошибка
        return setError;
    }
};