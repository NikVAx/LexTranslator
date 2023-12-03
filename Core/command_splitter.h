#pragma once

#include <vector>

#include "parse_result.h"
#include "command.h"

class MathCommandSplitter {
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

                command.tokens.push_back(item.token);

                // TODO: add list of value-types
                if (item.token.termType == TermTypes::NUMBER || item.token.termType == TermTypes::IDENTIFIER) {
                    command.values.push_back(item.token);
                }
                
                if (item.token.value == ";") {
                    command.tokens.push_back(Token("�", TermTypes::LIMIT));
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