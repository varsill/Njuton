#include "Parser.h"



Production::Production(string l, string r)
{
	left = l;
	right = r;
}
Zmienna::Zmienna(string n, string i)
{
	name = n;
	type = i;

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
	/*do//calculating number of words in string
	{
		rp = rp.substr(rp.find(" ") + 1, rp.size() - rp.find(" ") - 1);
		i++;
	} while (rp.find(" ") != string::npos);
	*/
	size_t n= std::count(r.begin(), r.end(), ' ');
	
	productions[n+1].push_back(Production(l, r));
}
/*
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
*/
int ktore_slowo(string str, int pos)
{
	int x=0;
	int i = 1;
	//pos--;//becouse we want to have space position, not given position of first letter of common substring
	if (pos == 0) { return 1; }
	do
	{
		pos -= (x + 1);
		x = str.find(" ");
		str.erase(0, x + 1);
		i++;
		
	} while (x != pos);
	return i;
}
/*
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
				stos.push_back(productions[i][j]); //adding to stack in order to analyze it while translating to asembler
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
*/
void Parser::Generate()
{
	string name;
	bool add = true;
	for (int i = 0; i < stos.size(); i++)
	{
		if (stos[i].left == "DEKLARACJA")
		{
			for (int j = 0; j < stos.size(); j++)
			{
				if (stos[j].left == "TYP")
				{
				 add = true;
					name = stos[i].right.substr(stos[i].right.find(":") + 2, stos[i].right.size() - stos[i].right.find(":") - 2);
					for (int k = 0; k < zmienne.size(); k++)
					{
						if (zmienne[k].name == name)
						{
							add = false;
							break;//Print error about redeclaration of variable;
						}
					}
					if(add)
					{
						zmienne.push_back(Zmienna(name, stos[j].right));
						stos.erase(stos.begin() + j);
					}
				
					break;
				}
			}
			stos.erase(stos.begin()+i);
		}


	}

}

void Parser::Parse()
{
	int i, x;
	Tree drzewo;
	string bufor;
	bool byla_zmiana = true;
	while (byla_zmiana)
	{
		byla_zmiana = false;
		
		bufor = help();

		for (int i = 0; i < productions.size(); i++)
		{
			for (int j = 0; j < productions[i].size(); j++)
			{
					x = bufor.find(productions[i][j].right);
					if (x > -1)
					{
						Tree* drzewko = new Tree(productions[i][j].left);
						for (int a = 0; a < i; a++)
						{
							drzewa[ktore_slowo(bufor, x) - 1+a]->AddFather(drzewko);
						}
						byla_zmiana = true;
			
						break;
					}
					
			
			}
			if (byla_zmiana)break;
		}

	
	}
	trees.push_back(drzewa[0]);//adding last tree member to general list of peaks
		return;
}


string Parser::help()
{
	string bufor;
	Tree * drzewo;
	vector <Tree*> drzewka;

	i = 0;
	drzewka.clear();
	while (i < drzewa.size())
	{
		drzewo = drzewa[i];
		while (drzewo->father != NULL)//UWAGA
		{
			drzewo = drzewo->father;
		}
		
			drzewka.push_back(drzewo);
		
		
		bufor += drzewo->name + " ";
		i = i+ drzewo->sons.size();//becouse sons are next to each others
		 
	}
	bufor.erase(bufor.size() - 1);
	drzewa = drzewka;
	return bufor;
}

void Tree::AddFather(Tree* f)
{
	father = f;
	f->AddSon(this);
}
void Tree::AddSon(Tree* s)
{
	sons.push_back(s);
}
Tree::Tree(string n)
{
	name = n;
	father = NULL;
}
Tree::Tree()
{
	father = NULL;
	//sons.push_back();
}
