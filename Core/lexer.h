#pragma once

#include "term_type.h"
#include "parse_result.h"
#include "state_machine.h"
#include "parser_config.h"

#include <string>
#include <sstream>
#include <vector>

class Lexer {
private:
    StateMachine _sm;
public:
    Lexer() : _sm(CurrentParserConfig) { }

    ParseResult parse(std::string input) {
        ParseResult result;

        _sm.reset();

        std::string text = input + "\n";
        std::string tokenString = "";

        for (int head = 0; head < text.length(); head++) {
            char ch = text[head];

            TransitionInfo info = _sm.getTransition(ch);

            if (info.isNotSuccess()) {
                result.addError(tokenString, info.getStatusCode());
                
                continue;
            }

            if (info.isTokenBoundary() && !tokenString.empty()) {
                TermType tokenType = CurrentParserConfig.mapTokenType(_sm.currentState);


                if (tokenType != TermTypes::COMMENT) {
                    result.add(tokenString, tokenType);
                } // else ingore comment

                tokenString.clear();
            }

            if (!info.isEmptyChar()) {
                tokenString.append(1, ch);
            }

            _sm.currentState = info.getNextState();
        }

        return result;
    }
};