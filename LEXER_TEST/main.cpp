
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


struct Triad {
    RefValue* oper;
    RefValue* arg1;
    RefValue* arg2;
};


int main() {
    setlocale(LC_ALL, "");

    Parser lexer;
     
    std::string line = "A:=B+((C-D-E)+(F+G)+(H+I));";
    
    std::cout << "ВВОД: " << line << "\n";

    auto parseResult = lexer.parse(line);  
    auto commands = MathCommandSplitter()
        .split(parseResult);
    
    for (auto& command : commands) {
        std::cout << "СТАТУС КОМАНДЫ: " << 
            (command.isValid ? "ВЕРНА" : "НЕ ВЕРНА") << "\n";

        for (auto& item : command.tokens) {
            std::cout
                << item.value << "\t"
                << item.termType.toString() << "\t"
                << item.termType << "\n"
                ;
        }

        if (command.isValid) {  
            Syntax syntax = Syntax(CurrentSyntaxConfig);
            SyntaxResult syntaxResult = syntax.proccess(command);

            std::list<SyntaxNode> ruleNodes1 = syntaxResult.nodes;
            std::list<SyntaxNode> ruleNodes2 = syntaxResult.nodes;

            RefTree<std::string> myTreeView;
            
            SyntaxTreeBuilder(myTreeView)
                .build(ruleNodes1, command.getValueTokens());
            
            myTreeView.print([&](RefTreeNode<std::string>* item, int depth) {
                std::cout << std::setw(3) << depth << ": " << std::string(depth + 1, '-') << "" << (*(item->value)) << "\n";
                }
            );


            RefTree<RefValue> myTreeRefView;
            SyntaxTreeByCharBuilder(myTreeRefView)
                .build(ruleNodes2, command.getValueTokens());

      

            std::cout << "\n";
            std::cout << " --- \n";
            std::cout << "\n";

            
            myTreeRefView.print([&](RefTreeNode<RefValue>* item, int depth) {
                std::cout << std::setw(3) << depth << ": " << std::string(depth + 1, '#');
                    
                if (*item->value->syntaxChar == SyntaxChars::IDENTIFIER) {
                    std::cout << item->value->value->value;
                }
                else {
                    std::cout << item->value->syntaxChar->tokenString;
                }

                std::cout << "\n";
            });
         
            
            OperatorsTreeBuilder(myTreeRefView).build();

            std::cout << "\n";
            std::cout << " --- \n";
            std::cout << "\n";

      
            myTreeRefView.print([&](RefTreeNode<RefValue>* item, int depth) {
                std::cout << std::setw(3) << depth << ": " << std::string(depth + 1, '#');

                if (*item->value->syntaxChar == SyntaxChars::IDENTIFIER) {
                    std::cout << item->value->value->value;
                }
                else {
                    std::cout << item->value->syntaxChar->tokenString;
                }

                std::cout << " <-> " << item->items.size();

                std::cout << "\n";
                });

        }
    }
}
