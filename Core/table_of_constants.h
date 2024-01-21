#pragma once
#include <map>
#include <string>
#include "boolean.h"
#include "triad.h"

struct TableOfContants {
private:
    std::map<std::string, Triad*> values;
public:

    void saveVariable(std::string identifier, Triad* value) {
        values.insert_or_assign(identifier, value);
    }

    bool tryAssignBoolTo(std::string key, bool& variable) {
        const auto& valueIterator = values.find(key);

        if (valueIterator != values.end()) {
            variable = Boolean::to_boolean(valueIterator->second->getToken()->value);
            return true;
        }

        return false;
    }
};