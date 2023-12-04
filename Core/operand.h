#pragma once
#include "token.h"

struct Operand {
	Token token;
	int link;

	bool IsLinked() {
		return link != -1;
	}
};