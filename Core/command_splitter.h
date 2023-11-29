#pragma once

#include <vector>

#include "parse_result.h"
#include "command.h"

class CommandSplitter {
public:
    std::vector<Command> split(ParseResult& parseResult) {
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