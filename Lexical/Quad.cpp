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
	}
}

Quad::~Quad() {

}