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
		LOOP,
		jmp,
		input,
		output
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
		case Quad::opType::jmp: return "jmp";
		case Quad::opType::input: return "input";
		case Quad::opType::output: return "output";
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
		case Quad::opType::input: return "input";
		case Quad::opType::output: return "output";
		default: return "not an OP" + (int)reverseop;
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
		case Quad::opType::jmp:
			return "quad complete " + this->printopType() + " " + this->label.toString();
		case Quad::opType::LOOP:
			return "quad complete " + this->printopType() + " " + this->label.toString() + " " + this->printreverseopType();
		case Quad::opType::WHILE:
		case Quad::opType::FOR:
		case Quad::opType::IF:
			return "quad complete " + this->destination.tokenString + " " + this->left.tokenString + " " + this->printopType() + " " + this->right.tokenString;
		case Quad::opType::THEN:
			return "quad complete " + this->printopType() + " " + this->label.toString() + " " + this->printreverseopType();
		case Quad::opType::ELSE:
			return "quad complete " + this->printopType() + " " + this->label.toString();
		case Quad::opType::NOOP:
			return "quad complete " + this->label.toString();
		case Quad::opType::ERROR:
			return "Quad ERROR " + this->printopType();
		case Quad::opType::input: 
			return "Quad complete input";
		case Quad::opType::output: 
			return "quad complete output";
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
				output += "mul word [" + this->right.tokenString + "]\n";
			}
			else {
				output += "mul word " + this->right.tokenString + "\n";
			}

			output += "mov [" + this->destination.tokenString + "], eax\n";
			break;
		}


		case Quad::opType::divide: {
			output += "mov edx, 0\n";
			if (this->left.tempType != Token::tokenType::integer) {
				output += "mov eax, [" + this->left.tokenString + "]\n";
			}
			else {
				output += "mov eax, " + this->left.tokenString + "\n";
			}

			if (this->right.tempType != Token::tokenType::integer) {
				output += "div word [" + this->right.tokenString + "]\n";
			}
			else {
				output += "div word " + this->right.tokenString + "\n";
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
			output += "J" + this->printreverseopType() + " " + this->label.ll + "\n";
			break;
		}
		case Quad::opType::jmp: {
			output += "jmp " + this->label.ll + "\n";
			break;
		}

		case Quad::opType::assignment: {
			if (this->right.tempType != Token::tokenType::integer) {
				output += "mov ax, [" + this->right.tokenString + "]\n";
			}
			else {
				output += "mov ax, " + this->right.tokenString + "\n";
			}

			output += "mov [" + this->destination.tokenString + "], ax\n";
			break;
		}

		case Quad::opType::input: {
			output += "\n\ncall PrintString\n";			
			output += "call GetAnInteger\n";
			output += "mov ax, [ReadInt]\n";
			output += "mov [" + this->destination.tokenString + "], ax\n\n\n";
			break;
		}

		case Quad::opType::output: {
			output += "\n\nmov ax, [" + this->destination.tokenString + "]\n";
			output += "call ConvertIntegerToString\n";
			output += "mov eax, 4\n";
			output += "mov ebx, 1\n";
			output += "mov ecx, Result\n";
			output += "mov edx, ResultEnd\n";
			output += "int 80h\n\n\n";
			break;
		}


		case Quad::opType::lessthan:;
		case Quad::opType::greaterthan:;
		case Quad::opType::lessthanequal:;
		case Quad::opType::greaterthanequal:;
		case Quad::opType::equalto:;
		case Quad::opType::notequal:
			if (this->left.tempType != Token::tokenType::integer) {
				output += "mov ax, [" + this->left.tokenString + "]\n";
			}
			else {
				output += "mov ax, " + this->left.tokenString + "\n";
			}

			if (this->right.tempType != Token::tokenType::integer) {
				output += "mov bx, [" + this->right.tokenString + "]\n";
			}
			else {
				output += "mov bx, " + this->right.tokenString + "\n";
			}

			output += "cmp ax, bx\n";
			break;
		case Quad::opType::NOOP:
			output += this->label.ll + ":\n";
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
	Quad(Token, Token);
	Quad(Token, Label);
	Quad(opType, Label);
	Label label;
	opType reverseop;
	opType op;
	Token left, right, destination;
};