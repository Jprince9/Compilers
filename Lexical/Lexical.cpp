// Lexical.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Token.h"
#include <fstream>
#include <sstream>
#include "Symbol.h"

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
	case Token::tokenType::relationalop:{
		if (token.tokenString == ">") {
			return 13;
		}
		else if(token.tokenString == "<"){

		}
		else if (token.tokenString == ">=") {

		}
		else if (token.tokenString == "<=") {

		}
		else if (token.tokenString == "!=") {

		}
		else if (token.tokenString == "==") {

		}
	}
	case Token::tokenType::{
	}
	case Token::tokenType:{
	}
	case Token::tokenType:{
	}
	case Token::tokenType:{
	}
	case Token::tokenType:{
	}
	case Token::tokenType:{
	}
	}

}





int main()
{
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
		step = step +1;
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
			else {
				tokens.push_back(Token(tempString, Token::tokenType::variable, currentpoint)); //adds a new token to vector
			}
			currentpoint = currentpoint - 2;
			break;
		}
		case StateRow::intermediate7: {
			//std::cout << " state = int.7 \n";
			tempString += read[currentpoint];
			//std::cout << "new string is " << tempString << "\n";
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
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::divide, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
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
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::relationalop, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::rlessthanequal: {
			//std::cout << " state = rlessthanequal \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::relationalop, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
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
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];	
			tokens.push_back(Token(tempString, Token::tokenType::relationalop, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
			break;
		}
		case StateRow::rgreaterthanequal: {
			//std::cout << " state = rgreaterthanequal \n";
			//std::cout << "finished token = " << tempString << "\n";
			tempString += read[currentpoint];
			tokens.push_back(Token(tempString, Token::tokenType::relationalop, currentpoint)); //adds a new token to vector
			currentpoint = currentpoint - 1;
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
			symbolTable.push_back(Symbol(tokens[x].tokenString, "CONST", stoi(tokens[x+2].tokenString), daddress, "DS"));
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
			symbolTable.push_back(Symbol(tokens[x].tokenString, "numLit", stoi(tokens[x].tokenString), daddress, "DS"));
			daddress = daddress + 2;
		}

	}

	for (Symbol s : symbolTable) {
		std::cout << s.symbolName << "\t" << s.className << "\t" << s.value << "\t" << s.address << "\t" << s.segment << endl;
		outputfile << s.symbolName << "\t\t" << s.className << "\t\t" << s.value << "\t\t" << s.address << "\t\t" << s.segment << endl;
	}
	outputfile.close();
	
	//END LEXICAL ANALYZER

	//BEGIN SYNTAX ANALYZER
	std::vector<Token> precedenceStack = std::vector<Token>();
 
	
	//< gives,  > takes 
	//Terminator , = , + , - , ( , ) , * , / , IF, THEN, WHILE, ==, !=, >, <, >=, <=, {, }, LOOP
	Precedence pr[20][20]{
		/*terminator*/{Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*=*/{Precedence::takes,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::gives,Precedence::none,Precedence::none,Precedence::none, Precedence::none, Precedence::none, Precedence::none, Precedence::none, Precedence::none, Precedence::none, Precedence::none,Precedence::none,Precedence::none},
		/*+*/{Precedence::takes,Precedence::none,Precedence::takes,Precedence::takes,Precedence::gives,Precedence::takes,Precedence::gives,Precedence::gives,Precedence::none,Precedence::takes,Precedence::none, Precedence::takes, Precedence::takes, Precedence::takes, Precedence::takes, Precedence::takes, Precedence::takes, Precedence::none,Precedence::none,Precedence::none},
		/*-*/{Precedence::takes,Precedence::none,Precedence::takes,Precedence::takes,Precedence::gives,Precedence::takes,Precedence::gives,Precedence::gives,Precedence::none,Precedence::takes,Precedence::none,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::none,Precedence::none,Precedence::none},
		/*(*/{Precedence::none,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::equal,Precedence::gives,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*)*/{Precedence::takes,Precedence::none,Precedence::takes,Precedence::takes,Precedence::none,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/***/{Precedence::takes,Precedence::none,Precedence::takes,Precedence::takes,Precedence::gives,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::none,Precedence::takes,Precedence::none,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::none,Precedence::none,Precedence::none},
		/*/*/{Precedence::takes,Precedence::none,Precedence::takes,Precedence::takes,Precedence::gives,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::none,Precedence::takes,Precedence::none,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::takes,Precedence::none,Precedence::none,Precedence::none},
		/*IF*/{Precedence::none,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::gives,Precedence::none,Precedence::equal,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::none,Precedence::none},
		/*Then*/{Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::gives,Precedence::none,Precedence::none},
		/*WHILE*/{Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*==*/{Precedence::none,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*!=*/{Precedence::none,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*>*/{Precedence::none,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*<*/{Precedence::none,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*>=*/{Precedence::none,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*<=*/{Precedence::none,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*{*/{Precedence::none,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*}*/{Precedence::none,Precedence::none,Precedence::gives,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::gives,Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none},
		/*LOOP*/{Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::gives,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none,Precedence::none}
	};
	
	

	for (int x = 0; x < tokens.size(); x++) {
		if (tokens[x].tempType == Token::tokenType::CLASS || tokens[x].tempType == Token::tokenType::VAR || tokens[x].tempType == Token::tokenType::CONST) {
			continue;
		}
		if (tokens[x].tempType == Token::tokenType::integer || tokens[x].tempType == Token::tokenType::variable) {
			precedenceStack.push_back(tokens[x]);
		}
		else {
			switch (pr[mapToken(tokens[x])[mapToken(precedenceStack.back())]) {
				case gives{
					//example push_back
				}
				case takes{
					//example pop_back until last gives
				}

		}

		
	}
	}
	//pop_back

//needs a way to output each item to a table with correct type, address, and value
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu