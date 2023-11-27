
#include "../LEXER/lexer.h"
#include "../LEXER/token.h"
#include "../SYNTAX/syntax.cpp";
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

namespace LEX {
    
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
                command.tokens.push_back(Token("К", TermTypes::END_TERMINAL, "К"));
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

    //LEX::WhiteBox::s_run();   
    //LEX::BlackBox::s_run();

    LEX::Lexer lexer;
    
    
    //std::string line = "x:=a+((IV+a)+b);";
    //std::string line = "abc:=(a+-(-(VIII+b*a+b)+a)+a);";

    std::string line = "a:=some+((value*XXIV)+(value+XX)+(value+IV));b:=c*(I*-(g+a));";
    
    std::cout << "ВВОД: " << line << "\n";

    auto parseResult = lexer.parse(line);  

    auto commands = splitCommands(parseResult);
    
    if (parseResult.success()) {        
        for (auto& command : commands) {
            SyntaxScanner syntax;
            syntax.init(command);
            syntax.proccess();

            build_line(syntax);

            auto tree = TreeBuilder(syntax.rules).build();
            std::cout << "TREE" << std::endl;
            tree.print();
        }
    }
}