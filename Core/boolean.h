#pragma once

#include <string>
#include <map>

struct Boolean
{
    static std::string to_constant(bool value)
    {
        std::map<bool, std::string> values = {
            { true, "T" },
            { false, "F" },
        };
        return values[value];
    }

    static bool to_boolean(std::string boolean) {
        std::map<std::string, int> values = {
            { "T", true},
            { "F", false},
        };

        return values[boolean];
    }
};