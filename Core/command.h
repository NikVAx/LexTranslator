#pragma once

#include <vector>
#include <sstream>
#include <list>
#include <functional>

#include "token.h"

struct Command {
    bool isValid = true;

    std::vector<Token> tokens;
    std::list<Token> values;

    std::string toString() {
        std::stringstream ss;

        for (auto& token : tokens) {
            ss << token.value;
        }

        return ss.str();
    }

    std::list<Token> getValues() {
        return values;
    }
};