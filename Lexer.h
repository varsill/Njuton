#pragma once
#include <iostream>
#include <vector>
#include "Parser.h"
using namespace std;
class Lexer
{
public:
	vector <Tree*> trees;
	string str;
	void lexer(string, string &);
	int recognize(char);
	Lexer(string);
	string Lex();
	vector <string> keywords;
	void Create_Tree();
};



