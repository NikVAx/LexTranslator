#pragma once
#include "term_type.h"
#include "term_types.h"

struct Operator {
	Operator(const TermType& type)
		: type(type)
	{ }

	const TermType& type;
};

namespace Operators {
	const Operator ADD(TermTypes::PLUS);
	const Operator SUB(TermTypes::MINUS);
	const Operator MUL(TermTypes::MULTIPLY);
	const Operator DIV(TermTypes::DIVIDE);
	const Operator ASSIGN(TermTypes::ASSIGNMENT);
}