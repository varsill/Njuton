#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Lexer
{
public:
	string str;
	void lexer(string, string &);
	int recognize(char);
	Lexer(string);
	string Lex();
	vector <string> typy; //types of variables
};



