#include "Quad.h"

Quad::Quad() {
}
Quad::Quad(Token op, Token left, Token right, Token destination) {
	this->left = left;
	this->right = right;
	this->destination = destination;
	switch (op.tempType) {
	case Token::tokenType::add: {
		this->op = opType::add;
		break;
	}
	case Token::tokenType::subtract: {
		this->op = opType::subtract;
		break;
	}
	case Token::tokenType::multiply: {
		this->op = opType::multiply;
		break;
	}
	case Token::tokenType::divide: {
		this->op = opType::divide;
		break;
	}
	case Token::tokenType::assignment: {
		this->op = opType::assignment;
		break;
	}
	case Token::tokenType::IF: {
		this->op = opType::IF;
		break;
	}
							 //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	case Token::tokenType::relationalop: {
		switch (op.tokenString) {
		case std::string::"==": {
			this->op = opType::equalto;
			break;
		}
		case std::string::"<=": {
			this->op = opType::lessthanequal;
			break;
		}
		case std::string::">=": {
			this->op = opType::greaterthanequal;
			break;
		}
		case std::string::"<": {
			this->op = opType::lessthan;
			break;
		}
		case std::string::">": {
			this->op = opType::greaterthan;
			break;
		}
		case std::string::"!=": {
			this->op = opType::notequal;
			break;
		}
		}
		break;
	}
	}
}

Quad::~Quad() {

}