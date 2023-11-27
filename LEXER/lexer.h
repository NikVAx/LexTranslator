#pragma once

#include "../Core/status_codes.h"
#include "../Core/parse_result.h"
#include "../Core/token.h"

#include "transition_info.h"
#include "lexer_config.h"
#include "state_machine.h"

#include <string>
#include <sstream>
#include <vector>

namespace LEX {
    class Lexer {
        private:
            LexerConfiguration _lexConfig;
            StateMachine _sm;
        public:
            Lexer() : _lexConfig(LexerConfiguration()) , _sm(LexerConfiguration().getSmConfig()) { }

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
                    TermTypes tokenType = _lexConfig.mapTokenType(_sm.currentState);

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
}