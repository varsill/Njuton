#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#define FINAL_STATEMENT "INSTRUKCJA"
#define MAX_WORDS_IN_PRODUCTION 10
using namespace std;

class Zmienna
{
public:
	string name;
	string type; //number of bytes

	Zmienna(string, string);
};

class Production
{
public:
	string left;
	string right;
	
	Production(string, string);
	
};

class Tree
{
public:
	vector<Tree*> sons;
	Tree * father;
	string name;
	void AddFather(Tree*);
	void AddSon(Tree*);
	Tree::Tree(string);
	Tree::Tree();

};
class Parser
{
public:
	vector <Tree*> trees;
	vector <Tree*> drzewa;
	vector <Zmienna> zmienne;
	vector<vector<Production>> productions;
	vector <string> words;
	vector <Production> stos;
	int i;//string word position counter
	string str; //whole string being operated
	
public:
	Parser(string);
	void Add_production(string, string);
	void CYK();
	bool Checking();
	bool Check();//returs 0 if there is an error and 1 if everything is correct
	void Generate();//generates assembler code from instructions in "stos"
	void Parse();
	string help();

};
int ktore_slowo(string, int);

