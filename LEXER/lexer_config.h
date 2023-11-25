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
    UNDEFINED, IDENTIFIER,
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

    END_TERMINAL,

    FOR, DO, // Оператор цикла
    LESS, GREATER, EQUAL, // Операторы сравнения
    
    TRUE, FALSE, // Логические константы (true-false, 1-0, 'T'-'F')

    COUNT_OF_TYPES
};

std::string getTermTypeName(TermTypes type) {
    static std::string NAMES[(int)TermTypes::COUNT_OF_TYPES];

    NAMES[(int)TermTypes::UNDEFINED] = "Неопределенный";
    NAMES[(int)TermTypes::IDENTIFIER] = "Идентификатор";
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

static const int ARGUMENTS_COUNT = 3;

const std::vector<int> INPUT_ALPHABET_MAP =
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

static const std::vector <std::string> TYPE_NAMES =
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

const std::vector<std::string> ERROR_NAMES =
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
const std::vector<TermTypes> TOKEN_TYPE_MAP =
{
    TermTypes::UNDEFINED,
    TermTypes::SEMICOLON,
    TermTypes::IDENTIFIER,
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
    TermTypes::IDENTIFIER,
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
        return STATES_MATRIX.size();
    }

    int getArgumentsCount() {
        return ARGUMENTS_COUNT;
    }

    int getCountOfInputs() {
        return STATES_MATRIX[0].size();
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

    TermTypes mapTokenType(int state) {
        TermTypes typeCode = inRange(state, 0, _smConfig.getCountOfStates())
            ? TOKEN_TYPE_MAP[state]
            : TermTypes::UNDEFINED;
        return typeCode;
    }

    std::string mapTokenTypeName(TermTypes termType) {
        return getTermTypeName(termType);
    }

    static std::string mapStatusMessage(int statusCode) {
        std::string setError = inRange(statusCode, 0, ERROR_NAMES.size())
            ? ERROR_NAMES[statusCode]
            : ERROR_NAMES[1]; // Неизвестная ошибка
        return setError;
    }
};