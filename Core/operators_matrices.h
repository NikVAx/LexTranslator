#pragma once

#include "relations.h"
#include <vector>

const std::vector<std::vector<Relations>> MATRIX_1 =
{
    { Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::BASE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::BASE, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::BASE} ,
    { Relations::NONE, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::BASE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NONE, Relations::BASE, Relations::NONE} ,
};