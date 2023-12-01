#pragma once

#include "relations.h"

#include <stdexcept>

class SyntaxConfig {
public:
    SyntaxConfig(const std::vector<std::vector<Relations>> matrix, const std::map<TermType, int> termTypeToMatrixIndex, std::vector<SyntaxRule> rules)
        : matrix(matrix)
        , termTypeToMatrixIndex(termTypeToMatrixIndex)
    {
        if (matrix.size() != matrix.at(0).size()) {
            throw std::invalid_argument("SyntaxConfig `matrix` is not relation matrix.");
        }

        for (SyntaxRule rule : rules) {
            stringRuleMap.insert({ rule.buildRule.ruleString, rule });
        }
    }

    Relations getRelation(int leftTermIndex, int rightTermIndex) const {
        if (leftTermIndex >= matrix.size() || rightTermIndex >= matrix.size())
            throw std::exception("Relation matrix out of range");

        return matrix.at(leftTermIndex).at(rightTermIndex);
    }

    int getIndex(TermType tokenType) const {
        return termTypeToMatrixIndex.at(tokenType);
    }

    SyntaxRule getRuleByString(std::string ruleString) {
        return stringRuleMap.at(ruleString);
    }

private:
    const std::vector<std::vector<Relations>> matrix;
    const std::map<TermType, int> termTypeToMatrixIndex;

    std::map<std::string, SyntaxRule> stringRuleMap;
};