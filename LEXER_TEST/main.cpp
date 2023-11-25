﻿
#include "../LEXER/lexer.h"
#include "../LEXER/shared_types.h"
#include "../SYNTAX/syntax.cpp";
#include "../Utils/utils.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <functional>
#include <algorithm>

namespace LEX {
    class Test {
    public:
        int N = 1;
        int PassCount = 0;
        int FailCount = 0;

        void summary(std::string title = "") {
            std::cout << title << "\n";
            std::cout << "PASS: " << PassCount << "\n";
            std::cout << "FAIL: " << FailCount << "\n\n";
        }

        void PASS() { std::cout << std::setw(3) << N++ << ": PASS" << std::endl; PassCount += 1; }

        void FAIL(ParseResult* r = nullptr) {
            std::cout << std::setw(3) << N++ << ": FAIL" << std::endl;
            FailCount += 1;

            if (r != nullptr) {
                DEBUG(*r);
            }
        }

        void DEBUG(ParseResult act) {
            std::cout << std::string(32, '#') << "\n";
            std::cout << "success: " << act.success() << "\n";
            std::cout << "code: " << act.code() << "\n";
            std::cout << "message: " << act.message() << "\n";
            std::cout << "location.index: " << act.current.head << "\n";
            std::cout << "location.row: " << act.current.row << "\n";
            std::cout << "location.column: " << act.current.column << "\n";
            std::cout << "tokens.size: " << act.tokens.size() << "\n";
            for (auto& token : act.tokens) {
                std::cout << token.value << "\t" << (int)token.typeCode << "\t" << token.typeName << "\n";
            }
            std::cout << std::string(32, '#') << "\n";
        }

    };

    class WhiteBox : public Test {

        static const int SUCCESS_CODE = 0;
        static const int INVALID_CHAR_CODE = 2;
        static const int END_OF_FILE_CODE = 3;
        static const int ASSIGNMENT_EXPECTED_CODE = 5;
        static const int INVALID_IDENTIFIER_CODE = 6;
        static const int UNCOMPLITE_ASSIGNMEN_CODE = 7;
        static const int EXPRESSION_EXPECTED_CODE = 8;
        static const int OPERATOR_EXPECTED_CODE = 9;

        Lexer lexer = Lexer();

#pragma region  UnexpectedEof

        bool is_unexpected_eof(std::string line)
        {
            ParseResult act = lexer.parse(line);

            if (act.success() == false &&
                act.code() == END_OF_FILE_CODE &&
                act.message() == "Неожиданный конец файла")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        void T__1_empty_file_1()
        {
            if (is_unexpected_eof("  ") == true)
            {
                PASS();
            }
            else {
                FAIL();
            }
        }

        void T__2_empty_file_2()
        {
            if (is_unexpected_eof("\n") == true)
            {
                PASS();
            }
            else
            {
                FAIL();
            }
        }

        void T__3_empty_file_3()
        {
            if (is_unexpected_eof("\n\t \n \t") == true)
            {
                PASS();
            }
            else
            {
                FAIL();
            }
        }

        void T__4_empty_file_4()
        {
            if (is_unexpected_eof("\n\t x:=II; \n \t") == false)
            {
                PASS();
            }
            else
            {
                FAIL();
            }
        }

        void T__5_empty_file_5()
        {
            if (is_unexpected_eof("\n\t x:=II \n \t") == true)
            {
                PASS();
            }
            else
            {
                FAIL();
            }
        }
#pragma endregion

        // Тест, что однострочный комментарий не добавляется в таблицу лексем
        void T__6_comment_1()
        {
            std::string source =
                "x:=X; //комментарий";

            ParseResult act = lexer.parse(source);

            if (act.success() &&
                act.code() == SUCCESS_CODE &&
                act.tokens.size() == 4 &&
                act.tokens[0].value == "x" &&
                act.tokens[1].value == ":=" &&
                act.tokens[2].value == "X" &&
                act.tokens[3].value == ";")
            {
                PASS();
            }
            else
            {
                std::cout << act.code() << "\n";

                FAIL(&act);
            }
        }

        // Тест, что многострочный комментарий не добавляется в таблицу лексем
        void T__7_comment_2()
        {
            std::string source =
                "x:=X; /* текст комментарий\n"
                " текст комментарий на строке №2*/\n"
                "y:=X;";

            ParseResult act = lexer.parse(source);

            if (act.success() == true &&
                act.code() == SUCCESS_CODE &&
                act.tokens.size() == 8 &&
                act.tokens[0].value == "x" && act.tokens[0].typeCode == TermTypes::IDENTIFIER &&
                act.tokens[1].value == ":=" &&
                act.tokens[2].value == "X" &&
                act.tokens[3].value == ";" &&
                act.tokens[4].value == "y" && act.tokens[0].typeCode == TermTypes::IDENTIFIER &&
                act.tokens[5].value == ":=" &&
                act.tokens[6].value == "X" &&
                act.tokens[7].value == ";")
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        // Тест, что комментарий НЕ может находится в середине операции
        void T__8_comment_3() {
            std::string source =
                "x:= /*123*/X;";

            ParseResult act = lexer.parse(source);

            if (act.success() == false &&
                act.code() == EXPRESSION_EXPECTED_CODE)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        // Тест, что можно присваивать значение идентификатору
        void T__9_assignment_1() {
            std::string source =
                "x:=X;";

            ParseResult act = lexer.parse(source);

            if (act.success() &&
                act.code() == SUCCESS_CODE &&
                act.tokens.size() == 4 &&
                act.tokens[0].value == "x" &&
                act.tokens[1].value == ":=" &&
                act.tokens[2].value == "X" &&
                act.tokens[3].value == ";")
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        // Тест, что множественное присваивание не допустимо
        void T_10_assignment_2() {
            std::string source =
                "x:=y:=z;";

            ParseResult act = lexer.parse(source);

            if (act.success() == false &&
                act.code() == OPERATOR_EXPECTED_CODE &&
                act.tokens.size() == 2)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        // Тест, что анализатор не пропускает недопустимые символы
        void T_11_invalid_char() {
            std::string source =
                "x:=а;";

            ParseResult act = lexer.parse(source);

            if (act.success() == false &&
                act.code() == INVALID_CHAR_CODE &&
                act.tokens.size() == 1)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T_12_assignment_expected() {
            std::string source =
                "x+y;";

            ParseResult act = lexer.parse(source);

            if (act.success() == false &&
                act.code() == ASSIGNMENT_EXPECTED_CODE &&
                act.tokens.size() == 0)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T_13_invalid_identifier() {
            std::string source =
                "3x:=III;";

            ParseResult act = lexer.parse(source);

            if (act.success() == false &&
                act.code() == INVALID_IDENTIFIER_CODE &&
                act.tokens.size() == 0)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T_14_incomplite_assignment() {
            std::string source =
                "x:III;";

            ParseResult act = lexer.parse(source);

            if (act.success() == false &&
                act.code() == UNCOMPLITE_ASSIGNMEN_CODE &&
                act.message() == "Незавершенный оператор присваивания" &&
                act.tokens.size() == 1)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T_15_operator_expected() {
            std::string source =
                "x:=(I + V)X;";

            ParseResult act = lexer.parse(source);

            if (act.success() == false &&
                act.code() == OPERATOR_EXPECTED_CODE &&
                act.message() == "Ожидался оператор" &&
                act.tokens.size() == 6)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T_16_success() {
            std::string source =
                "x:=(IV*MMMDCCXLIV)-II;";

            ParseResult act = lexer.parse(source);

            if (act.success() &&
                act.code() == SUCCESS_CODE &&
                act.tokens.size() == 10 &&
                act.tokens[0].typeCode == TermTypes::IDENTIFIER && act.tokens[0].value == "x" &&
                act.tokens[1].typeCode == TermTypes::ASSIGNMENT && act.tokens[1].value == ":=" &&
                act.tokens[2].typeCode == TermTypes::OPEN_BRACKET && act.tokens[2].value == "(" &&
                act.tokens[3].typeCode == TermTypes::NUMBER && act.tokens[3].value == "IV" &&
                act.tokens[4].typeCode == TermTypes::MULTIPLY && act.tokens[4].value == "*" &&
                act.tokens[5].typeCode == TermTypes::NUMBER && act.tokens[5].value == "MMMDCCXLIV" &&
                act.tokens[6].typeCode == TermTypes::CLOSE_BRACKET && act.tokens[6].value == ")" &&
                act.tokens[7].typeCode == TermTypes::MINUS && act.tokens[7].value == "-" &&
                act.tokens[8].typeCode == TermTypes::NUMBER && act.tokens[8].value == "II" &&
                act.tokens[9].typeCode == TermTypes::SEMICOLON && act.tokens[9].value == ";")
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T_17_success() {
            std::string source =
                "x:=II;\n"
                "y:=IV*x-II; // 6\n"
                "/* x * y = 12 \n"
                "   z = 12 \n"
                "*/\n"
                "z:=x*y;";

            ParseResult act = lexer.parse(source);

            if (act.success() &&
                act.code() == SUCCESS_CODE &&
                act.tokens.size() == 18 &&
                act.tokens[0].typeCode == TermTypes::IDENTIFIER && act.tokens[0].value == "x" &&
                act.tokens[1].typeCode == TermTypes::ASSIGNMENT && act.tokens[1].value == ":=" &&
                act.tokens[2].typeCode == TermTypes::NUMBER && act.tokens[2].value == "II" &&
                act.tokens[3].typeCode == TermTypes::SEMICOLON && act.tokens[3].value == ";" &&
                act.tokens[4].typeCode == TermTypes::IDENTIFIER && act.tokens[4].value == "y" &&
                act.tokens[5].typeCode == TermTypes::ASSIGNMENT && act.tokens[5].value == ":=" &&
                act.tokens[6].typeCode == TermTypes::NUMBER && act.tokens[6].value == "IV" &&
                act.tokens[7].typeCode == TermTypes::MULTIPLY && act.tokens[7].value == "*" &&
                act.tokens[8].typeCode == TermTypes::IDENTIFIER && act.tokens[8].value == "x" &&
                act.tokens[9].typeCode == TermTypes::MINUS && act.tokens[9].value == "-" &&
                act.tokens[10].typeCode == TermTypes::NUMBER && act.tokens[10].value == "II" &&
                act.tokens[11].typeCode == TermTypes::SEMICOLON && act.tokens[11].value == ";" &&
                act.tokens[12].typeCode == TermTypes::IDENTIFIER && act.tokens[12].value == "z" &&
                act.tokens[13].typeCode == TermTypes::ASSIGNMENT && act.tokens[13].value == ":=" &&
                act.tokens[14].typeCode == TermTypes::IDENTIFIER && act.tokens[14].value == "x" &&
                act.tokens[15].typeCode ==  TermTypes::MULTIPLY && act.tokens[15].value == "*" &&
                act.tokens[16].typeCode == TermTypes::IDENTIFIER && act.tokens[16].value == "y" &&
                act.tokens[17].typeCode == TermTypes::SEMICOLON && act.tokens[17].value == ";")
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T_18_success() {
            std::string source =
                "x:=((II * MMM)/VI);";

            ParseResult act = lexer.parse(source);

            if (act.success() &&
                act.code() == SUCCESS_CODE &&
                act.tokens.size() == 12 &&
                act.tokens[0].typeCode == TermTypes::IDENTIFIER && act.tokens[0].value == "x" &&
                act.tokens[1].typeCode == TermTypes::ASSIGNMENT && act.tokens[1].value == ":=" &&
                act.tokens[2].typeCode == TermTypes::OPEN_BRACKET && act.tokens[2].value == "(" &&
                act.tokens[3].typeCode == TermTypes::OPEN_BRACKET && act.tokens[3].value == "(" &&
                act.tokens[4].typeCode == TermTypes::NUMBER && act.tokens[4].value == "II" &&
                act.tokens[5].typeCode == TermTypes::MULTIPLY && act.tokens[5].value == "*" &&
                act.tokens[6].typeCode == TermTypes::NUMBER && act.tokens[6].value == "MMM" &&
                act.tokens[7].typeCode == TermTypes::CLOSE_BRACKET && act.tokens[7].value == ")" &&
                act.tokens[8].typeCode == TermTypes::DIVIDE && act.tokens[8].value == "/" &&
                act.tokens[9].typeCode == TermTypes::NUMBER && act.tokens[9].value == "VI" &&
                act.tokens[10].typeCode == TermTypes::OPEN_BRACKET && act.tokens[10].value == ")" &&
                act.tokens[11].typeCode == TermTypes::SEMICOLON && act.tokens[11].value == ";")
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

    public:

        void run() {
            T__1_empty_file_1();
            T__2_empty_file_2();
            T__3_empty_file_3();
            T__4_empty_file_4();
            T__5_empty_file_5();
            T__6_comment_1();
            T__7_comment_2();
            T__8_comment_3();
            T__9_assignment_1();
            T_10_assignment_2();
            T_11_invalid_char();
            T_12_assignment_expected();
            T_13_invalid_identifier();
            T_14_incomplite_assignment();
            T_15_operator_expected();
            T_16_success();
            T_17_success();
            T_18_success();
        }

        static void s_run() {
            WhiteBox tests;
            tests.run();
            tests.summary("\nWhite Box Symmary:");
        }
    };

    class BlackBox : Test {

    private:
        Lexer lexer = Lexer();

        // Преобразует результат разбора в стандартную строку для дальнейшего
        // сравнения результатов. Если строки равны, то ожидаемый и фактический результат
        // совпадают. 
        static std::string toString(ParseResult parseResult) {
            std::stringstream ss;

            ss << "success: " << (parseResult.success() ? "true" : "false") << "\n";
            if (!parseResult.success()) {
                ss << "error_code: " << parseResult.code() << "\n";
                ss << "message: " << parseResult.message() << "\n";
                ss << "index: " << parseResult.current.head << "\n";
            }
            else
            {
                ss << "tokens:\n";
                for (Token& token : parseResult.tokens) {
                    ss << (int)token.typeCode << " " << token.typeName << " " <<
                        token.value << "\n";
                }
            }
            ss << "\n";

            return ss.str();
        }

        void T__1_success() {
            std::string expected =
                "success: true\n"
                "tokens:\n"
                "1 Идентификатор           x\n"
                "3 Присваивание            :=\n"
                "4 Открывающая скобка      (\n"
                "2 Римское число           IV\n"
                "11 Оператор \"*\"          *\n"
                "2 Римское число           MMMDCCXLIV\n"
                "5 Закрывающая скобка      )\n"
                "10 Оператор \"-\"          -\n"
                "2 Римское число           II\n"
                "7 Разделитель             ;\n\n";

            std::string source =
                "x:=(IV*MMMDCCXLIV)-II;";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (actual == expected)
            {
                PASS();
            }
            else
            {
                std::cout << expected << "\n\n";
                FAIL(&act);
            }
        }

        void T__2_success() {
            // поддержка сложных выражений
            std::string expected =
                "success: true\n"
                "tokens:\n"
                "1 Идентификатор           x\n"
                "3 Присваивание            :=\n"
                "2 Римское число           I\n"
                "7 Разделитель             ;\n"
                "1 Идентификатор           y\n"
                "3 Присваивание            :=\n"
                "2 Римское число           II\n"
                "7 Разделитель             ;\n\n";

            std::string source =
                "x:=I;"
                "y:=II;";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__3_success() {
            // Тест, что однострочный комментарий поддерживается
            std::string expected =
                "success: true\n"
                "tokens:\n"
                "1 Идентификатор           x\n"
                "3 Присваивание            :=\n"
                "2 Римское число           I\n"
                "7 Разделитель             ;\n\n";

            std::string source =
                "x:=I; // комментарий";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__4_success() {
            // Тест, что многострочный комментарий поддерживается
            std::string expected =
                "success: true\n"
                "tokens:\n"
                "1 Идентификатор           x\n"
                "3 Присваивание            :=\n"
                "2 Римское число           I\n"
                "7 Разделитель             ;\n\n";

            std::string source =
                "x:=I; /* многострочный"
                "комментарий */";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__5_success() {
            // Тест, что работает присовение переменных переменным
            std::string expected =
                "success: true\n"
                "tokens:\n"
                "1 Идентификатор           x\n"
                "3 Присваивание            :=\n"
                "2 Римское число           I\n"
                "7 Разделитель             ;\n"
                "1 Идентификатор           y\n"
                "3 Присваивание            :=\n"
                "2 Римское число           II\n"
                "7 Разделитель             ;\n"
                "1 Идентификатор           z\n"
                "3 Присваивание            :=\n"
                "1 Идентификатор           x\n"
                "11 Оператор \"*\"          *\n"
                "1 Идентификатор           y\n"
                "7 Разделитель             ;\n\n";
            std::cout << expected.length() << "\n";
            std::string source =
                "x:=I;\n"
                "y:=II;\n"
                "z:=x*y;";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);
            std::cout << actual.length() << "\n";
            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__6_success() {
            // тест, что работают математические операторы с идентификаторами
            std::string expected =
                "success: true\n"
                "tokens:\n"
                "1 Идентификатор           x\n"
                "3 Присваивание            :=\n"
                "2 Римское число           I\n"
                "7 Разделитель             ;\n"
                "1 Идентификатор           y\n"
                "3 Присваивание            :=\n"
                "2 Римское число           II\n"
                "11 Оператор \"*\"          *\n"
                "1 Идентификатор           x\n"
                "7 Разделитель             ;\n\n";

            std::string source =
                "x:=I;\n"
                "y:=II * x;";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__7_success() {
            // тест, что работают математические операторы с идентификаторами
            std::string expected =
                "success: true\n"
                "tokens:\n"
                "1 Идентификатор           x\n"
                "3 Присваивание            :=\n"
                "2 Римское число           I\n"
                "7 Разделитель             ;\n"
                "1 Идентификатор           y\n"
                "3 Присваивание            :=\n"
                "2 Римское число           II\n"
                "11 Оператор \"*\"          *\n"
                "1 Идентификатор           x\n"
                "7 Разделитель             ;\n\n";

            std::string source =
                "x:=I;\n"
                "y:=II * x;\n";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__8_success() {
            // тест, что работает обрезка пустых символов
            std::string expected =
                "success: true\n"
                "tokens:\n"
                "1 Идентификатор           x\n"
                "3 Присваивание            :=\n"
                "2 Римское число           I\n"
                "7 Разделитель             ;\n\n";

            std::string source =
                "\n\t x:=I; \n \t";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__1_error() {
            std::string expected =
                "success: false\n"
                "error_code: 3\n"
                "message: Неожиданный конец файла\n"
                "index: 2\n\n";

            std::string source =
                "\n";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__2_error() {
            std::string expected =
                "success: false\n"
                "error_code: 3\n"
                "message: Неожиданный конец файла\n"
                "index: 2\n\n";

            std::string source =
                " ";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__3_error() {
            std::string expected =
                "success: false\n"
                "error_code: 3\n"
                "message: Неожиданный конец файла\n"
                "index: 6\n\n";

            std::string source =
                "\n\t \n\t";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__4_error() {
            std::string expected =
                "success: false\n"
                "error_code: 3\n"
                "message: Неожиданный конец файла\n"
                "index: 6\n\n";

            std::string source =
                "\n\t \n\t";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__5_error() {
            std::string expected =
                "success: false\n"
                "error_code: 2\n"
                "message: Недопустимый входной символ\n"
                "index: 4\n\n";

            std::string source =
                "x:=а;";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__6_error() {
            std::string expected =
                "success: false\n"
                "error_code: 5\n"
                "message: Ожидалось присваивание\n"
                "index: 2\n\n";

            std::string source =
                "x+y;";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__7_error() {
            std::string expected =
                "success: false\n"
                "error_code: 6\n"
                "message: Недопустимый формат идентификатора\n"
                "index: 1\n\n";

            std::string source =
                "1x:=I;";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__8_error() {
            std::string expected =
                "success: false\n"
                "error_code: 7\n"
                "message: Незавершенный оператор присваивания\n"
                "index: 3\n\n";

            std::string source =
                "x:I;";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__9_error() {
            std::string expected =
                "success: false\n"
                "error_code: 8\n"
                "message: Ожидалось выражение\n"
                "index: 5\n\n";

            std::string source =
                "x:= /*1*/I;";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__10_error() {
            std::string expected =
                "success: false\n"
                "error_code: 9\n"
                "message: Ожидался оператор\n"
                "index: 7\n\n";

            std::string source =
                "x:=(I)I;";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

        void T__11_error() {
            std::string expected =
                "success: false\n"
                "error_code: 10\n"
                "message: Ожидался идентификатор\n"
                "index: 2\n\n";

            std::string source =
                "I:=y";

            ParseResult act = lexer.parse(source);

            std::string actual = toString(act);

            if (expected == actual)
            {
                PASS();
            }
            else
            {
                FAIL(&act);
            }
        }

    public:
        void run()
        {
            T__1_success();
            T__2_success();
            T__3_success();
            T__4_success();
            T__5_success();
            T__6_success();
            T__7_success();
            T__8_success();

            T__1_error();
            T__2_error();
            T__3_error();
            T__4_error();
            T__5_error();
            T__6_error();
            T__7_error();
            T__8_error();
            T__9_error();
            T__10_error();
            T__11_error();
        }

        static void s_run() {
            BlackBox tests;
            tests.run();
            tests.summary("\nBlack Box Summary: ");
        }

    };

}



//SyntaxTree tree_e;

//void buildTreeCascade(TreeNode* node) {
//
//}

void build_line(SyntaxScanner& scanner) {
    std::string line = "S"; 
    //tree_e.root = tree_e.create(line);
    int term_index_2 = 0;
    
    std::cout << "ПРАВИЛА\n";
    for (int r : scanner.rules) {
        std::cout << r << "\n";
    }
    std::cout << "КОНЕЦ ПРАВИЛА\n";

    for (int i = scanner.rules.size() - 1; i >= 0; --i) {
        std::cout << line << "\n";
        int rule = scanner.rules[i];
        BuildRule buildRule = BUILD_RULES[rule];

        for (auto& lexem : buildRule.items) {
               
        }

        
        //int location = line.find_last_of("S");
        //if (location != -1) {
        //    line.erase(location, 1);
        //    line.insert(location, stringRule);
        //}
    }
    std::cout << line << " \n";

    int term_index = 0;

    for (int i = 0; i <= line.size() - 1; ++i) {
        if (line[i] == 'I' || line[i] == 'R') {
            auto trm = scanner.terms[term_index++];
            line.erase(i, 1);
            line.insert(i, trm);
            i += trm.size();
            std::cout << line << "\n";
        }
    }
    std::cout << line << "\n";
    
    //tree_e.print();
}

int main() {
    setlocale(LC_ALL, "");

    LEX::WhiteBox::s_run();   
    //LEX::BlackBox::s_run();

    LEX::Lexer lexer;
    SyntaxScanner syntax;
    
    //std::string line = "x:=a+((IV+a)+b);";
    //std::string line = "abc:=(a+-(-(VIII+b*a+b)+a)+a);";

    std::string line = "a:=some+-(value*XXIV);";
    
    std::cout << "ВВОД: " << line << "\n";

    auto parseResult = lexer.parse(line);
    
    int index = 0;
    int page = 0;

    std::vector<std::vector<Token>> commands;
    while (index < parseResult.tokens.size()) {
        commands.push_back(std::vector<Token>());
        while (index < parseResult.tokens.size()) {
            commands[page].push_back(parseResult.tokens[index]);           
            if (parseResult.tokens[index].value == ";") {
                commands[page].push_back(Token("К", TermTypes::END_TERMINAL, "К"));
                page += 1;
                index += 1;
                break;
            }
            index += 1;
        }
    }
   

    parseResult.add(Token("К", TermTypes::END_TERMINAL, "К"));
    
    if (parseResult.success()) {
        // TODO: тут нужно разделять токены на подсписки
        // чтобы синтаксический анализатор принимал только конструктцию вида
        // I:=S;
        
        syntax.init(parseResult.tokens);
        syntax.proccess();
        syntax.terms.insert(syntax.terms.cbegin(), parseResult.tokens[0].value);
        
        build_line(syntax);

        //std::string line = "a:=some+-(value*XXIV);";
    }
}