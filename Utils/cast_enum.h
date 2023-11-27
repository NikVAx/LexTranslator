#pragma once
#include <type_traits>

template <typename Enumeration>
auto cast_enum(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}