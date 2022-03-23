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
		relationalop,
		WHILE,
		FOR,
		IF,
		THEN,
		ELSE,
		LB,
		RB,
		LP,
		RP,
		comma,
		semicolon,
		CONST,
		VAR,
		CLASS,
		LOOP
	};

	tokenType tempType;
	Token();
	Token(std::string, Token::tokenType, int);
	~Token();

	std::string printTokenType() {
		switch (this->tempType) {
		case tokenType::integer: return "integer";
		case tokenType::variable: return "variable";
		case tokenType::multiply: return "multiply";
		case tokenType::divide: return "divide";
		case tokenType::add: return "add";
		case tokenType::subtract: return "subtract";
		case tokenType::assignment: return "assignment";
		case tokenType::relationalop: return "relationalop";
		case tokenType::WHILE: return "WHILE";
		case tokenType::FOR: return "FOR";
		case tokenType::IF: return "IF";
		case tokenType::THEN: return "THEN";
		case tokenType::ELSE: return "ELSE";
		case tokenType::LB: return "LB";
		case tokenType::RB: return "RB";
		case tokenType::LP: return "LP";
		case tokenType::RP: return "RP";
		case tokenType::comma: return "comma";
		case tokenType::semicolon: return "semicolon";
		case tokenType::CONST: return "CONST";
		case tokenType::VAR: return "VAR";
		case tokenType::CLASS: return "CLASS";
		default: return "not a token";
		}
	};

};

