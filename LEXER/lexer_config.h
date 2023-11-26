#pragma once
/*
  Файл конфигурации конечного автомата лексического анализатора.
*/

#include "matrices.h"

#include <string>
#include <map>
#include <exception>

#include <string>
#include "TermTypes.h"

enum class StatusCodes {
    SUCCESS,
    BAD_IDENTIFIER,
    INVALID_OPERATOR,
    CODE3,
    CODE4,
    CODE5,
    CODE6,
    CODE7,
    CODE8,
    CODE9,
    CODE10,
    CODE11,
    CODE12,
};

static const int IS_BOUNDARY_CODE = 1;


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

    int getNextState(int state, int inputType) {
        return STATES_MATRIX[state][inputType];
    }

    int getBoundary(int state, int inputType) {
        return BOUNDS_MATRIX[state][inputType];
    }

    int getStatusCode(int state, int inputType) {
        return ERRORS_MATRIX[state][inputType];
    }

    int mapMatrix(int arg, int state, int inputType) {
        switch (arg) {
        case 0:
            return getNextState(state, inputType);
     
        case 1: 
            return getBoundary(state, inputType);
            
        case 2: 
            return getStatusCode(state, inputType);
     
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

    std::string getTokenTypeName(TermTypes termType) {
        return termType.string;
    }

    static std::string mapStatusMessage(StatusCodes statusCode) {
        std::string addError = inRange((int)statusCode, 0, ERROR_NAMES.size())
            ? ERROR_NAMES[(int)statusCode]
            : ERROR_NAMES[1]; // Неизвестная ошибка
        return addError;
    }
};