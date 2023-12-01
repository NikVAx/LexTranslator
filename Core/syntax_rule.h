#pragma once

#include "build_rule.h"
#include <ostream>

struct SyntaxRule {
    SyntaxRule()
        : SyntaxRule(BuildRule())
    { };

    SyntaxRule(BuildRule buildRule)
        : buildRule(buildRule)
    { }

    BuildRule buildRule;

    friend std::ostream& operator<<(std::ostream& s, const SyntaxRule& syntaxRule)
    {
        s << "rule: " << syntaxRule.buildRule;
        return s;
    }

};
