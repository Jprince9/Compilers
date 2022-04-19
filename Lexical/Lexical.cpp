// Lexical.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Token.h"
#include <fstream>
#include <sstream>
#include "Symbol.h"
#include "Quad.h"
#include "Label.h"
using namespace std;




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

enum class Precedence {
	takes,
	gives,
	equal,
	none
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
	else if (asciichar == 32 || asciichar == 13 || asciichar == 10 || asciichar == 9) { //space
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
		//std::cout << " digit found \n";
		return StateColumn::digit;
		break;
	case 'b':
		//std::cout << " letter found \n";
		return StateColumn::letter;
		break;
	case 'c':
		//std::cout << " space found \n";
		return StateColumn::brk;
		break;
	case 'd':
		//std::cout << " left brace found\n";
		return StateColumn::leftbrace;
		break;
	case 'e':
		//std::cout << " right brace found\n";
		return StateColumn::rightbrace;
		break;
	case 'f':
		//std::cout << " multiply found\n";
		return StateColumn::multiply;
		break;
	case 'g':
		//std::cout << " divide found\n";
		return StateColumn::divide;
		break;
	case 'h':
		//std::cout << " equal found\n";
		return StateColumn::equal;
		break;
	case 'i':
		//std::cout << " less than found\n";
		return StateColumn::lessthan;
		break;
	case 'j':
		//std::cout << " greater than found\n";
		return StateColumn::greaterthan;
		break;
	case 'k':
		//std::cout << " left parenthesis found\n";
		return StateColumn::leftparenthesis;
		break;
	case 'l':
		//std::cout << " right parenthesis found \n";
		return StateColumn::rightparenthesis;
		break;
	case 'm':
		//std::cout << " add found\n";
		return StateColumn::plus;
		break;
	case 'n':
		//std::cout << " subtract found\n";
		return StateColumn::minus;
		break;
	case 'o':
		//std::cout << " comma found \n";
		return StateColumn::comma;
		break;
	case 'p':
		//std::cout << " semicolon found\n";
		return StateColumn::semicolon;
		break;
	default:
		//std::cout << " something else was found \n";
		return StateColumn::other;
		break;
	}
}


int mapToken(Token token) {

	switch (token.tempType) {
	case Token::tokenType::relationalop: {
		if (token.tokenString == ">") {
			return 13;
		}
		else if (token.tokenString == "<") {
			return 14;
		}
		else if (token.tokenString == ">=") {
			return 15;
		}
		else if (token.tokenString == "<=") {
			return 16;
		}
		else if (token.tokenString == "!=") {
			return 12;
		}
		else if (token.tokenString == "==") {
			return 11;
		}
	}
	case Token::tokenType::assignment: {
		return 1;
	}
	case Token::tokenType::divide: {
		return 7;
	}
	case Token::tokenType::multiply: {
		return 6;
	}
	case Token::tokenType::add: {
		return 2;
	}
	case Token::tokenType::subtract: {
		return 3;
	}
	case Token::tokenType::LB: {
		return 17;
	}
	case Token::tokenType::RB: {
		return 18;
	}
	case Token::tokenType::LP: {
		return 4;
	}
	case Token::tokenType::RP: {
		return 5;
	}
	case Token::tokenType::IF: {
		return 8;
	}
	case Token::tokenType::ELSE: {					
		return 20;					 
	}
	/*case Token::tokenType::FOR: {
		return;
	}*/
	case Token::tokenType::WHILE: {
		return 10;
	}
	case Token::tokenType::THEN: {
		return 9;
	}
	case Token::tokenType::semicolon: {
		return 0;
	}
	case Token::tokenType::LOOP: {
		return 19;
	}
	}
}

void PrintOPStack(std::vector<Token> vector) {
	int x = vector.size();
	int y = 0;
	cout << "printing Operator Stack " << endl;
	if(x > 0) {
		while (x > 0) {
			cout << vector[y].tokenString << endl;
			x--;
			y++;
		}
	};
}

void PrintSymbStack(std::vector<Token> vector) {
	int x = vector.size();
	int y = 0;
	cout << "printing Symbol Stack " << endl;
	if (x > 0) {
		while (x > 0) {
			cout << vector[y].tokenString << endl;
			x--;
			y++;
		}
	};
}

void PrintQuad(std::vector<Quad> quad) {
	int x = quad.size();
	int y = 0;
	if (x > 0) {
		cout << "printing Quads  " << endl;
		while (x > 0) {
			std::cout << quad[y].toString() << endl;
			x--;
			y++;
		}
	};
}



Token reverserelational(Quad::opType input) {
	Token tok = Token();
	tok.tempType = Token::tokenType::relationalop;
	switch (input)
	{
	case Quad::opType::lessthan: {
		tok.tokenString = ">=";
		break;
	}

	case Quad::opType::greaterthan: {
		tok.tokenString = "<=";
		break;
	}
	case Quad::opType::lessthanequal: {
		tok.tokenString = ">";
		break;
	}
	case Quad::opType::greaterthanequal: {
		tok.tokenString = "<";
		break;
	}
	case Quad::opType::equalto: {
		tok.tokenString = "!=";
		break;
	}
	case Quad::opType::notequal: {
		tok.tokenString = "==";
		break;
	}

	}
	return tok;
}




int main()
{
	string temps[] = { "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9", "t10", "t11", "t12", "t13", "t14", "t15" }; //used for temp number assignment
	ofstream file;
	file.open("output.txt");
	ifstream input("input.txt");
	string read;
	if (input) {
		ostringstream ss;
		ss << input.rdbuf();
		read = ss.str();
	}

	//this is my enumerated state table
	StateRow sT[28][17]{
		{StateRow::intermediate5,StateRow::intermediate3,StateRow::mOp,StateRow::intermediate7,StateRow::intermediate11,StateRow::intermediate14,StateRow::start,StateRow::intermediate17,StateRow::error,StateRow::lbrace,StateRow::rbrace,StateRow::lparenthesis,StateRow::rparenthesis,StateRow::plusoperator,StateRow::minusoperator,StateRow::commaValue,StateRow::semicolonValue},
		/*error*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*mOp*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		{StateRow::intValue,StateRow::intermediate3,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue,StateRow::intValue},
		/*intValue*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		{StateRow::intermediate5,StateRow::intermediate5,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue,StateRow::varValue},
		/*varValue*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		{StateRow::dOp,StateRow::dOp,StateRow::intermediate8,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp,StateRow::dOp},
		{StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate9,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8},
		{StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::start,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8,StateRow::intermediate8},
		/*dOp*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		{StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::requals,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment,StateRow::assignment},
		/*assignment*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*requals*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		{StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthanequal,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan,StateRow::rlessthan},
		/*rlessthan*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*rlessthanequal*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		{StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthanequal,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan,StateRow::rgreaterthan},
		/*rgreaterthan*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*rgreaterthanequal*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*lbrace*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*rbrace*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*lparenthesis*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*rparenthesis*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*plusoperator*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*minusoperator*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*commaValue*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
		/*semicolonValue*/{StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start,StateRow::start},
	};

	std::string tempString = "";
	std::vector<Token> tokens = std::vector<Token>();

	int currentpoint = 0;

	char semi = ';';
	char coma = ',';
	char spce = ' ';
	int step = 1;

	//std::string read = "CLASS Pgm1 { ((CONST M = 13, N == 56; VAR X, Y, Z; Y = 97; X = M * N + 18 - Y; ))}"; //scan entire file save to this string


	StateRow currentState = sT[0][int(findColumn(read[currentpoint]))];


	while (currentpoint < read.length()) {
		//std::cout<<"STEP : " << step << std::endl;
		step = step + 1;
		switch (currentState) {
		case StateRow::start: {
			//std::cout << " state = start \n";
			tempString = "";
			break;
		}
		case StateRow::error: {
			//std::cout << " state = error \n";
			//std::cout << "new string is : " << tempString << "\n";
			break;
		}
		case StateRow::mOp: {
			//std::cout << " state = mOp \n"; //displays state to console for debugging
			//std::cout << "finished token = " << tempString << "\n";  //displays the finished token to console for debugging
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::multiply, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::intermediate3: {
			//std::cout << " state = int.3 \n";
			tempString += read[currentpoint];
			//std::cout << "new string is : " << tempString << "\n";
			break;
		}
		case StateRow::intValue: {
			//std::cout << " state = intValue \n";
			//std::cout << "finished token = " << tempString <<"\n";
			//std::cout << "new string is : " << tempString << "\n";
			tokens.push_back(Token(tempString, Token::tokenType::integer, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 2;
			break;
		}
		case StateRow::intermediate5: {
			//std::cout << " state = int.5 \n";	
			tempString += read[currentpoint];
			//std::cout << "new string is " << tempString << "\n";
			break;
		}
		case StateRow::varValue: {
			//std::cout << " state = varValue \n";
			//std::cout << "finished token = " << tempString << "\n";
			if (tempString == "WHILE") {
				tokens.push_back(Token(tempString, Token::tokenType::WHILE, currentpoint)); //adds a new token to vector
			}
			else if (tempString == "FOR") {
				tokens.push_back(Token(tempString, Token::tokenType::FOR, currentpoint)); //adds a new token to vector
			}
			else if (tempString == "IF") {
				tokens.push_back(Token(tempString, Token::tokenType::IF, currentpoint)); //adds a new token to vector
			}
			else if (tempString == "THEN") {
				tokens.push_back(Token(tempString, Token::tokenType::THEN, currentpoint)); //adds a new token to vector
			}
			else if (tempString == "ELSE") {
				tokens.push_back(Token(tempString, Token::tokenType::ELSE, currentpoint)); //adds a new token to vector
			}
			else if (tempString == "CONST") {
				tokens.push_back(Token(tempString, Token::tokenType::CONST, currentpoint)); //adds a new token to vector
			}
			else if (tempString == "VAR") {
				tokens.push_back(Token(tempString, Token::tokenType::VAR, currentpoint)); //adds a new token to vector
			}
			else if (tempString == "CLASS") {
				tokens.push_back(Token(tempString, Token::tokenType::CLASS, currentpoint)); //adds a new token to vector
			}
			else if (tempString == "LOOP") {
				tokens.push_back(Token(tempString, Token::tokenType::LOOP, currentpoint)); //adds a new token to vector
			}
			else if (tempString == "input") {
				tokens.push_back(Token(tempString, Token::tokenType::input, currentpoint)); //adds a new token to vector
			}
			else if (tempString == "output") {
				tokens.push_back(Token(tempString, Token::tokenType::output, currentpoint)); //adds a new token to vector
			}
			else {
				tokens.push_back(Token(tempString, Token::tokenType::variable, currentpoint)); //adds a new token to vector
			}
			currentpoint = currentpoint - 2;
			break;
		}
		case StateRow::intermediate7: {
			//std::cout << " state = int.7 \n";
			tempString += read[currentpoint];
			std::cout << "new string is " << tempString << "\n";
			break;
		}
		case StateRow::intermediate8: {
			//std::cout << " state = int.8 \n";
			tempString += read[currentpoint];
			//std::cout << "new string is " << tempString << "\n";
			break;
		}
		case StateRow::intermediate9: {
			//std::cout << " state = int.9 \n";
			tempString += read[currentpoint];
			//std::cout << "new string is " << tempString << "\n";
			break;
		}
		case StateRow::dOp: {
			//std::cout << " state = dOp \n";
			//std::cout << "finished token = " << tempString << "\n";
			//tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::divide, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 2;
			break;
		}
		case StateRow::intermediate11: {
			//std::cout << " state = int.11 \n";
			tempString += read[currentpoint];
			//std::cout << "new string is " << tempString << "\n";
			break;
		}
		case StateRow::assignment: {
			//std::cout << " state = assignment \n";
			//std::cout << "finished token = " << tempString << "\n";
			tokens.push_back(Token(tempString, Token::tokenType::assignment, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 2;
			break;
		}
		case StateRow::requals: {
			//std::cout << " state = requals \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::relationalop, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::intermediate14: {
			//std::cout << " state = int.14 \n";
			tempString += read[currentpoint];
			std::cout << "new string is " << tempString << "\n";
			break;
		}
		case StateRow::rlessthan: {
			//std::cout << " state = rlessthan \n";
			std::cout << "finished token = \"" << tempString << "\"\n";
			tokens.push_back(Token(tempString, Token::tokenType::relationalop, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 2;
			break;
		}
		case StateRow::rlessthanequal: {
			//std::cout << " state = rlessthanequal \n";
			std::cout << "finished token = \"" << tempString << "\"\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::relationalop, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 2;
			break;
		}
		case StateRow::intermediate17: {
			//std::cout << " state = int.17 \n";
			tempString += read[currentpoint];
			//std::cout << "new string is " << tempString << "\n";
			break;
		}
		case StateRow::rgreaterthan: {
			//std::cout << " state = rgreaterthan \n";
			std::cout << "finished token = \"" << tempString << "\"\n";
			tokens.push_back(Token(tempString, Token::tokenType::relationalop, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 2;
			break;
		}
		case StateRow::rgreaterthanequal: {
			//std::cout << " state = rgreaterthanequal \n";
			std::cout << "finished token = \"" << tempString << "\"\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::relationalop, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 2;
			break;
		}
		case StateRow::lbrace: {
			//std::cout << " state = lbrace \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::LB, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::rbrace: {
			//std::cout << " state = rbrace \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::RB, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::lparenthesis: {
			//std::cout << " state = lparenthesis \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::LP, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::rparenthesis: {
			//std::cout << " state = rparenthesis \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::RP, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::plusoperator: {
			//std::cout << " state = plusoperator \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::add, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::minusoperator: {
			//std::cout << " state = minusoperator \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::subtract, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::commaValue: {
			//std::cout << " state = commaValue \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::comma, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::semicolonValue: {
			//std::cout << " state = semicolonValue \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::semicolon, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		}
		currentState = sT[int(currentState)][int(findColumn(read[++currentpoint]))]; //sets current state to next place on the table
		//std::cout << "CURRENT STRING : " << tempString << std::endl;
		//std::cout << "CURRENT CHARACTER : " << read[currentpoint] << std::endl;
	}


	for (Token t : tokens)
		file << t.tokenString << "\t" << t.printTokenType() << endl;
	file.close();

	ofstream outputfile;
	outputfile.open("symboltable");

	std::vector<Symbol> symbolTable = std::vector<Symbol>();
	int caddress = 0;
	int daddress = 0;
	std::cout << "Token" << "\t\t" << "Class" << "\t\t" << "Value" << "\t\t" << "Address" << "\t\t" << "Segment" << endl;
	std::cout << "-----------------------------------------------------" << endl;
	outputfile << "Token" << "\t\t" << "Class" << "\t\t" << "Value" << "\t\t" << "Address" << "\t\t" << "Segment" << endl;
	outputfile << "-----------------------------------------------------------------------" << endl;
	for (int x = 0; x < tokens.size(); x++) {
		if (tokens[x].tempType == Token::tokenType::CLASS) {
			x++;
			symbolTable.push_back(Symbol(tokens[x].tokenString, "CLASS", NULL, caddress, "CS"));
			caddress = caddress + 2;
		}

		if (tokens[x].tempType == Token::tokenType::CONST) {
			x++;
			symbolTable.push_back(Symbol(tokens[x].tokenString, "CONST", stoi(tokens[x + 2].tokenString), daddress, "DS"));
			daddress = daddress + 2;

			while (tokens[x + 3].tokenString == ",") {
				x = x + 4;
				symbolTable.push_back(Symbol(tokens[x].tokenString, "CONST", stoi(tokens[x + 2].tokenString), daddress, "DS"));
				daddress = daddress + 2;
			}
			x = x + 4;
		}

		if (tokens[x].tempType == Token::tokenType::VAR) {
			x++;
			while (tokens[x].tempType == Token::tokenType::variable) {
				if (tokens[x + 1].tokenString == "=") {
					symbolTable.push_back(Symbol(tokens[x].tokenString, "VAR", stoi(tokens[x + 2].tokenString), daddress, "DS"));
					daddress = daddress + 2;
					if (tokens[x + 3].tokenString == ",") {
						x = x + 4;
					}
					else if (tokens[x + 3].tokenString == ";") {
						x = x + 3;
					}
				}
				else if (tokens[x + 1].tokenString == ",") {
					symbolTable.push_back(Symbol(tokens[x].tokenString, "VAR", NULL, daddress, "DS"));
					daddress = daddress + 2;
					if (tokens[x + 1].tokenString == ",") {
						x = x + 2;
					}
					else if (tokens[x + 1].tokenString == ";") {
						x = x + 1;
					}
				}
				else {
					symbolTable.push_back(Symbol(tokens[x].tokenString, "VAR", NULL, daddress, "DS"));
					daddress = daddress + 2;
					x++;
				}
			}
		}

		if (tokens[x].tempType == Token::tokenType::integer) {
			bool exists = false;
			for (Symbol S : symbolTable) {
				if (tokens[x].tokenString == S.symbolName) {
					exists = true;
				}
			}
			if (exists == false) {
				symbolTable.push_back(Symbol(tokens[x].tokenString, "numLit", stoi(tokens[x].tokenString), daddress, "DS"));
				daddress = daddress + 2;
			}
		}

	}
	for (string t : temps) {
		symbolTable.push_back(Symbol(t, "VAR", 0, daddress, "DS"));
		daddress = daddress + 2;
	}
	for (Symbol s : symbolTable) {
		std::cout << s.symbolName << "\t" << s.className << "\t" << s.value << "\t" << s.address << "\t" << s.segment << endl;
		outputfile << s.symbolName << "\t\t" << s.className << "\t\t" << s.value << "\t\t" << s.address << "\t\t" << s.segment << endl;
	}

	outputfile.close();

	//END LEXICAL ANALYZER


















	//BEGIN SYNTAX ANALYZER
	std::vector<Token> symbolStack = std::vector<Token>();
	std::vector<Token> operatorStack = std::vector<Token>();
	std::vector<Quad> quadlist = std::vector<Quad>();
	std::vector<Label> fixup = std::vector<Label>();
	std::vector<Label> endstack = std::vector<Label>();
	std::vector<Quad> outputlist = std::vector<Quad>();

	int tempcount = 0;
	//< gives,  > takes 
	//0 , 1 , 2 , 3 , 4 , 5,  6 , 7 , 8 , 9  , 10   ,  11, 12,13,14, 15, 16,17,18, 19  , 20
	//; , = , + , - , ( , ) , * , / , IF, THEN, WHILE, ==, !=, >, <, >=, <=, {, }, LOOP, ELSE
	Precedence pr[21][21]{
		//           ;						=					+					-					(					)					*				/						IF					THEN				WHILE				==					!=					>					<					>=					<=					{						}			LOOP				ELSE
		/*;*/{Precedence::none,		Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none},
		/*=*/{Precedence::takes,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	 Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none},
		/*+*/{Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::takes,	Precedence::gives,	Precedence::takes,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::takes,	Precedence::takes,	 Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none},
		/*-*/{Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::takes,	Precedence::gives,	Precedence::takes,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none},
		/*(*/{Precedence::none,		Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::equal,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none},
		/*)*/{Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none},
		/***/{Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::takes,	Precedence::gives,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none},
		/*/*/{Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::takes,	Precedence::gives,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::none,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::takes,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none},
		/*IF*/{Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::equal,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::equal},
		/*Then*/{Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::equal},
		/*WHILE*/{Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::equal,	Precedence::none},
		/*==*/{Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::takes,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::takes,	Precedence::none},
		/*!=*/{Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::takes,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::takes,	Precedence::none},
		/*>*/{Precedence::none,		Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::takes,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::takes,	Precedence::none},
		/*<*/{Precedence::none,		Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::takes,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::takes,	Precedence::none},
		/*>=*/{Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::takes,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::takes,	Precedence::none},
		/*<=*/{Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::takes,	Precedence::none},
		/*{*/{Precedence::none,		Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none},
		/*}*/{Precedence::none,		Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none},
		/*LOOP*/{Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::equal},
		/*ELSE*/{Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::equal,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::none,	Precedence::gives,	Precedence::none,	Precedence::none,	Precedence::none},
	};
	//IF() THEN { } ELSE { }
	//IF <run> THEN <run> ELSE 

	for (int x = 0; x < tokens.size(); x++) {

		//&*&*&*&*&*&*&*&*&*&*&*&*&&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&*&
		if (tokens[x].tempType == Token::tokenType::input) {
			//needs to skip
			Quad q = Quad(tokens[x], tokens[x+1]);
			quadlist.push_back(q);
			while (tokens[x++].tempType != Token::tokenType::semicolon);
			x = x - 2;
		}
		if (tokens[x].tempType == Token::tokenType::output) {
			//needs to skip
			Quad q = Quad(tokens[x], tokens[x+1]);
			outputlist.push_back(q);
			while (tokens[x++].tempType != Token::tokenType::semicolon);
			x = x - 2;
		}

		if (tokens[x].tempType == Token::tokenType::CLASS) {
			while (tokens[x++].tempType != Token::tokenType::LB);
			std::cout << "skipping CLASS" << endl;
			x = x - 2;
			continue;
		}
		if (tokens[x].tempType == Token::tokenType::comma) {
			std::cout << "skipping comma" << endl;
			x += 1;
		}
		if (tokens[x].tempType == Token::tokenType::LB) 
		{
			if (operatorStack.size() > 0) {
				if (operatorStack.back().tempType != Token::tokenType::THEN
					|| operatorStack.back().tempType != Token::tokenType::ELSE || operatorStack.back().tempType != Token::tokenType::LOOP) {
					std::cout << "not skipping LB" << endl;
				}
			}
			else {
				std::cout << "skipping LB" << endl;
				x += 1;
			}
		}
		if (tokens[x].tempType == Token::tokenType::VAR || tokens[x].tempType == Token::tokenType::CONST) {
			while (tokens[x++].tempType != Token::tokenType::semicolon);
			std::cout << "skipping VAR/CONST" << endl;
			x--;
			continue;
		}
		if (tokens[x].tempType == Token::tokenType::integer || tokens[x].tempType == Token::tokenType::variable) {
			symbolStack.push_back(tokens[x]);
			std::cout << "symbol  " << tokens[x].tokenString << "  pushed to symbol stack" << endl;
		}
		else {
			if (operatorStack.size() == 0) {
				std::cout << "stack was empty, pushing first item to operator stack " << tokens[x].tokenString << endl;
				if (tokens[x].tempType == Token::tokenType::semicolon) {
				continue;
				}
				else {
					operatorStack.push_back(tokens[x]);
					if (tokens[x].tempType == Token::tokenType::IF) {
						Quad q = Quad(tokens[x]);
						quadlist.push_back(q);
					}
					else if (tokens[x].tempType == Token::tokenType::WHILE) {
						Label label = Label();
						fixup.push_back(label);
						Quad q = Quad(tokens[x]);
						quadlist.push_back(q);
						Quad w = Quad(label);
						quadlist.push_back(w);
					}
				}
				continue;
			}
			std::cout << "top of stack " << operatorStack.back().tokenString << " next input " << tokens[x].tokenString << endl;
			switch (pr[mapToken(operatorStack.back())][mapToken(tokens[x])]) {
			case Precedence::gives: {
				std::cout << "gives precedence case entered" << endl;  //output
				operatorStack.push_back(tokens[x]);
				std::cout << "operator " << tokens[x].printTokenType() << " pushed to operator stack" << endl;

				if (tokens[x].tempType == Token::tokenType::IF) {
					Quad q = Quad(tokens[x]);
					quadlist.push_back(q);
				}
				if (tokens[x].tempType == Token::tokenType::WHILE) {
					Label label = Label();
					fixup.push_back(label);
					Quad q = Quad(tokens[x]);
					quadlist.push_back(q);
					Quad w = Quad(label);
					quadlist.push_back(w);
				}
				//while loops
				break;//example push_back
			}
			case Precedence::takes: { 
				std::cout << "takes precedence case entered" << endl;  //output
				std::cout << mapToken(operatorStack.back()) << " " << mapToken(tokens[x]) << endl;
				switch (operatorStack.back().tempType) {

				case Token::tokenType::assignment: {
					std::cout << "assignment case entered" << endl;  //output
					if (tokens[x].tempType == Token::tokenType::semicolon) {
						Token right = symbolStack.back();
						symbolStack.pop_back();
						Token left = symbolStack.back();
						symbolStack.pop_back();
						Token op = operatorStack.back();
						operatorStack.pop_back();
						Token destination = Token(temps[tempcount], Token::tokenType::variable, -1);
						Quad q = Quad(op, left, right, left);
						quadlist.push_back(q);
						std::cout << q.toString() << endl;  //output
						PrintOPStack(operatorStack);
						PrintSymbStack(symbolStack);
						tempcount = 0;
						continue;
					}
					break;
				}

				case Token::tokenType::add: {
					std::cout << "addition case entered" << endl;  //output
					//if last thing pushed was a + and takes precedence over next in string < + >
				}
				case Token::tokenType::divide: {
					std::cout << "division case entered" << endl;  //output
					//if last thing pushed was a / and takes precedence over next in string < / >
				}
				case Token::tokenType::multiply: {
					std::cout << "multiply case entered" << endl;  //output
					//if last thing pushed was a * and takes precedence over next in string < * >
				}
				case Token::tokenType::subtract: {
					std::cout << "subtract case entered" << endl;  //output
					//if last thing pushed was a - and takes precedence over next in string < - >
					Token right = symbolStack.back();
					symbolStack.pop_back();
					Token left = symbolStack.back();
					symbolStack.pop_back();
					Token op = operatorStack.back();
					operatorStack.pop_back();
					Token destination = Token(temps[tempcount], Token::tokenType::variable, -1);
					tempcount = tempcount + 1;
					symbolStack.push_back(destination);
					Quad q = Quad(op, left, right, destination);
					quadlist.push_back(q);
					std::cout << q.toString() << endl;   //output
					x--;
					break;
					//continue;
				}

				case Token::tokenType::RP: {
					std::cout << "right parenthesis case entered" << endl;  //output
					PrintOPStack(operatorStack);
					PrintSymbStack(symbolStack);
					operatorStack.pop_back(); // )
					operatorStack.pop_back(); // (  poofed out of existence
					PrintOPStack(operatorStack);
					PrintSymbStack(symbolStack);
					if (operatorStack.size() >= 1) {
						x--;
					}
					break;
				}
				case Token::tokenType::relationalop: {
					std::cout << "relational op case entered" << endl;  //output
					Token right = symbolStack.back();
					symbolStack.pop_back();
					Token left = symbolStack.back();
					symbolStack.pop_back();
					Token op = operatorStack.back();
					operatorStack.pop_back();
					Token destination = Token(temps[tempcount], Token::tokenType::variable, -2);
					tempcount = tempcount + 1;
					symbolStack.push_back(destination);
					Quad q = Quad(op, left, right, destination);
					quadlist.push_back(q);
					std::cout << q.toString() << endl;		//output
					x--;
					break;
				}
				default: cout << "case not handled" << endl;
				}
				break;
			}

			case Precedence::equal: {
				std::cout << "equal precedence case entered" << endl;  //output
				PrintOPStack(operatorStack);
				PrintSymbStack(symbolStack);
				operatorStack.push_back(tokens[x]);

				if (operatorStack.back().tempType == Token::tokenType::LOOP) {
					Label label = Label();
					endstack.push_back(label);
					Token op = operatorStack.back();
					Token reverseop = reverserelational(quadlist.back().op);
					Quad q = Quad(op, label, reverseop);
					quadlist.push_back(q);
					symbolStack.pop_back();
					std::cout << "\n\n &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \n\n" << endl;
					std::cout << q.toString() << endl;

				}
				if (operatorStack.back().tempType == Token::tokenType::THEN) {
					std::cout << "then case entered for equal precedence" << endl;
					Label l = Label();
					fixup.push_back(l);
					Token op = operatorStack.back();
					Token reverseop = reverserelational(quadlist.back().op);
					Quad q = Quad(op, l, reverseop);
					quadlist.push_back(q);
					symbolStack.pop_back();
					std::cout << "\n\n &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \n\n" << endl;
					std::cout << q.toString() << endl;
				}
				//******************************************************************************************************
				if (operatorStack.back().tempType == Token::tokenType::ELSE) {
					std::cout << "ELSE case entered for equal precedence" << endl;
					Label l = Label();
					endstack.push_back(l);
					Token op = operatorStack.back();
					Token reverseop = reverserelational(quadlist.back().op);
					Quad q = Quad(op, l);
					quadlist.push_back(q);
					quadlist.push_back(Quad(fixup.back()));
					fixup.pop_back();
					std::cout << "\n\n &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \n\n" << endl;
					//std::cout << q.toString() << endl;
				}


				std::cout << "operatorstack at time of equal precedence " << operatorStack.back().tokenString << " next in " << tokens[x].tokenString << endl;

				break;


			}
			case Precedence::none: {
				std::cout << "none precedence case entered" << endl;  //output
				std::cout << "printing locations " <<  mapToken(operatorStack.back()) << " " << mapToken(tokens[x]) << endl;
				std::cout << "operatorstack at time of none precedence " << operatorStack.back().tokenString << " next in " << tokens[x].tokenString << endl;
				tempcount = 0; // sets temp strings back to beginning

				switch (operatorStack.back().tempType) {

				case Token::tokenType::THEN: {

					//*************************************************************************************
					std::cout << "THEN case entered" << endl;  //output
					if (tokens[x+1].tempType == Token::tokenType::ELSE) {
						
						
						break;
					}
					else {
						//there is an < IF <BE>  THEN <STMT> ELSE 
						operatorStack.pop_back(); // THEN
						operatorStack.pop_back(); // IF
						Quad q = Quad(fixup.back());
						quadlist.push_back(q);
						fixup.pop_back();
						break;
					}
				}

				//*************************************************************************************
				case Token::tokenType::ELSE: {
					std::cout << "ELSE case entered" << endl;  //output
						//there is an < IF <BE>  THEN <STMT>  >  to pop
						//symbolStack.pop_back(); //temp for <STMT> 
						operatorStack.pop_back(); // THEN
						//symbolStack.pop_back(); // temp for <BE>
						operatorStack.pop_back(); // IF
						operatorStack.pop_back(); // ELSE
						Quad q = Quad(endstack.back());
						quadlist.push_back(q);
						endstack.pop_back();
						break;
				}
				case Token::tokenType::LOOP: {
					std::cout << "LOOP case entered" << endl;  //output
					operatorStack.pop_back(); // LOOP
					operatorStack.pop_back(); // WHILE
					Quad q = Quad(endstack.back());
					Quad w = Quad(Quad::opType::jmp, fixup.back());
					quadlist.push_back(w);
					fixup.pop_back();
					quadlist.push_back(q);
					endstack.pop_back();
					
					break;
				}
				case Token::tokenType::assignment: {
					std::cout << "assignment case entered" << endl;  //output
					//symbol on left, assignment, symbol or temp on right
					symbolStack.pop_back(); //symbol or temp
					operatorStack.pop_back(); // = 
					symbolStack.pop_back(); //symbol for destination
					break;
				}
				case Token::tokenType::semicolon: {
					std::cout << "semicolon case entered" << endl;  //output
					// can this happen???
					break;
				}
				case Token::tokenType::RB: {
					std::cout << "right brace case entered" << endl;
					//if no relation the quad is complete
					//pop the entire stack into a quad
					break;
				}	
				case Token::tokenType::LB: {
					std::cout << "left brace case entered" << endl;
					if (tokens[x].tempType == Token::tokenType::RB) {
						operatorStack.pop_back();
						x--;
					}
					else if (tokens[x].tempType == Token::tokenType::semicolon) {
						
					}
					//if no relation the quad is complete
					//pop the entire stack into a quad
					break;
				}
				}
				break;
			}
			default: cout << "default case entered" << endl;
			}

		}
	}
	PrintOPStack(operatorStack);
	PrintSymbStack(symbolStack);
	PrintQuad(quadlist);
	PrintQuad(outputlist);



	file.open("assemblyoutput.asm");
	file << "sys_exit equ 1\nsys_read equ 3\nsys_write equ 4\nstdin equ 4\nstdout equ 1\nstderr equ 3\n\n";
	file << "section .data\n\n";
	file << "userMsg db 'Enter an integer(less than 32,765): '\nlenUserMsg equ $-userMsg\ndisplayMsg db 'You entered: '\nlenDisplayMsg equ $-displayMsg\n";
	file << "newline db 0xA\nTen DW 10\nprintTempchar db 'Tempchar = : '\nlenprintTempchar equ $-printTempchar\n";
	file << "Result db 'Ans = '\nResultValue db 'aaaaa'\ndb	0xA\nResultEnd equ $-Result\nnum times 6 db 'ABCDEF'\nnumEnd equ $-num\n\n";

	for (Symbol s : symbolTable) {
		if (s.className == "CONST") {
			file << s.symbolName << " DW " << s.value << endl;
		}
		if (s.className == "numLit") {
			file <<"Lit"<< s.value << " DW " << s.value << endl;
		}
	}


	file << "section .bss" << endl;
	file << "\n\n";
	file << "TempChar RESB 1\ntestchar RESB 1\nReadInt RESW 1\ntempint RESW 1\nnegflag RESB 1\n";
	file << "\n\n";
	for (Symbol s : symbolTable) {
		if (s.className == "VAR") {
			file << s.symbolName << " RESW 1" << endl;
		}
	}


	file << "\n\n";
	file << "section .text\n_start: nop\nAgain: \n";
	for (Quad q : quadlist) {
		file << q.assemble();
	}

	for (Quad o : outputlist) {
		file << o.assemble();
	}

	file << "\njmp fini\n\n";
	file << "PrintString:\npush ax\npush dx\n";
	file << "mov eax, 4\nmov ebx, 1\nmov ecx, userMsg\nmov edx, lenUserMsg\nint 80h\npop dx\npop ax\nret\n\n";
	file << "GetAnInteger:\nmov eax, 3\nmov ebx, 2\nmov ecx, num\nmov edx,6\nint 0x80\n";
	file << "mov edx, eax\nmov eax, 4\nmov ebx, 1\nmov ecx, num\nint 80h\n";
	file << "ConvertStringToInteger:\nmov ax, 0\nmov [ReadInt], ax\nmov ecx, num\nmov bx, 0\nmov bl, byte [ecx]\nNext: sub bl, '0'\nmov ax, [ReadInt]\n";
	file << "mov dx, 10\nmul dx\nadd ax, bx\nmov [ReadInt], ax\nmov bx, 0\nadd ecx, 1\nmov bl, byte[ecx]\ncmp bl, 0xA\njne Next\nret\n";
	file << "ConvertIntegerToString:\nmov ebx, ResultValue + 4\n";
	file << "ConvertLoop:\nsub dx, dx\nmov cx, 10\ndiv cx\nadd dl, '0'\nmov [ebx], dl\ndec ebx\ncmp ebx, ResultValue\njge ConvertLoop\nret\n";



		//not sure if needed???

	file << "\n";

	file << "Terminate:\nfini:\nmov eax, sys_exit\nxor ebx, ebx\nint 80h\n";

	file.close();






}
//need to look at the output and figure out how to get the correct thing to output




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


//loop through symbol table to find the things that belong in .data, and then loop again for .bss
//.text will hold the input, the assembly from quads, the output, and the exit
