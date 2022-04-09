#pragma once
#include <stdio.h>
#include <string>



class Label
{

public:
	static int labelcount;
	std::string toString() {
		return "Label: " + this->ll;
	};


	~Label();
	Label();
	Label(int);
	std::string ll;
	int address = 0;
	void setAddress(int address); //define later in cpp
	int getAddress(); //define later in cpp
};