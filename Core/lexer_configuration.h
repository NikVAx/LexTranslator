#pragma once

#include "state_machine_configuration.h"
#include "term_type.h"

class LexerConfiguration {
private:
    StateMachineConfiguration _smConfig;
public:
    LexerConfiguration()
        : _smConfig(StateMachineConfiguration())
    { }

    StateMachineConfiguration& getSmConfig() {
        return _smConfig;
    }

    TermType mapTokenType(int state) {
        TermType termType = (0 <= state && state < _smConfig.getCountOfStates())
            ? TOKEN_TYPE_MAP[state]
            : TermTypes::UNDEFINED;
        return termType;
    }

    std::string getTokenTypeName(TermType termType) {
        return termType.toString();
    }
};