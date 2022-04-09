#pragma once
#include <stdio.h>
#include <string>
#include "Token.h"
#include "Label.h"

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
		ELSE,
		ERROR,
		NOOP
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
		case Quad::opType::NOOP: return "NO OP";
		case Quad::opType::ERROR: return "ERROR";
		default: return "not an OP";
		}
	}

	std::string printreverseopType() {
		switch (this->reverseop) {
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
		case Quad::opType::NOOP: return "NO OP";
		case Quad::opType::ERROR: return "ERROR";
		default: return "not an OP";
		}
	}


	std::string toString() {
		switch (this->op)
		{
		case Quad::opType::multiply:
		case Quad::opType::divide:
		case Quad::opType::add:
		case Quad::opType::subtract:
		case Quad::opType::assignment:
		case Quad::opType::greaterthan:
		case Quad::opType::lessthan:
		case Quad::opType::greaterthanequal:
		case Quad::opType::lessthanequal:
		case Quad::opType::equalto:
		case Quad::opType::notequal:
			return "quad complete " + this->destination.tokenString + " " + this->left.tokenString + " " + this->printopType() + " " + this->right.tokenString;

		case Quad::opType::WHILE:
		case Quad::opType::FOR:
		case Quad::opType::IF:
			return "quad complete " + this->destination.tokenString + " " + this->left.tokenString + " " + this->printopType() + " " + this->right.tokenString;


		case Quad::opType::THEN:
		case Quad::opType::ELSE:
			return "quad complete " + this->printopType() + " " + this->label.toString() + " " + this->printreverseopType();
		case Quad::opType::NOOP:
			return "quad complete " + this->label.toString();
		case Quad::opType::ERROR:
			return "Quad ERROR ";
		}
	}
	opType getOpType(Token);

	~Quad();
	Quad();
	Quad(Token, Token, Token, Token);
	Quad(Token, Token, Token);
	Quad(Token, Label, Token);
	Quad(Token);
	Quad(Label);
	Label label;
	opType reverseop;
	opType op;
	Token left, right, destination;
};