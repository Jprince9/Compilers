#include "Quad.h"

Quad::Quad() {
	this->label = Label(0);
}
Quad::Quad(opType op, Label l) {
	this->label = l;

}
Quad::Quad(Token op, Token left, Token right, Token destination) {
	this->left = left;
	this->right = right;
	this->destination = destination;
	this->op = Quad::getOpType(op);
	this->label = Label(0);
}

Quad::Quad(Token op){
	this->destination = Token("?", Token::tokenType::none, -5);
	this->left = Token("?", Token::tokenType::none, -5);
	this->right = Token("?", Token::tokenType::none, -5);
	this->op = Quad::getOpType(op);
	this->label = Label(0);
}


Quad::Quad(Token op, Label l, Token reverseop) {
	this->op = Quad::getOpType(op);
	this->label = l;
	this-> reverseop = Quad::getOpType(reverseop);
}

Quad::Quad(Label l){
	this->label = l;
	this->op = opType::NOOP;
}

Quad::Quad(Token op, Label l) {
	this->label = l;
	this->op = Quad::getOpType(op);
}

Quad::~Quad() {

}

Quad::opType Quad::getOpType(Token op) {
	switch (op.tempType) {
	case Token::tokenType::add: {
		return opType::add;
	}
	case Token::tokenType::subtract: {
		return opType::subtract;
	}
	case Token::tokenType::multiply: {
		return opType::multiply;
	}
	case Token::tokenType::divide: {
		return opType::divide;
	}
	case Token::tokenType::assignment: {
		return opType::assignment;
	}
	case Token::tokenType::IF: {
		return opType::IF;
	}
	case Token::tokenType::WHILE: {
		return opType::WHILE;
	}
	case Token::tokenType::THEN: {
		return opType::THEN;
	}
	case Token::tokenType::ELSE: {
		return opType::ELSE;
	}
	case Token::tokenType::LOOP:{
		return opType::LOOP;				   
	}
	case Token::tokenType::relationalop: {
		if (op.tokenString == "==") {
			return opType::equalto;
		}
		else if (op.tokenString == "<=") {
			return opType::lessthanequal;
		}
		else if (op.tokenString == ">=") {
			return opType::greaterthanequal;
		}
		else if (op.tokenString == "<") {
			return opType::lessthan;
		}
		else if (op.tokenString == ">") {
			return opType::greaterthan;
		}
		else if (op.tokenString == "!=")
			return opType::notequal;
	}
	default: return opType::ERROR;
	}
}