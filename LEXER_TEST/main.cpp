
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

    Test t = Test();
    t.describe("black box",
        [&](TestUtils utils) {
            utils.it("parse True value", [&](TestDescriptionArgs args) {
                std::string line = "A:=T;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult{
                        Location{ 7, 0 },
                        {
                          ParseItem{Token{"A", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                          ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                          ParseItem{Token{"T", TermTypes::TRUE}, StatusCodes::SUCCESS__ },
                          ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                        },
                        false
                    }
                );
            });
            utils.it("parse False value", [&](TestDescriptionArgs args) {
                std::string line = "A:=F;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult{
                        Location{ 7, 0 },
                        {
                          ParseItem{Token{"A", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                          ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                          ParseItem{Token{"F", TermTypes::TRUE}, StatusCodes::SUCCESS__ },
                          ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                        },
                        false
                    }
                );
            });
            utils.it("parse or operator", [&](TestDescriptionArgs args) {
                std::string line = "A:=T or F;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(12, 0),
                        {
                          ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                          ParseItem(Token("T", TermTypes::TRUE), StatusCodes::SUCCESS__),
                          ParseItem(Token("or", TermTypes::OR), StatusCodes::SUCCESS__),
                          ParseItem(Token("F", TermTypes::FALSE), StatusCodes::SUCCESS__),
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                        },
                        false
                    )
                );
            });
            utils.it("parse and operator", [&](TestDescriptionArgs args) {
                std::string line = "A:=T and F;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(13, 0),
                        {
                          ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                          ParseItem(Token("T", TermTypes::TRUE), StatusCodes::SUCCESS__),
                          ParseItem(Token("and", TermTypes::AND), StatusCodes::SUCCESS__),
                          ParseItem(Token("F", TermTypes::FALSE), StatusCodes::SUCCESS__),
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                        },
                        false
                    )
                );
            });
            utils.it("parse xor operator", [&](TestDescriptionArgs args) {
                std::string line = "A:=T xor F;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(13, 0),
                        {
                          ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                          ParseItem(Token("T", TermTypes::TRUE), StatusCodes::SUCCESS__),
                          ParseItem(Token("xor", TermTypes::XOR), StatusCodes::SUCCESS__),
                          ParseItem(Token("F", TermTypes::FALSE), StatusCodes::SUCCESS__),
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                        },
                        false
                    )
                );
            });
            utils.it("parse not operator", [&](TestDescriptionArgs args) {
                std::string line = "A:= not F;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(12, 0),
                        {
                          ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                          ParseItem(Token("not", TermTypes::NOT), StatusCodes::SUCCESS__),
                          ParseItem(Token("F", TermTypes::FALSE), StatusCodes::SUCCESS__),
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                        },
                        false
                    )
                );
            });
            utils.it("parse identifier operator", [&](TestDescriptionArgs args) {
                std::string line = "A:=c;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(7, 0),
                        {
                          ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                          ParseItem(Token("c", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                        },
                        false
                    )
                );
            });
            utils.it("parse brackets operator", [&](TestDescriptionArgs args) {
                std::string line = "A:=(T or F);";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(14, 0),
                        {
                          ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                          ParseItem(Token("(", TermTypes::OPEN_BRACKET), StatusCodes::SUCCESS__),
                          ParseItem(Token("T", TermTypes::TRUE), StatusCodes::SUCCESS__),
                          ParseItem(Token("or", TermTypes::OR), StatusCodes::SUCCESS__),
                          ParseItem(Token("F", TermTypes::FALSE), StatusCodes::SUCCESS__),
                          ParseItem(Token(")", TermTypes::CLOSE_BRACKET), StatusCodes::SUCCESS__),
                          ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                        },
                        false
                    )
                );
            });
            utils.it("parse invalid assigment", [&](TestDescriptionArgs args) {
                std::string line = "A:B;";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(3, 0),
                        {
                          ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                          ParseItem(Token(":", TermTypes::UNDEFINED), StatusCodes::LEX_1)
                        },
                        true
                    )
                );
            });
            utils.it("parse comment", [&](TestDescriptionArgs args) {
                std::string line = "A:=T;//TRUE";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(13, 0),
                        {
                          ParseItem{Token{"A", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                          ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                          ParseItem{Token{"T", TermTypes::TRUE}, StatusCodes::SUCCESS__ },
                          ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                        },
                        false
                    )
                );
            });
            utils.it("parse multiline comment", [&](TestDescriptionArgs args) {
                std::string line = "A:=T;/*\nTRUE\n*/";
                auto parseResult = lexer.parse(line);
                args.c_u.are_equal(parseResult,
                    ParseResult(
                        Location(17, 0),
                        {
                          ParseItem{Token{"A", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                          ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                          ParseItem{Token{"T", TermTypes::TRUE}, StatusCodes::SUCCESS__ },
                          ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                        },
                        false
                    )
                );
            });
        });

    t.describe("White box", [&](TestUtils utils) {
        utils.it("parse True value", [&](TestDescriptionArgs args) {
            std::string line = "A:=T;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult{
                    Location{ 7, 0 },
                    {
                      ParseItem{Token{"A", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                      ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                      ParseItem{Token{"T", TermTypes::TRUE}, StatusCodes::SUCCESS__ },
                      ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                    },
                    false
            };
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
        utils.it("parse False value", [&](TestDescriptionArgs args) {
            std::string line = "A:=F;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult{
                    Location{ 7, 0 },
                    {
                      ParseItem{Token{"A", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                      ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                      ParseItem{Token{"F", TermTypes::TRUE}, StatusCodes::SUCCESS__ },
                      ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                    },
                    false
            };
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
        utils.it("parse or operator", [&](TestDescriptionArgs args) {
            std::string line = "A:=T or F;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(12, 0),
                {
                  ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                  ParseItem(Token("T", TermTypes::TRUE), StatusCodes::SUCCESS__),
                  ParseItem(Token("or", TermTypes::OR), StatusCodes::SUCCESS__),
                  ParseItem(Token("F", TermTypes::FALSE), StatusCodes::SUCCESS__),
                  ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
        utils.it("parse and operator", [&](TestDescriptionArgs args) {
            std::string line = "A:=T and F;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(13, 0),
                {
                  ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                  ParseItem(Token("T", TermTypes::TRUE), StatusCodes::SUCCESS__),
                  ParseItem(Token("and", TermTypes::AND), StatusCodes::SUCCESS__),
                  ParseItem(Token("F", TermTypes::FALSE), StatusCodes::SUCCESS__),
                  ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
        utils.it("parse xor operator", [&](TestDescriptionArgs args) {
            std::string line = "A:=T xor F;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(13, 0),
                {
                  ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                  ParseItem(Token("T", TermTypes::TRUE), StatusCodes::SUCCESS__),
                  ParseItem(Token("xor", TermTypes::XOR), StatusCodes::SUCCESS__),
                  ParseItem(Token("F", TermTypes::FALSE), StatusCodes::SUCCESS__),
                  ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
        utils.it("parse not operator", [&](TestDescriptionArgs args) {
            std::string line = "A:= not F;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(12, 0),
                {
                  ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                  ParseItem(Token("not", TermTypes::NOT), StatusCodes::SUCCESS__),
                  ParseItem(Token("F", TermTypes::FALSE), StatusCodes::SUCCESS__),
                  ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
        utils.it("parse identifier operator", [&](TestDescriptionArgs args) {
            std::string line = "A:=c;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(7, 0),
                {
                  ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                  ParseItem(Token("c", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
        utils.it("parse brackets operator", [&](TestDescriptionArgs args) {
            std::string line = "A:=(T or F);";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(14, 0),
                {
                  ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":=", TermTypes::ASSIGNMENT), StatusCodes::SUCCESS__),
                  ParseItem(Token("(", TermTypes::OPEN_BRACKET), StatusCodes::SUCCESS__),
                  ParseItem(Token("T", TermTypes::TRUE), StatusCodes::SUCCESS__),
                  ParseItem(Token("or", TermTypes::OR), StatusCodes::SUCCESS__),
                  ParseItem(Token("F", TermTypes::FALSE), StatusCodes::SUCCESS__),
                  ParseItem(Token(")", TermTypes::CLOSE_BRACKET), StatusCodes::SUCCESS__),
                  ParseItem(Token(";", TermTypes::SEMICOLON), StatusCodes::SUCCESS__)
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
        utils.it("parse invalid assigment", [&](TestDescriptionArgs args) {
            std::string line = "A:B;";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(3, 0),
                {
                  ParseItem(Token("A", TermTypes::IDENTIFIER), StatusCodes::SUCCESS__),
                  ParseItem(Token(":", TermTypes::UNDEFINED), StatusCodes::LEX_1)
                },
                true
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
        utils.it("parse comment", [&](TestDescriptionArgs args) {
            std::string line = "A:=T;//TRUE";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(13, 0),
                {
                  ParseItem{Token{"A", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                  ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                  ParseItem{Token{"T", TermTypes::TRUE}, StatusCodes::SUCCESS__ },
                  ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
        utils.it("parse multiline comment", [&](TestDescriptionArgs args) {
            std::string line = "A:=T;/*\nTRUE\n*/";
            auto parseResult = lexer.parse(line);
            ParseResult expected = ParseResult(
                Location(17, 0),
                {
                  ParseItem{Token{"A", TermTypes::IDENTIFIER}, StatusCodes::SUCCESS__},
                  ParseItem{Token{":=", TermTypes::ASSIGNMENT}, StatusCodes::SUCCESS__},
                  ParseItem{Token{"T", TermTypes::TRUE}, StatusCodes::SUCCESS__ },
                  ParseItem{Token{ ";", TermTypes::SEMICOLON }, StatusCodes::SUCCESS__}
                },
                false
            );
            args.c_u.are_equal(parseResult, expected);
            std::cout << "\nФактический: " << parseResult << "\nОжидаемый: " << expected;
        });
    });
}
