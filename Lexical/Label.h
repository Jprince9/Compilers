#pragma once
#include <stdio.h>
#include <string>

class Label
{
public:
	
	std::string toString() {
		return "label complete ";
	};
	~Label();
	Label();
	Label(std::string label);
};