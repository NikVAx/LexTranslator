#pragma once

#include "token.h"
#include "term_type.h"
#include "parse_item.h"

#include <vector>

struct ParseResult {
private:
    bool error = false;
public:
    struct Location {
        int index = 0;
        int tokenIndex = 0;
    };

    std::vector<ParseItem> items;
    Location current;

    void addError(std::string value, StatusCode statusCode) {
        items.push_back(ParseItem(Token(value, TermTypes::UNDEFINED), statusCode));
        error = true;
    }

    bool isSuccess() const {
        return !error;
    }

    void add(Token token) {
        items.push_back(ParseItem(token));
    }

    void add(std::string value, TermType tokenType) {
        items.push_back(ParseItem(Token(value, tokenType)));
    }
};
