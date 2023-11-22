#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace Shared {
    struct Token {
        Token(std::string value, int typeCode, std::string typeName) {
            this->value = value;
            this->typeCode = typeCode;
            this->typeName = typeName;
        }

        std::string value = "";
        std::string typeName = "";
        int typeCode = 0;

        friend bool operator==(const Token& t1, const Token& t2) {
            return t1.value == t2.value &&
                t1.typeCode == t2.typeCode &&
                t1.typeName == t2.typeName;
        }

        friend bool operator!=(const Token& t1, const Token& t2) {
            return !(t1 == t2);
        }
    };

    struct ParseResult {
    private:
        bool _error = false;
        int _code = 0;
        std::string _message = "";
    public:
        struct Location {
            int index = 0;
            int row = 1;
            int column = 1;
        };

        std::vector<Shared::Token> tokens;
        Location current;

        void setError(int code, std::string errorMessage) {
            _message = errorMessage;
            _error = true;
            _code = code;
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

        void add(Shared::Token token) {
            tokens.push_back(token);
        }

        void add(std::string value, int typeCode, std::string typeName) {
            tokens.push_back(Token(value, typeCode, typeName));
        }

        void move(char ch) {
            current.index += 1;
            current.column += 1;
            if (ch == '\n') {
                current.row += 1;
                current.column = 1;
            }
        }
    };
}

