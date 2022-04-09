#include "Token.h"

Token::Token() {
	this->tokenString = "";
	this->tempType = Token::tokenType::relationalop;
	this->position = -1;
}
Token::Token(std::string text, tokenType type, int cursor) {
	this->tokenString = text;
	this->tempType = type;
	this->position = cursor;
}

Token::~Token() {

}