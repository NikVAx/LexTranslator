
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
#include <string>

#include "../Utils/utils.h"

class StringTreeBuilder {
private:
    SyntaxScanner& scanner;
    int i = 0;
    int termIndex = 0;
public:
    StringTreeBuilder(SyntaxScanner& scanner) 
        : scanner(scanner)
    { 
    
    }

    Tree<std::string>* build() {
        Tree<std::string>* tree = new Tree<std::string>();
        tree->root = new TreeNode<std::string>("S");
        i = scanner.rules.size() - 1;

        addCascade(tree->root, 0);

        return tree;
    }

    void addCascade(TreeNode<std::string>* root, int depth) {
        if (root == NULL) {
            return;
        }
        
        int childIndex = 0;

        std::cout << depth << ": " << root->value << "\n";

        for (int j = root->value.size() - 1; j >= 0; --j) {
            if (root->value[j] == 'S') {
                int rule = scanner.rules[i];
                BuildRule buildRule = BUILD_RULES[rule];

                std::cout << "Using rule at " << i << " #" << rule << "\n";
                i -= 1;
               
                std::string ruleString = buildRule.ruleString;



                std::cout << "S at pos " << j << "\n";
                TreeNode<std::string>* node = new TreeNode<std::string>(ruleString);
                root->addChild(node);
                addCascade(node, depth + 1);
            }
            if (root->value[j] == 'I') {
                TreeNode<std::string>* node = new TreeNode<std::string>(scanner.terms[termIndex++]);
                root->addChild(node);
            }
            if (root->value[j] == 'R') {
                TreeNode<std::string>* node = new TreeNode<std::string>(scanner.terms[termIndex++]);
                root->addChild(node);
            }
        
        }

        ///int rule = scanner.rules[i];
    
        //int location = line.find_last_of("S");
    
        //for (int i = 0; i < root->children.size(); ++i) {
        //    addCascade(root->children[i], depth + 1);
        //}
    }

    void add() {
        int rule = scanner.rules[i];
        std::string ruleString = BUILD_RULES[rule].ruleString;
    }

};

void build_line_2(SyntaxScanner& scanner) {
    std::string line = "S";
    for (int i = scanner.rules.size() - 1; i >= 0; --i) {
        std::cout << line << "\n";
        int rule = scanner.rules[i];
        int location = line.find_last_of("S");
        if (location != -1) {
            line.erase(location, 1);
            line.insert(location, BUILD_RULES[rule].ruleString);
        }
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

    LEX::Lexer lexer;
    
    
    //std::string line = "x:=a+((IV+a)+b);";
    //std::string line = "abc:=(a+-(-(VIII+b*a+b)+a)+a);";

    //std::string line = "a:=some+(value*XXIV);b:=c*(I*-(g+a));";

    std::string line = "a:=some+((value*XXIV)+(value+XX)+(value+IV));";
    
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

            build_line_2(syntax);

            StringTreeBuilder builder(syntax);

            Tree<std::string>* tree =  builder.build();
            std::cout << "\nвывод:\n";
            tree->print();
        }     
        std::cout << "\n\n";
    }
}