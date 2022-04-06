#pragma once
#include <stdio.h>
#include <string>
#include "Token.h"

class Quad
{
public:
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
		LABEL,
		WHILE,
		FOR,
		THEN,
		ELSE
	};

	std::string printopType() {
		switch (this->op) {
		case Quad::opType::multiply: return "multiply";
		case Quad::opType::divide: return "divide";
		case Quad::opType::add: return "add";
		case Quad::opType::subtract: return "subtract";
		case Quad::opType::assignment: return "assignment";
		case Quad::opType::greaterthan: return "greater";
		case Quad::opType::lessthan: return "less";
		case Quad::opType::greaterthanequal: return "greater or equal";
		case Quad::opType::lessthanequal: return "less or equal";
		case Quad::opType::equalto: return "equal to";
		case Quad::opType::notequal: return "not equal to";
		case Quad::opType::WHILE: return "WHILE";
		case Quad::opType::FOR: return "FOR";
		case Quad::opType::IF: return "IF";
		case Quad::opType::THEN: return "THEN";
		case Quad::opType::ELSE: return "ELSE";
		default: return "not an OP";
		}
	}

	std::string toString() {
		return "quad complete " + this->destination.tokenString + " " + this->left.tokenString +" "+ this->printopType() +" "+ this->right.tokenString;
	}
	~Quad();
	Quad();
	Quad(Token, Token, Token, Token);
	Quad(Token, Token, Token);
	Quad(Token);
	opType op;
	Token left, right, destination;
};