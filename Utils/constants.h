#pragma once

#include <string>

// ������ � ���������������, ������� ����� ������������ ���������� �� ��������
class SharedData {
public:
    enum TermTypes {
        UNDEFINED, COMMENT, ID, ASSIGNMENT, SEMICOLON,
        PLUS, MULTIPLY, DIVIDE, MINUS, // �������������� ���������
        OR, XOR, AND, NOT, // ��������� ���������
        IF, THEN, ELSE, // �������� ��������
        FOR, DO, // �������� �����
        LESS, GREATER, EQUAL, // ��������� ���������
        OPEN_PRT, CLOSE_PRT, // ������
        TRUE, FALSE, // ���������� ��������� (true-false, 1-0, 'T'-'F')
        FLOAT, // ����� � ��������� ������
        ROMAN,// ������� ��������
        HEX, // ����������������� ��������

        COUNT_OF_TYPES
    };

    std::string getTermTypeName(TermTypes type) {
        static std::string NAMES[COUNT_OF_TYPES];

        NAMES[UNDEFINED] = "��������������";
        NAMES[COMMENT] = "�����������";
        NAMES[ID] = "�������������";
        NAMES[ASSIGNMENT] = "�������� ������������";
        NAMES[SEMICOLON] = "����� � �������";
        NAMES[PLUS] = "�������� \"+\"";
        NAMES[MULTIPLY] = "�������� \"*\"";
        NAMES[DIVIDE] = "�������� \"/\"";
        NAMES[MINUS] = "�������� \"-\"";
        NAMES[OR] = "�������� OR";
        NAMES[XOR] = "�������� XOR";
        NAMES[AND] = "�������� AND";
        NAMES[NOT] = "�������� NOT";
        NAMES[IF] = "�������� IF";
        NAMES[THEN] = "�������� THEN";
        NAMES[ELSE] = "�������� ELSE";
        NAMES[FOR] = "�������� FOR";
        NAMES[DO] = "�������� DO";
        NAMES[LESS] = "�������� \"<\"";
        NAMES[GREATER] = "�������� \">\"";
        NAMES[EQUAL] = "�������� \"=\"";
        NAMES[OPEN_PRT] = "����������� ������";
        NAMES[CLOSE_PRT] = "����������� ������";
        NAMES[TRUE] = "������";
        NAMES[FALSE] = "����";
        NAMES[FLOAT] = "����� � ��������� ������";
        NAMES[ROMAN] = "������� �����";
        NAMES[HEX] = "����������������� �����";

        return type <= 0 || type >= COUNT_OF_TYPES
            ? NAMES[UNDEFINED]
            : NAMES[type];
    }
};