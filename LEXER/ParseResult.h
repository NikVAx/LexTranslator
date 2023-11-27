#pragma once

#include "Token.h"
#include "ParseItem.h"

#include <vector>

struct ParseResult {
private:
    bool error = false;
public:
    struct Location {
        int head = 0;
        int row = 1;
        int column = 1;
    };

    std::vector<ParseItem> items;
    Location current;

    void addError(std::string value, StatusCodes statusCode) {
        items.push_back(ParseItem(Token(value, TermTypes::UNDEFINED), statusCode));
        error = true;
    }

    bool success() {
        return !error;
    }

    void add(Token token) {
        items.push_back(ParseItem(token));
    }

    void add(std::string value, TermTypes tokenType) {
        items.push_back(ParseItem(Token(value, tokenType)));
    }

    void updateCurrentCharLocationData(char ch) {

    }
};