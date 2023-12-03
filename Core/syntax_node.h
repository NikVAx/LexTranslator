#pragma once

#include "syntax_rule.h"
#include "syntax_value.h"

struct SyntaxNode {
    // TODO: Если заменить "SyntaxRule syntaxRule" на "const SyntaxRule& syntaxRule" падает bad_alloc
    SyntaxNode(SyntaxRule syntaxRule, SyntaxValue value)
        : syntaxRule(syntaxRule)
        , value(value)
    { };

    SyntaxRule syntaxRule;

    SyntaxValue value;

    friend std::ostream& operator<<(std::ostream& s, const SyntaxNode& token)
    {
        s << "[rule]: " << token.syntaxRule << "[value]: " << token.value << std::endl;
        return s;
    }
};
