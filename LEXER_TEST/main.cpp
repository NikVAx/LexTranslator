
#include "../SYNTAX/syntax.cpp"
#include "../SYNTAX/tree_builder.h"
#include "../Core/lexer.h"
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

int main() {
    setlocale(LC_ALL, "");

    Parser lexer;
     
    std::string line = "_assign:=_1+((_2-_x1-x2)+(_3+XX)+(_4+IV));b:=c*(I*-(g+a));";
    
    std::cout << "ВВОД: " << line << "\n";

    auto parseResult = lexer.parse(line);  
    auto commands = MathCommandSplitter()
        .split(parseResult);
    
    for (auto& command : commands) {
        std::cout << "СТАТУС КОМАНДЫ: " << (command.isValid ? "ВЕРНА" : "НЕ ВЕРНА") << "\n";
        for (auto& item : command.tokens) {
            std::cout
                << item.value << "\t"
                << item.termType << "\n"
                ;
        }

        if (command.isValid) {  
            auto scanner = Syntax(MathGrammarConfig);
            auto nodes = scanner.proccess(command);
            //auto tree = TreeBuilder(nodes).build();
            //tree.print();            
        }
    }
}