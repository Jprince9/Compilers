// Lexical.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Token.h"

//{L,D,*,/,=,<,B,>,other, { , } , ( , ) , + , - , , , ;}
enum class StateColumn {
	letter,
	digit,
	multiply,//columns
	divide,
	equal,
	lessthan,
	brk,
	greaterthan,
	other,
	leftbrace,
	rightbrace,
	leftparenthesis,
	rightparenthesis,
	plus,
	minus,
	comma,
	semicolon
};
//{L,D,*,/,=,<,B,>,other, { , } , ( , ) , + , - , , , ;}
enum class StateRow {
	start, // rows
	error,
	mOp,
	intermediate3, //rename
	intValue,
	intermediate5, //rename
	varValue,
	intermediate7, //rename
	intermediate8, //rename
	intermediate9, //rename
	dOp,
	intermediate11, //rename
	assignment,
	requals,
	intermediate14, //rename
	rlessthan,
	rlessthanequal,
	intermediate17, //rename
	rgreaterthan,
	rgreaterthanequal,
	lbrace,
	rbrace,
	lparenthesis,
	rparenthesis,
	plusoperator,
	minusoperator,
	commaValue,
	semicolonValue

};

//input characters from file to determine which column for next state
StateColumn findColumn(char nextChar) {   //FINISH******

	//converts character to ascii DEC for shortened cases
	int asciichar = (int)nextChar;
	char col;
	if (asciichar >= 48 && asciichar <= 57) { //digits
		col = 'a';
	}
	else if(asciichar >= 65 && asciichar <= 90) { //letters
		col = 'b';
	}
	else if (asciichar >= 97 && asciichar <= 122) { //letters
		col = 'b';
	}
	else if (asciichar == 32) { //space
		col = 'c';
	}
	else if (asciichar == 123) { //left brace
		col = 'd';
	}
	else if (asciichar == 125) { //right brace
		col = 'e';
	}
	else if (asciichar == 42) { // * multiply op
		col = 'f';
	}
	else if (asciichar == 47) { // / divide op
		col = 'g';
	}
	else if (asciichar == 61) { // = equal
		col = 'h';
	}
	else if (asciichar == 60) { // < less than
		col = 'i';
	}
	else if (asciichar == 62) { // > greater than
		col = 'j';
	}
	else if (asciichar == 40) { // ( left parenthesis
		col = 'k';
	}
	else if (asciichar == 41) { // ) right parenthesis
		col = 'l';
	}
	else if (asciichar == 43) { // + add op
		col = 'm';
	}
	else if (asciichar == 45) { // - subtract op
		col = 'n';
	}
	else if (asciichar == 44) { // , comma
		col = 'o';
	}
	else if (asciichar == 59) { // ; semicolon
		col = 'p';
	}
	else { //something not listed, other
		col = 'q';
	}

	switch (col) {
	case 'a': 
		std::cout << " digit found \n";
		return StateColumn::digit;
		break;
	case 'b':
		std::cout << " letter found \n";
		return StateColumn::letter;
		break;
	case 'c':
		std::cout << " space found \n";
		return StateColumn::brk;
		break;
	case 'd':
		std::cout << " left brace found\n";
		return StateColumn::leftbrace;
		break;
	case 'e':
		std::cout << " right brace found\n";
		return StateColumn::rightbrace;
		break;
	case 'f':
		std::cout << " multiply found\n";
		return StateColumn::multiply;
		break;
	case 'g':
		std::cout << " divide found\n";
		return StateColumn::divide;
		break;
	case 'h':
		std::cout << " equal found\n";
		return StateColumn::equal;
		break;
	case 'i':
		std::cout << " less than found\n";
		return StateColumn::lessthan;
		break;
	case 'j':
		std::cout << " greater than found\n";
		return StateColumn::greaterthan;
		break;
	case 'k':
		std::cout << " left parenthesis found\n";
		return StateColumn::leftparenthesis;
		break;
	case 'l':
		std::cout << " right parenthesis found \n";
		return StateColumn::rightparenthesis;
		break;
	case 'm':
		std::cout << " add found\n";
		return StateColumn::plus;
		break;
	case 'n':
		std::cout << " subtract found\n";
		return StateColumn::minus;
		break;
	case 'o':
		std::cout << " comma found \n";
		return StateColumn::comma;
		break;
	case 'p':
		std::cout << " semicolon found\n";
		return StateColumn::semicolon;
		break;
	default:
		std::cout << " something else was found \n";
		return StateColumn::other;
		break;
	}
}


int main()
{
	StateRow sT[28][17]{
		{StateRow::intermediate5,StateRow::intermediate3,StateRow::mOp,StateRow::intermediate7,StateRow::intermediate11,StateRow::intermediate14,StateRow::start,StateRow::intermediate17,StateRow::error,StateRow::lbrace,StateRow::rbrace,StateRow::lparenthesis,StateRow::rparenthesis,StateRow::plusoperator,StateRow::minusoperator,StateRow::commaValue,StateRow::semicolonValue},
		/*not needed?*/{StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error},
		/*not needed?*/{StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp,StateRow::mOp},
		{StateRow::intValue,StateRow::intermediate3,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue},
		/*not needed?*/{StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue},
		{StateRow::intermediate5,StateRow::intermediate5,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue},
		/*not needed?*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		{StateRow::dOp,StateRow::dOp,StateRow::intermediate8,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp},
		{StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate9,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8},
		{StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::start,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8},
		/*not needed?*/{StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp},
		{StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::requals,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment},
		/*not needed?*/{StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment},
		/*not needed?*/{StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals,StateRow::requals},
		{StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthanequal,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan},
		/*not needed?*/{StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan},
		/*not needed?*/{StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal,StateRow::rlessthanequal},
		{StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthanequal,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan},
		/*not needed?*/{StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan},
		/*not needed?*/{StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal,StateRow::rgreaterthanequal},
		/*not needed?*/{StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace,StateRow::lbrace},
		/*not needed?*/{StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace,StateRow::rbrace},
		/*not needed?*/{StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis,StateRow::lparenthesis},
		/*not needed?*/{StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis,StateRow::rparenthesis},
		/*not needed?*/{StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator,StateRow::plusoperator},
		/*not needed?*/{StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator,StateRow::minusoperator},
		/*not needed?*/{StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue,StateRow::commaValue},
		/*not needed?*/{StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue,StateRow::semicolonValue},

	};

	std::string tempString;
	std::vector<Token> tokens = std::vector<Token>();

	int currentpoint = 0;

	std::string read = "CLASS Pgm1 { CONST M = 13, N = 56; VAR X, Y, Z;  Y = 97; X = M * N + 18 - Y; }"; //scan entire file save to this string
	StateRow currentState = StateRow::start;

	while (currentpoint < read.length()) {

		switch (currentState) {
		case StateRow::start: {
			std::cout << " state = start \n";
			tempString = "";
			tempString += read[currentpoint];
			break;
		}
		case StateRow::error: {
			std::cout << " state = error \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::mOp: {
			std::cout << " state = mOp \n";
			tempString += read[currentpoint]; //reads single character where pointer currently located
			std::cout << tempString;
			tokens.push_back(Token(tempString, Token::tokenType::multiply, currentpoint)); //adds a new token to vector
			StateRow currentState = StateRow::start; //restarts at beginning state
			break;
		}
		case StateRow::intermediate3: {
			std::cout << " state = int.3 \n";
			tempString += read[currentpoint];
			break;
		}
		case StateRow::intValue: {
			std::cout << " state = intValue \n";
			std::cout << "finished token = " << tempString <<"\n";
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::intermediate5: {
			std::cout << " state = int.5 \n";
			tempString += read[currentpoint];
			break;
		}
		case StateRow::varValue: {
			std::cout << " state = varValue \n";
			std::cout << "finished token = " << tempString << "\n";
			StateRow currentState = StateRow::start;
			tempString = "";
			currentpoint--;
			break;
		}
		case StateRow::intermediate7: {
			std::cout << " state = int.7 \n";
			tempString += read[currentpoint];
			break;
		}
		case StateRow::intermediate8: {
			std::cout << " state = int.8 \n";
			tempString += read[currentpoint];
			break;
		}
		case StateRow::intermediate9: {
			std::cout << " state = int.9 \n";
			tempString += read[currentpoint];
			break;
		}
		case StateRow::dOp: {
			std::cout << " state = dOp \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::intermediate11: {
			std::cout << " state = int.11 \n";
			tempString += read[currentpoint];
			break;
		}
		case StateRow::assignment: {
			std::cout << " state = assignment \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::requals: {
			std::cout << " state = requals \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::intermediate14: {
			std::cout << " state = int.14 \n";
			tempString += read[currentpoint];
			break;
		}
		case StateRow::rlessthan: {
			std::cout << " state = rlessthan \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::rlessthanequal: {
			std::cout << " state = rlessthanequal \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::intermediate17: {
			std::cout << " state = int.17 \n";
			tempString += read[currentpoint];
			break;
		}
		case StateRow::rgreaterthan: {
			std::cout << " state = rgreaterthan \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::rgreaterthanequal: {
			std::cout << " state = rgreaterthanequal \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::lbrace: {
			std::cout << " state = lbrace \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::rbrace: {
			std::cout << " state = rbrace \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::lparenthesis: {
			std::cout << " state = lparenthesis \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::rparenthesis: {
			std::cout << " state = rparenthesis \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::plusoperator: {
			std::cout << " state = plusoperator \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::minusoperator: {
			std::cout << " state = minusoperator \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::commaValue: {
			std::cout << " state = commaValue \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::semicolonValue: {
			std::cout << " state = semicolonValue \n";
			std::cout << tempString;
			StateRow currentState = StateRow::start;
			break;
		}
		}

		currentState = sT[int(currentState)][int(findColumn(read[currentpoint++]))]; //sets current state to next place on the table

		std::cout << "new string is " << tempString << "\n";
																   //moves pointer to the next location in the string
	}

}

//FOREACH TOKENS IN VECTOR



	//implement if or while  FINISHED?

	//needs a way to read an entire input file, stop at each stop state, resume from next character after stop state

	//needs a switch case to assign each state based on 2d array return

	//needs a way to output each item to a table with correct type, address, and value


/* */
static void analyze() {

}







// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu