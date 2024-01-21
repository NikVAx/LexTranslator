#include <iostream>
#include <algorithm>

#include "../Core/lexer.h"
#include "../SYNTAX/syntax.h"
#include "../Core/command_splitter.h"

SyntaxConfig& gmconf = MathGrammarConfig;

class SyntaxLineBuilder {
public:

	size_t rfind_rule(std::string line, int ignore) {
		int posS = line.rfind('E', line.size() - 1);
		int posI = line.size() - 1;
		for (int i = 0; i <= ignore; ++i) {
			posI = line.rfind('I', posI - 1);
		}
		return std::max(posS, posI);
	}

	std::pair<std::string, std::string> buildline(SyntaxResult& result, Command& command) {
		int IDR = 10;
		
		std::stringstream ss;

		auto nodes = result.nodes;
		auto terms = command.getValueTokens();
			
		std::string line = "E";

		int ignore = 0;

		//ss << line;

		while (true) {
			size_t pos = rfind_rule(line, ignore);

			if (pos == std::string::npos) {
				break;
			}
			else {
				if (line.at(pos) == 'E') {
					auto node = nodes.back();

					std::string rString = node.syntaxRule.buildRule.ruleString;

					line.replace(pos, 1, rString);
					nodes.pop_back();

					if (node.syntaxRule.code != 10) {
						ss << /*"ПРАВИЛО: " << <<*/ node.syntaxRule.code /* << "  -> " << line*/ << " ";
					}
				}
				else if (line.at(pos) == 'I') {
					std::string value = terms.back().value;
					line.replace(pos, 1, value);
					ss << /*"ПРАВИЛО: " <<*/ "10" /* << " -> " << line*/ << " ";
					size_t n = std::count(value.begin(), value.end(), 'I');

					ignore += n;
					terms.pop_back();
				}

			}
		}
		std::cout << "\n";
		return std::pair<std::string, std::string>(line, ss.str());
	}

};


std::pair<bool, Command> prepare_command(std::string input) {
	Parser parser;
	auto parseResult = parser.parse(input);

	if (parseResult.isSuccess()) {
		auto commands = CommandSplitter()
			.split(parseResult);
		auto command = commands[0];

		return std::pair<bool, Command>(true, command);
	}
	else {
		std::cout << " - ОШИБКА ПРИ ЛЕКСИЧЕСКОМ АНАЛИЗЕ\n";
		return std::pair<bool, Command>(false, Command());
	}
}

std::pair<bool, std::string> run_syntax(Command& command) {
	Syntax syntax(gmconf);
	auto syntaxResult = syntax.proccess(command);
	
	if (syntaxResult.isSuccess()) {
		auto generated = SyntaxLineBuilder().buildline(syntaxResult, command);

		// std::cout << "ПОРЯДОК РАЗБОРА:\n" << generated.second << "\n";

		return std::pair<bool, std::string>(true, generated.first);

	} else {
		return std::pair<bool, std::string>(false, syntaxResult.message);
	}
}

std::pair<bool, std::string> run_syntax_f(Command& command) {
	Syntax syntax(gmconf);
	auto syntaxResult = syntax.proccess(command);

	if (syntaxResult.isSuccess()) {
		auto generated = SyntaxLineBuilder().buildline(syntaxResult, command);

		//std::cout << "ПОРЯДОК РАЗБОРА:\n" << generated.second << "\n";

		return std::pair<bool, std::string>(true, generated.second);

	}
	else {
		return std::pair<bool, std::string>(false, syntaxResult.message);
	}
}

void on_result(std::string expected, std::string actual, std::string input) {
	std::cout << "ВХОДНАЯ СТРОКА\:\n" << input << "\n";
	std::cout << "ОЖИДАЕМЫЙ ВЫВОД:\n" << expected << "\n";
	std::cout << "РЕАЛЬНЫЙ ВЫВОД:\n" << actual << "\n\n";

	if (expected == actual) {
		std::cout << "СТАТУС: ПРОЙДЕН\n";
	}
	else {
		std::cout << "СТАТУС: ПРОВАЛЕН\n";
	}
}

std::string replace(std::string input, std::string in, std::string out) {
	size_t begin = 0;
	while (true) {
		size_t index = input.find(in, begin);

		if (index == std::string::npos) {
			break;
		}

		input = input.replace(index, in.size(), out);
		begin = index + out.size();
	}
	return input;
}

std::string truncate(std::string input) {
	std::string new_string;
	for(auto& el : input) {
		if (el != ' ' && el != '\n' && el != '\t' && el != '\r') {
			new_string.append(1, el);
		}
	}
	
	new_string = replace(new_string, "if", "if ");
	new_string = replace(new_string, "then"," then ");
	new_string = replace(new_string, "else", " else ");

	return new_string;
}

void success_1() {
	std::cout << "\nТЕСТ #1\n";
	
	std::string input =
		"if A > B then      \n"
		"  B:= A       \n"
		"else   \n"
		"  B:=20.0;           \n";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string expected = truncate(input);
	std::string actual = b_actual.second;
	
	on_result(expected, actual, input);
}


void success_2() {
	std::cout << "\nТЕСТ #2\n";
	std::string input =
		"if A > B then             \n"
		"  if B > 1 then           \n"
		"    A := B                \n"
		"  else                    \n"
		"    B:= 6.1e2             \n"
		"else if A<25 then         \n"
		"  B:=20.0;                \n";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string expected = truncate(input);
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void success_3() {
	std::cout << "\nТЕСТ #3\n";
	std::string input =
		"if A > B then      \n"
		"  if B > 100 then    \n"
		"    A := B   \n"
		"  else                    \n"
		"    B:= 5.255e+2       \n"
		"else if A<25 then    \n"
		"  B:=20.0;           \n";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string expected = truncate(input);
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void second_then() {
	std::cout << "\nТЕСТ #4\n";
	std::string input =
		"if A > B then      \n"
		"  if B > 100 then then   \n"
		"    A := B   \n"
		"  else                    \n"
		"    B:= 5.255e+2       \n"
		"else if A<25 then    \n"
		"  B:=20.0;           \n";;
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string expected = StatusCodes::SYN_ERROR.toString();
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void second_condition() {
	std::cout << "\nТЕСТ #5\n";

	std::string input =
		"if A > B > C then      \n"
		"  if B > 100 then    \n"
		"    A := B   \n"
		"  else                    \n"
		"    B:= 5.255e+2       \n"
		"else if A<25 then    \n"
		"  B:=20.0;           \n";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax(b_command.second);

	std::string expected = StatusCodes::SYN_EXPR_EXPECT.toString();
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void success_w1() {
	std::cout << "\nТЕСТ #1\n";

	std::string input =
		"if A > B then      \n"
		"  B:= A       \n"
		"else   \n"
		"  B:=20.0;           \n";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax_f(b_command.second);

	std::string expected = "1 2 4 10 10 4 10 10 6 10 10 ";
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}


void success_w2() {
	std::cout << "\nТЕСТ #2\n";
	std::string input =
		"if A > B then         \n"
		"  if B > 1 then       \n"
		"    A := B            \n"
		"  else                \n"
		"    B:= 6.1e2         \n"
		"else if A<25 then     \n"
		"  B:=20.0;            \n";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax_f(b_command.second);

	std::string expected = "1 2 3 4 10 10 5 10 10 2 4 10 10 4 10 10 6 10 10 6 10 10 ";
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void success_w3() {
	std::cout << "\nТЕСТ #3\n";
	std::string input =
		"if A > B then      \n"
		"  if B > 100 then  \n"
		"    A := B         \n"
		"  else             \n"
		"    B:= 5.255e+2   \n"
		"else if A<25 then  \n"
		"  B:=20.0;         \n";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax_f(b_command.second);

	std::string expected = "1 2 3 4 10 10 5 10 10 2 4 10 10 4 10 10 6 10 10 6 10 10 ";
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void second_then_w() {
	std::cout << "\nТЕСТ #4\n";
	std::string input =
		"if A > B then             \n"
		"  if B > 100 then then    \n"
		"    A := B                \n"
		"  else                    \n"
		"    B:= 5.255e+2          \n"
		"else if A<25 then         \n"
		"  B:=20.0;                \n";;
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax_f(b_command.second);

	std::string expected = StatusCodes::SYN_ERROR.toString();
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}

void second_condition_w() {
	std::cout << "\nТЕСТ #5\n";

	std::string input =
		"if A > B > C then      \n"
		"  if B > 100 then      \n"
		"    A := B             \n"
		"  else                 \n"
		"    B:= 5.255e+2       \n"
		"else if A<25 then      \n"
		"  B:=20.0;             \n";
	auto b_command = prepare_command(input);

	if (b_command.first != true)
		return;

	auto b_actual = run_syntax_f(b_command.second);

	std::string expected = StatusCodes::SYN_EXPR_EXPECT.toString();
	std::string actual = b_actual.second;

	on_result(expected, actual, input);
}




int main() {
	setlocale(LC_ALL, "");

	success_1();
	success_2();
	success_3();
	second_then();
	second_condition();

	success_w1();
	success_w2();
	success_w3();
	second_then_w();
	second_condition_w();
	
	return 0;
}
