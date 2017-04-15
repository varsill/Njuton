#include "Parser.h"



Production::Production(string l, string r)
{
	left = l;
	right = r;
}


Parser::Parser(string s)
{
	string bufor;
	int od, nw;//pointing on spaces in str
	od = 0;
	i = 0;
	str = s;
	productions.resize(MAX_WORDS_IN_PRODUCTION);
	do
	{
		nw = s.find(" ");
		bufor = s.substr(0, nw);
		s = s.substr(nw + 1, str.size() - nw - 1);
		words.push_back(bufor);
		od = nw;
	} while (nw != string::npos);
}

void Parser::Add_production(string l, string r)
{
	string rp = r;
	int i = 0;
	do//calculating number of words in string
	{
		rp = rp.substr(rp.find(" ") + 1, rp.size() - rp.find(" ") - 1);
		i++;
	} while (rp.find(" ") != string::npos);
	productions[i].push_back(Production(l, r));
}
void Parser::CYK()
{
	string bufor;
	vector<string> newwords;
	newwords = words;
	for (int i = 0; i < MAX_WORDS_IN_PRODUCTION; i++) //loop for particular numberr of words in production
	{
		words = newwords;
		newwords.clear();
		for (int j = 0; j < words.size(); j++) //loop for starting word
		{
			bufor = "";
			for (int k = 0; k <= i; k++) //loop for currently added word
			{
				if (j + k < words.size())
				{
					bufor = bufor + " " + words[j + k];
				}
			}



			for (int k = 0; k < productions[i].size(); k++)
			{
				if (bufor == productions[i][k].right)
				{
					newwords.push_back(productions[i][k].left);
					break;
				}
				else
				{
					newwords.push_back(words[j]);
				}
			}
		}

	}
}

bool Parser::Checking()
{
	bool byla_zmiana=false;
	int x;
	for (int i = productions.size()-1; i >=0 ; i--)
	{
	for (int j = 0; j < productions[i].size(); j++)
		{
		
		do
		{
			x = str.find(productions[i][j].right);
			if (x != -1)
			{
				byla_zmiana = true;
				str =str.erase(x, productions[i][j].right.length());
				str.insert(x, productions[i][j].left);
			}
		} while (x != -1);
		}
	}
	return byla_zmiana;
}

bool Parser::Check()
{
	bool byla_zmiana=true;
	while (byla_zmiana)
	{
		byla_zmiana=Checking();
	}
	if (str == FINAL_STATEMENT)
	{
		return 1;
	}
	return 0;

}
