
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

int main() {
    setlocale(LC_ALL, "");

    Parser lexer;
     
    std::string line = "a:=X;\n"
                       "b:=X+I-I;\n"
                       "c:=II+((C-IX-VI)/(XVI+b)+(a+I))*(II+II)+(z*(II+II));\n"
                       "f:=UNDEF*b+b;\n"
                       "d:=(c+IV)+(z*(II+II)-(II+II+c));\n" 
                       "c:=(z*IV+(a+c))+V+(c+d)-(z*(II*II)+(a+c));\n"
                       "e:=c+d;\n";
    
   
    std::cout << "ВХОДНЫЕ ДАННЫЕ:\n" 
        << std::string(32, '-') << "\n" 
        << line << "\n" 
        << std::string(32, '-') << "\n";

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

    std::cout << "\n";
    std::cout << "\n";

    print_triads(triads__);

    TriadOpt1(triads__).reduce();

    TriadOpt2 triadOpt2(triads__);

    triadOpt2.setDepValues();

    std::cout << "\n";

    for (Triad* triad : triads__) {
        std::cout
            << " | "
            << std::setw(2) << (triad->id) << "  | "
            << triad->toString() <<  " DEP="
            << triad->dep << " \n";
    }
   
    std::cout << "\n";

    triadOpt2.clearSameTriads();

    for (Triad* triad : triads__) {
        std::cout
            << " | "
            << std::setw(2) << (triad->id) << "  | "
            << triad->toString() << " ";

        std::cout << "\n";
    }
}

