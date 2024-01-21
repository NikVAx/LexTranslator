
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



void unit_for(std::string line, const ParseResult& expected) {
    Parser lexer;
    auto real = lexer.parse(line);
    
    std::cout << "Ожидаемый:" << std::endl;
    if (expected.isSuccess()) {
        for (auto& item : expected.items) {
            std::cout << item << std::endl;
        }
    }
    else {
        std::cout << StatusCodes::LEX_9.toString() << std::endl;
    }
    
    std::cout << "Фактический:" << std::endl;
    if (real.isSuccess()) {
        for (auto& item : real.items) {
            std::cout << item << std::endl;
        }
    }
    else {
        std::cout << real.getError() << std::endl;
    }
    

    bool isEqual = true;

    if (real.items.size() != expected.items.size()) {
        isEqual = false;       
    }

    for (int i = 0; i < real.items.size() && isEqual; ++i) {
        if (real.items[i].token != expected.items[i].token) {
            isEqual = false;
        }
    }

    if (!real.isSuccess() && !expected.isSuccess()) {
        isEqual = true;
    }

    if (isEqual) {
        std::cout << "Результат: ТЕСТ ПРОЙДЕН" << "\n\n";
    }
    else {
        std::cout << "Результат: ТЕСТ ПРОВАЛЕН" << "\n\n";
    }
    
}

void unit_black(std::string line, std::string expected) {
    Parser lexer;
    std::stringstream ss;
    auto parseResult = lexer.parse(line);


    std::cout << "Ожидаемый:" << std::endl;
    std::cout << expected << std::endl;
    

    std::cout << "Фактический:" << std::endl;
    for (auto& item : parseResult.items) {
        std::cout << item << std::endl;
        ss << item << std::endl;
    }

    
    if (expected == ss.str()) {
        std::cout << "Результат: ТЕСТ ПРОЙДЕН" << "\n\n";
    }
    else {
        std::cout << "Результат: ТЕСТ ПРОВАЛЕН" << "\n\n";
    }
}

void units1() {
    unit_for("if a > b then x:=a else x:=b;",
        ParseResult({ 0,0 }, {
        ParseItem(Token("if", TermTypes::IF), StatusCodes::SUCCESS__),
        ParseItem(Token("a", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(">", TermTypes::GREATER), StatusCodes::SUCCESS__),
        ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token("then", TermTypes::THEN), StatusCodes::SUCCESS__),
        ParseItem(Token("x", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
        ParseItem(Token("a", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token("else", TermTypes::ELSE), StatusCodes::SUCCESS__),
        ParseItem(Token("x", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
        ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__),
            }, false));

    unit_for("if a > 100 then b:=1 else if a=1.2e-1 then b:=2 else b:=3.3;",
        ParseResult({ 0,0 }, {
        ParseItem(Token("if", TermTypes::IF), StatusCodes::SUCCESS__),
        ParseItem(Token("a", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(">", TermTypes::GREATER), StatusCodes::SUCCESS__),
        ParseItem(Token("100", TermTypes::NUMBER), StatusCodes::SUCCESS__),
        ParseItem(Token("then", TermTypes::THEN), StatusCodes::SUCCESS__),
        ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
        ParseItem(Token("1", TermTypes::NUMBER), StatusCodes::SUCCESS__),
        ParseItem(Token("else", TermTypes::ELSE), StatusCodes::SUCCESS__),
        ParseItem(Token("if", TermTypes::IF), StatusCodes::SUCCESS__),
        ParseItem(Token("a", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token("=", TermTypes::EQUAL), StatusCodes::SUCCESS__),
        ParseItem(Token("1.2e-1", TermTypes::NUMBER), StatusCodes::SUCCESS__),
        ParseItem(Token("then", TermTypes::THEN), StatusCodes::SUCCESS__),
        ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
        ParseItem(Token("2", TermTypes::NUMBER), StatusCodes::SUCCESS__),
        ParseItem(Token("else", TermTypes::ELSE), StatusCodes::SUCCESS__),
        ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
        ParseItem(Token("3.3", TermTypes::NUMBER), StatusCodes::SUCCESS__),
        ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__),
            }, false));

    unit_for("if a > b then a:=b; //123\n /*123*/\n",
        ParseResult({ 0,0 }, {
        ParseItem(Token("if", TermTypes::IF), StatusCodes::SUCCESS__),
        ParseItem(Token("a", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(">", TermTypes::GREATER), StatusCodes::SUCCESS__),
        ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token("then", TermTypes::THEN), StatusCodes::SUCCESS__),
        ParseItem(Token("a", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
        ParseItem(Token("b", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
        ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__),
            }, false));

    unit_for("if a > b then a :=- b;", ParseResult({ 0,0 }, { }, true));
}

void units2() {
    unit_black("if a > b then x:=a else x:=b;",
        " 17          if             Оператор IF\n"
        "  1           a           Идентификатор\n"
        " 24           >              Оператор >\n"
        "  1           b           Идентификатор\n"
        " 18        then           Оператор THEN\n"
        "  1           x           Идентификатор\n"
        "  3          :=   Оператор присваивания\n"
        "  1           a           Идентификатор\n"
        " 19        else           Оператор ELSE\n"
        "  1           x           Идентификатор\n"
        "  3          :=   Оператор присваивания\n"
        "  1           b           Идентификатор\n"
        "  7           ;         Точка с запятой\n");

    unit_black("if a > 100 then b:=1 else if a=1.2e-1 then b:=2 else b:=3.3;",
        " 17          if             Оператор IF\n"
        "  1           a           Идентификатор\n"
        " 24           >              Оператор >\n"
        "  2         100        Числовой литерал\n"
        " 18        then           Оператор THEN\n"
        "  1           b           Идентификатор\n"
        "  3          :=   Оператор присваивания\n"
        "  2           1        Числовой литерал\n"
        " 19        else           Оператор ELSE\n"
        " 17          if             Оператор IF\n"
        "  1           a           Идентификатор\n"
        " 25           =              Оператор =\n"
        "  2      1.2e-1        Числовой литерал\n"
        " 18        then           Оператор THEN\n"
        "  1           b           Идентификатор\n"
        "  3          :=   Оператор присваивания\n"
        "  2           2        Числовой литерал\n"
        " 19        else           Оператор ELSE\n"
        "  1           b           Идентификатор\n"
        "  3          :=   Оператор присваивания\n"
        "  2         3.3        Числовой литерал\n"
        "  7           ;         Точка с запятой\n");

    unit_black("if a > b then a:=b; //123\n /*123*/\n",
        " 17          if             Оператор IF\n"
        "  1           a           Идентификатор\n"
        " 24           >              Оператор >\n"
        "  1           b           Идентификатор\n"
        " 18        then           Оператор THEN\n"
        "  1           a           Идентификатор\n"
        "  3          :=   Оператор присваивания\n"
        "  1           b           Идентификатор\n"
        "  7           ;         Точка с запятой\n" 
    );
    unit_black("if a > b then a :=- b;", 
        " 17          if             Оператор IF\n"
        "  1           a           Идентификатор\n"
        " 24           >              Оператор >\n"
        "  1           b           Идентификатор\n"
        " 18        then           Оператор THEN\n"
        "  1           a           Идентификатор\n"
        "  0          :=            Неопределено\n"
        );
}

int main() {
    setlocale(LC_ALL, "");
   
    units2();

}
