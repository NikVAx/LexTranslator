
#include "../LEXER/lexer.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace Shared;

namespace LexAnalizer {
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
            std::cout << "location.index: " << act.current.index << "\n";
            std::cout << "location.row: " << act.current.row << "\n";
            std::cout << "location.column: " << act.current.column << "\n";
            std::cout << "tokens.size: " << act.tokens.size() << "\n";
            for (auto& token : act.tokens) {
                std::cout << token.value << "\t" << token.typeCode << "\t" << token.typeName << "\n";
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
                act.tokens[0].value == "x" && act.tokens[0].typeCode == 1 &&
                act.tokens[1].value == ":=" &&
                act.tokens[2].value == "X" &&
                act.tokens[3].value == ";" &&
                act.tokens[4].value == "y" && act.tokens[0].typeCode == 1 &&
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
                act.tokens[0].typeCode == 1 && act.tokens[0].value == "x" &&
                act.tokens[1].typeCode == 3 && act.tokens[1].value == ":=" &&
                act.tokens[2].typeCode == 4 && act.tokens[2].value == "(" &&
                act.tokens[3].typeCode == 2 && act.tokens[3].value == "IV" &&
                act.tokens[4].typeCode ==11 && act.tokens[4].value == "*" &&
                act.tokens[5].typeCode == 2 && act.tokens[5].value == "MMMDCCXLIV" &&
                act.tokens[6].typeCode == 5 && act.tokens[6].value == ")" &&
                act.tokens[7].typeCode ==10 && act.tokens[7].value == "-" &&
                act.tokens[8].typeCode == 2 && act.tokens[8].value == "II" &&
                act.tokens[9].typeCode == 7 && act.tokens[9].value == ";")
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
                act.tokens[0].typeCode == 1 && act.tokens[0].value == "x" &&
                act.tokens[1].typeCode == 3 && act.tokens[1].value == ":=" &&
                act.tokens[2].typeCode == 2 && act.tokens[2].value == "II" &&
                act.tokens[3].typeCode == 7 && act.tokens[3].value == ";" &&
                act.tokens[4].typeCode == 1 && act.tokens[4].value == "y" &&
                act.tokens[5].typeCode == 3 && act.tokens[5].value == ":=" &&
                act.tokens[6].typeCode == 2 && act.tokens[6].value == "IV" &&
                act.tokens[7].typeCode ==11 && act.tokens[7].value == "*" &&
                act.tokens[8].typeCode == 1 && act.tokens[8].value == "x" &&
                act.tokens[9].typeCode ==10 && act.tokens[9].value == "-" &&
                act.tokens[10].typeCode == 2 && act.tokens[10].value == "II" &&
                act.tokens[11].typeCode == 7 && act.tokens[11].value == ";" &&
                act.tokens[12].typeCode == 1 && act.tokens[12].value == "z" &&
                act.tokens[13].typeCode == 3 && act.tokens[13].value == ":=" &&
                act.tokens[14].typeCode == 1 && act.tokens[14].value == "x" &&
                act.tokens[15].typeCode ==11 && act.tokens[15].value == "*" &&
                act.tokens[16].typeCode == 1 && act.tokens[16].value == "y" &&
                act.tokens[17].typeCode == 7 && act.tokens[17].value == ";")
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
                act.tokens[0].typeCode == 1 && act.tokens[0].value == "x" &&
                act.tokens[1].typeCode == 3 && act.tokens[1].value == ":=" &&
                act.tokens[2].typeCode == 4 && act.tokens[2].value == "(" &&
                act.tokens[3].typeCode == 4 && act.tokens[3].value == "(" &&
                act.tokens[4].typeCode == 2 && act.tokens[4].value == "II" &&
                act.tokens[5].typeCode == 11 && act.tokens[5].value == "*" &&
                act.tokens[6].typeCode == 2 && act.tokens[6].value == "MMM" &&
                act.tokens[7].typeCode == 5 && act.tokens[7].value == ")" &&
                act.tokens[8].typeCode == 12 && act.tokens[8].value == "/" &&
                act.tokens[9].typeCode == 2 && act.tokens[9].value == "VI" &&
                act.tokens[10].typeCode == 5 && act.tokens[10].value == ")" &&
                act.tokens[11].typeCode == 7 && act.tokens[11].value == ";")
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
                ss << "index: " << parseResult.current.index << "\n";
            }
            else
            {
                ss << "tokens:\n";
                for (Shared::Token& token : parseResult.tokens) {
                    ss << token.typeCode << " " << token.typeName << " " <<
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

            if (expected == actual)
            {
                PASS();
            }
            else
            {
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

//char OPER_MTX[11][11] = {
//    
//}
//
//class SyntaxScanner
//{
//
//
//
//
//};

int main() {
    setlocale(LC_ALL, "");

    LexAnalizer::WhiteBox::s_run();
    
    LexAnalizer::BlackBox::s_run();
}
