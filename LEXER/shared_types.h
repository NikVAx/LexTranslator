#pragma once

#include "lexer_config.h"

#include <string>
#include <vector>
#include <sstream>

struct Token {
    Token(std::string value, TermTypes typeCode)
        : value(value)
        , typeCode(typeCode)
        , typeName(typeCode.name)
    { }

    std::string value = "";
    std::string typeName = "";
    TermTypes typeCode = TermTypes::UNDEFINED;

    friend bool operator==(const Token& t1, const Token& t2) {
        return t1.value == t2.value &&
            t1.typeCode == t2.typeCode &&
            t1.typeName == t2.typeName;
    }

    friend bool operator!=(const Token& t1, const Token& t2) {
        return !(t1 == t2);
    }
};


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

