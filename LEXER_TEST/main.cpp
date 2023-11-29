
#include "../Core/lexer.h"
#include "../SYNTAX/syntax.cpp"
#include "../SYNTAX/tree_builder.h"
#include "../SYNTAX/relation_matrix_configuration.h"
#include "../Core/token.h"
#include "../Core/command_splitter.h"
#include "../Core/command.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <functional>
#include <algorithm>
#include <string>

void build_line(SyntaxScanner& scanner) {
    std::string line = "S"; 
    int term_index_2 = 0;
    
    std::cout << "ПРАВИЛА\n";
    for (SyntaxNode r : scanner.syntaxNodes) {
        std::cout << r << "\n";
    }
    std::cout << "КОНЕЦ ПРАВИЛА\n";
}

int main() {
    setlocale(LC_ALL, "");

    Lexer lexer;
     
    std::string line = "_assign:=_1+((_2*XXIV)+(_3+XX)+(_4+IV));b:=c*(I*-(g+a));";
    
    std::cout << "ВВОД: " << line << "\n";

    auto parseResult = lexer.parse(line);  

    auto commands = CommandSplitter().split(parseResult);
    
    for (auto& command : commands) {

        std::cout << "СТАТУС КОМАНДЫ: " << (command.isValid ? "ВЕРНА" : "НЕ ВЕРНА") << "\n";
        for (auto& item : command.tokens) {
            std::cout
                << item.value << "\t"
                << item.termType << "\n"
                ;
        }

        if (command.isValid) {         
            auto syntaxNodes = SyntaxScanner(MATH_MATRIX)
                .build(command)
                .proccess();           

            auto tree = TreeBuilder(syntaxNodes)
                .build();

            tree.print();            
        }
    }
}