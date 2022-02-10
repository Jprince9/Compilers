#pragma once
#include <stdio.h>
#include <string>
class Token
{
public:
	std::string tokenString;
	int position;

	enum class tokenType {
		integer,
		variable,
		multiply,
		divide,
		add,
		subtract,
		assignment,
		relationalequal,
		relationallessthan,
		relationallessthanequal,
		relationalgreaterthan,
		relationalgreaterthanequal,
		type
	};

	tokenType tempType;
	Token();
	Token(std::string, Token::tokenType, int);
	~Token();


};

