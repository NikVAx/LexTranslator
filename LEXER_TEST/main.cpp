
#include "../LEXER/lexer.h"
#include "../LEXER/shared_types.h"
#include "../SYNTAX/syntax.cpp";
#include "../Utils/utils.h"


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
    for (int r : scanner.rules) {
        std::cout << r << "\n";
    }
    std::cout << "КОНЕЦ ПРАВИЛА\n";

    for (int i = scanner.rules.size() - 1; i >= 0; --i) {
        std::cout << line << "\n";
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
    
    //tree_e.print();
}

int main() {
    setlocale(LC_ALL, "");

    //LEX::WhiteBox::s_run();   
    //LEX::BlackBox::s_run();

    LEX::Lexer lexer;
    SyntaxScanner syntax;
    
    //std::string line = "x:=a+((IV+a)+b);";
    //std::string line = "abc:=(a+-(-(VIII+b*a+b)+a)+a);";

    std::string line = "a:=some+-(value*XXIV);b:=c*(I-g);";
    
    std::cout << "ВВОД: " << line << "\n";

    auto parseResult = lexer.parse(line);
    
    int index = 0;
    int page = 0;

    std::vector<std::vector<Token>> commands;
    while (index < parseResult.items.size()) {
        commands.push_back(std::vector<Token>());
        while (index < parseResult.items.size()) {
            commands[page].push_back(parseResult.items[index].token);           
            if (parseResult.items[index].token.value == ";") {
                commands[page].push_back(Token("К", TermTypes::END_TERMINAL, "К"));
                page += 1;
                index += 1;
                break;
            }
            index += 1;
        }
    }

    int lsm = 1;
   

    parseResult.add(Token("К", TermTypes::END_TERMINAL, "К"));
    
    if (parseResult.success()) {
        // TODO: тут нужно разделять токены на подсписки
        // чтобы синтаксический анализатор принимал только конструктцию вида
        // I:=S;
        
        syntax.init(parseResult.items);
        syntax.proccess();
        syntax.terms.insert(syntax.terms.cbegin(), parseResult.items[0].token.value);
        
        build_line(syntax);

        //std::string line = "a:=some+-(value*XXIV);";
    }
}