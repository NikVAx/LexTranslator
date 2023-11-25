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
    UNDEFINED, INDENTIFIER,
    NUMBER,// Числовые литералы
    ASSIGNMENT,
    OPEN_BRACKET, CLOSE_BRACKET, // Скобки
    PLUS,
    SEMICOLON,
    COMMENT,

    KEYWORD,
    
    MINUS,
    MULTIPLY,
    DIVIDE,  // Математические операторы
    
    OR, XOR, AND, NOT, // Побитовые операторы
    IF, THEN, ELSE, // Условный оператор
    FOR, DO, // Оператор цикла
    LESS, GREATER, EQUAL, // Операторы сравнения
    
    TRUE, FALSE, // Логические константы (true-false, 1-0, 'T'-'F')

    COUNT_OF_TYPES
};

std::string getTermTypeName(TermTypes type) {
    static std::string NAMES[(int)TermTypes::COUNT_OF_TYPES];

    NAMES[(int)TermTypes::UNDEFINED] = "Неопределенный";
    NAMES[(int)TermTypes::INDENTIFIER] = "Идентификатор";
    NAMES[(int)TermTypes::COMMENT] = "Комментарий";
    NAMES[(int)TermTypes::ASSIGNMENT] = "Присваивание";
    NAMES[(int)TermTypes::SEMICOLON] = "Разделитель";
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
    NAMES[(int)TermTypes::NUMBER] = "Римское число";

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

// Часть конфигурации, зависит от матрицы переходов
static const TermTypes TOKEN_TYPE_MAP[COUNT_OF_STATES] =
{
    TermTypes::UNDEFINED,
    TermTypes::SEMICOLON,
    TermTypes::INDENTIFIER,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::INDENTIFIER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::UNDEFINED,
    TermTypes::ASSIGNMENT,
    TermTypes::PLUS,
    TermTypes::MINUS,
    TermTypes::MULTIPLY,
    TermTypes::DIVIDE,
    TermTypes::OPEN_BRACKET,
    TermTypes::CLOSE_BRACKET,
    TermTypes::UNDEFINED,
    TermTypes::COMMENT,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::COMMENT
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
            ? (int)TOKEN_TYPE_MAP[state]
            : (int)TermTypes::UNDEFINED;
        return typeCode;
    }

    std::string mapTokenTypeName(int tokenTypeCode) {
        return getTermTypeName( static_cast<TermTypes>(tokenTypeCode) );
    }

    static std::string mapStatusMessage(int statusCode) {
        std::string setError = inRange(statusCode, 0, COUNT_OF_ERRORS)
            ? ERROR_NAMES[statusCode]
            : ERROR_NAMES[1]; // Неизвестная ошибка
        return setError;
    }
};