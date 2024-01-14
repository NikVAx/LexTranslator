
#include "../Core/command.h"
#include "../Core/command_splitter.h"
#include "../Core/current_config.h"
#include "../Core/lexer.h"
#include "../Core/parse_item.h"
#include "../Core/parse_result.h"
#include "../Core/ref_value.h"
#include "../Core/syntax_tree_builder.h"
#include "../Core/syntax_tree_by_char_builder.h"
#include "../Core/token.h"

#include "../SYNTAX/syntax.h"


#include "../Core/operators_tree_builder.h"
#include "../Core/triads_builder.h"

#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include "../Core/triadopt2.h"

static void print_triads(std::list<Triad*>& triads) {
    for (Triad* triad : triads) {
        std::cout 
            << " | " 
            << std::setw(2) << (triad->id)    << "  | " 
            << triad->toString()  << " \n";
    }
}



struct ReNode {
    int value;
    std::vector<ReNode> nodes;
};


std::list<Triad*> prepare_triads(std::string line) {
    Parser lexer;
    std::cout << "ВХОДНЫЕ ДАННЫЕ:\n"
        << std::string(32, '-') << "\n"
        << line << ""
        << std::string(32, '-') << "\n";
    std::cout << "Фактический вывод:\n";
    std::cout << "Список триад:\n";

    auto parseResult = lexer.parse(line);

    auto commands = MathCommandSplitter().split(parseResult);

    int tCount = 0;

    std::list<Triad*> triads__;

    for (auto& command : commands) {
        if (command.isValid) {
            Syntax syntax = Syntax(CurrentSyntaxConfig);
            SyntaxResult syntaxResult = syntax.proccess(command);

            std::list<SyntaxNode> ruleNodes2 = syntaxResult.nodes;

            RefTree<RefValue> myTreeRefView;

            SyntaxTreeByCharBuilder(myTreeRefView)
                .build(ruleNodes2, command.getValueTokens());
            OperatorsTreeBuilder(myTreeRefView)
                .build();
            std::list<Triad*> triads = TriadBuilderV2(myTreeRefView)
                .build(tCount);

            tCount += triads.size();

            for (Triad* triad : triads) {
                triads__.push_back(triad);
            }
        }
    }
    return triads__;
}


std::string triads_to_string(std::list<Triad*>& triads, bool showDep = false, bool isShowConst = false) {
    std::stringstream ss;

    for (Triad* triad : triads) {
        ss
            << " | "
            << std::setw(2) << (triad->id) << "  | "
            << std::setw(18) << triad->toString(); 
        if (showDep) {
            ss << " DEP=" << triad->dep;
        }

        ss << " \n";
    }

    return ss.str();
}

class BlackBoxTriads {
public:

    std::string base_test(std::string input) {
        std::list<Triad*> triads = prepare_triads(input); 
        std::string table1 = triads_to_string(triads);
        
        TriadOpt1(triads).reduce();
        std::string table2 = triads_to_string(triads);
        
        TriadOpt2 triadOpt2(triads);
        triadOpt2.setDepValues();
        triadOpt2.clearSameTriads();
        std::string table3 = triads_to_string(triads);

        return
            "Список триад:\n" + table1 +
            "После свертки:\n" + table2 +
            "Без лишних операций:\n" + table3;
    }

    int N = 1;

    void test1() {
        std::cout << "Тест # " << N << "\n\n";

        std::string input = "a:=X;\n"
                            "b:=X+I-I;\n";
        std::string expected = "Список триад:\n"
                               " |  1  |  := ( a, X ); \n"
                               " |  2  |   + ( X, I ); \n"
                               " |  3  |   - ( ^2, I ); \n"
                               " |  4  |  := ( b, ^3 ); \n"
                               "После свертки:\n"
                               " |  1  |  := ( a, X ); \n"
                               " |  2  |  := ( b, X ); \n"
                               "Без лишних операций:\n"
                               " |  1  |  := ( a, X ); \n"
                               " |  2  |  := ( b, X ); \n";
        std::string actual =  base_test(input);

        std::cout << "Фактический вывод:\n" << actual << "\n";
        std::cout << "Ожидаемый вывод:\n" << expected << "\n";

        if (actual == expected) {
            std::cout << "Тест # " << N++ << " пройден!\n\n";
        }
        else {
            std::cout << "Тест # " << N++ << " пройден!\n\n";
        }
    }

    void test2() {
        std::cout << "Тест # " << N << "\n\n";

        std::string input = "a:=nil;\n"
                            "b:=a-I;\n"
                            "c:=V*(a-I);\n"
                            "a:=(a-I)+(a-I);\n"
                            "d:=a-I;\n";

        std::string expected = "Список триад:\n"
            " |  1  |  := ( a, nil ); \n"
            " |  2  |   - ( a, I ); \n"
            " |  3  |  := ( b, ^2 ); \n"
            " |  4  |   - ( a, I ); \n"
            " |  5  |   * ( V, ^4 ); \n"
            " |  6  |  := ( c, ^5 ); \n"
            " |  7  |   - ( a, I ); \n"
            " |  8  |   - ( a, I ); \n"
            " |  9  |   + ( ^8, ^7 ); \n"
            " | 10  |  := ( a, ^9 ); \n"
            " | 11  |   - ( a, I ); \n"
            " | 12  |  := ( d, ^11 ); \n"
            "После свертки:\n"
            " |  1  |  := ( a, nil ); \n"
            " |  2  |   - ( a, I ); \n"
            " |  3  |  := ( b, ^2 ); \n"
            " |  4  |   - ( a, I ); \n"
            " |  5  |   * ( V, ^4 ); \n"
            " |  6  |  := ( c, ^5 ); \n"
            " |  7  |   - ( a, I ); \n"
            " |  8  |   - ( a, I ); \n"
            " |  9  |   + ( ^8, ^7 ); \n"
            " | 10  |  := ( a, ^9 ); \n"
            " | 11  |   - ( a, I ); \n"
            " | 12  |  := ( d, ^11 ); \n"
            "Без лишних операций:\n"
            " |  1  |  := ( a, nil ); \n"
            " |  2  |   - ( a, I ); \n"
            " |  3  |  := ( b, ^2 ); \n"
            " |  4  |   * ( V, ^2 ); \n"
            " |  5  |  := ( c, ^4 ); \n"
            " |  6  |   + ( ^2, ^2 ); \n"
            " |  7  |  := ( a, ^6 ); \n"
            " |  8  |   - ( a, I ); \n"
            " |  9  |  := ( d, ^8 ); \n";
        std::string actual = base_test(input);

        std::cout << "Фактический вывод:\n" << actual << "\n";
        std::cout << "Ожидаемый вывод:\n" << expected << "\n";

        if (actual == expected) {
            std::cout << "Тест # " << N++ << " пройден!\n\n";
        }
        else {
            std::cout << "Тест # " << N++ << " провален!\n\n";
        }
    }

    void roman_number_owerflow() {
        std::cout << "Тест # " << N << "\n\n";

        std::string input = "a:=X-M;\n";
        std::string expected = "Семантическая ошибка: \nПереполнение типа 'Римское число' [1-3999] при выполнении операции: `X - M`";
        std::string actual;

        std::list<Triad*> triads = prepare_triads(input);
        std::string table1 = triads_to_string(triads);
        
        TriadOpt1 triadOpt1(triads);

        triadOpt1.reduce();

        if (triadOpt1.error) {
            actual = triadOpt1.message;
        }
        else {
            actual = base_test(input);
        }
        
        std::cout << "Фактический вывод:\n  " << actual << "\n";
        std::cout << "Ожидаемый вывод:\n  " << expected << "\n";

        if (actual == expected) {
            std::cout << "Тест # " << N++ << " пройден!\n\n";
        }
        else {
            std::cout << "Тест # " << N++ << " провален!\n\n";
        }
    }

    void run() {
        test1();
        test2();
        roman_number_owerflow();
    }

    static void s_run() {
        BlackBoxTriads bbt;
        bbt.run();
    }

};

class WhiteBoxTriads {
public:

    std::string base_test(std::string input) {
        
        std::list<Triad*> triads = prepare_triads(input);
        std::string table1 = triads_to_string(triads);
        
        
        TriadOpt1(triads).reduce();
        TriadOpt2 triadOpt2(triads);
        triadOpt2.setDepValues();
        std::cout << "После свертки:\n";
        std::string table2 = triads_to_string(triads, true);

        triadOpt2.clearSameTriads();
        std::string table3 = triads_to_string(triads);

        return "Без лишних операций:\n" + table3;
    }

    int N = 1;

    void test1() {
        std::cout << "Тест # " << N << "\n\n";

        std::string input =
            "a:=nil;\n"
            "b:=a-I+(I+II+III);\n"
            "c:=V*(a-I);\n"
            "a:=(a-I)+(a-I)*(II*III);\n"
            "d:=a-I;\n";

        std::string expected = 
            "Список триад:\n"
            " |  1  |  := ( a, X ); \n"
            " |  2  |   + ( X, I ); \n"
            " |  3  |   - ( ^2, I ); \n"
            " |  4  |  := ( b, ^3 ); \n"
            "После свертки:\n"
            " |  1  |  := ( a, X ); \n"
            " |  2  |  := ( b, X ); \n"
            "Без лишних операций:\n"
            " |  1  |  := ( a, X ); \n"
            " |  2  |  := ( b, X ); \n";

        

        std::string actual = base_test(input);
        std::cout << actual << "\n";
        
        //std::cout << "Ожидаемый вывод:\n" << expected << "\n";

        if (actual == expected) {
            std::cout << "Тест # " << N++ << " пройден!\n\n";
        }
        else {
            std::cout << "Тест # " << N++ << " провален!\n\n";
        }
    }

    void run() {
        test1();
    }

    static void s_run() {
        WhiteBoxTriads bbt;
        bbt.run();
    }
};

int main() {
    setlocale(LC_ALL, "");
    
    Parser lexer;

    std::string line = "for (a := 0; a < 10; a) do";
    
    auto parseResult = lexer.parse(line);

    for (auto item : parseResult.items) {
        std::cout << item << std::endl;
    }

}