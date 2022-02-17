#include "Symbol.h"

Symbol::Symbol() {
}
Symbol::Symbol(std::string symbolName, std::string className, int value, int address, std::string segment) {
	this->symbolName = symbolName;
	this->className = className;
	this->value = value;
	this->address = address;
	this->segment = segment;
}

Symbol::~Symbol() {

}
