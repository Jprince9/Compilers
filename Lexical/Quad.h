#pragma once
#include <stdio.h>
#include <string>
#include "Token.h"

class Quad
{
	enum class opType {
		multiply,
		divide,
		add,
		subtract,
		assignment,
		greaterthan,
		lessthan,
		greaterthanequal,
		lessthanequal,
		equalto,
		notequal,
		IF,
		JUMP,
		LABEL
	};
	Quad();
	Quad(Token, Token, Token, Token);
	opType op;
	Token left, right, destination;
};