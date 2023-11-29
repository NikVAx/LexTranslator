
#include "../LEXER/lexer.h"
#include "../Core/token.h"


#include "../SYNTAX/syntax.cpp"
#include "../SYNTAX/tree_builder.h"
#include "../Utils/utils.h"
#include "../SYNTAX/command.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <functional>
#include <algorithm>
#include <string>

#include "../Utils/utils.h"



void build_line(SyntaxScanner& scanner) {
    std::string line = "S"; 
    int term_index_2 = 0;
    
    std::cout << "ПРАВИЛА\n";
    for (SyntaxNode r : scanner.rules) {
        std::cout << r << "\n";
    }
    std::cout << "КОНЕЦ ПРАВИЛА\n";
}



std::vector<Command> splitCommands(ParseResult& parseResult) {
    int index = 0;

    std::vector<Command> commands;
    
    while (index < parseResult.items.size()) {
        Command command;
        while (index < parseResult.items.size()) {
            if (!parseResult.items[index].isValid()) {
                command.isValid = false;
            }
                 
            command.tokens.push_back(parseResult.items[index].token);
            if (parseResult.items[index].token.value == ";") {
                command.tokens.push_back(Token("К", TermTypes::END_TERMINAL));
                index += 1;
                break;
            }
            index += 1;
        }
        commands.push_back(command);
    }
    return commands;
}

int main() {
    setlocale(LC_ALL, "");

    Lexer lexer;
     
    //std::string line = "x:=a+((IV+a)+b);";
    //std::string line = "abc:=(a+-(-(VIII+b*a+b)+a)+a);";

    std::string line = "_assign:=_1+((_2*XXIV)+(_3+XX)+(_4+IV));b:=c*(I*-(g+a));";
    
    std::cout << "ВВОД: " << line << "\n";

    auto parseResult = lexer.parse(line);  

    auto commands = splitCommands(parseResult);
    
    for (auto& command : commands) {

        std::cout << "СТАТУС КОМАНДЫ: " << (command.isValid ? "ВЕРНА" : "НЕ ВЕРНА") << "\n";

        for (auto& item : command.tokens) {
            std::cout
                << item.value << "\t"
                << item.typeCode << "\n"
                ;
        }

        if (command.isValid) {
            SyntaxScanner syntax(MATH_MATRIX);
            syntax.init(command);
            syntax.proccess();

            build_line(syntax);

            auto tree = TreeBuilder(syntax.rules).build();
            std::cout << "TREE" << std::endl;
            tree.print();            
        }
    }
}