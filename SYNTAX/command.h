#pragma once

#include "../Core/token.h"

#include <vector>;

typedef struct Command {
    bool isValid = true;
    std::vector<Token> tokens;
};