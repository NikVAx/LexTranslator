#pragma once

#include <vector>

#include "parse_result.h"
#include "command.h"

class CommandSplitter {
private:
    std::list<TermType> VALUES_TO_INCLUDE = { TermTypes::TRUE, TermTypes::FALSE, TermTypes::IDENTIFIER };

    bool shouldAddToValue(ParseItem& item) {
        return std::find(VALUES_TO_INCLUDE.begin(), VALUES_TO_INCLUDE.end(), item.token.type) != VALUES_TO_INCLUDE.end();
    }
public:
    std::vector<Command> split(ParseResult& parseResult) {
        int index = 0;

        std::vector<Command> commands;

        while (index < parseResult.items.size()) {
            Command command;
            
            while (index < parseResult.items.size()) {
                ParseItem item = parseResult.items[index];
                
                if (!item.isValid()) {
                    command.isValid = false;
                }

                Token token = item.token;

                if (token.type == TermTypes::TRUE || token.type == TermTypes::FALSE) {
                    command.tokens.push_back(Token(item.token.value, TermTypes::BOOL));
                }
                else {
                    command.tokens.push_back(token);
                }

                // TODO: add list of value-types
                if (this->shouldAddToValue(item)) {
                    if (token.type == TermTypes::TRUE || token.type == TermTypes::FALSE) {
                        command.values.push_back(Token(item.token.value, TermTypes::BOOL));
                    }
                    else {
                        command.values.push_back(token);
                    } 
                }
                
                if (token.value == ";") {
                    command.tokens.push_back(Token("Ê", TermTypes::LIMIT));
                    index += 1;
                    break;
                }
                index += 1;
            }
            commands.push_back(command);
        }
        return commands;
    }
};