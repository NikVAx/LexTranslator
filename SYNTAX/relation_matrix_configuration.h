#pragma once

#include "../Core/relation_matrix.h"
#include "../Core/relations.h"

RelationMatrix MATH_MATRIX({
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
    });

RelationMatrix FOR_MATRIX({
    { Relations::NONE }
    });
RelationMatrix IF_MATRIX({
    { Relations::NONE }
    });
RelationMatrix BOOL_MATRIX({
    { Relations::NONE }
    });