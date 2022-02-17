#pragma once
#include <string>
class Symbol
{
public:
	std::string symbolName;
	std::string className;
	int value;
	int address;
	std::string segment;


	Symbol();
	Symbol(std::string, std::string, int, int, std::string);
	~Symbol();
};

