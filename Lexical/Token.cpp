#include "Token.h"

Token::Token() {
}
Token::Token(std::string text, tokenType type, int cursor) {
	this->tokenString = text;
	this->tempType = type;
	this->position = cursor;
}

Token::~Token() {

}