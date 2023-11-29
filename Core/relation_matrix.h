#pragma once

#include "relations.h"
#include <vector>

class RelationMatrix {
public:
    const std::vector<std::vector<Relations>> MATRIX;

    const int size() {
        return MATRIX.size();
    }

    RelationMatrix(const std::vector<std::vector<Relations>> matrix)
        : MATRIX(matrix) {
        if (MATRIX.size() != MATRIX[0].size()) {
            throw std::exception("It is not relation matrix");
        }
    }
};