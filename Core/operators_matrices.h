#pragma once

#include "relations.h"

#include <vector>

const std::vector<std::vector<Relations>> MATRIX_1 =
{
{
Relations::PREV,	Relations::PREV,	Relations::NONE,	Relations::NONE,	Relations::PREV,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::PREV
},
{
Relations::NONE,	Relations::PREV,	Relations::BASE,	Relations::NONE,	Relations::PREV,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::BASE,	Relations::NONE,	Relations::NONE
},
{
Relations::NONE,	Relations::PREV,	Relations::NONE,	Relations::BASE,	Relations::PREV,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE
},
{
Relations::NONE,	Relations::PREV,	Relations::NONE,	Relations::NEXT,	Relations::PREV,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NEXT
},
{
Relations::NONE,	Relations::NONE,	Relations::NEXT,	Relations::NEXT,	Relations::NONE,	Relations::BASE,	Relations::BASE,	Relations::BASE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::NEXT
},
{
Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::BASE,	Relations::NONE,	Relations::NONE
},
{
Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::BASE,	Relations::NONE,	Relations::NONE
},
{
Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::BASE,	Relations::NONE,	Relations::NONE
},
{
Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE
},
{
Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE
},
{
Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::BASE,	Relations::BASE,	Relations::NONE,	Relations::NONE
},
{
Relations::NEXT,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE,	Relations::NONE
}
};

const std::vector<std::vector<StatusCode>> MATRIX_1_ERRORS =
{
{
StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__
},
{
StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR
},
{
StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR
},
{
StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__
},
{
StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__
},
{
StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR
},
{
StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR
},
{
StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR
},
{
StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR
},
{
StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR
},
{
StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SUCCESS__,	StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR
},
{
StatusCodes::SUCCESS__,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR,	StatusCodes::SYN_ERROR
}
};

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