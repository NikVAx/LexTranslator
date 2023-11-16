
#include "../LEXER/lexer.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace LexAnalizer {
    class BlackBox {
        int N = 1;

        void PASS() { std::cout << std::setw(3) << N++ << ": PASS" << std::endl; }
        void FAIL() { std::cout << std::setw(3) << N++ << ": FAIL" << std::endl; }
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

        static const int SUCCESS_CODE = 0;
        static const int END_OF_FILE_CODE = 3;
        static const int EXPRESSION_EXPECTED_CODE = 8;
        
        Lexer lexer;

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

        void empty_file_1() 
        {
            if (is_unexpected_eof("  ") == true) 
            {
                PASS();
            }
            else {
                FAIL();
            }
        }

        void empty_file_2() 
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

        void empty_file_3() 
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

        void empty_file_4() 
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

        void empty_file_5() 
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
        void comment_1() 
        {
            std::string source =
                "x:=X; //комментарий";
            
            ParseResult act = lexer.parse(source);
            
            if (act.success() &&
                act.code() == SUCCESS_CODE  &&
                act.tokens[0].value == "x"  &&
                act.tokens[1].value == ":=" &&
                act.tokens[2].value == "X"  &&
                act.tokens[3].value == ";") 
            {
                PASS();
            }
            else 
            {
                std::cout << act.code() << "\n";

                FAIL();
            }
        }

        // Тест, что многострочный комментарий не добавляется в таблицу лексем
        void comment_2() 
        {
            std::string source =
                "x:=X; /* текст комментарий\n"
                " текст комментарий на строке №2*/\n"
                "y:=X;";

            ParseResult act = lexer.parse(source);

            if (act.success() == true &&
                act.code() == SUCCESS_CODE  &&
                act.tokens[0].value == "x"  && act.tokens[0].typeCode == 1 &&
                act.tokens[1].value == ":=" &&
                act.tokens[2].value == "X"  &&
                act.tokens[3].value == ";"  &&
                act.tokens[4].value == "y"  &&
                act.tokens[5].value == ":=" &&
                act.tokens[6].value == "X"  &&
                act.tokens[7].value == ";")
            {
                PASS();
            }
            else
            {
                FAIL();
            }
        }

        // Тест, что комментарий НЕ может находится в середине операции
        void comment_3() {
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
                FAIL();
            }
        }

        // Тест, что можно присваивать значение идентификатору
        void assignment_1() {
            std::string source =
                "x:=X;";

            ParseResult act = lexer.parse(source);

            if (act.success() &&
                act.code() == SUCCESS_CODE &&
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

                FAIL();
            }
        }

    public:
        BlackBox()
            : lexer()
        { }

        void run() {
            empty_file_1();
            empty_file_2();
            empty_file_3();
            empty_file_4();
            empty_file_5();

            comment_1();
            comment_2();
            comment_3();
           
        }

        static void s_run() {
            BlackBox tests;
            tests.run();
        }
    };
}

int main() {
    setlocale(LC_ALL, "");
    LexAnalizer::BlackBox::s_run();
}
