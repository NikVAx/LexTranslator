#pragma once

#include "relations.h"

#include <vector>

const std::vector<std::vector<Relations>> MATRIX_1 =
{
    { Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::BASE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NEXT, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NEXT, Relations::NEXT, Relations::PREV, Relations::PREV, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::BASE} ,
    { Relations::NONE, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::BASE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NEXT, Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NEXT, Relations::NEXT, Relations::NONE} ,
    { Relations::NEXT, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE, Relations::NONE} ,
    { Relations::NONE, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::PREV, Relations::NONE, Relations::BASE, Relations::NONE} ,
};

const std::vector<std::vector<StatusCode>> MATRIX_1_ERRORS =
{
    { StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR} ,
    { StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SYN_ERROR} ,
    { StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SYN_ERROR} ,
    { StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SYN_ERROR} ,
    { StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SYN_ERROR} ,
    { StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SYN_OPEXP, StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS} ,
    { StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SYN_UNCLOSED_BRACKET, StatusCodes::SYN_ERROR} ,
    { StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SYN_ERROR} ,
    { StatusCodes::SUCCESS, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR, StatusCodes::SYN_ERROR} ,
    { StatusCodes::SYN_ERROR, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SUCCESS, StatusCodes::SYN_UEXPECTED_BRACKET, StatusCodes::SUCCESS, StatusCodes::SYN_ERROR} ,
};

/*
6-8: ���������� ������
9-7: �������� ���������� ������

*/


const std::vector<std::vector<Relations>> MATRIX_2 =
{
    { Relations::NONE } ,
};

const std::vector<std::vector<Relations>> MATRIX_3 =
{
    { Relations::NONE } ,
};

const std::vector<std::vector<Relations>> MATRIX_4 =
{
    { Relations::NONE } ,
};