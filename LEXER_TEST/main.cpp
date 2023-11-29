
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

struct CharTreeItem {
    CharTreeItem(SyntaxRule* rule, std::string value)
        : currentRule(rule)
        , value(value)
    {

    }

    friend std::ostream& operator<<(std::ostream& s, const CharTreeItem& item) {
        s << item.value << std::endl;
        return s;
    }

    SyntaxRule* currentRule;
    std::string value;
};

class SyntaxTreeBuilder {
public:
    std::vector<SyntaxNode> rules;

    SyntaxTreeBuilder(std::vector<SyntaxNode> rules)
    {
        for (int i = rules.size() - 1; i >= 0; --i) {
            this->rules.push_back(rules[i]);
        }

    }



    int ruleIndex = 0;
    

    Tree<CharTreeItem>* build() {
        Tree<CharTreeItem>* charTree = new Tree<CharTreeItem>();
        CharTreeItem rootRuleItem = CharTreeItem(NULL, "S");
        charTree->root = new TreeNode<CharTreeItem>(rootRuleItem);
        useRule(charTree->root);
        return charTree;
    }

    void useRule(TreeNode<CharTreeItem>* node) {
        if (ruleIndex >= rules.size()) {
            return;
        }
        
        SyntaxNode syntaxNode = rules.at(ruleIndex);

        for (TokenMeta meta : syntaxNode.rule.rule.items) {

            if (meta.type == TokenType::TERMINAL) {
                CharTreeItem item(NULL, meta.symbol);
                TreeNode<CharTreeItem>* child = new TreeNode<CharTreeItem>(item);
                node->addChild(child);
            }
            else {
                if (ruleIndex >= rules.size()) {
                    return;
                }

                std::string value = SYNTAX_TOKENS::IDENTIFIER == meta 
                    ? syntaxNode.value.value
                    : meta.symbol;

                CharTreeItem item(NULL, value);
                TreeNode<CharTreeItem>* child = new TreeNode<CharTreeItem>(item);
                node->addChild(child);
                ruleIndex += 1;
                useRule(child);
            }
        }

        ruleIndex += 1;
    }

};

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
            SyntaxScanner syntax;
            syntax.init(command);
            syntax.proccess();

            build_line(syntax);



            auto tree = TreeBuilder(syntax.rules).build();
            std::cout << "TREE" << std::endl;
            tree.print();

            auto syntaxTree = SyntaxTreeBuilder(syntax.rules).build();
            
            std::cout << "SYNTAX TREE" << std::endl;
            syntaxTree->print();

            
        }
    }
}