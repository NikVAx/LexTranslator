#pragma once

#include <string>

struct EnumStruct {
public:
	EnumStruct(const int code, const std::string string)
		: _code(code)
		, _string(string)
	{ }

	std::string toString() const {
		return _string;
	}

	operator int() const {
		return _code;
	}

protected:
	const int _code;
	const std::string _string;
};