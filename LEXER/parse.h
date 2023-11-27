#pragma once

#include "lexer_config.h"

#include "token.h";

#include <string>
#include <vector>
#include <sstream>


struct ParseItem {
    Token token;
    StatusCodes statusCode;

    bool isValid() {
        return statusCode == StatusCodes::SUCCESS;
    }

    ParseItem(Token token, StatusCodes statusCode = StatusCodes::SUCCESS)
        : token(token), statusCode(statusCode)
    {
    }
};



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
        items.push_back(ParseItem(Token(value, TermTypes::UNDEFINED,
            getTermTypeName(TermTypes::UNDEFINED)), statusCode));
        error = true;
    }

    bool success() {
        return !error;
    }

    void add(Token token) {
        items.push_back(ParseItem(token));
    }

    void add(std::string value, TermTypes typeCode, std::string typeName) {
        items.push_back(ParseItem(Token(value, typeCode, typeName)));
    }

    void updateCurrentCharLocationData(char ch) {

    }
};

