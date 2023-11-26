#pragma once

#include <vector>
#include "TermTypes.h"

static const int INPUT_ALPHABET_SIZE = 128;
const std::vector<int> INPUT_ALPHABET_MAP =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 19, 0, 0, 20, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0,  0, 0, 0, 0, 0,
    20, 0, 0, 0, 0, 0,  0, 0, 12, 13, 16, 14, 0, 15, 0, 17,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 18, 0, 11, 0, 0,
    0, 8, 8, 5, 6, 8, 8, 8, 8, 1, 8, 8, 4, 7, 8, 8,
    8, 8, 8, 8, 8, 8, 2, 8, 3, 8, 8, 0, 0, 0, 0, 8,
    0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0
};

static const int INITIAL_STATE = 53;

const std::vector<std::vector<int>> STATES_MATRIX = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 8, 9, 13, 14, 18, 2, 0, 0, 0, 0, 0, 0, 0, 0, 48, 0, 1, 1, 1},
    { 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 40, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2},
    { 0, 6, 7, 7, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 5, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 6, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 7, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 11, 12, 12, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 10, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 11, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 12, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 8, 9, 16, 17, 17, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 8, 9, 15, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 8, 9, 16, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 8, 9, 17, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 8, 9, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 8, 9, 13, 14, 19, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 8, 9, 13, 14, 20, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 3, 4, 8, 9, 13, 14, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 21, 21, 21, 21, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 21, 21, 21},
    { 0, 25, 26, 26, 21, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 22, 22, 22},
    { 0, 24, 21, 21, 21, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 23, 23, 23},
    { 0, 25, 21, 21, 21, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 24, 24, 24},
    { 0, 26, 21, 21, 21, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 25, 25, 25},
    { 0, 21, 21, 21, 21, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 26, 26, 26},
    { 0, 22, 23, 30, 31, 31, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 27, 27, 27},
    { 0, 22, 23, 29, 21, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 28, 28, 28},
    { 0, 22, 23, 30, 21, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 29, 29, 29},
    { 0, 22, 23, 31, 21, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 30, 30, 30},
    { 0, 22, 23, 21, 21, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 31, 31, 31},
    { 0, 22, 23, 27, 28, 35, 36, 36, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 32, 32, 32},
    { 0, 22, 23, 27, 28, 34, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 33, 33, 33},
    { 0, 22, 23, 27, 28, 35, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 34, 34, 34},
    { 0, 22, 23, 27, 28, 36, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 35, 35, 35},
    { 0, 22, 23, 27, 28, 21, 21, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 36, 36, 36},
    { 0, 22, 23, 27, 28, 32, 33, 38, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 37, 37, 37},
    { 0, 22, 23, 27, 28, 32, 33, 39, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 38, 38, 38},
    { 0, 22, 23, 27, 28, 32, 33, 21, 21, 21, 0, 0, 0, 47, 42, 43, 44, 45, 1, 39, 39, 39},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 22, 23, 27, 28, 32, 33, 37, 21, 0, 0, 0, 46, 0, 0, 43, 0, 0, 0, 41, 41, 41},
    { 0, 22, 23, 27, 28, 32, 33, 37, 21, 0, 0, 0, 46, 0, 0, 43, 0, 0, 0, 42, 42, 42},
    { 0, 22, 23, 27, 28, 32, 33, 37, 21, 0, 0, 0, 46, 0, 0, 43, 0, 0, 0, 43, 43, 43},
    { 0, 22, 23, 27, 28, 32, 33, 37, 21, 0, 0, 0, 46, 0, 0, 43, 0, 0, 0, 44, 44, 44},
    { 0, 22, 23, 27, 28, 32, 33, 37, 21, 0, 0, 0, 46, 0, 0, 43, 0, 0, 0, 45, 45, 45},
    { 0, 22, 23, 27, 28, 32, 33, 37, 21, 0, 0, 0, 46, 0, 0, 43, 0, 0, 0, 46, 46, 46},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 47, 42, 43, 44, 45, 1, 47, 47, 47},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 49, 0, 0, 0, 0},
    { 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 1, 49, 49},
    { 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 51, 50, 50, 50, 50, 50},
    { 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 52, 50, 50, 50, 50},
    { 0, 3, 4, 8, 9, 13, 14, 18, 2, 0, 0, 0, 0, 0, 0, 0, 0, 48, 0, 1, 1, 1 },
    { 0, 3, 4, 8, 9, 13, 14, 18, 2, 0, 0, 0, 0, 0, 0, 0, 0, 48, 0, 53, 53, 53}
};

const std::vector<std::vector<int>> BOUNDS_MATRIX = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1}
};

const std::vector<std::vector<int>> ERRORS_MATRIX = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 6, 10, 10, 10, 10, 10, 10, 10, 0, 10, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 8, 8, 0, 8, 8, 8, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 8, 8, 0, 8, 8, 8, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 8, 8, 0, 8, 8, 8, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 8, 8, 0, 8, 8, 8, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 8, 8, 0, 8, 8, 8, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 8, 8, 0, 8, 8, 8, 0, 0, 0},
    { 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 4, 4, 4, 4},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 6,	10, 10, 10, 10, 10, 10, 10, 0, 10, 0, 0, 0},
    { 2, 0, 0, 0, 0, 0, 0, 0, 0, 6, 10, 10, 10, 10, 10, 10, 10, 0, 10, 0, 0, 0},
};

const std::vector<TermTypes> TOKEN_TYPE_MAP =
{
    TermTypes::UNDEFINED,
    TermTypes::SEMICOLON,
    TermTypes::IDENTIFIER,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::IDENTIFIER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::NUMBER,
    TermTypes::UNDEFINED,
    TermTypes::ASSIGNMENT,
    TermTypes::PLUS,
    TermTypes::MINUS,
    TermTypes::MULTIPLY,
    TermTypes::DIVIDE,
    TermTypes::OPEN_BRACKET,
    TermTypes::CLOSE_BRACKET,
    TermTypes::UNDEFINED,
    TermTypes::COMMENT,
    TermTypes::UNDEFINED,
    TermTypes::UNDEFINED,
    TermTypes::COMMENT
};
