#include "Label.h"

int Label::labelcount = 0;

Label::Label() {
	this->ll = "L" + std::to_string(labelcount++);
	this->address = -1;
}

Label::Label(int i) {
	this->address = -1;
}

Label::~Label() {

}

void Label::setAddress(int address) { //use at the end of the stack to set address
	this->address = address;
}

int Label::getAddress() {
	return this->address;
}