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
		NOOP,
		LOOP
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
		case Quad::opType::LOOP: return "LOOP";
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
		case Quad::opType::greaterthan: return "G";
		case Quad::opType::lessthan: return "L";
		case Quad::opType::greaterthanequal: return "GE";
		case Quad::opType::lessthanequal: return "LE";
		case Quad::opType::equalto: return "E";
		case Quad::opType::notequal: return "NE";
		case Quad::opType::WHILE: return "WHILE";
		case Quad::opType::LOOP: return "LOOP";
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
		case Quad::opType::LOOP:
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

	std::string assemble() {
		std::string output = "";
		switch (this->op)
		{
		case Quad::opType::add: {
			if (this->left.tempType != Token::tokenType::integer) {
				output += "mov ax, [" + this->left.tokenString + "]\n";
			}
			else {
				output += "mov ax, " + this->left.tokenString + "\n";
			}


			if (this->right.tempType != Token::tokenType::integer) {
				output += "add ax, [" + this->right.tokenString + "]\n";
			}
			else {
				output += "add ax, " + this->right.tokenString + "\n";
			}
			output += "mov [" + this->destination.tokenString + "], ax\n";
			break;
		}


		case Quad::opType::subtract: {
			if (this->left.tempType != Token::tokenType::integer) {
				output += "mov ax, [" + this->left.tokenString + "]\n";
			}
			else {
				output += "mov ax, " + this->left.tokenString + "\n";
			}


			if (this->right.tempType != Token::tokenType::integer) {
				output += "sub ax, [" + this->right.tokenString + "]\n";
			}
			else {
				output += "sub ax, " + this->right.tokenString + "\n";
			}
			output += "mov [" + this->destination.tokenString + "], ax\n";
			break;
		}


		case Quad::opType::multiply: {
			if (this->left.tempType != Token::tokenType::integer) {
				output += "mov eax, [" + this->left.tokenString + "]\n";
			}
			else {
				output += "mov eax, " + this->left.tokenString + "\n";
			}

			if (this->right.tempType != Token::tokenType::integer) {
				output += "mul [" + this->right.tokenString + "]\n";
			}
			else {
				output += "mul " + this->right.tokenString + "\n";
			}

			output += "mov [" + this->destination.tokenString + "], eax\n";
			break;
		}


		case Quad::opType::divide: {
			output += "mov edx, 0";
			if (this->left.tempType != Token::tokenType::integer) {
				output += "mov eax, [" + this->left.tokenString + "]\n";
			}
			else {
				output += "mov eax, " + this->left.tokenString + "\n";
			}

			if (this->right.tempType != Token::tokenType::integer) {
				output += "div [" + this->right.tokenString + "]\n";
			}
			else {
				output += "div " + this->right.tokenString + "\n";
			}

			output += "mov [" + this->destination.tokenString + "], eax\n";
			break;
		}


		case Quad::opType::IF: {
			break;
		}


		case Quad::opType::THEN: {
			output += "J" + this->printreverseopType() + " " + this->label.ll + "\n";
			break;
		}


		case Quad::opType::ELSE: {
			output += "jmp " + this->label.ll + "\n";
			break;
		}


		case Quad::opType::WHILE: {
			break;;
		}


		case Quad::opType::LOOP: {
			break;
		}


		case Quad::opType::assignment: {
			if (this->left.tempType != Token::tokenType::integer) {
				output += "mov ax, [" + this->right.tokenString + "]\n";
			}
			else {
				output += "mov ax, " + this->right.tokenString + "\n";
			}

			output += "mov [" + this->destination.tokenString + "], ax\n";					
			break;
		}


		case Quad::opType::lessthan:;
		case Quad::opType::greaterthan:;
		case Quad::opType::lessthanequal:;
		case Quad::opType::greaterthanequal:;
		case Quad::opType::equalto:;
		case Quad::opType::notequal:
			//covers all 
			//mov
			//mov
			//cmp
			break;
		case Quad::opType::NOOP:

			break;
		}
		return output;
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