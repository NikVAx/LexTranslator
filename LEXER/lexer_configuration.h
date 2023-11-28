#pragma once

#include "../Core/term_types.h"
#include "state_machine_configuration.h"

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
        TermType typeCode = (0 <= state && state < _smConfig.getCountOfStates())
            ? TOKEN_TYPE_MAP[state]
            : TermTypes::UNDEFINED;
        return typeCode;
    }

    std::string getTokenTypeName(TermType termType) {
        return termType.toString();
    }
};