#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"
using namespace std;

void Lexer::lexer(string s, string & result)
{
	if (s == ":=")
	{
		result += "PRZYPISZ ";
		return;
	}
	if (s == ">")
	{
		result += "WIEKSZE ";
		return;
	}
	if (s == "<")
	{
		result += "MNIEJSZE ";
		return;
	}
	if (s == "=")
	{
		result += "ROWNE ";
		return;
	}
	if (s == ":")
	{
		result += ": ";
		return;
	}

	if (s == "+")
	{
		result += "DODAJ ";
		return;
	}
	if (s == "-")
	{
		result += "ODEJMIJ ";
		return;
	}
	if (s == "*")
	{
		result += "MNOZ ";
		return;
	}
	if (s == "/")
	{
		result += "DZIEL ";
		return;
	}
	if (s == "[")
	{
		result += "[ ";
		return;
	}
	if (s == "]")
	{
		result += "] ";
		return;
	}
	if (s == "(")
	{
		result += "( ";
		return;
	}
	if (s == ")")
	{
		result += ") ";
		return;
	}


	//inlicjalizacja maszyny stanów skończonych




	int stany[4][3] = { {1, 2, 3},  {1,3, 3}, {2, 2, 3}, {3, 3, 3} };
	int stan = 0;
	for (int i = 0; i < s.length(); i++)
	{
		stan = stany[stan][recognize(s[i])];
	}

	if (stan == 1)
	{
	
		result += "LICZBA ";
		return;

	}
	if (stan == 2)
	{
		for (int i = 0; i < keywords.size(); i++)
		{
			if (s == keywords[i])
			{
				result = result + s + " " ;
				return;
			}
		}
		result += "ZMIENNA ";
		return;
	}
	if (stan == 3)
	{
		cout << "BLAD!";
	}
}



//funkcja pomocnicza zwracajaca 0, jesli dany znak jest cyfrą, 1, jesli dany znak jest literą i 2, jeśli dany znak nie jest ani tym ani tym

int Lexer::recognize(char c)
{

	if (c >= 48 && c <= 57)
	{
		return 0;
	}
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
	{
		return 1;
	}
	return 2;
}

Lexer::Lexer(string s)
{
	str = s;
	keywords.push_back("bool");
	keywords.push_back("integer");
	keywords.push_back("word");
	keywords.push_back("short");
	keywords.push_back("array");
	keywords.push_back("of");
}

string Lexer::Lex()
{
	
	int i = 0;//iterator on tree
	string s = str;
	string result, bufor;
	int nw, od;
	nw = od = 0;
	do
	{
		
		nw = s.find(" ");
		bufor = s.substr(0, nw);
		s = s.substr(nw + 1, str.size() - nw - 1);
		od = nw;
		lexer(bufor, result);
		
	}while (nw != string::npos);
	s = result;
	nw = od = 0;
	while (nw != string::npos&&i < trees.size())
	{
		
		nw = s.find(" ");
		bufor = s.substr(0, nw);
		s = s.substr(nw + 1, result.size() - nw - 1);
		od = nw;

		trees[i]->AddFather(new Tree(bufor)); //TU JEST BLAD!!!
		i++;
		
	}





	result.erase(result.size() - 1, 1);
	return result;
}
void Lexer::Create_Tree()
{
	trees.clear();
	int nw = 0;
	int od = 0;
	string s = str;
	string bufor;
	do
	{
		nw = s.find(" ");
		bufor = s.substr(0, nw);
		s = s.substr(nw + 1, str.size() - nw - 1);
		trees.push_back(new Tree(bufor));
		od = nw;
	} while (nw != string::npos);
	trees.pop_back();
}
