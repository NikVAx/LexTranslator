#pragma once

#include "lexer_config.h"

#include <string>
#include <vector>
#include <sstream>

struct Token {
    Token(std::string value, TermTypes typeCode, std::string typeName) {
        this->value = value;
        this->typeCode = typeCode;
        this->typeName = typeName;
    }

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
};



struct ParseResult {
private:
    bool _error = false;
    int _code = 0;
    std::string _message = "";
public:
    struct Location {
        int head = 0;
        int row = 1;
        int column = 1;
    };

    std::vector<Token> tokens;
    Location current;

    void setError(int statusCode) {
        _message = LexerConfiguration::mapStatusMessage(statusCode);
        _error = true;
        _code = statusCode;
    }

    std::string message() {
        return _message;
    }

    bool success() {
        return !_error;
    }

    int code() {
        return _code;
    }

    void add(Token token) {
        tokens.push_back(token);
    }

    void add(std::string value, TermTypes typeCode, std::string typeName) {
        tokens.push_back(Token(value, typeCode, typeName));
    }

    void updateCurrentCharLocationData(char ch) {
        current.head += 1;
        current.column += 1;
        if (ch == '\n') {
            current.row += 1;
            current.column = 1;
        }
    }
};

