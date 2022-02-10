// Lexical.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Token.h"

//{L,D,*,/,=,<,B,>,other, { , } , ( , ) , ; , , + , - , !}
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
		std::cout << " space \n";
		return StateColumn::brk;
		break;
	case 'd':
		std::cout << " left brace \n";
		return StateColumn::rightbrace;
		break;
	case 'e':
		std::cout << " right brace \n";
		return StateColumn::leftbrace;
		break;
	case 'f':
		std::cout << " multiply \n";
		return StateColumn::multiply;
		break;
	case 'g':
		std::cout << " divide \n";
		return StateColumn::divide;
		break;
	case 'h':
		std::cout << " equal \n";
		return StateColumn::equal;
		break;
	case 'i':
		std::cout << " less than \n";
		return StateColumn::lessthan;
		break;
	case 'j':
		std::cout << " greater than \n";
		return StateColumn::greaterthan;
		break;
	case 'k':
		std::cout << " left parenthesis \n";
		return StateColumn::leftparenthesis;
		break;
	case 'l':
		std::cout << " right parenthesis \n";
		return StateColumn::rightparenthesis;
		break;
	case 'm':
		std::cout << " add \n";
		return StateColumn::plus;
		break;
	case 'n':
		std::cout << " subtract \n";
		return StateColumn::minus;
		break;
	case 'o':
		std::cout << " comma \n";
		return StateColumn::comma;
		break;
	case 'p':
		std::cout << " semicolon \n";
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

	//20 is error state
	//21 multiply op * <mop>
	//22 int value <int>
	//23 variable value <var>
	//24 multiply op / <mop>
	//25 assignment op = <assignment>
	//26 relational op == <relop>
	//27 relational op < <relop>
	//28 relational op <= <relop>
	//29 relational op > <relop>
	//30 relational op >= <relop>

	StateRow sT[28][17]{
		{StateRow::intermediate5,StateRow::intermediate3,StateRow::mOp,StateRow::intermediate7,StateRow::intermediate11,StateRow::intermediate14,StateRow::start,StateRow::intermediate17,StateRow::error},
		{StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error,StateRow::error}


		//continue for rest of table
	};


	int statetable[20][9] = {
		//{L,D,*,/,=,<,B,>,other, { , } , , , ; , , + , - }
		  {5,3,2,7,11,14,0,17,1},		//0
		  {20,20,20,20,20,20,20,20,20}, //1 error
		  {21,21,21,21,21,21,21,21,21}, //2 multiply
		  {4,3,4,4,4,4,4,4,1},			//3
		  {22,22,22,22,22,22,22,22,22}, //4 int
		  {5,5,6,6,6,6,6,6,1},			//5
		  {23,23,23,23,23,23,23,23,23}, //6 var
		  {10,10,8,10,10,10,10,10,1},   //7
		  {8,8,9,8,8,8,8,8,8},			//8
		  {8,8,8,0,8,8,8,8,8},			//9
		  {24,24,24,24,24,24,24,24},	//10 divide
		  {12,12,12,12,13,12,12,12,1},  //11
		  {25,25,25,25,25,25,25,25,25}, //12 assign =
		  {26,26,26,26,26,26,26,26,26}, //13 relational ==
		  {15,15,15,15,16,15,15,15,1},  //14
		  {27,27,27,27,27,27,27,27,27}, //15 relational <
		  {28,28,28,28,28,28,28,28,28}, //16 relational <=
		  {18,18,18,18,19,18,18,18,1},	//17
		  {29,29,29,29,30,29,29,29,29}, //18 relational >
		  {30,30,30,30,30,30,30,30,30}  //19 relational >=
	};

	std::string tempString;
	std::vector<Token> tokens = std::vector<Token>();

	int currentpoint = 0;
	bool finished = false;
	std::string read = "CLASS Pgm1 { CONST M = 13, N = 56; VAR X, Y, Z;  Y = 97; X = M * N + 18 - Y; }"; //scan entire file save to this string
	StateRow currentState = StateRow::start;
	while (currentpoint < read.length()) {
		switch (currentState) {
		case StateRow::start: {
			tempString = "";
			break;
		}
		case StateRow::error: {
			std::cout << "error";
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::mOp: {
			tempString += read[currentpoint]; //reads single character where pointer currently located
			tokens.push_back(Token(tempString, Token::tokenType::multiply, currentpoint)); //adds a new token to vector
			StateRow currentState = StateRow::start; //restarts at beginning state
			break;
		}
		case StateRow::intermediate3: {
			tempString += read[currentpoint];
			break;
		}
		case StateRow::intValue: {
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::intermediate5: {
			tempString += read[currentpoint];
			break;
		}
		case StateRow::varValue: {
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::intermediate7: {
			tempString += read[currentpoint];
			break;
		}
		case StateRow::intermediate8: {
			tempString += read[currentpoint];
			break;
		}
		case StateRow::intermediate9: {
			tempString += read[currentpoint];
			break;
		}
		case StateRow::dOp: {
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::intermediate11: {
			tempString += read[currentpoint];
			break;
		}
		case StateRow::assignment: {
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::requals: {
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::intermediate14: {
			tempString += read[currentpoint];
			break;
		}
		case StateRow::rlessthan: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::rlessthanequal: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::intermediate17: {
			tempString += read[currentpoint];
			break;
		}
		case StateRow::rgreaterthan: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::rgreaterthanequal: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::lbrace: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::rbrace: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::lparenthesis: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::rparenthesis: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::plusoperator: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::minusoperator: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::commaValue: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		case StateRow::semicolonValue: {
			finished = true;
			StateRow currentState = StateRow::start;
			break;
		}
		}
		currentState = sT[int(currentState)][int(findColumn(read[currentpoint]))]; //sets current state to next place on the table
		++currentpoint; //moves pointer to the next location in the string
	}

	char a = 'B';
	int ascichar = (int)a;
	std::cout << statetable[0][0] << "ascii of this is" << ascichar;
	std::cout << "";

	//findColumn(a);

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