#pragma once
#include <iostream>
#include <vector>
#include <string>
#define FINAL_STATEMENT "INSTRUKCJA"
#define MAX_WORDS_IN_PRODUCTION 5
using namespace std;
class Production
{
public:
	string left;
	string right;

	Production(string, string);
	
};

class Parser
{
public:
	vector<vector<Production>> productions;
	vector <string> words;
	int i;//string word position counter
	string str; //whole string being operated
	
public:
	Parser(string);
	void Add_production(string, string);
	void CYK();
	bool Checking();
	bool Check();//returs 0 if there is an error and 1 if everything is correct
};
