#include <iostream>
#include <string>
#include "Lexer.h"
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
		for (int i = 0; i < typy.size(); i++)
		{
			if (s == typy[i])
			{
				result += "TYP ";
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
	typy.push_back("bool");
	typy.push_back("integer");
	typy.push_back("word");
	typy.push_back("short");
}

string Lexer::Lex()
{

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
	} while (nw != string::npos);
	result.erase(result.size() - 1, 1);
	return result;
}
