#include <iostream>

#include "../Core/lexer.h"
#include "../SYNTAX/syntax.h"
#include "../Core/command_splitter.h"

int main() {
	Parser parser;
	

	std::string input = "a:=XXV-(III*x+y/(a-(I+III)-VI));";

	auto parseResult = parser.parse(input);


	if (!parseResult.isSuccess()) {
		return 0;
	}

	auto commands = MathCommandSplitter().split(parseResult);

	for (auto& command : commands) {
		Syntax syntax(MathGrammarConfig);
		auto syntaxResult = syntax.proccess(command);

		if (!syntaxResult.isSuccess()) {
			
		}
	}
	
	return 0;
}
