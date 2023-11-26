
#include "../LEXER/lexer.h"
#include "../SYNTAX/syntax.cpp";
#include "../Utils/utils.h"
#include "../LEXER/ParseResult.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <functional>
#include <algorithm>



void build_line(SyntaxScanner& scanner) {
    std::string line = "S"; 
    int term_index_2 = 0;
    
    std::cout << "ПРАВИЛА\n";
    for (int r : scanner.rules) {
        std::cout << r << "\n";
    }
    std::cout << "КОНЕЦ ПРАВИЛА\n";

    for (int i = scanner.rules.size() - 1; i >= 0; --i) {
        
        std::cout << line << " <--\n";
        
        int rule = scanner.rules[i];
        
        BuildRule buildRule = BUILD_RULES[rule];

        for (auto& lexem : buildRule.items) {
               
        }

        
        //int location = line.find_last_of("S");
        //if (location != -1) {
        //    line.erase(location, 1);
        //    line.insert(location, stringRule);
        //}
    }
    std::cout << line << " \n";

    int term_index = 0;

    for (int i = 0; i <= line.size() - 1; ++i) {
        if (line[i] == 'I' || line[i] == 'R') {
            auto trm = scanner.terms[term_index++];
            line.erase(i, 1);
            line.insert(i, trm);
            i += trm.size();
            std::cout << line << "\n";
        }
    }
    std::cout << line << "\n";
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

    //LEX::WhiteBox::s_run();   
    //LEX::BlackBox::s_run();

    LEX::Lexer lexer;
    
    
    //std::string line = "x:=a+((IV+a)+b);";
    //std::string line = "abc:=(a+-(-(VIII+b*a+b)+a)+a);";

    std::string line = "a:=some+(value*XXIV);b:=c*(I*-(g+a));";
    
    std::cout << "ВВОД: " << line << "\n";

    auto parseResult = lexer.parse(line);  

    auto commands = splitCommands(parseResult);
    
    for (auto& command : commands) {

        std::cout << "СТАТУС КОМАНДЫ: " << (command.isValid ? "ВЕРНА" : "НЕ ВЕРНА") << "\n";

        for (auto& item : command.tokens) {
            std::cout
                << item.value << "\t"
                << item.typeCode << "\t"
                << item.typeName << "\n"
                ;
        }

        if (command.isValid) {
            SyntaxScanner syntax;
            syntax.init(command);
            syntax.proccess();
            syntax.terms.insert(syntax.terms.cbegin(), parseResult.items[0].token.value);

            build_line(syntax);
        }     
        std::cout << "\n\n";
    }
}