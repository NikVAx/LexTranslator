#pragma once

#include <vector>;
#include "../LEXER/token.h"


typedef struct Command {
    bool isValid = true;
    std::vector<Token> tokens;
};