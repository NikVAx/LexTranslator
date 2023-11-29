#pragma once

#include <vector>;

#include "token.h"

typedef struct Command {
    bool isValid = true;
    std::vector<Token> tokens;
};