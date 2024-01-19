
#include "../Core/lexer.h"
#include "../Core/token.h"
#include "../Core/command_splitter.h"
#include "../Core/command.h"
#include "../Core/parse_result.h"
#include "../Core/parse_item.h"
#include "../Core/current_config.h"
#include "../Core/syntax_tree_builder.h"
#include "../Core/ref_value.h"
#include "../Core/syntax_tree_by_char_builder.h"

#include "../SYNTAX/syntax.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include "../Core/operators_tree_builder.h"

class TestError {
public:
    std::string message;
    int code;
    TestError(int code, std::string message) : code(code), message(message) {}
};

class StreamUtils {
    std::stringbuf sbuf;
    std::streambuf* oldbuf;

    void update_state() {
        this->sbuf = std::stringbuf(std::ios::out);
        this->oldbuf = std::cout.rdbuf(std::addressof(this->sbuf));
    }

public:
    void capture_stream() {
        this->update_state();
    }
    bool out_stream_to_be(std::string expect) {

        std::cout.rdbuf(this->oldbuf);

        std::string output = this->sbuf.str();

        return output == expect;
    }
};



class CompareUtils {
private:
    TestError ERROR = TestError(1, "Invalid type");
public:
    template<class C1>
    void are_equal(C1 c1, C1 c2){    
        try {
            bool equal = c1 == c2;
            if (!equal) throw ERROR;
            std::cout << "Успешно";
        }
        catch (TestError& error) {
            std::cout << "Ошибка: " << error.message << "\n";
            std::cout << "Фактический результат: \n" << c1 << "\nОжидаемый результат: " << "\n" << c2 << "\n";
        }
        catch (...) {
            std::cout << "Неизвестная ошибка: \n";
            std::cout << "Фактический результат: \n" << c1 << "\nОжидаемый результат: " << "\n" << c2 << "\n";
        }
    }
};

class TestDescriptionArgs {
public:
    StreamUtils s_u = StreamUtils();
    CompareUtils c_u = CompareUtils();
};

class TestUtils {
public:
    void it(std::string testName, std::function<void(TestDescriptionArgs utils)> description) {
        std::cout << testName << ": ";
        description(TestDescriptionArgs());
        std::cout << "\n";
    }
};

class Test {
public:
    void describe(std::string testName, std::function<void(TestUtils utils)> description) {
        std::cout << "------------------ start " << testName << "------------------\n";
        description(TestUtils());
        std::cout << "------------------ end " << testName << "------------------\n";
        std::cout << "\n";
    }
};


int main() {
    setlocale(LC_ALL, "");

    Parser lexer;

    std::cout << "TEST #1" << std::endl;
    std::string testline_1 =
        "A:= 6.1;";
    
    auto parseResult = lexer.parse(testline_1);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }

    std::cout << "TEST #2" << std::endl;
    std::string testline_2 =
        "A:= 0;";

    parseResult = lexer.parse(testline_2);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }

    std::cout << "TEST #3" << std::endl;
    std::string testline_3 =
        "A:= 4.55;";

    parseResult = lexer.parse(testline_3);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }

    std::cout << "TEST #4" << std::endl;
    std::string testline_4 =
        "A:=10.5e-3 < 10.5e+3;";

    parseResult = lexer.parse(testline_4);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }

    std::cout << "TEST #5" << std::endl;
    std::string testline_5 =
        "A:= 65.358e+10;";

    parseResult = lexer.parse(testline_5);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }

    std::cout << "TEST #6" << std::endl;
    std::string testline_6 =
        "if A > B then A:= B;";

    parseResult = lexer.parse(testline_6);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }

    std::cout << "TEST #7" << std::endl;
    std::string testline_7 =
        "if A < B then A:= B else B:= A";

    parseResult = lexer.parse(testline_7);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }

    std::cout << "TEST #8" << std::endl;
    std::string testline_8 =
        "A:=25.36e-9;";

    parseResult = lexer.parse(testline_8);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }

    std::cout << "TEST #9" << std::endl;
    std::string testline_9 =
        "A:=0.e+8;";

    parseResult = lexer.parse(testline_9);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }

    std::cout << "TEST #10" << std::endl;
    std::string testline_10 =
        "A:=5.6;" 
        "// comment ";

    parseResult = lexer.parse(testline_10);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }

    std::cout << "TEST #11" << std::endl;
    std::string testline_11 =
        "A:=5.6; /* comment */ ";

    parseResult = lexer.parse(testline_11);
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
    }
}
