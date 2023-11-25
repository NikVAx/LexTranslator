#pragma once
/*
  ���� ������������ ��������� �������� ������������ �����������.
*/

#include "matrices.h"

#include <string>
#include <map>
#include <exception>

#include <string>

enum class TermTypes {
    UNDEFINED, INDENTIFIER,
    NUMBER,// �������� ��������
    ASSIGNMENT,
    OPEN_BRACKET, CLOSE_BRACKET, // ������
    PLUS,
    SEMICOLON,
    COMMENT,

    KEYWORD,
    
    MINUS,
    MULTIPLY,
    DIVIDE,  // �������������� ���������
    
    OR, XOR, AND, NOT, // ��������� ���������
    IF, THEN, ELSE, // �������� ��������
    FOR, DO, // �������� �����
    LESS, GREATER, EQUAL, // ��������� ���������
    
    TRUE, FALSE, // ���������� ��������� (true-false, 1-0, 'T'-'F')

    COUNT_OF_TYPES
};

std::string getTermTypeName(TermTypes type) {
    static std::string NAMES[(int)TermTypes::COUNT_OF_TYPES];

    NAMES[(int)TermTypes::UNDEFINED] = "��������������";
    NAMES[(int)TermTypes::INDENTIFIER] = "�������������";
    NAMES[(int)TermTypes::COMMENT] = "�����������";
    NAMES[(int)TermTypes::ASSIGNMENT] = "������������";
    NAMES[(int)TermTypes::SEMICOLON] = "�����������";
    NAMES[(int)TermTypes::PLUS] = "�������� \"+\"";
    NAMES[(int)TermTypes::MULTIPLY] = "�������� \"*\"";
    NAMES[(int)TermTypes::DIVIDE] = "�������� \"/\"";
    NAMES[(int)TermTypes::MINUS] = "�������� \"-\"";
    NAMES[(int)TermTypes::OR] = "�������� OR";
    NAMES[(int)TermTypes::XOR] = "�������� XOR";
    NAMES[(int)TermTypes::AND] = "�������� AND";
    NAMES[(int)TermTypes::NOT] = "�������� NOT";
    NAMES[(int)TermTypes::IF] = "�������� IF";
    NAMES[(int)TermTypes::THEN] = "�������� THEN";
    NAMES[(int)TermTypes::ELSE] = "�������� ELSE";
    NAMES[(int)TermTypes::FOR] = "�������� FOR";
    NAMES[(int)TermTypes::DO] = "�������� DO";
    NAMES[(int)TermTypes::LESS] = "�������� \"<\"";
    NAMES[(int)TermTypes::GREATER] = "�������� \">\"";
    NAMES[(int)TermTypes::EQUAL] = "�������� \"=\"";
    NAMES[(int)TermTypes::OPEN_BRACKET] = "����������� ������";
    NAMES[(int)TermTypes::CLOSE_BRACKET] = "����������� ������";
    NAMES[(int)TermTypes::TRUE] = "������";
    NAMES[(int)TermTypes::FALSE] = "����";
    NAMES[(int)TermTypes::NUMBER] = "������� �����";

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
    "������                 ",
    "�������������          ",
    "������� �����          ",
    "������������           ",
    "����������� ������     ",
    "����������� ������     ",
    "�������� \"+\"         ",
    "�����������            ",
    "�����������            ",
    "�������� �����         ",
    "�������� \"-\"         ",
    "�������� \"*\"         ",
    "�������� \"/\"         ",
};

static const std::string ERROR_NAMES[COUNT_OF_ERRORS] =
{
    "�������",
    "����������� ������",
    "������������ ������� ������",
    "����������� ����� �����",
    "�������� ������������� �����������",
    "��������� ������������",
    "������������ ������ ��������������",
    "������������� �������� ������������",
    "��������� ���������",
    "�������� ��������",
    "�������� �������������"
};

// ����� ������������, ������� �� ������� ���������
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
            : 0; // ����� ������ �� �������� � ����������
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
            : ERROR_NAMES[1]; // ����������� ������
        return setError;
    }
};